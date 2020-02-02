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

#ifdef HAS_KINETISK_LPUART0

#define GPIO_BITBAND_ADDR(reg, bit) (((uint32_t)&(reg) - 0x40000000) * 32 + (bit) * 4 + 0x42000000)
#define GPIO_BITBAND_PTR(reg, bit) ((uint32_t *)GPIO_BITBAND_ADDR((reg), (bit)))
#define BITBAND_SET_BIT(reg, bit) (*GPIO_BITBAND_PTR((reg), (bit)) = 1)
#define BITBAND_CLR_BIT(reg, bit) (*GPIO_BITBAND_PTR((reg), (bit)) = 0)
#define TCIE_BIT 22
#define TIE_BIT  23


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
#if SERIAL6_TX_BUFFER_SIZE > 255
static volatile uint16_t tx_buffer_head = 0;
static volatile uint16_t tx_buffer_tail = 0;
#else
static volatile uint8_t tx_buffer_head = 0;
static volatile uint8_t tx_buffer_tail = 0;
#endif
#if SERIAL6_RX_BUFFER_SIZE > 255
static volatile uint16_t rx_buffer_head = 0;
static volatile uint16_t rx_buffer_tail = 0;
#else
static volatile uint8_t rx_buffer_head = 0;
static volatile uint8_t rx_buffer_tail = 0;
#endif

static uint8_t tx_pin_num = 48;

// UART0 and UART1 are clocked by F_CPU, UART2 is clocked by F_BUS
// UART0 has 8 byte fifo, UART1 and UART2 have 1 byte buffer


void serial6_begin(uint32_t desiredBaudRate)
{
	#define F_LPUART_CLOCK_SPEED  48000000 //F_BUS
	// Make sure the clock for this uart is enabled, else the registers are not
	// vailable. 
	SIM_SCGC2 |= SIM_SCGC2_LPUART0; 	// Turn on the clock

	// Convert the baud rate to best divisor and OSR, based off of code I found in posting
	// try to find an OSR > 4 with the minimum difference from the actual disired baud rate. 
    uint16_t sbr, sbrTemp, osrCheck;
    uint32_t osr, baudDiffCheck, calculatedBaud, baudDiff;
    uint32_t clockSpeed;

    // First lets figure out what the LPUART Clock speed is. 
    uint32_t PLLFLLSEL = SIM_SOPT2 & SIM_SOPT2_IRC48SEL;	// Note: Bot bits on here

    if (PLLFLLSEL == SIM_SOPT2_IRC48SEL)
    	clockSpeed = 48000000;  // Fixed to 48mhz
    else if (PLLFLLSEL == SIM_SOPT2_PLLFLLSEL)
    	clockSpeed = F_PLL;		// Using PLL clock
    else
    	clockSpeed = F_CPU/4;	// FLL clock, guessing
 
    osr = 4;
    sbr = (clockSpeed/(desiredBaudRate * osr));
    /*set sbr to 1 if the clockSpeed can not satisfy the desired baud rate*/
    if(sbr == 0) {
    	// Maybe print something.
    	return;	// can not initialize
    }

     // With integer math the divide*muliply implies the calculated baud will be >= desired baud
    calculatedBaud = (clockSpeed / (osr * sbr));
    baudDiff = calculatedBaud - desiredBaudRate;

    // Check if better off with sbr+1
    if (baudDiff != 0) {
      calculatedBaud = (clockSpeed / (osr * (sbr + 1)));
      baudDiffCheck = desiredBaudRate - calculatedBaud ;
      if (baudDiffCheck < baudDiff) {
        sbr++;  // use the higher sbr
        baudDiff = baudDiffCheck;
      }
    }

    // loop to find the best osr value possible, one that generates minimum baudDiff
    for (osrCheck = 5; osrCheck <= 32; osrCheck++)     {
        sbrTemp = (clockSpeed/(desiredBaudRate * osrCheck));

        if(sbrTemp == 0)
          break;    // higher divisor returns 0 so can not use...

        // Remember integer math so (X/Y)*Y will always be <=X
        calculatedBaud = (clockSpeed / (osrCheck * sbrTemp));
        baudDiffCheck = calculatedBaud - desiredBaudRate;
        if (baudDiffCheck <= baudDiff) {
            baudDiff = baudDiffCheck;
            osr = osrCheck;
            sbr = sbrTemp; 
        }
        // Lets try the rounded up one as well
        if (baudDiffCheck) {
          calculatedBaud = (clockSpeed / (osrCheck * ++sbrTemp));
          baudDiffCheck = desiredBaudRate - calculatedBaud;
          if (baudDiffCheck <= baudDiff) {
              baudDiff = baudDiffCheck;
              osr = osrCheck;
              sbr = sbrTemp; 
          }
        }
    }
	// for lower OSR <= 7x turn on both edge sampling
	uint32_t lpb = LPUART_BAUD_OSR(osr-1) | LPUART_BAUD_SBR(sbr);
    if (osr < 8) {
      lpb |= LPUART_BAUD_BOTHEDGE; 
    }
	LPUART0_BAUD = lpb;

	SIM_SOPT2 |= SIM_SOPT2_LPUARTSRC(1);	// Lets use PLL?

	rx_buffer_head = 0;
	rx_buffer_tail = 0;
	tx_buffer_head = 0;
	tx_buffer_tail = 0;
	transmitting = 0;
	CORE_PIN47_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_PFE | PORT_PCR_MUX(5);
	CORE_PIN48_CONFIG = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(5);
	LPUART0_CTRL = 0;
	LPUART0_MATCH = 0;
	LPUART0_STAT = 0;

	// Enable the transmitter, receiver and enable receiver interrupt
	LPUART0_CTRL |= LPUART_CTRL_RIE | LPUART_CTRL_TE | LPUART_CTRL_RE;
	NVIC_SET_PRIORITY(IRQ_LPUART0, IRQ_PRIORITY);
	NVIC_ENABLE_IRQ(IRQ_LPUART0);
}

