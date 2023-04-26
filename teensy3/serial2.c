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

////////////////////////////////////////////////////////////////
// Tunable parameters (relatively safe to edit these numbers)
////////////////////////////////////////////////////////////////

#ifndef SERIAL2_TX_BUFFER_SIZE
#define SERIAL2_TX_BUFFER_SIZE     40 // number of outgoing bytes to buffer
#endif
#ifndef SERIAL2_RX_BUFFER_SIZE
#define SERIAL2_RX_BUFFER_SIZE     64 // number of incoming bytes to buffer
#endif
#define RTS_HIGH_WATERMARK (SERIAL2_RX_BUFFER_SIZE-24) // RTS requests sender to pause
#define RTS_LOW_WATERMARK  (SERIAL2_RX_BUFFER_SIZE-38) // RTS allows sender to resume
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

static volatile BUFTYPE tx_buffer[SERIAL2_TX_BUFFER_SIZE];
static volatile BUFTYPE rx_buffer[SERIAL2_RX_BUFFER_SIZE];
static volatile BUFTYPE	*rx_buffer_storage_ = NULL;
static volatile BUFTYPE	*tx_buffer_storage_ = NULL;

static size_t tx_buffer_total_size_ = SERIAL2_TX_BUFFER_SIZE;
static size_t rx_buffer_total_size_ = SERIAL2_RX_BUFFER_SIZE;
static size_t rts_low_watermark_ = RTS_LOW_WATERMARK;
static size_t rts_high_watermark_ = RTS_HIGH_WATERMARK;

static volatile uint8_t transmitting = 0;
#if defined(KINETISK)
  static volatile uint8_t *transmit_pin=NULL;
  #define transmit_assert()   *transmit_pin = 1
  #define transmit_deassert() *transmit_pin = 0
  static volatile uint8_t *rts_pin=NULL;
  #define rts_assert()        *rts_pin = 0
  #define rts_deassert()      *rts_pin = 1
#elif defined(KINETISL)
  static volatile uint8_t *transmit_pin=NULL;
  static uint8_t transmit_mask=0;
  #define transmit_assert()   *(transmit_pin+4) = transmit_mask;
  #define transmit_deassert() *(transmit_pin+8) = transmit_mask;
  static volatile uint8_t *rts_pin=NULL;
  static uint8_t rts_mask=0;
  #define rts_assert()        *(rts_pin+8) = rts_mask;
  #define rts_deassert()      *(rts_pin+4) = rts_mask;
#endif
#if SERIAL2_TX_BUFFER_SIZE > 65535
static volatile uint32_t tx_buffer_head = 0;
static volatile uint32_t tx_buffer_tail = 0;
#elif SERIAL2_TX_BUFFER_SIZE > 255
static volatile uint16_t tx_buffer_head = 0;
static volatile uint16_t tx_buffer_tail = 0;
#else
static volatile uint8_t tx_buffer_head = 0;
static volatile uint8_t tx_buffer_tail = 0;
#endif
#if SERIAL2_RX_BUFFER_SIZE > 65535
static volatile uint32_t rx_buffer_head = 0;
static volatile uint32_t rx_buffer_tail = 0;
#elif SERIAL2_RX_BUFFER_SIZE > 255
static volatile uint16_t rx_buffer_head = 0;
static volatile uint16_t rx_buffer_tail = 0;
#else
static volatile uint8_t rx_buffer_head = 0;
static volatile uint8_t rx_buffer_tail = 0;
#endif
#if defined(KINETISK)
static uint8_t rx_pin_num = 9;
static uint8_t tx_pin_num = 10;
#endif
#if defined(KINETISL)
static uint8_t half_duplex_mode = 0;
#endif

// 7-bit mode support
static uint8_t data_mask = 0xff;  // Use all bits by default

// UART0 and UART1 are clocked by F_CPU, UART2 is clocked by F_BUS
// UART0 has 8 byte fifo, UART1 and UART2 have 1 byte buffer

