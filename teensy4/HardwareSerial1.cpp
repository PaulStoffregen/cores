
/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2019 PJRC.COM, LLC.
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

#include <Arduino.h>
#include "HardwareSerial.h"

#ifndef SERIAL1_TX_BUFFER_SIZE
#define SERIAL1_TX_BUFFER_SIZE     64 // number of outgoing bytes to buffer
#endif
#ifndef SERIAL1_RX_BUFFER_SIZE
#define SERIAL1_RX_BUFFER_SIZE     64 // number of incoming bytes to buffer
#endif
#define IRQ_PRIORITY  64  // 0 = highest priority, 255 = lowest

void IRQHandler_Serial1()
{
	Serial1.IRQHandler();
}


// Serial1
static BUFTYPE tx_buffer1[SERIAL1_TX_BUFFER_SIZE];
static BUFTYPE rx_buffer1[SERIAL1_RX_BUFFER_SIZE];
uint8_t _serialEvent1_default __attribute__((weak)) PROGMEM = 0 ;

const HardwareSerial::hardware_t UART6_Hardware = {
	0, IRQ_LPUART6, &IRQHandler_Serial1, 
	&serialEvent1, &_serialEvent1_default,
	CCM_CCGR3, CCM_CCGR3_LPUART6(CCM_CCGR_ON),
	#if defined(ARDUINO_TEENSY41)
	{{0,2, &IOMUXC_LPUART6_RX_SELECT_INPUT, 1}, {52, 2, &IOMUXC_LPUART6_RX_SELECT_INPUT, 0}},
	{{1,2, &IOMUXC_LPUART6_TX_SELECT_INPUT, 1}, {53, 2, &IOMUXC_LPUART6_TX_SELECT_INPUT, 0}},
	#else
	{{0,2, &IOMUXC_LPUART6_RX_SELECT_INPUT, 1}, {0xff, 0xff, nullptr, 0}},
	{{1,2, &IOMUXC_LPUART6_TX_SELECT_INPUT, 1}, {0xff, 0xff, nullptr, 0}},
	#endif
	0xff, // No CTS pin
	0, // No CTS
	IRQ_PRIORITY, 38, 24, // IRQ, rts_low_watermark, rts_high_watermark
	XBARA1_OUT_LPUART6_TRG_INPUT	// XBar Tigger 
};
HardwareSerial Serial1(&IMXRT_LPUART6, &UART6_Hardware, tx_buffer1, SERIAL1_TX_BUFFER_SIZE,
	rx_buffer1,  SERIAL1_RX_BUFFER_SIZE);

//void serialEvent1() __attribute__((weak));
//void serialEvent1() {Serial1.disableSerialEvents(); }		// No use calling this so disable if called...

// C wrapper functions to help take care of places that used to call these from standard C
void serial_print(const char *p)
{
	Serial1.write(p);
}

static void serial_phex1(uint32_t n)
{
	n &= 15;
	if (n < 10) {
		Serial1.write('0' + n);
	} else {
		Serial1.write('A' - 10 + n);
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

