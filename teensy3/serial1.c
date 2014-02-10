/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2013 PJRC.COM, LLC.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * 1. The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 *
 * 2. If the Software is incorporated into a build system that allows 
 * selection among a list of target devices, then similar target
 * devices manufactured by PJRC.COM must be included in the list of
 * target devices and selectable in the same manner.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "mk20dx128.h"
#include "core_pins.h"
#include "HardwareSerial.h"

////////////////////////////////////////////////////////////////
// Tunable parameters (relatively safe to edit these numbers)
////////////////////////////////////////////////////////////////

#define TX_BUFFER_SIZE 64 // number of outgoing bytes to buffer
#define RX_BUFFER_SIZE 64 // number of incoming bytes to buffer
#define IRQ_PRIORITY  64  // 0 = highest priority, 255 = lowest


////////////////////////////////////////////////////////////////
// changes not recommended below this point....
////////////////////////////////////////////////////////////////

#ifdef SERIAL_9BIT_SUPPORT
static uint8_t use9Bits = 0;
#define BUFTYPE uint16_t
#else
#define BUFTYPE uint8_t
#define use9Bits 0
#endif

static volatile BUFTYPE tx_buffer[TX_BUFFER_SIZE];
static volatile BUFTYPE rx_buffer[RX_BUFFER_SIZE];
static volatile uint8_t transmitting = 0;
static volatile uint8_t *transmit_pin=NULL;
#if TX_BUFFER_SIZE > 255
static volatile uint16_t tx_buffer_head = 0;
static volatile uint16_t tx_buffer_tail = 0;
#else
static volatile uint8_t tx_buffer_head = 0;
static volatile uint8_t tx_buffer_tail = 0;
#endif
#if RX_BUFFER_SIZE > 255
static volatile uint16_t rx_buffer_head = 0;
static volatile uint16_t rx_buffer_tail = 0;
#else
static volatile uint8_t rx_buffer_head = 0;
static volatile uint8_t rx_buffer_tail = 0;
#endif

// UART0 and UART1 are clocked by F_CPU, UART2 is clocked by F_BUS
// UART0 has 8 byte fifo, UART1 and UART2 have 1 byte buffer

#define C2_ENABLE		UART_C2_TE | UART_C2_RE | UART_C2_RIE | UART_C2_ILIE
#define C2_TX_ACTIVE		C2_ENABLE | UART_C2_TIE
#define C2_TX_COMPLETING	C2_ENABLE | UART_C2_TCIE
#define C2_TX_INACTIVE		C2_ENABLE

void serial_begin(uint32_t divisor)
{
	SIM_SCGC4 |= SIM_SCGC4_UART0;	// turn on clock, TODO: use bitband
	rx_buffer_head = 0;
	rx_buffer_tail = 0;
	tx_buffer_head = 0;
	tx_buffer_tail = 0;
	transmitting = 0;
	CORE_PIN0_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_PFE | PORT_PCR_MUX(3);
	CORE_PIN1_CONFIG = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(3);
	UART0_BDH = (divisor >> 13) & 0x1F;
	UART0_BDL = (divisor >> 5) & 0xFF;
	UART0_C4 = divisor & 0x1F;
	//UART0_C1 = 0;
	UART0_C1 = UART_C1_ILT;
	UART0_TWFIFO = 2; // tx watermark, causes S1_TDRE to set
	UART0_RWFIFO = 4; // rx watermark, causes S1_RDRF to set
	UART0_PFIFO = UART_PFIFO_TXFE | UART_PFIFO_RXFE;
	UART0_C2 = C2_TX_INACTIVE;
	NVIC_SET_PRIORITY(IRQ_UART0_STATUS, IRQ_PRIORITY);
	NVIC_ENABLE_IRQ(IRQ_UART0_STATUS);
}

void serial_format(uint32_t format)
{
        uint8_t c;

        c = UART0_C1;
        c = (c & ~0x13) | (format & 0x03);      // configure parity
        if (format & 0x04) c |= 0x10;           // 9 bits (might include parity)
        UART0_C1 = c;
        if ((format & 0x0F) == 0x04) UART0_C3 |= 0x40; // 8N2 is 9 bit with 9th bit always 1
        c = UART0_S2 & ~0x10;
        if (format & 0x10) c |= 0x10;           // rx invert
        UART0_S2 = c;
        c = UART0_C3 & ~0x10;
        if (format & 0x20) c |= 0x10;           // tx invert
        UART0_C3 = c;
#ifdef SERIAL_9BIT_SUPPORT
        c = UART0_C4 & 0x1F;
        if (format & 0x08) c |= 0x20;           // 9 bit mode with parity (requires 10 bits)
        UART0_C4 = c;
        use9Bits = format & 0x80;
#endif
}