#ifdef HAS_KINETISK_UART1_FIFO
#define C2_ENABLE		UART_C2_TE | UART_C2_RE | UART_C2_RIE | UART_C2_ILIE
#else
#define C2_ENABLE		UART_C2_TE | UART_C2_RE | UART_C2_RIE
#endif
#define C2_TX_ACTIVE		C2_ENABLE | UART_C2_TIE
#define C2_TX_COMPLETING	C2_ENABLE | UART_C2_TCIE
#define C2_TX_INACTIVE		C2_ENABLE

// BITBAND Support
#define GPIO_BITBAND_ADDR(reg, bit) (((uint32_t)&(reg) - 0x40000000) * 32 + (bit) * 4 + 0x42000000)
#define GPIO_BITBAND_PTR(reg, bit) ((uint32_t *)GPIO_BITBAND_ADDR((reg), (bit)))
#define C3_TXDIR_BIT 5

void serial2_begin(uint32_t divisor)
{
	SIM_SCGC4 |= SIM_SCGC4_UART1;	// turn on clock, TODO: use bitband
	rx_buffer_head = 0;
	rx_buffer_tail = 0;
	tx_buffer_head = 0;
	tx_buffer_tail = 0;
	transmitting = 0;
#if defined(KINETISK)
	switch (rx_pin_num) {
		case 9: CORE_PIN9_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_PFE | PORT_PCR_MUX(3); break;
		#if defined(__MK20DX128__) || defined(__MK20DX256__)    // T3.0, T3.1, T3.2
		case 26: CORE_PIN26_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_PFE | PORT_PCR_MUX(3); break;
		#elif defined(__MK64FX512__) || defined(__MK66FX1M0__)  // T3.5 or T3.6
		case 59: CORE_PIN59_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_PFE | PORT_PCR_MUX(3); break;
		#endif
	}
	switch (tx_pin_num) {
		case 10: CORE_PIN10_CONFIG = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(3); break;
		#if defined(__MK20DX128__) || defined(__MK20DX256__)    // T3.0, T3.1, T3.2
		case 31: CORE_PIN31_CONFIG = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(3); break;
		#elif defined(__MK64FX512__) || defined(__MK66FX1M0__)  // T3.5 or T3.6
		case 58: CORE_PIN58_CONFIG = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(3); break;
		#endif
	}
#elif defined(KINETISL)
	CORE_PIN9_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_PFE | PORT_PCR_MUX(3);
	CORE_PIN10_CONFIG = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(3);
#endif
#if defined(HAS_KINETISK_UART1)
	if (divisor < 32) divisor = 32;
	UART1_BDH = (divisor >> 13) & 0x1F;
	UART1_BDL = (divisor >> 5) & 0xFF;
	UART1_C4 = divisor & 0x1F;
#ifdef HAS_KINETISK_UART1_FIFO
	UART1_C1 = UART_C1_ILT;
	UART1_TWFIFO = 2; // tx watermark, causes S1_TDRE to set
	UART1_RWFIFO = 4; // rx watermark, causes S1_RDRF to set
	UART1_PFIFO = UART_PFIFO_TXFE | UART_PFIFO_RXFE;
#else
	UART1_C1 = 0;
	UART1_PFIFO = 0;
#endif
#elif defined(HAS_KINETISL_UART1)
	if (divisor < 1) divisor = 1;
	UART1_BDH = (divisor >> 8) & 0x1F;
	UART1_BDL = divisor & 0xFF;
	UART1_C1 = 0;
#endif
	UART1_C2 = C2_TX_INACTIVE;
	NVIC_SET_PRIORITY(IRQ_UART1_STATUS, IRQ_PRIORITY);
	NVIC_ENABLE_IRQ(IRQ_UART1_STATUS);
}

