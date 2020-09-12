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

#ifndef SERIAL7_TX_BUFFER_SIZE
#define SERIAL7_TX_BUFFER_SIZE     40 // number of outgoing bytes to buffer
#endif
#ifndef SERIAL7_RX_BUFFER_SIZE
#define SERIAL7_RX_BUFFER_SIZE     64 // number of incoming bytes to buffer
#endif
#define IRQ_PRIORITY  64  // 0 = highest priority, 255 = lowest

void IRQHandler_Serial7()
{
	Serial7.IRQHandler();
}

// Serial7
static BUFTYPE tx_buffer7[SERIAL7_TX_BUFFER_SIZE];
static BUFTYPE rx_buffer7[SERIAL7_RX_BUFFER_SIZE];
uint8_t _serialEvent7_default __attribute__((weak)) PROGMEM = 0 ;

static HardwareSerial::hardware_t UART7_Hardware = {
	6, IRQ_LPUART7, &IRQHandler_Serial7, 
	&serialEvent7, &_serialEvent7_default,
	CCM_CCGR5, CCM_CCGR5_LPUART7(CCM_CCGR_ON),
	{{28,2, &IOMUXC_LPUART7_RX_SELECT_INPUT, 1}, {0xff, 0xff, nullptr, 0}},
	{{29,2, &IOMUXC_LPUART7_TX_SELECT_INPUT, 1}, {0xff, 0xff, nullptr, 0}},
	0xff, // No CTS pin
	0, // No CTS
	IRQ_PRIORITY, 38, 24, // IRQ, rts_low_watermark, rts_high_watermark
	XBARA1_OUT_LPUART7_TRG_INPUT
};
HardwareSerial Serial7(&IMXRT_LPUART7, &UART7_Hardware, tx_buffer7, SERIAL7_TX_BUFFER_SIZE,
	rx_buffer7,  SERIAL7_RX_BUFFER_SIZE);
