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
#if defined(__IMXRT1052__)   

#ifndef SERIAL8_TX_BUFFER_SIZE
#define SERIAL8_TX_BUFFER_SIZE     40 // number of outgoing bytes to buffer
#endif
#ifndef SERIAL8_RX_BUFFER_SIZE
#define SERIAL8_RX_BUFFER_SIZE     64 // number of incoming bytes to buffer
#endif
#define IRQ_PRIORITY  64  // 0 = highest priority, 255 = lowest

void IRQHandler_Serial8()
{
	Serial8.IRQHandler();
}

void serial_event_check_serial8()
{
	if (Serial8.available()) serialEvent8();
}



// Serial8
static BUFTYPE tx_buffer8[SERIAL8_TX_BUFFER_SIZE];
static BUFTYPE rx_buffer8[SERIAL8_RX_BUFFER_SIZE];

static HardwareSerial::hardware_t UART5_Hardware = {
	7, IRQ_LPUART5, &IRQHandler_Serial8, &serial_event_check_serial8,
	CCM_CCGR3, CCM_CCGR3_LPUART5(CCM_CCGR_ON),
	{{30,2, &IOMUXC_LPUART5_RX_SELECT_INPUT, 0}, {0xff, 0xff, nullptr, 0}},
	{{31,2, nullptr, 0}, {0xff, 0xff, nullptr, 0}},
	0xff, // No CTS pin
	0, // No CTS
	IRQ_PRIORITY, 38, 24, // IRQ, rts_low_watermark, rts_high_watermark
};
HardwareSerial Serial8(&IMXRT_LPUART5, &UART5_Hardware, tx_buffer8, SERIAL8_TX_BUFFER_SIZE,
	rx_buffer8,  SERIAL8_RX_BUFFER_SIZE);

void serialEvent8() __attribute__((weak));
void serialEvent8() {Serial8.disableSerialEvents(); }		// No use calling this so disable if called...
#endif