void serial2_format(uint32_t format)
{
	uint8_t c;

	c = UART1_C1;
	c = (c & ~0x13) | (format & 0x03);	// configure parity
	if (format & 0x04) c |= 0x10;		// 9 bits (might include parity)
	UART1_C1 = c;
	if ((format & 0x0F) == 0x04) UART1_C3 |= 0x40; // 8N2 is 9 bit with 9th bit always 1
	c = UART1_S2 & ~0x10;
	if (format & 0x10) c |= 0x10;		// rx invert
	UART1_S2 = c;
	c = UART1_C3 & ~0x10;
	if (format & 0x20) c |= 0x10;		// tx invert
	UART1_C3 = c;

	// 7-bit support
	if ((format & 0x0E) == 0x02) {
		data_mask = 0x7f;	// Use only 7 bits of data
	} else {
		data_mask = 0xff;	// Use all bits
	}

#if defined(SERIAL_9BIT_SUPPORT) && !defined(KINETISL)
	c = UART1_C4 & 0x1F;
	if (format & 0x08) c |= 0x20;		// 9 bit mode with parity (requires 10 bits)
	UART1_C4 = c;
	use9Bits = format & 0x80;
#endif
#if defined(__MK64FX512__) || defined(__MK66FX1M0__) || defined(KINETISL)
	// For T3.5/T3.6/TLC See about turning on 2 stop bit mode
	if ( format & 0x100) {
		uint8_t bdl = UART1_BDL;
		UART1_BDH |= UART_BDH_SBNS;		// Turn on 2 stop bits - was turned off by set baud
		UART1_BDL = bdl;		// Says BDH not acted on until BDL is written
	}
#endif
	// process request for half duplex.
	if ((format & SERIAL_HALF_DUPLEX) != 0) {
		c = UART1_C1;
		c |= UART_C1_LOOPS | UART_C1_RSRC;
		UART1_C1 = c;

		// Lets try to make use of bitband address to set the direction for ue...
		#if defined(KINETISL)
		//CORE_PIN10_CONFIG = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(1) | PORT_PCR_PE | PORT_PCR_PS;
		CORE_PIN10_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_PFE | PORT_PCR_MUX(3);
		half_duplex_mode = 1;
		#else
		volatile uint32_t *reg = portConfigRegister(tx_pin_num);
		*reg = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(3) | PORT_PCR_PE | PORT_PCR_PS; // pullup on output pin;
		transmit_pin = (uint8_t*)GPIO_BITBAND_PTR(UART1_C3, C3_TXDIR_BIT);
		#endif

	} else {
		#if defined(KINETISL)
		half_duplex_mode = 0;
		#else
		if (transmit_pin == (uint8_t*)GPIO_BITBAND_PTR(UART1_C3, C3_TXDIR_BIT)) transmit_pin = NULL;
		#endif
	}
}

void serial2_end(void)
{
	if (!(SIM_SCGC4 & SIM_SCGC4_UART1)) return;
	while (transmitting) yield();  // wait for buffered data to send
	NVIC_DISABLE_IRQ(IRQ_UART1_STATUS);
	UART1_C2 = 0;
#if defined(KINETISK)
	switch (rx_pin_num) {
		case 9: CORE_PIN9_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_MUX(1); break; // PTC3
		#if defined(__MK20DX128__) || defined(__MK20DX256__)  // T3.0, T3.1, T3.2
		case 26: CORE_PIN26_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_MUX(1); break; // PTE1
		#elif defined(__MK64FX512__) || defined(__MK66FX1M0__) // T3.5, T3.6
		case 59: CORE_PIN59_CONFIG = 0; break;
		#endif
	}
	switch (tx_pin_num & 127) {
		case 10: CORE_PIN10_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_MUX(1); break; // PTC4
		#if defined(__MK20DX128__) || defined(__MK20DX256__)  // T3.0, T3.1, T3.2
		case 31: CORE_PIN31_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_MUX(1); break; // PTE0
		#elif defined(__MK64FX512__) || defined(__MK66FX1M0__) // T3.5, T3.6
		case 58: CORE_PIN58_CONFIG = 0; break;
		#endif
	}
#elif defined(KINETISL)
	CORE_PIN9_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_MUX(1);  // PTC3
	CORE_PIN10_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_MUX(1); // PTC4
#endif
	UART1_S1;
	UART1_D; // clear leftover error status
	rx_buffer_head = 0;
	rx_buffer_tail = 0;
	if (rts_pin) rts_deassert();
}

