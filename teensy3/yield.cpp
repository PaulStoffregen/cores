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

#include <Arduino.h>
#include "EventResponder.h"

void yield(void) __attribute__ ((weak));
void yield(void)
{
	static uint8_t running=0;

	if (running) return; // TODO: does this need to be atomic?
	running = 1;
	if (Serial.available()) serialEvent();
#if defined(USB_DUAL_SERIAL) || defined(USB_TRIPLE_SERIAL)
	if (SerialUSB1.available()) serialEventUSB1();
#endif
#ifdef USB_TRIPLE_SERIAL
	if (SerialUSB2.available()) serialEventUSB2();
#endif
	if (Serial1.available()) serialEvent1();
	if (Serial2.available()) serialEvent2();
	if (Serial3.available()) serialEvent3();
#ifdef HAS_KINETISK_UART3
	if (Serial4.available()) serialEvent4();
#endif
#ifdef HAS_KINETISK_UART4
	if (Serial5.available()) serialEvent5();
#endif
#if defined(HAS_KINETISK_UART5) || defined (HAS_KINETISK_LPUART0)
	if (Serial6.available()) serialEvent6();
#endif
	running = 0;
	EventResponder::runFromYield();
};
