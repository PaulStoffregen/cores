/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2017 PJRC.COM, LLC.
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

#ifdef HAS_KINETISK_UART5

////////////////////////////////////////////////////////////////
// Tunable parameters (relatively safe to edit these numbers)
////////////////////////////////////////////////////////////////

#ifndef SERIAL6_TX_BUFFER_SIZE
#define SERIAL6_TX_BUFFER_SIZE     40 // number of outgoing bytes to buffer
#endif
#ifndef SERIAL6_RX_BUFFER_SIZE
#define SERIAL6_RX_BUFFER_SIZE     64 // number of incoming bytes to buffer
#endif
#define RTS_HIGH_WATERMARK (SERIAL6_RX_BUFFER_SIZE-24) // RTS requests sender to pause
#define RTS_LOW_WATERMARK  (SERIAL6_RX_BUFFER_SIZE-38) // RTS allows sender to resume
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

static volatile BUFTYPE tx_buffer[SERIAL6_TX_BUFFER_SIZE];
static volatile BUFTYPE rx_buffer[SERIAL6_RX_BUFFER_SIZE];
static volatile uint8_t transmitting = 0;
static volatile uint8_t *transmit_pin=NULL;
#define transmit_assert()   *transmit_pin = 1
#define transmit_deassert() *transmit_pin = 0
static volatile uint8_t *rts_pin=NULL;
#define rts_assert()        *rts_pin = 0
#define rts_deassert()      *rts_pin = 1
#if SERIAL6_TX_BUFFER_SIZE > 65535
static volatile uint32_t tx_buffer_head = 0;
static volatile uint32_t tx_buffer_tail = 0;
#elif SERIAL6_TX_BUFFER_SIZE > 255
static volatile uint16_t tx_buffer_head = 0;
static volatile uint16_t tx_buffer_tail = 0;
#else
static volatile uint8_t tx_buffer_head = 0;
static volatile uint8_t tx_buffer_tail = 0;
#endif
#if SERIAL6_RX_BUFFER_SIZE > 65535
static volatile uint32_t rx_buffer_head = 0;
static volatile uint32_t rx_buffer_tail = 0;
#elif SERIAL6_RX_BUFFER_SIZE > 255
static volatile uint16_t rx_buffer_head = 0;
static volatile uint16_t rx_buffer_tail = 0;
#else
static volatile uint8_t rx_buffer_head = 0;
static volatile uint8_t rx_buffer_tail = 0;
#endif

static uint8_t tx_pin_num = 48;

// UART0 and UART1 are clocked by F_CPU, UART2 is clocked by F_BUS
// UART0 has 8 byte fifo, UART1 and UART2 have 1 byte buffer

#define C2_ENABLE		UART_C2_TE | UART_C2_RE | UART_C2_RIE
#define C2_TX_ACTIVE		C2_ENABLE | UART_C2_TIE
#define C2_TX_COMPLETING	C2_ENABLE | UART_C2_TCIE
#define C2_TX_INACTIVE		C2_ENABLE

void serial6_begin(uint32_t divisor)
{
	SIM_SCGC1 |= SIM_SCGC1_UART5;	// turn on clock, TODO: use bitband
	rx_buffer_head = 0;
	rx_buffer_tail = 0;
	tx_buffer_head = 0;
	tx_buffer_tail = 0;
	transmitting = 0;
	CORE_PIN47_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_PFE | PORT_PCR_MUX(3);
	CORE_PIN48_CONFIG = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(3);
	if (divisor < 32) divisor = 32;
	UART5_BDH = (divisor >> 13) & 0x1F;
	UART5_BDL = (divisor >> 5) & 0xFF;
	UART5_C4 = divisor & 0x1F;
	UART5_C1 = 0;
	UART5_PFIFO = 0;
	UART5_C2 = C2_TX_INACTIVE;
	NVIC_SET_PRIORITY(IRQ_UART5_STATUS, IRQ_PRIORITY);
	NVIC_ENABLE_IRQ(IRQ_UART5_STATUS);
}