void serial6_format(uint32_t format)
{
	uint32_t c;

	// Bits 0-2 - Parity plus 9  bit. 
	c = LPUART0_CTRL;
	//c = (c & ~(LPUART_CTRL_M | LPUART_CTRL_PE | LPUART_CTRL_PT)) | (format & (LPUART_CTRL_PE | LPUART_CTRL_PT));	// configure parity
	//if (format & 0x04) c |= LPUART_CTRL_M;		// 9 bits (might include parity)
	c = (c & ~0x13) | (format & 0x03);	// configure parity
	if (format & 0x04) c |= 0x10;		// 9 bits (might include parity)
	LPUART0_CTRL = c;
	if ((format & 0x0F) == 0x04) LPUART0_CTRL |= LPUART_CTRL_T8; // 8N2 is 9 bit with 9th bit always 1

	// Bit 3 10 bit - Will assume that begin already cleared it.
	if (format & 0x08)
		LPUART0_BAUD |= LPUART_BAUD_M10;
	
	// Bit 4 RXINVERT 
	c = LPUART0_STAT & ~LPUART_STAT_RXINV;
	if (format & 0x10) c |= LPUART_STAT_RXINV;		// rx invert
	LPUART0_STAT = c;

	// Bit 5 TXINVERT
	c = LPUART0_CTRL & ~LPUART_CTRL_TXINV;
	if (format & 0x20) c |= LPUART_CTRL_TXINV;		// tx invert
	LPUART0_CTRL = c;

	// For T3.6 See about turning on 2 stop bit mode
	if ( format & 0x100) LPUART0_BAUD |= LPUART_BAUD_SBNS;	
}

void serial6_end(void)
{
	if (!(SIM_SCGC2 & SIM_SCGC2_LPUART0)) return;
	while (transmitting) yield();  // wait for buffered data to send
	NVIC_DISABLE_IRQ(IRQ_LPUART0);
	LPUART0_CTRL = 0;
	CORE_PIN47_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_MUX(1);
	CORE_PIN48_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_MUX(1);
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
	if ((SIM_SCGC2 & SIM_SCGC2_LPUART0)) {
		switch (tx_pin_num & 127) {
			case 48:  CORE_PIN48_CONFIG = 0; break; // PTE24
		}
		if (opendrain) {
			cfg = PORT_PCR_DSE | PORT_PCR_ODE;
		} else {
			cfg = PORT_PCR_DSE | PORT_PCR_SRE;
		}
		switch (pin & 127) {
			case 48:  CORE_PIN48_CONFIG = cfg | PORT_PCR_MUX(5); break;
		}
	}
	tx_pin_num = pin;
}

