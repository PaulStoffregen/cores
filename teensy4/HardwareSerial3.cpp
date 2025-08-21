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

#ifndef SERIAL3_TX_BUFFER_SIZE
#define SERIAL3_TX_BUFFER_SIZE     40 // number of outgoing bytes to buffer
#endif
#ifndef SERIAL3_RX_BUFFER_SIZE
#define SERIAL3_RX_BUFFER_SIZE     64 // number of incoming bytes to buffer
#endif
#define IRQ_PRIORITY  64  // 0 = highest priority, 255 = lowest

void IRQHandler_Serial3()
{
	Serial3.IRQHandler();
}

#ifndef SERIAL3_RX_PINS 
#define SERIAL3_UART_ADDR IMXRT_LPUART2_ADDRESS
#define SERIAL3_LPUART IRQ_LPUART2, CCM_CCGR0, CCM_CCGR0_LPUART2(CCM_CCGR_ON), XBARA1_OUT_LPUART2_TRG_INPUT
#define SERIAL3_CTS_PIN 19, 2 
#define SERIAL3_RX_PINS {{15,2, &IOMUXC_LPUART2_RX_SELECT_INPUT, 1}, {0xff, 0xff, nullptr, 0}}
#define SERIAL3_TX_PINS {{14,2, &IOMUXC_LPUART2_TX_SELECT_INPUT, 1}, {0xff, 0xff, nullptr, 0}}
#endif




// Serial3
static BUFTYPE tx_buffer3[SERIAL3_TX_BUFFER_SIZE];
static BUFTYPE rx_buffer3[SERIAL3_RX_BUFFER_SIZE];

const HardwareSerialIMXRT::hardware_t SERIAL3_Hardware = {
	2, 
	&IRQHandler_Serial3, 
	&serialEvent3,
	IRQ_PRIORITY, 38, 24, // IRQ, rts_low_watermark, rts_high_watermark
	// Stuff that can be overwritten easily by variant
	SERIAL3_LPUART, SERIAL3_RX_PINS, SERIAL3_TX_PINS, SERIAL3_CTS_PIN
};
HardwareSerialIMXRT Serial3(SERIAL3_UART_ADDR, &SERIAL3_Hardware, tx_buffer3,
	SERIAL3_TX_BUFFER_SIZE, rx_buffer3, SERIAL3_RX_BUFFER_SIZE);

