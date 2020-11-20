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

#include "HardwareSerial.h"
#include "core_pins.h"
#include "Arduino.h"

// define our static objects
HardwareSerial 	*HardwareSerial::s_serials_with_serial_events[CNT_HARDWARE_SERIAL];
uint8_t 		HardwareSerial::s_count_serials_with_serial_events = 0;

// simple helper function that add us to the list of Serial ports that have
// their own serialEvent code defined that needs to be called at yield.
void HardwareSerial::addToSerialEventsList() {
	for (uint8_t i = 0; i < s_count_serials_with_serial_events; i++) {
		if (s_serials_with_serial_events[i] == this) return; // already in the list.
	}

	s_serials_with_serial_events[s_count_serials_with_serial_events++] = this;
	yield_active_check_flags |= YIELD_CHECK_HARDWARE_SERIAL;
}

