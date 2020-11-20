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
#include <stddef.h>

#ifdef HAS_KINETISK_UART3

////////////////////////////////////////////////////////////////
// Tunable parameters (relatively safe to edit these numbers)
////////////////////////////////////////////////////////////////

#ifndef SERIAL4_TX_BUFFER_SIZE
#define SERIAL4_TX_BUFFER_SIZE     40 // number of outgoing bytes to buffer
#endif
#ifndef SERIAL4_RX_BUFFER_SIZE
#define SERIAL4_RX_BUFFER_SIZE     64 // number of incoming bytes to buffer
#endif
#define RTS_HIGH_WATERMARK (SERIAL4_RX_BUFFER_SIZE-24) // RTS requests sender to pause
#define RTS_LOW_WATERMARK  (SERIAL4_RX_BUFFER_SIZE-38) // RTS allows sender to resume
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

static volatile BUFTYPE tx_buffer[SERIAL4_TX_BUFFER_SIZE];
static volatile BUFTYPE rx_buffer[SERIAL4_RX_BUFFER_SIZE];
static volatile BUFTYPE	*rx_buffer_storage_ = NULL;
static volatile BUFTYPE	*tx_buffer_storage_ = NULL;

static size_t tx_buffer_total_size_ = SERIAL4_TX_BUFFER_SIZE;
static size_t rx_buffer_total_size_ = SERIAL4_RX_BUFFER_SIZE;
static size_t rts_low_watermark_ = RTS_LOW_WATERMARK;
static size_t rts_high_watermark_ = RTS_HIGH_WATERMARK;
static volatile uint8_t transmitting = 0;
static volatile uint8_t *transmit_pin=NULL;
#define transmit_assert()   *transmit_pin = 1
#define transmit_deassert() *transmit_pin = 0
static volatile uint8_t *rts_pin=NULL;
#define rts_assert()        *rts_pin = 0
#define rts_deassert()      *rts_pin = 1
#if SERIAL4_TX_BUFFER_SIZE > 65535
static volatile uint32_t tx_buffer_head = 0;
static volatile uint32_t tx_buffer_tail = 0;
#elif SERIAL4_TX_BUFFER_SIZE > 255
static volatile uint16_t tx_buffer_head = 0;
static volatile uint16_t tx_buffer_tail = 0;
#else
static volatile uint8_t tx_buffer_head = 0;
static volatile uint8_t tx_buffer_tail = 0;
#endif
#if SERIAL4_RX_BUFFER_SIZE > 65535
static volatile uint32_t rx_buffer_head = 0;
static volatile uint32_t rx_buffer_tail = 0;
#elif SERIAL4_RX_BUFFER_SIZE > 255
static volatile uint16_t rx_buffer_head = 0;
static volatile uint16_t rx_buffer_tail = 0;
#else
static volatile uint8_t rx_buffer_head = 0;
static volatile uint8_t rx_buffer_tail = 0;
#endif

static uint8_t rx_pin_num = 31;
static uint8_t tx_pin_num = 32;

// UART0 and UART1 are clocked by F_CPU, UART2 is clocked by F_BUS
// UART0 has 8 byte fifo, UART1 and UART2 have 1 byte buffer

#define C2_ENABLE		UART_C2_TE | UART_C2_RE | UART_C2_RIE
#define C2_TX_ACTIVE		C2_ENABLE | UART_C2_TIE
#define C2_TX_COMPLETING	C2_ENABLE | UART_C2_TCIE
#define C2_TX_INACTIVE		C2_ENABLE

// BITBAND Support
#define GPIO_BITBAND_ADDR(reg, bit) (((uint32_t)&(reg) - 0x40000000) * 32 + (bit) * 4 + 0x42000000)
#define GPIO_BITBAND_PTR(reg, bit) ((uint32_t *)GPIO_BITBAND_ADDR((reg), (bit)))
#define C3_TXDIR_BIT 5

