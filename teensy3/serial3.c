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

#include "kinetis.h"
#include "core_pins.h"
#include "HardwareSerial.h"

////////////////////////////////////////////////////////////////
// Tunable parameters (relatively safe to edit these numbers)
////////////////////////////////////////////////////////////////

#define TX_BUFFER_SIZE 40
#define RX_BUFFER_SIZE 64
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

#define C2_ENABLE		UART_C2_TE | UART_C2_RE | UART_C2_RIE
#define C2_TX_ACTIVE		C2_ENABLE | UART_C2_TIE
#define C2_TX_COMPLETING	C2_ENABLE | UART_C2_TCIE
#define C2_TX_INACTIVE		C2_ENABLE

void serial3_begin(uint32_t divisor)
{
	SIM_SCGC4 |= SIM_SCGC4_UART2;	// turn on clock, TODO: use bitband
	rx_buffer_head = 0;
	rx_buffer_tail = 0;
	tx_buffer_head = 0;
	tx_buffer_tail = 0;
	transmitting = 0;
	CORE_PIN7_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_PFE | PORT_PCR_MUX(3);
	CORE_PIN8_CONFIG = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(3);
	UART2_BDH = (divisor >> 13) & 0x1F;
	UART2_BDL = (divisor >> 5) & 0xFF;
	UART2_C4 = divisor & 0x1F;
	UART2_C1 = 0;
	UART2_PFIFO = 0;
	UART2_C2 = C2_TX_INACTIVE;
	NVIC_SET_PRIORITY(IRQ_UART2_STATUS, IRQ_PRIORITY);
	NVIC_ENABLE_IRQ(IRQ_UART2_STATUS);
}

void serial3_format(uint32_t format)
{
        uint8_t c;

        c = UART2_C1;
        c = (c & ~0x13) | (format & 0x03);      // configure parity
        if (format & 0x04) c |= 0x10;           // 9 bits (might include parity)
        UART2_C1 = c;
        if ((format & 0x0F) == 0x04) UART2_C3 |= 0x40; // 8N2 is 9 bit with 9th bit always 1
        c = UART2_S2 & ~0x10;
        if (format & 0x10) c |= 0x10;           // rx invert
        UART2_S2 = c;
        c = UART2_C3 & ~0x10;
        if (format & 0x20) c |= 0x10;           // tx invert
        UART2_C3 = c;
#ifdef SERIAL_9BIT_SUPPORT
        c = UART2_C4 & 0x1F;
        if (format & 0x08) c |= 0x20;           // 9 bit mode with parity (requires 10 bits)
        UART2_C4 = c;
        use9Bits = format & 0x80;
#endif
}

void serial3_end(void)
{
	if (!(SIM_SCGC4 & SIM_SCGC4_UART2)) return;
	while (transmitting) yield();  // wait for buffered data to send
	NVIC_DISABLE_IRQ(IRQ_UART2_STATUS);
	UART2_C2 = 0;
	CORE_PIN7_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_MUX(1);
	CORE_PIN8_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_MUX(1);
	rx_buffer_head = 0;
	rx_buffer_tail = 0;
}

void serial3_putchar(uint32_t c)
{
	uint32_t head;

	if (!(SIM_SCGC4 & SIM_SCGC4_UART2)) return;
	head = tx_buffer_head;
	if (++head >= TX_BUFFER_SIZE) head = 0;
	while (tx_buffer_tail == head) {
		int priority = nvic_execution_priority();
		if (priority <= IRQ_PRIORITY) {
			if ((UART2_S1 & UART_S1_TDRE)) {
				uint32_t tail = tx_buffer_tail;
				if (++tail >= TX_BUFFER_SIZE) tail = 0;
				UART2_D = tx_buffer[tail];
				tx_buffer_tail = tail;
			}
		} else if (priority >= 256) {
			yield(); // wait
		}
	}
	tx_buffer[head] = c;
	transmitting = 1;
	tx_buffer_head = head;
	UART2_C2 = C2_TX_ACTIVE;
}

void serial3_write(const void *buf, unsigned int count)
{
	const uint8_t *p = (const uint8_t *)buf;
	while (count-- > 0) serial3_putchar(*p++);
}

void serial3_flush(void)
{
	while (transmitting) yield(); // wait
}

int serial3_write_buffer_free(void)
{
	uint32_t head, tail;

	head = tx_buffer_head;
	tail = tx_buffer_tail;
	if (head >= tail) return TX_BUFFER_SIZE - 1 - head + tail;
	return tail - head - 1;
}

int serial3_available(void)
{
	uint32_t head, tail;

	head = rx_buffer_head;
	tail = rx_buffer_tail;
	if (head >= tail) return head - tail;
	return RX_BUFFER_SIZE + head - tail;
}

int serial3_getchar(void)
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

int serial3_peek(void)
{
	uint32_t head, tail;

	head = rx_buffer_head;
	tail = rx_buffer_tail;
	if (head == tail) return -1;
	if (++tail >= RX_BUFFER_SIZE) tail = 0;
	return rx_buffer[tail];
}

void serial3_clear(void)
{
	rx_buffer_head = rx_buffer_tail;
}

// status interrupt combines 
//   Transmit data below watermark  UART_S1_TDRE
//   Transmit complete              UART_S1_TC
//   Idle line                      UART_S1_IDLE
//   Receive data above watermark   UART_S1_RDRF
//   LIN break detect               UART_S2_LBKDIF
//   RxD pin active edge            UART_S2_RXEDGIF

void uart2_status_isr(void)
{
	uint32_t head, tail, n;
	uint8_t c;

	//digitalWriteFast(4, HIGH);
	if (UART2_S1 & UART_S1_RDRF) {
		//digitalWriteFast(5, HIGH);
		n = UART2_D;
		if (use9Bits && (UART2_C3 & 0x80)) n |= 0x100;
		head = rx_buffer_head + 1;
		if (head >= RX_BUFFER_SIZE) head = 0;
		if (head != rx_buffer_tail) {
			rx_buffer[head] = n;
			rx_buffer_head = head; 
		}
		//digitalWriteFast(5, LOW);
	}
	c = UART2_C2;
	if ((c & UART_C2_TIE) && (UART2_S1 & UART_S1_TDRE)) {
		//digitalWriteFast(5, HIGH);
		head = tx_buffer_head;
		tail = tx_buffer_tail;
		if (head == tail) {
			UART2_C2 = C2_TX_COMPLETING;
		} else {
			if (++tail >= TX_BUFFER_SIZE) tail = 0;
			n = tx_buffer[tail];
			if (use9Bits) UART2_C3 = (UART2_C3 & ~0x40) | ((n & 0x100) >> 2);
			UART2_D = n;
			tx_buffer_tail = tail;
		}
		//digitalWriteFast(5, LOW);
	}
	if ((c & UART_C2_TCIE) && (UART2_S1 & UART_S1_TC)) {
		transmitting = 0;
		UART2_C2 = C2_TX_INACTIVE;
	}
	//digitalWriteFast(4, LOW);
}