void serial2_set_transmit_pin(uint8_t pin)
{
	while (transmitting) ;
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
	transmit_pin = portOutputRegister(pin);
	#if defined(KINETISL)
	transmit_mask = digitalPinToBitMask(pin);
	#endif
}

void serial2_set_tx(uint8_t pin, uint8_t opendrain)
{
	#if defined(KINETISK)
	uint32_t cfg;

	if (opendrain) pin |= 128;
	if (pin == tx_pin_num) return;
	if ((SIM_SCGC4 & SIM_SCGC4_UART1)) {
		switch (tx_pin_num & 127) {
			case 10: CORE_PIN10_CONFIG = 0; break; // PTC4
			#if defined(__MK20DX128__) || defined(__MK20DX256__)  // T3.0, T3.1, T3.2
			case 31: CORE_PIN31_CONFIG = 0; break; // PTE0
			#elif defined(__MK64FX512__) || defined(__MK66FX1M0__) // T3.5, T3.6
			case 58: CORE_PIN58_CONFIG = 0; break;
			#endif
		}
		if (opendrain) {
			cfg = PORT_PCR_DSE | PORT_PCR_ODE;
		} else {
			cfg = PORT_PCR_DSE | PORT_PCR_SRE;
		}
		switch (pin & 127) {
			case 10: CORE_PIN10_CONFIG = cfg | PORT_PCR_MUX(3); break;
			#if defined(__MK20DX128__) || defined(__MK20DX256__)  // T3.0, T3.1, T3.2
			case 31: CORE_PIN31_CONFIG = cfg | PORT_PCR_MUX(3); break;
			#elif defined(__MK64FX512__) || defined(__MK66FX1M0__) // T3.5, T3.6
			case 58: CORE_PIN58_CONFIG = cfg | PORT_PCR_MUX(3); break;
			#endif
		}
	}
	tx_pin_num = pin;
	#endif
}

void serial2_set_rx(uint8_t pin)
{
	#if defined(KINETISK)
	if (pin == rx_pin_num) return;
	if ((SIM_SCGC4 & SIM_SCGC4_UART1)) {
		switch (rx_pin_num) {
			case 9: CORE_PIN9_CONFIG = 0; break; // PTC3
			#if defined(__MK20DX128__) || defined(__MK20DX256__)  // T3.0, T3.1, T3.2
			case 26: CORE_PIN26_CONFIG = 0; break; // PTE1
			#elif defined(__MK64FX512__) || defined(__MK66FX1M0__) // T3.5, T3.6
			case 59: CORE_PIN59_CONFIG = 0; break;
			#endif
		}
		switch (pin) {
			case 9: CORE_PIN9_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_PFE | PORT_PCR_MUX(3); break;
			#if defined(__MK20DX128__) || defined(__MK20DX256__)  // T3.0, T3.1, T3.2
			case 26: CORE_PIN26_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_PFE | PORT_PCR_MUX(3); break;
			#elif defined(__MK64FX512__) || defined(__MK66FX1M0__) // T3.5, T3.6
			case 59: CORE_PIN59_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_PFE | PORT_PCR_MUX(3); break;
			#endif
		}
	}
	rx_pin_num = pin;
	#endif
}

int serial2_set_rts(uint8_t pin)
{
	if (!(SIM_SCGC4 & SIM_SCGC4_UART1)) return 0;
	if (pin < CORE_NUM_DIGITAL) {
		rts_pin = portOutputRegister(pin);
		#if defined(KINETISL)
		rts_mask = digitalPinToBitMask(pin);
		#endif
		pinMode(pin, OUTPUT);
		rts_assert();
	} else {
		rts_pin = NULL;
		return 0;
	}
/*
	if (!(SIM_SCGC4 & SIM_SCGC4_UART1)) return 0;
	if (pin == 22) {
		CORE_PIN22_CONFIG = PORT_PCR_MUX(3);
	} else {
		UART1_MODEM &= ~UART_MODEM_RXRTSE;
		return 0;
	}
	UART1_MODEM |= UART_MODEM_RXRTSE;
*/
	return 1;
}

