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
#if defined(__IMXRT1062__) && (defined(ARDUINO_TEENSY41) || defined(SERIAL8_RX_PINS))

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

#ifndef SERIAL8_RX_PINS 
#define SERIAL8_UART_ADDR IMXRT_LPUART5_ADDRESS
#define SERIAL8_LPUART IRQ_LPUART5, CCM_CCGR3, CCM_CCGR3_LPUART5(CCM_CCGR_ON), XBARA1_OUT_LPUART5_TRG_INPUT
#define SERIAL8_CTS_PIN 50, 2 
#define SERIAL8_RX_PINS {{34,1, &IOMUXC_LPUART5_RX_SELECT_INPUT, 1}, {48, 2, &IOMUXC_LPUART5_RX_SELECT_INPUT, 0}}
#define SERIAL8_TX_PINS {{35,1, &IOMUXC_LPUART5_TX_SELECT_INPUT, 1}, {0xff, 0xff, nullptr, 0}}
#endif


// Serial8
static BUFTYPE tx_buffer8[SERIAL8_TX_BUFFER_SIZE];
static BUFTYPE rx_buffer8[SERIAL8_RX_BUFFER_SIZE];

static HardwareSerialIMXRT::hardware_t Serial8_Hardware = {
	7, 
	&IRQHandler_Serial8, 
	&serialEvent8,
	IRQ_PRIORITY, 38, 24, // IRQ, rts_low_watermark, rts_high_watermark
	SERIAL8_LPUART, SERIAL8_RX_PINS, SERIAL8_TX_PINS, SERIAL8_CTS_PIN
};
HardwareSerialIMXRT Serial8(IMXRT_LPUART5_ADDRESS, &Serial8_Hardware, tx_buffer8,
	SERIAL8_TX_BUFFER_SIZE, rx_buffer8, SERIAL8_RX_BUFFER_SIZE);
#endif

