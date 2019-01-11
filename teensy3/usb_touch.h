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

#ifndef USBtouchscreen_h_
#define USBtouchscreen_h_

#include "usb_desc.h"

#if defined(MULTITOUCH_INTERFACE)

#include <inttypes.h>

// C language implementation
#ifdef __cplusplus
extern "C" {
#endif
void usb_touchscreen_press(uint8_t finger, uint32_t x, uint32_t y, uint32_t pressure);
void usb_touchscreen_release(uint8_t finger);
void usb_touchscreen_update_callback(void);
#ifdef __cplusplus
}
#endif

// C++ interface
#ifdef __cplusplus
class usb_touchscreen_class
{
        public:
        void begin(void) { }
        void end(void) { }
	void press(uint8_t finger, uint32_t x, uint32_t y, uint32_t pressure=128) {
		usb_touchscreen_press(finger, x, y, pressure);
	}
	void release(uint8_t finger) {
		usb_touchscreen_release(finger);
	}
};
extern usb_touchscreen_class TouchscreenUSB;

#endif // __cplusplus

#endif // MULTITOUCH_INTERFACE

#endif // USBtouchscreen_h_