void serial4_begin(uint32_t divisor)
{
	SIM_SCGC4 |= SIM_SCGC4_UART3;	// turn on clock, TODO: use bitband
	rx_buffer_head = 0;
	rx_buffer_tail = 0;
	tx_buffer_head = 0;
	tx_buffer_tail = 0;
	transmitting = 0;
	switch (rx_pin_num) {
		case 31: CORE_PIN31_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_PFE | PORT_PCR_MUX(3); break;
		case 63: CORE_PIN63_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_PFE | PORT_PCR_MUX(3); break;
	}
	switch (tx_pin_num) {
		case 32: CORE_PIN32_CONFIG = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(3); break;
		case 62: CORE_PIN62_CONFIG = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(3); break;
	}
	if (divisor < 32) divisor = 32;
	UART3_BDH = (divisor >> 13) & 0x1F;
	UART3_BDL = (divisor >> 5) & 0xFF;
	UART3_C4 = divisor & 0x1F;
	UART3_C1 = 0;
	UART3_PFIFO = 0;
	UART3_C2 = C2_TX_INACTIVE;
	NVIC_SET_PRIORITY(IRQ_UART3_STATUS, IRQ_PRIORITY);
	NVIC_ENABLE_IRQ(IRQ_UART3_STATUS);
}

void serial4_format(uint32_t format)
{
	uint8_t c;

	c = UART3_C1;
	c = (c & ~0x13) | (format & 0x03);	// configure parity
	if (format & 0x04) c |= 0x10;		// 9 bits (might include parity)
	UART3_C1 = c;
	if ((format & 0x0F) == 0x04) UART3_C3 |= 0x40; // 8N2 is 9 bit with 9th bit always 1
	c = UART3_S2 & ~0x10;
	if (format & 0x10) c |= 0x10;		// rx invert
	UART3_S2 = c;
	c = UART3_C3 & ~0x10;
	if (format & 0x20) c |= 0x10;		// tx invert
	UART3_C3 = c;
#ifdef SERIAL_9BIT_SUPPORT
	c = UART3_C4 & 0x1F;
	if (format & 0x08) c |= 0x20;		// 9 bit mode with parity (requires 10 bits)
	UART3_C4 = c;
	use9Bits = format & 0x80;
#endif
#if defined(__MK64FX512__) || defined(__MK66FX1M0__) || defined(KINETISL)
	// For T3.5/T3.6/TLC See about turning on 2 stop bit mode
	if ( format & 0x100) {
		uint8_t bdl = UART3_BDL;
		UART3_BDH |= UART_BDH_SBNS;		// Turn on 2 stop bits - was turned off by set baud
		UART3_BDL = bdl;		// Says BDH not acted on until BDL is written
	}
#endif
	// process request for half duplex.
	if ((format & SERIAL_HALF_DUPLEX) != 0) {
		UART3_C1 |= UART_C1_LOOPS | UART_C1_RSRC;
		volatile uint32_t *reg = portConfigRegister(tx_pin_num);
		*reg = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(3) | PORT_PCR_PE | PORT_PCR_PS; // pullup on output pin;

		// Lets try to make use of bitband address to set the direction for ue...
		#if defined(KINETISL)
		transmit_pin = &UART3_C3;
		transmit_mask = UART_C3_TXDIR;
		#else
		transmit_pin = (uint8_t*)GPIO_BITBAND_PTR(UART3_C3, C3_TXDIR_BIT);
		#endif

	} else {
		#if defined(KINETISL)
		if (transmit_pin == &UART3_C3) transmit_pin = NULL;
		#else
		if (transmit_pin == (uint8_t*)GPIO_BITBAND_PTR(UART3_C3, C3_TXDIR_BIT)) transmit_pin = NULL;
		#endif
	}
}

void serial4_end(void)
{
	if (!(SIM_SCGC4 & SIM_SCGC4_UART3)) return;
	while (transmitting) yield();  // wait for buffered data to send
	NVIC_DISABLE_IRQ(IRQ_UART3_STATUS);
	UART3_C2 = 0;
	switch (rx_pin_num) {
		case 31: CORE_PIN31_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_MUX(1); break; // PTC3
		case 63: CORE_PIN63_CONFIG = 0; break;
	}
	switch (tx_pin_num & 127) {
		case 32: CORE_PIN32_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_MUX(1); break; // PTC4
		case 62: CORE_PIN62_CONFIG = 0; break;
	}
	UART3_S1;
	UART3_D; // clear leftover error status
	rx_buffer_head = 0;
	rx_buffer_tail = 0;
	if (rts_pin) rts_deassert();
}

