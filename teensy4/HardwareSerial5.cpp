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

#ifndef SERIAL5_TX_BUFFER_SIZE
#define SERIAL5_TX_BUFFER_SIZE     40 // number of outgoing bytes to buffer
#endif
#ifndef SERIAL5_RX_BUFFER_SIZE
#define SERIAL5_RX_BUFFER_SIZE     64 // number of incoming bytes to buffer
#endif
#define IRQ_PRIORITY  64  // 0 = highest priority, 255 = lowest


void IRQHandler_Serial5()
{
	Serial5.IRQHandler();
}
// Serial5
static BUFTYPE tx_buffer5[SERIAL5_TX_BUFFER_SIZE];
static BUFTYPE rx_buffer5[SERIAL5_RX_BUFFER_SIZE];
uint8_t _serialEvent5_default __attribute__((weak)) PROGMEM = 0 ;

static HardwareSerial::hardware_t UART8_Hardware = {
	4, IRQ_LPUART8, &IRQHandler_Serial5, 
	&serialEvent5, &_serialEvent5_default,
	CCM_CCGR6, CCM_CCGR6_LPUART8(CCM_CCGR_ON),
	#if defined(ARDUINO_TEENSY41)
	{{21,2, &IOMUXC_LPUART8_RX_SELECT_INPUT, 1}, {46, 2, &IOMUXC_LPUART8_RX_SELECT_INPUT, 0}},
	{{20,2, &IOMUXC_LPUART8_TX_SELECT_INPUT, 1}, {47, 2, &IOMUXC_LPUART8_TX_SELECT_INPUT, 0}},
	43, //  CTS pin
	2, //  CTS
	#else
	{{21,2, &IOMUXC_LPUART8_RX_SELECT_INPUT, 1}, {38, 2, &IOMUXC_LPUART8_RX_SELECT_INPUT, 0}},
	{{20,2, &IOMUXC_LPUART8_TX_SELECT_INPUT, 1}, {39, 2, &IOMUXC_LPUART8_TX_SELECT_INPUT, 0}},
	35, //  CTS pin
	2, //  CTS
	#endif
	IRQ_PRIORITY, 38, 24, // IRQ, rts_low_watermark, rts_high_watermark
	XBARA1_OUT_LPUART8_TRG_INPUT
};
HardwareSerial Serial5(&IMXRT_LPUART8, &UART8_Hardware, tx_buffer5, SERIAL5_TX_BUFFER_SIZE,
	rx_buffer5,  SERIAL5_RX_BUFFER_SIZE);