void serial6_format(uint32_t format)
{
	uint8_t c;

	c = UART5_C1;
	c = (c & ~0x13) | (format & 0x03);	// configure parity
	if (format & 0x04) c |= 0x10;		// 9 bits (might include parity)
	UART5_C1 = c;
	if ((format & 0x0F) == 0x04) UART5_C3 |= 0x40; // 8N2 is 9 bit with 9th bit always 1
	c = UART5_S2 & ~0x10;
	if (format & 0x10) c |= 0x10;		// rx invert
	UART5_S2 = c;
	c = UART5_C3 & ~0x10;
	if (format & 0x20) c |= 0x10;		// tx invert
	UART5_C3 = c;
#ifdef SERIAL_9BIT_SUPPORT
	c = UART5_C4 & 0x1F;
	if (format & 0x08) c |= 0x20;		// 9 bit mode with parity (requires 10 bits)
	UART5_C4 = c;
	use9Bits = format & 0x80;
#endif
	// For T3.5 See about turning on 2 stop bit mode
	if ( format & 0x100) {
		uint8_t bdl = UART5_BDL;
		UART5_BDH |= UART_BDH_SBNS;		// Turn on 2 stop bits - was turned off by set baud
		UART5_BDL = bdl;		// Says BDH not acted on until BDL is written
	}
}

void serial6_end(void)
{
	if (!(SIM_SCGC1 & SIM_SCGC1_UART5)) return;
	while (transmitting) yield();  // wait for buffered data to send
	NVIC_DISABLE_IRQ(IRQ_UART5_STATUS);
	UART5_C2 = 0;
	CORE_PIN47_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_MUX(1);
	CORE_PIN48_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_MUX(1);
	UART5_S1;
	UART5_D; // clear leftover error status
	rx_buffer_head = 0;
	rx_buffer_tail = 0;
	if (rts_pin) rts_deassert();
}

void serial6_set_transmit_pin(uint8_t pin)
{
	while (transmitting) ;
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
	transmit_pin = portOutputRegister(pin);
}

void serial6_set_tx(uint8_t pin, uint8_t opendrain)
{
	uint32_t cfg;

	if (opendrain) pin |= 128;
	if (pin == tx_pin_num) return;
	if ((SIM_SCGC1 & SIM_SCGC1_UART5)) {
		switch (tx_pin_num & 127) {
			case 48:  CORE_PIN48_CONFIG = 0; break; // PTE24
		}
		if (opendrain) {
			cfg = PORT_PCR_DSE | PORT_PCR_ODE;
		} else {
			cfg = PORT_PCR_DSE | PORT_PCR_SRE;
		}
		switch (pin & 127) {
			case 48:  CORE_PIN48_CONFIG = cfg | PORT_PCR_MUX(3); break;
		}
	}
	tx_pin_num = pin;
}

void serial6_set_rx(uint8_t pin)
{
}

int serial6_set_rts(uint8_t pin)
{
	if (!(SIM_SCGC1 & SIM_SCGC1_UART5)) return 0;
	if (pin < CORE_NUM_DIGITAL) {
		rts_pin = portOutputRegister(pin);
		pinMode(pin, OUTPUT);
		rts_assert();
	} else {
		rts_pin = NULL;
		return 0;
	}
	return 1;
}

int serial6_set_cts(uint8_t pin)
{
	if (!(SIM_SCGC1 & SIM_SCGC1_UART5)) return 0;
	if (pin == 56) {
		CORE_PIN56_CONFIG = PORT_PCR_MUX(3) | PORT_PCR_PE; // weak pulldown
	} else {
		UART5_MODEM &= ~UART_MODEM_TXCTSE;
		return 0;
	}
	UART5_MODEM |= UART_MODEM_TXCTSE;
	return 1;
}

void serial6_putchar(uint32_t c)
{
	uint32_t head, n;

	if (!(SIM_SCGC1 & SIM_SCGC1_UART5)) return;
	if (transmit_pin) transmit_assert();
	head = tx_buffer_head;
	if (++head >= SERIAL6_TX_BUFFER_SIZE) head = 0;
	while (tx_buffer_tail == head) {
		int priority = nvic_execution_priority();
		if (priority <= IRQ_PRIORITY) {
			if ((UART5_S1 & UART_S1_TDRE)) {
				uint32_t tail = tx_buffer_tail;
				if (++tail >= SERIAL6_TX_BUFFER_SIZE) tail = 0;
				n = tx_buffer[tail];
				if (use9Bits) UART5_C3 = (UART5_C3 & ~0x40) | ((n & 0x100) >> 2);
				UART5_D = n;
				tx_buffer_tail = tail;
			}
		} else if (priority >= 256) {
			yield(); // wait
		}
	}
	tx_buffer[head] = c;
	transmitting = 1;
	tx_buffer_head = head;
	UART5_C2 = C2_TX_ACTIVE;
}