int serial2_set_cts(uint8_t pin)
{
#if defined(KINETISK)
	if (!(SIM_SCGC4 & SIM_SCGC4_UART1)) return 0;
	if (pin == 23) {
		CORE_PIN23_CONFIG = PORT_PCR_MUX(3) | PORT_PCR_PE; // weak pulldown
	#if defined(__MK64FX512__) || defined(__MK66FX1M0__)  // on T3.5 or T3.6
	} else if (pin == 60) {
		CORE_PIN60_CONFIG = PORT_PCR_MUX(3) | PORT_PCR_PE; // weak pulldown
	#endif
	} else {
		UART1_MODEM &= ~UART_MODEM_TXCTSE;
		return 0;
	}
	UART1_MODEM |= UART_MODEM_TXCTSE;
	return 1;
#else
	return 0;
#endif
}

void serial2_putchar(uint32_t c)
{
	uint32_t head, n;

	if (!(SIM_SCGC4 & SIM_SCGC4_UART1)) return;
	if (transmit_pin) transmit_assert();
	#if defined(KINETISL)
	if (half_duplex_mode) {
		__disable_irq();
		volatile uint32_t reg = UART1_C3;
		reg |= UART_C3_TXDIR;
		UART1_C3 = reg;
		__enable_irq();
	}
	#endif 
	head = tx_buffer_head;
	if (++head >= tx_buffer_total_size_) head = 0;
	while (tx_buffer_tail == head) {
		int priority = nvic_execution_priority();
		if (priority <= IRQ_PRIORITY) {
			if ((UART1_S1 & UART_S1_TDRE)) {
				uint32_t tail = tx_buffer_tail;
				if (++tail >= tx_buffer_total_size_) tail = 0;
				if (tail < SERIAL2_TX_BUFFER_SIZE) {
					n = tx_buffer[tail];
				} else {
					n = tx_buffer_storage_[tail-SERIAL2_TX_BUFFER_SIZE];
				}
				if (use9Bits) UART1_C3 = (UART1_C3 & ~0x40) | ((n & 0x100) >> 2);
				UART1_D = n;
				tx_buffer_tail = tail;
			}
		} else if (priority >= 256) {
			yield(); // wait
		}
	}
	if (head < SERIAL2_TX_BUFFER_SIZE) {
		tx_buffer[head] = c;
	} else {
		tx_buffer_storage_[head - SERIAL2_TX_BUFFER_SIZE] = c;
	}
	transmitting = 1;
	tx_buffer_head = head;
	UART1_C2 = C2_TX_ACTIVE;
}

#ifdef HAS_KINETISK_UART1_FIFO
void serial2_write(const void *buf, unsigned int count)
{
	const uint8_t *p = (const uint8_t *)buf;
	const uint8_t *end = p + count;
	uint32_t head, n;

	if (!(SIM_SCGC4 & SIM_SCGC4_UART1)) return;
	if (transmit_pin) transmit_assert();
	while (p < end) {
		head = tx_buffer_head;
		if (++head >= tx_buffer_total_size_) head = 0;
		if (tx_buffer_tail == head) {
			UART1_C2 = C2_TX_ACTIVE;
			do {
				int priority = nvic_execution_priority();
				if (priority <= IRQ_PRIORITY) {
					if ((UART1_S1 & UART_S1_TDRE)) {
						uint32_t tail = tx_buffer_tail;
						if (++tail >= tx_buffer_total_size_) tail = 0;
						if (tail < SERIAL2_TX_BUFFER_SIZE) {
							n = tx_buffer[tail];
						} else {
							n = tx_buffer_storage_[tail-SERIAL2_TX_BUFFER_SIZE];
						}
						if (use9Bits) UART1_C3 = (UART1_C3 & ~0x40) | ((n & 0x100) >> 2);
						UART1_D = n;
						tx_buffer_tail = tail;
					}
				} else if (priority >= 256) {
					yield();
				}
			} while (tx_buffer_tail == head);
		}
		if (head < SERIAL2_TX_BUFFER_SIZE) {
			tx_buffer[head] = *p++;
		} else {
			tx_buffer_storage_[head - SERIAL2_TX_BUFFER_SIZE] = *p++;
		}
		transmitting = 1;
		tx_buffer_head = head;
	}
	UART1_C2 = C2_TX_ACTIVE;
}
#else
void serial2_write(const void *buf, unsigned int count)
{
	const uint8_t *p = (const uint8_t *)buf;
	while (count-- > 0) serial2_putchar(*p++);
}
#endif