void serial_end(void)
{
	if (!(SIM_SCGC4 & SIM_SCGC4_UART0)) return;
	while (transmitting) yield();  // wait for buffered data to send
	NVIC_DISABLE_IRQ(IRQ_UART0_STATUS);
	UART0_C2 = 0;
	CORE_PIN0_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_MUX(1);
	CORE_PIN1_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_MUX(1);
	rx_buffer_head = 0;
	rx_buffer_tail = 0;
}

void serial_set_transmit_pin(uint8_t pin)
{
	while (transmitting) ;
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
	transmit_pin = portOutputRegister(pin);
}

void serial_putchar(uint32_t c)
{
	uint32_t head, n;

	if (!(SIM_SCGC4 & SIM_SCGC4_UART0)) return;
	if (transmit_pin) *transmit_pin = 1;
	head = tx_buffer_head;
	if (++head >= TX_BUFFER_SIZE) head = 0;
	while (tx_buffer_tail == head) {
		int priority = nvic_execution_priority();
		if (priority <= IRQ_PRIORITY) {
			if ((UART0_S1 & UART_S1_TDRE)) {
				uint32_t tail = tx_buffer_tail;
				if (++tail >= TX_BUFFER_SIZE) tail = 0;
				n = tx_buffer[tail];
				if (use9Bits) UART0_C3 = (UART0_C3 & ~0x40) | ((n & 0x100) >> 2);
				UART0_D = n;
				tx_buffer_tail = tail;
			}
		} else if (priority >= 256) {
			yield();
		}
	}
	tx_buffer[head] = c;
	transmitting = 1;
	tx_buffer_head = head;
	UART0_C2 = C2_TX_ACTIVE;
}

void serial_write(const void *buf, unsigned int count)
{
	const uint8_t *p = (const uint8_t *)buf;
	const uint8_t *end = p + count;
        uint32_t head, n;

        if (!(SIM_SCGC4 & SIM_SCGC4_UART0)) return;
	if (transmit_pin) *transmit_pin = 1;
	while (p < end) {
        	head = tx_buffer_head;
        	if (++head >= TX_BUFFER_SIZE) head = 0;
		if (tx_buffer_tail == head) {
        		UART0_C2 = C2_TX_ACTIVE;
			do {
				int priority = nvic_execution_priority();
				if (priority <= IRQ_PRIORITY) {
					if ((UART0_S1 & UART_S1_TDRE)) {
						uint32_t tail = tx_buffer_tail;
						if (++tail >= TX_BUFFER_SIZE) tail = 0;
						n = tx_buffer[tail];
						if (use9Bits) UART0_C3 = (UART0_C3 & ~0x40) | ((n & 0x100) >> 2);
						UART0_D = n;
						tx_buffer_tail = tail;
					}
				} else if (priority >= 256) {
					yield();
				}
			} while (tx_buffer_tail == head);
		}
        	tx_buffer[head] = *p++;
        	transmitting = 1;
        	tx_buffer_head = head;
	}
        UART0_C2 = C2_TX_ACTIVE;
}

void serial_flush(void)
{
	while (transmitting) yield(); // wait
}

int serial_available(void)
{
	uint32_t head, tail;

	head = rx_buffer_head;
	tail = rx_buffer_tail;
	if (head >= tail) return head - tail;
	return RX_BUFFER_SIZE + head - tail;
}

int serial_getchar(void)
{
	uint32_t head, tail;
	int c;

	head = rx_buffer_head;
	tail = rx_buffer_tail;
	if (head == tail) return -1;
	if (++tail >= RX_BUFFER_SIZE) tail = 0;
	c = rx_buffer[tail];
	rx_buffer_tail = tail;
	return c;
}

int serial_peek(void)
{
	uint32_t head, tail;

	head = rx_buffer_head;
	tail = rx_buffer_tail;
	if (head == tail) return -1;
	if (++tail >= RX_BUFFER_SIZE) tail = 0;
	return rx_buffer[tail];
}