void serial4_set_transmit_pin(uint8_t pin)
{
	while (transmitting) ;
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
	transmit_pin = portOutputRegister(pin);
}

void serial4_set_tx(uint8_t pin, uint8_t opendrain)
{
	uint32_t cfg;

	if (opendrain) pin |= 128;
	if (pin == tx_pin_num) return;
	if ((SIM_SCGC4 & SIM_SCGC4_UART3)) {
		switch (tx_pin_num & 127) {
			case 32:  CORE_PIN32_CONFIG = 0; break; // PTB11
			case 62: CORE_PIN62_CONFIG = 0; break;
		}
		if (opendrain) {
			cfg = PORT_PCR_DSE | PORT_PCR_ODE;
		} else {
			cfg = PORT_PCR_DSE | PORT_PCR_SRE;
		}
		switch (pin & 127) {
			case 32: CORE_PIN32_CONFIG = cfg | PORT_PCR_MUX(3); break;
			case 62: CORE_PIN62_CONFIG = cfg | PORT_PCR_MUX(3); break;
		}
	}
	tx_pin_num = pin;

}

void serial4_set_rx(uint8_t pin)
{
	if (pin == rx_pin_num) return;
	if ((SIM_SCGC4 & SIM_SCGC4_UART3)) {
		switch (rx_pin_num) {
			case 31: CORE_PIN31_CONFIG = 0; break; // PTC3
			case 63: CORE_PIN63_CONFIG = 0; break;
		}
		switch (pin) {
			case 31: CORE_PIN31_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_PFE | PORT_PCR_MUX(3); break;
			case 63: CORE_PIN63_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_PFE | PORT_PCR_MUX(3); break;
		}
	}
	rx_pin_num = pin;
}

