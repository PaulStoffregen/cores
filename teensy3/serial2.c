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

// UART0 and UART1 are clocked by F_CPU, UART2 is clocked by F_BUS
// UART0 has 8 byte fifo, UART1 and UART2 have 1 byte buffer

#define TX_BUFFER_SIZE 40
static volatile uint8_t tx_buffer[TX_BUFFER_SIZE];
static volatile uint8_t transmitting = 0;
#if TX_BUFFER_SIZE > 255
static volatile uint16_t tx_buffer_head = 0;
static volatile uint16_t tx_buffer_tail = 0;
#else
static volatile uint8_t tx_buffer_head = 0;
static volatile uint8_t tx_buffer_tail = 0;
#endif

#define RX_BUFFER_SIZE 64
static volatile uint8_t rx_buffer[RX_BUFFER_SIZE];
static volatile uint8_t rx_buffer_head = 0;
static volatile uint8_t rx_buffer_tail = 0;

#define C2_ENABLE		UART_C2_TE | UART_C2_RE | UART_C2_RIE
#define C2_TX_ACTIVE		C2_ENABLE | UART_C2_TIE
#define C2_TX_COMPLETING	C2_ENABLE | UART_C2_TCIE
#define C2_TX_INACTIVE		C2_ENABLE

void serial2_begin(uint32_t divisor)
{
	SIM_SCGC4 |= SIM_SCGC4_UART1;	// turn on clock, TODO: use bitband
	rx_buffer_head = 0;
	rx_buffer_tail = 0;
	tx_buffer_head = 0;
	tx_buffer_tail = 0;
	transmitting = 0;
	CORE_PIN9_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_PFE | PORT_PCR_MUX(3);
	CORE_PIN10_CONFIG = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(3);
	UART1_BDH = (divisor >> 13) & 0x1F;
	UART1_BDL = (divisor >> 5) & 0xFF;
	UART1_C4 = divisor & 0x1F;
	UART1_C1 = 0;
	UART1_PFIFO = 0;
	UART1_C2 = C2_TX_INACTIVE;
	NVIC_SET_PRIORITY(IRQ_UART1_STATUS, 64);
	NVIC_ENABLE_IRQ(IRQ_UART1_STATUS);
}

void serial2_end(void)
{
	if (!(SIM_SCGC4 & SIM_SCGC4_UART1)) return;
	while (transmitting) yield();  // wait for buffered data to send
	NVIC_DISABLE_IRQ(IRQ_UART1_STATUS);
	UART1_C2 = 0;
	CORE_PIN9_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_MUX(1);
	CORE_PIN10_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_MUX(1);
	rx_buffer_head = 0;
	rx_buffer_tail = 0;
}

void serial2_putchar(uint8_t c)
{
	uint32_t head;

	if (!(SIM_SCGC4 & SIM_SCGC4_UART1)) return;
	head = tx_buffer_head;
	if (++head >= TX_BUFFER_SIZE) head = 0;
	while (tx_buffer_tail == head) {
		yield(); // wait
	}
	tx_buffer[head] = c;
	transmitting = 1;
	tx_buffer_head = head;
	UART1_C2 = C2_TX_ACTIVE;
}

void serial2_write(const void *buf, unsigned int count)
{
	const uint8_t *p = (const uint8_t *)buf;
	while (count-- > 0) serial2_putchar(*p++);
}

void serial2_flush(void)
{
	while (transmitting) yield(); // wait
}

int serial2_available(void)
{
	uint32_t head, tail;

	head = rx_buffer_head;
	tail = rx_buffer_tail;
	if (head >= tail) return head - tail;
	return RX_BUFFER_SIZE + head - tail;
}

int serial2_getchar(void)
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

int serial2_peek(void)
{
	uint32_t head, tail;

	head = rx_buffer_head;
	tail = rx_buffer_tail;
	if (head == tail) return -1;
	if (++tail >= RX_BUFFER_SIZE) tail = 0;
	return rx_buffer[tail];
}

void serial2_clear(void)
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

void uart1_status_isr(void)
{
	uint32_t head, tail;
	uint8_t c;

	//digitalWriteFast(4, HIGH);
	if (UART1_S1 & UART_S1_RDRF) {
		//digitalWriteFast(5, HIGH);
		c = UART1_D;
		head = rx_buffer_head + 1;
		if (head >= RX_BUFFER_SIZE) head = 0;
		if (head != rx_buffer_tail) {
			rx_buffer[head] = c;
			rx_buffer_head = head; 
		}
		//digitalWriteFast(5, LOW);
	}
	c = UART1_C2;
	if ((c & UART_C2_TIE) && (UART1_S1 & UART_S1_TDRE)) {
		//digitalWriteFast(5, HIGH);
		head = tx_buffer_head;
		tail = tx_buffer_tail;
		if (head == tail) {
			UART1_C2 = C2_TX_COMPLETING;
		} else {
			if (++tail >= TX_BUFFER_SIZE) tail = 0;
			UART1_D = tx_buffer[tail];
			tx_buffer_tail = tail;
		}
		//digitalWriteFast(5, LOW);
	}
	if ((c & UART_C2_TCIE) && (UART1_S1 & UART_S1_TC)) {
		transmitting = 0;
		UART1_C2 = C2_TX_INACTIVE;
	}
	//digitalWriteFast(4, LOW);
}