void serial_clear(void)
{
	if (!(SIM_SCGC4 & SIM_SCGC4_UART0)) return;
	UART0_C2 &= ~(UART_C2_RE | UART_C2_RIE | UART_C2_ILIE);
	UART0_CFIFO = UART_CFIFO_RXFLUSH;
	UART0_C2 |= (UART_C2_RE | UART_C2_RIE | UART_C2_ILIE);
	rx_buffer_head = rx_buffer_tail;
}

// status interrupt combines 
//   Transmit data below watermark  UART_S1_TDRE
//   Transmit complete              UART_S1_TC
//   Idle line                      UART_S1_IDLE
//   Receive data above watermark   UART_S1_RDRF
//   LIN break detect               UART_S2_LBKDIF
//   RxD pin active edge            UART_S2_RXEDGIF

void uart0_status_isr(void)
{
	uint32_t head, newhead, tail, n;
	uint8_t avail, c;

	if (UART0_S1 & (UART_S1_RDRF | UART_S1_IDLE)) {
		__disable_irq();
		avail = UART0_RCFIFO;
		if (avail == 0) {
			// The only way to clear the IDLE interrupt flag is
			// to read the data register.  But reading with no
			// data causes a FIFO underrun, which causes the
			// FIFO to return corrupted data.  If anyone from
			// Freescale reads this, what a poor design!  There
			// write should be a write-1-to-clear for IDLE.
			c = UART0_D;
			// flushing the fifo recovers from the underrun,
			// but there's a possible race condition where a
			// new character could be received between reading
			// RCFIFO == 0 and flushing the FIFO.  To minimize
			// the chance, interrupts are disabled so a higher
			// priority interrupt (hopefully) doesn't delay.
			// TODO: change this to disabling the IDLE interrupt
			// which won't be simple, since we already manage
			// which transmit interrupts are enabled.
			UART0_CFIFO = UART_CFIFO_RXFLUSH;
			__enable_irq();
		} else {
			__enable_irq();
			head = rx_buffer_head;
			tail = rx_buffer_tail;
			do {
				n = UART0_D;
				if (use9Bits && (UART0_C3 & 0x80)) n |= 0x100;
				newhead = head + 1;
				if (newhead >= RX_BUFFER_SIZE) newhead = 0;
				if (newhead != tail) {
					head = newhead;
					rx_buffer[head] = n;
				}
			} while (--avail > 0);
			rx_buffer_head = head;
		}
	}
	c = UART0_C2;
	if ((c & UART_C2_TIE) && (UART0_S1 & UART_S1_TDRE)) {
		head = tx_buffer_head;
		tail = tx_buffer_tail;
		do {
			if (tail == head) break;
			if (++tail >= TX_BUFFER_SIZE) tail = 0;
			avail = UART0_S1;
			n = tx_buffer[tail];
			if (use9Bits) UART0_C3 = (UART0_C3 & ~0x40) | ((n & 0x100) >> 2);
			UART0_D = n;
		} while (UART0_TCFIFO < 8);
		tx_buffer_tail = tail;
		if (UART0_S1 & UART_S1_TDRE) UART0_C2 = C2_TX_COMPLETING;
	}
	if ((c & UART_C2_TCIE) && (UART0_S1 & UART_S1_TC)) {
		transmitting = 0;
		if (transmit_pin) *transmit_pin = 0;
		UART0_C2 = C2_TX_INACTIVE;
	}
}



void serial_print(const char *p)
{
	while (*p) {
		char c = *p++;
		if (c == '\n') serial_putchar('\r');
		serial_putchar(c);
	}
}

static void serial_phex1(uint32_t n)
{
	n &= 15;
	if (n < 10) {
		serial_putchar('0' + n);
	} else {
		serial_putchar('A' - 10 + n);
	}
}

void serial_phex(uint32_t n)
{
	serial_phex1(n >> 4);
	serial_phex1(n);
}

void serial_phex16(uint32_t n)
{
	serial_phex(n >> 8);
	serial_phex(n);
}

void serial_phex32(uint32_t n)
{
	serial_phex(n >> 24);
	serial_phex(n >> 16);
	serial_phex(n >> 8);
	serial_phex(n);
}