int serial4_set_rts(uint8_t pin)
{
	if (!(SIM_SCGC4 & SIM_SCGC4_UART3)) return 0;
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

int serial4_set_cts(uint8_t pin)
{
	return 0;
}

void serial4_putchar(uint32_t c)
{
	uint32_t head, n;

	if (!(SIM_SCGC4 & SIM_SCGC4_UART3)) return;
	if (transmit_pin) transmit_assert();
	head = tx_buffer_head;
	if (++head >= tx_buffer_total_size_) head = 0;
	while (tx_buffer_tail == head) {
		int priority = nvic_execution_priority();
		if (priority <= IRQ_PRIORITY) {
			if ((UART3_S1 & UART_S1_TDRE)) {
				uint32_t tail = tx_buffer_tail;
				if (++tail >= tx_buffer_total_size_) tail = 0;
				if (tail < SERIAL4_TX_BUFFER_SIZE) {
					n = tx_buffer[tail];
				} else {
					n = tx_buffer_storage_[tail-SERIAL4_TX_BUFFER_SIZE];
				}
				if (use9Bits) UART3_C3 = (UART3_C3 & ~0x40) | ((n & 0x100) >> 2);
				UART3_D = n;
				tx_buffer_tail = tail;
			}
		} else if (priority >= 256) {
			yield(); // wait
		}
	}
	if (head < SERIAL4_TX_BUFFER_SIZE) {
		tx_buffer[head] = c;
	} else {
		tx_buffer_storage_[head - SERIAL4_TX_BUFFER_SIZE] = c;
	}
	transmitting = 1;
	tx_buffer_head = head;
	UART3_C2 = C2_TX_ACTIVE;
}

void serial4_write(const void *buf, unsigned int count)
{
	const uint8_t *p = (const uint8_t *)buf;
	while (count-- > 0) serial4_putchar(*p++);
}

void serial4_flush(void)
{
	while (transmitting) yield(); // wait
}

int serial4_write_buffer_free(void)
{
	uint32_t head, tail;

	head = tx_buffer_head;
	tail = tx_buffer_tail;
	if (head >= tail) return tx_buffer_total_size_ - 1 - head + tail;
	return tail - head - 1;
}

int serial4_available(void)
{
	uint32_t head, tail;

	head = rx_buffer_head;
	tail = rx_buffer_tail;
	if (head >= tail) return head - tail;
	return rx_buffer_total_size_ + head - tail;
}

int serial4_getchar(void)
{
	uint32_t head, tail;
	int c;

	head = rx_buffer_head;
	tail = rx_buffer_tail;
	if (head == tail) return -1;
	if (++tail >= rx_buffer_total_size_) tail = 0;
	if (tail < SERIAL4_RX_BUFFER_SIZE) {
		c = rx_buffer[tail];
	} else {
		c = rx_buffer_storage_[tail-SERIAL4_RX_BUFFER_SIZE];
	}
	rx_buffer_tail = tail;
	if (rts_pin) {
		int avail;
		if (head >= tail) avail = head - tail;
		else avail = rx_buffer_total_size_ + head - tail;
		if (avail <= rts_low_watermark_) rts_assert();
	}
	return c;
}

int serial4_peek(void)
{
	uint32_t head, tail;

	head = rx_buffer_head;
	tail = rx_buffer_tail;
	if (head == tail) return -1;
	if (++tail >= rx_buffer_total_size_) tail = 0;
	if (tail < SERIAL4_RX_BUFFER_SIZE) {
		return rx_buffer[tail];
	}
	return rx_buffer_storage_[tail-SERIAL4_RX_BUFFER_SIZE];
}

void serial4_clear(void)
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

void uart3_status_isr(void)
{
	uint32_t head, tail, n;
	uint8_t c;

	if (UART3_S1 & UART_S1_RDRF) {
		if (use9Bits && (UART3_C3 & 0x80)) {
			n = UART3_D | 0x100;
		} else {
			n = UART3_D;
		}
		head = rx_buffer_head + 1;
		if (head >= rx_buffer_total_size_) head = 0;
		if (head != rx_buffer_tail) {
			if (head < SERIAL4_RX_BUFFER_SIZE) {
				rx_buffer[head] = n;
			} else {
				rx_buffer_storage_[head-SERIAL4_RX_BUFFER_SIZE] = n;
			}

			rx_buffer_head = head;
		}
		if (rts_pin) {
			int avail;
			tail = tx_buffer_tail;
			if (head >= tail) avail = head - tail;
			else avail = rx_buffer_total_size_ + head - tail;
			if (avail >= rts_high_watermark_) rts_deassert();
		}
	}
	c = UART3_C2;
	if ((c & UART_C2_TIE) && (UART3_S1 & UART_S1_TDRE)) {
		head = tx_buffer_head;
		tail = tx_buffer_tail;
		if (head == tail) {
			UART3_C2 = C2_TX_COMPLETING;
		} else {
			if (++tail >= tx_buffer_total_size_) tail = 0;
			if (tail < SERIAL4_TX_BUFFER_SIZE) {
				n = tx_buffer[tail];
			} else {
				n = tx_buffer_storage_[tail-SERIAL4_TX_BUFFER_SIZE];
			}
			if (use9Bits) UART3_C3 = (UART3_C3 & ~0x40) | ((n & 0x100) >> 2);
			UART3_D = n;
			tx_buffer_tail = tail;
		}
	}
	if ((c & UART_C2_TCIE) && (UART3_S1 & UART_S1_TC)) {
		transmitting = 0;
		if (transmit_pin) transmit_deassert();
		UART3_C2 = C2_TX_INACTIVE;
	}
}

void serial4_add_memory_for_read(void *buffer, size_t length)
{
	rx_buffer_storage_ = (BUFTYPE*)buffer;
	if (buffer) {
		rx_buffer_total_size_ = SERIAL4_RX_BUFFER_SIZE + length;
	} else {
		rx_buffer_total_size_ = SERIAL4_RX_BUFFER_SIZE;
	} 

	rts_low_watermark_ = RTS_LOW_WATERMARK + length;
	rts_high_watermark_ = RTS_HIGH_WATERMARK + length;
}

void serial4_add_memory_for_write(void *buffer, size_t length)
{
	tx_buffer_storage_ = (BUFTYPE*)buffer;
	if (buffer) {
		tx_buffer_total_size_ = SERIAL4_TX_BUFFER_SIZE + length;
	} else {
		tx_buffer_total_size_ = SERIAL4_TX_BUFFER_SIZE;
	} 
}


#endif // HAS_KINETISK_UART3
