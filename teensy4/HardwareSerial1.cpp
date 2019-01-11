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

void serial_event_check_serial1()
{
	if (Serial1.available()) serialEvent1();
}

// Serial1
static BUFTYPE tx_buffer1[SERIAL1_TX_BUFFER_SIZE];
static BUFTYPE rx_buffer1[SERIAL1_RX_BUFFER_SIZE];

const HardwareSerial::hardware_t UART6_Hardware = {
	0, IRQ_LPUART6, &IRQHandler_Serial1, &serial_event_check_serial1,
	CCM_CCGR3, CCM_CCGR3_LPUART6(CCM_CCGR_ON),
	0, //IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_03, // pin 0
	1, //IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_02, // pin 1
	0xff, // No CTS pin
	IOMUXC_LPUART6_RX_SELECT_INPUT,
	2, // page 473
	2, // page 472
	0, // No CTS
	1, // page 861
	IRQ_PRIORITY, 38, 24, // IRQ, rts_low_watermark, rts_high_watermark
};
HardwareSerial Serial1(&IMXRT_LPUART6, &UART6_Hardware, tx_buffer1, SERIAL1_TX_BUFFER_SIZE,
	rx_buffer1,  SERIAL1_RX_BUFFER_SIZE);

void serialEvent1() __attribute__((weak));
void serialEvent1() {Serial1.disableSerialEvents(); }		// No use calling this so disable if called...