void serial6_write(const void *buf, unsigned int count)
{
	const uint8_t *p = (const uint8_t *)buf;
	while (count-- > 0) serial6_putchar(*p++);
}

void serial6_flush(void)
{
	while (transmitting) yield(); // wait
}

int serial6_write_buffer_free(void)
{
	uint32_t head, tail;

	head = tx_buffer_head;
	tail = tx_buffer_tail;
	if (head >= tail) return SERIAL6_TX_BUFFER_SIZE - 1 - head + tail;
	return tail - head - 1;
}

int serial6_available(void)
{
	uint32_t head, tail;

	head = rx_buffer_head;
	tail = rx_buffer_tail;
	if (head >= tail) return head - tail;
	return SERIAL6_RX_BUFFER_SIZE + head - tail;
}

int serial6_getchar(void)
{
	uint32_t head, tail;
	int c;

	head = rx_buffer_head;
	tail = rx_buffer_tail;
	if (head == tail) return -1;
	if (++tail >= SERIAL6_RX_BUFFER_SIZE) tail = 0;
	c = rx_buffer[tail];
	rx_buffer_tail = tail;
	if (rts_pin) {
		int avail;
		if (head >= tail) avail = head - tail;
		else avail = SERIAL6_RX_BUFFER_SIZE + head - tail;
		if (avail <= RTS_LOW_WATERMARK) rts_assert();
	}
	return c;
}

int serial6_peek(void)
{
	uint32_t head, tail;

	head = rx_buffer_head;
	tail = rx_buffer_tail;
	if (head == tail) return -1;
	if (++tail >= SERIAL6_RX_BUFFER_SIZE) tail = 0;
	return rx_buffer[tail];
}

void serial6_clear(void)
{
	rx_buffer_head = rx_buffer_tail;
	if (rts_pin) rts_assert();
}

// status interrupt combines
//   Transmit data below watermark  UART_S1_TDRE
//   Transmit complete		    UART_S1_TC
//   Idle line			    UART_S1_IDLE
//   Receive data above watermark   UART_S1_RDRF
//   LIN break detect		    UART_S2_LBKDIF
//   RxD pin active edge	    UART_S2_RXEDGIF

void uart5_status_isr(void)
{
	uint32_t head, tail, n;
	uint8_t c;

	if (UART5_S1 & UART_S1_RDRF) {
		if (use9Bits && (UART5_C3 & 0x80)) {
			n = UART5_D | 0x100;
		} else {
			n = UART5_D;
		}
		head = rx_buffer_head + 1;
		if (head >= SERIAL6_RX_BUFFER_SIZE) head = 0;
		if (head != rx_buffer_tail) {
			rx_buffer[head] = n;
			rx_buffer_head = head;
		}
		if (rts_pin) {
			int avail;
			tail = tx_buffer_tail;
			if (head >= tail) avail = head - tail;
			else avail = SERIAL6_RX_BUFFER_SIZE + head - tail;
			if (avail >= RTS_HIGH_WATERMARK) rts_deassert();
		}
	}
	c = UART5_C2;
	if ((c & UART_C2_TIE) && (UART5_S1 & UART_S1_TDRE)) {
		head = tx_buffer_head;
		tail = tx_buffer_tail;
		if (head == tail) {
			UART5_C2 = C2_TX_COMPLETING;
		} else {
			if (++tail >= SERIAL6_TX_BUFFER_SIZE) tail = 0;
			n = tx_buffer[tail];
			if (use9Bits) UART5_C3 = (UART5_C3 & ~0x40) | ((n & 0x100) >> 2);
			UART5_D = n;
			tx_buffer_tail = tail;
		}
	}
	if ((c & UART_C2_TCIE) && (UART5_S1 & UART_S1_TC)) {
		transmitting = 0;
		if (transmit_pin) transmit_deassert();
		UART5_C2 = C2_TX_INACTIVE;
	}
}

#endif // HAS_KINETISK_UART5