void serial6_set_rx(uint8_t pin)
{
}

int serial6_set_rts(uint8_t pin)
{
	if (!(SIM_SCGC2 & SIM_SCGC2_LPUART0)) return 0;
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
	if (!(SIM_SCGC2 & SIM_SCGC2_LPUART0)) return 0;
	if (pin == 56) {
		CORE_PIN56_CONFIG = PORT_PCR_MUX(5) | PORT_PCR_PE; // weak pulldown
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

	if (!(SIM_SCGC2 & SIM_SCGC2_LPUART0)) return;
	if (transmit_pin) transmit_assert();
	head = tx_buffer_head;
	if (++head >= SERIAL6_TX_BUFFER_SIZE) head = 0;
	while (tx_buffer_tail == head) {
		int priority = nvic_execution_priority();
		if (priority <= IRQ_PRIORITY) {
			if ((LPUART0_STAT & LPUART_STAT_TDRE)) {
				uint32_t tail = tx_buffer_tail;
				if (++tail >= SERIAL6_TX_BUFFER_SIZE) tail = 0;
				n = tx_buffer[tail];
				//if (use9Bits) UART5_C3 = (UART5_C3 & ~0x40) | ((n & 0x100) >> 2);
				LPUART0_DATA = n;
				tx_buffer_tail = tail;
			}
		} else if (priority >= 256) {
			yield(); // wait
		}
	}
	tx_buffer[head] = c;
	transmitting = 1;
	tx_buffer_head = head;

	//LPUART0_CTRL |= LPUART_CTRL_TIE;	// enable the transmit interrupt
	BITBAND_SET_BIT(LPUART0_CTRL, TIE_BIT);

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
//   Transmit data below watermark  LPUART_STAT_TDRE
//   Transmit complete		    LPUART_STAT_TC
//   Idle line			    LPUART_STAT_IDLE
//   Receive data above watermark   LPUART_STAT_RDRF
//   LIN break detect		    UART_S2_LBKDIF
//   RxD pin active edge	    UART_S2_RXEDGIF

void lpuart0_status_isr(void)
{
	uint32_t head, tail, n;
	uint32_t c;

	if (LPUART0_STAT & LPUART_STAT_RDRF) {
//		if (use9Bits && (UART5_C3 & 0x80)) {
//			n = UART5_D | 0x100;
//		} else {
//			n = UART5_D;
//		}
		n = LPUART0_DATA & 0x3ff;	// use only the 10 data bits
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
	c = LPUART0_CTRL;
	if ((c & LPUART_CTRL_TIE) && (LPUART0_STAT & LPUART_STAT_TDRE)) {
		head = tx_buffer_head;
		tail = tx_buffer_tail;
		if (head == tail) {
			BITBAND_CLR_BIT(LPUART0_CTRL, TIE_BIT);
			BITBAND_SET_BIT(LPUART0_CTRL, TCIE_BIT);
			//LPUART0_CTRL &= ~LPUART_CTRL_TIE; 
  			//LPUART0_CTRL |= LPUART_CTRL_TCIE; // Actually wondering if we can just leave this one on...
		} else {
			if (++tail >= SERIAL6_TX_BUFFER_SIZE) tail = 0;
			n = tx_buffer[tail];
			//if (use9Bits) UART5_C3 = (UART5_C3 & ~0x40) | ((n & 0x100) >> 2);
			LPUART0_DATA = n;
			tx_buffer_tail = tail;
		}
	}
	if ((c & LPUART_CTRL_TCIE) && (LPUART0_STAT & LPUART_STAT_TC)) {
		transmitting = 0;
		if (transmit_pin) transmit_deassert();
		BITBAND_CLR_BIT(LPUART0_CTRL, TCIE_BIT);
		// LPUART0_CTRL &= ~LPUART_CTRL_TCIE; // Actually wondering if we can just leave this one on...
	}
}

#endif // HAS_KINETISK_LPUART0