void serial2_flush(void)
{
	while (transmitting) yield(); // wait
}

int serial2_write_buffer_free(void)
{
	uint32_t head, tail;

	head = tx_buffer_head;
	tail = tx_buffer_tail;
	if (head >= tail) return tx_buffer_total_size_ - 1 - head + tail;
	return tail - head - 1;
}

int serial2_available(void)
{
	uint32_t head, tail;

	head = rx_buffer_head;
	tail = rx_buffer_tail;
	if (head >= tail) return head - tail;
	return rx_buffer_total_size_ + head - tail;
}

int serial2_getchar(void)
{
	uint32_t head, tail;
	int c;

	head = rx_buffer_head;
	tail = rx_buffer_tail;
	if (head == tail) return -1;
	if (++tail >= rx_buffer_total_size_) tail = 0;
	if (tail < SERIAL2_RX_BUFFER_SIZE) {
		c = rx_buffer[tail];
	} else {
		c = rx_buffer_storage_[tail-SERIAL2_RX_BUFFER_SIZE];
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

int serial2_peek(void)
{
	uint32_t head, tail;

	head = rx_buffer_head;
	tail = rx_buffer_tail;
	if (head == tail) return -1;
	if (++tail >= rx_buffer_total_size_) tail = 0;
	if (tail < SERIAL2_RX_BUFFER_SIZE) {
		return rx_buffer[tail];
	}
	return rx_buffer_storage_[tail-SERIAL2_RX_BUFFER_SIZE];
}

void serial2_clear(void)
{
#ifdef HAS_KINETISK_UART1_FIFO
	if (!(SIM_SCGC4 & SIM_SCGC4_UART1)) return;
	UART1_C2 &= ~(UART_C2_RE | UART_C2_RIE | UART_C2_ILIE);
	UART1_CFIFO = UART_CFIFO_RXFLUSH;
	UART1_C2 |= (UART_C2_RE | UART_C2_RIE | UART_C2_ILIE);
#endif
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

void uart1_status_isr(void)
{
	uint32_t head, tail, n;
	uint8_t c;
#ifdef HAS_KINETISK_UART1_FIFO
	uint32_t newhead;
	uint8_t avail;

	if (UART1_S1 & (UART_S1_RDRF | UART_S1_IDLE)) {
		__disable_irq();
		avail = UART1_RCFIFO;
		if (avail == 0) {
			// The only way to clear the IDLE interrupt flag is
			// to read the data register.  But reading with no
			// data causes a FIFO underrun, which causes the
			// FIFO to return corrupted data.  If anyone from
			// Freescale reads this, what a poor design!  There
			// write should be a write-1-to-clear for IDLE.
			c = UART1_D;
			// flushing the fifo recovers from the underrun,
			// but there's a possible race condition where a
			// new character could be received between reading
			// RCFIFO == 0 and flushing the FIFO.  To minimize
			// the chance, interrupts are disabled so a higher
			// priority interrupt (hopefully) doesn't delay.
			// TODO: change this to disabling the IDLE interrupt
			// which won't be simple, since we already manage
			// which transmit interrupts are enabled.
			UART1_CFIFO = UART_CFIFO_RXFLUSH;
			__enable_irq();
		} else {
			__enable_irq();
			head = rx_buffer_head;
			tail = rx_buffer_tail;
			do {
				if (use9Bits && (UART1_C3 & 0x80)) {
					n = UART1_D | 0x100;
				} else {
					n = UART1_D & data_mask;
				}
				newhead = head + 1;
				if (newhead >= rx_buffer_total_size_) newhead = 0;
				if (newhead != tail) {
					head = newhead;
					if (newhead < SERIAL2_RX_BUFFER_SIZE) {
						rx_buffer[head] = n;
					} else {
						rx_buffer_storage_[head-SERIAL2_RX_BUFFER_SIZE] = n;
					}
				}
			} while (--avail > 0);
			rx_buffer_head = head;
			if (rts_pin) {
				int avail;
				if (head >= tail) avail = head - tail;
				else avail = rx_buffer_total_size_ + head - tail;
				if (avail >= rts_high_watermark_) rts_deassert();
			}
		}
	}
	c = UART1_C2;
	if ((c & UART_C2_TIE) && (UART1_S1 & UART_S1_TDRE)) {
		head = tx_buffer_head;
		tail = tx_buffer_tail;
		do {
			if (tail == head) break;
			if (++tail >= tx_buffer_total_size_) tail = 0;
			avail = UART1_S1;
			if (tail < SERIAL2_TX_BUFFER_SIZE) {
				n = tx_buffer[tail];
			} else {
				n = tx_buffer_storage_[tail-SERIAL2_TX_BUFFER_SIZE];
			}
			if (use9Bits) UART1_C3 = (UART1_C3 & ~0x40) | ((n & 0x100) >> 2);
			UART1_D = n;
		} while (UART1_TCFIFO < 8);
		tx_buffer_tail = tail;
		if (UART1_S1 & UART_S1_TDRE) UART1_C2 = C2_TX_COMPLETING;
	}
#else
	if (UART1_S1 & UART_S1_RDRF) {
		if (use9Bits && (UART1_C3 & 0x80)) {
			n = UART1_D | 0x100;
		} else {
			n = UART1_D & data_mask;
		}
		head = rx_buffer_head + 1;
		if (head >= rx_buffer_total_size_) head = 0;
		if (head != rx_buffer_tail) {
			if (head < SERIAL2_RX_BUFFER_SIZE) {
				rx_buffer[head] = n;
			} else {
				rx_buffer_storage_[head-SERIAL2_RX_BUFFER_SIZE] = n;
			}

			rx_buffer_head = head;
		}
	}
	c = UART1_C2;
	if ((c & UART_C2_TIE) && (UART1_S1 & UART_S1_TDRE)) {
		head = tx_buffer_head;
		tail = tx_buffer_tail;
		if (head == tail) {
			UART1_C2 = C2_TX_COMPLETING;
		} else {
			if (++tail >= tx_buffer_total_size_) tail = 0;
			if (tail < SERIAL2_TX_BUFFER_SIZE) {
				n = tx_buffer[tail];
			} else {
				n = tx_buffer_storage_[tail-SERIAL2_TX_BUFFER_SIZE];
			}
			if (use9Bits) UART1_C3 = (UART1_C3 & ~0x40) | ((n & 0x100) >> 2);
			UART1_D = n;
			tx_buffer_tail = tail;
		}
	}
#endif
	if ((c & UART_C2_TCIE) && (UART1_S1 & UART_S1_TC)) {
		transmitting = 0;
		if (transmit_pin) transmit_deassert();
		#if defined(KINETISL)
		if (half_duplex_mode) {
			__disable_irq();
			volatile uint32_t reg = UART1_C3;
			reg &= ~UART_C3_TXDIR;
			UART1_C3 = reg;
			__enable_irq();
		}
		#endif		
		UART1_C2 = C2_TX_INACTIVE;
	}
}

void serial2_add_memory_for_read(void *buffer, size_t length)
{
	rx_buffer_storage_ = (BUFTYPE*)buffer;
	if (buffer) {
		rx_buffer_total_size_ = SERIAL2_RX_BUFFER_SIZE + length;
	} else {
		rx_buffer_total_size_ = SERIAL2_RX_BUFFER_SIZE;
	} 

	rts_low_watermark_ = RTS_LOW_WATERMARK + length;
	rts_high_watermark_ = RTS_HIGH_WATERMARK + length;
}

void serial2_add_memory_for_write(void *buffer, size_t length)
{
	tx_buffer_storage_ = (BUFTYPE*)buffer;
	if (buffer) {
		tx_buffer_total_size_ = SERIAL2_TX_BUFFER_SIZE + length;
	} else {
		tx_buffer_total_size_ = SERIAL2_TX_BUFFER_SIZE;
	} 
}

