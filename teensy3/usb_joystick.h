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

#ifndef USBjoystick_h_
#define USBjoystick_h_

#include "usb_desc.h"

#if defined(JOYSTICK_INTERFACE)

#include <inttypes.h>

// C language implementation
#ifdef __cplusplus
extern "C" {
#endif
int usb_joystick_send(void);
extern uint32_t usb_joystick_data[(JOYSTICK_SIZE+3)/4];
#ifdef __cplusplus
}
#endif

// C++ interface
#ifdef __cplusplus
class usb_joystick_class
{
        public:
        void begin(void) { }
        void end(void) { }
#if JOYSTICK_SIZE == 12
	void button(uint8_t button, bool val) {
		if (--button >= 32) return;
		if (val) usb_joystick_data[0] |= (1 << button);
		else usb_joystick_data[0] &= ~(1 << button);
		if (!manual_mode) usb_joystick_send();
	}
	void X(unsigned int val) {
		if (val > 1023) val = 1023;
		usb_joystick_data[1] = (usb_joystick_data[1] & 0xFFFFC00F) | (val << 4);
		if (!manual_mode) usb_joystick_send();
	}
	void Y(unsigned int val) {
		if (val > 1023) val = 1023;
		usb_joystick_data[1] = (usb_joystick_data[1] & 0xFF003FFF) | (val << 14);
		if (!manual_mode) usb_joystick_send();
	}
	void position(unsigned int x, unsigned int y) {
		if (x > 1023) x = 1023;
		if (y > 1023) y = 1023;
		usb_joystick_data[1] = (usb_joystick_data[1] & 0xFFF00000)
			| (x << 4) | (y << 14);
		if (!manual_mode) usb_joystick_send();
	}
	void Z(unsigned int val) {
		if (val > 1023) val = 1023;
		usb_joystick_data[1] = (usb_joystick_data[1] & 0x00FFFFFF) | (val << 24);
		usb_joystick_data[2] = (usb_joystick_data[2] & 0xFFFFFFFC) | (val >> 8);
		if (!manual_mode) usb_joystick_send();
	}
	void Zrotate(unsigned int val) {
		if (val > 1023) val = 1023;
		usb_joystick_data[2] = (usb_joystick_data[2] & 0xFFFFF003) | (val << 2);
		if (!manual_mode) usb_joystick_send();
	}
	void sliderLeft(unsigned int val) {
		if (val > 1023) val = 1023;
		usb_joystick_data[2] = (usb_joystick_data[2] & 0xFFC00FFF) | (val << 12);
		if (!manual_mode) usb_joystick_send();
	}
	void sliderRight(unsigned int val) {
		if (val > 1023) val = 1023;
		usb_joystick_data[2] = (usb_joystick_data[2] & 0x003FFFFF) | (val << 22);
		if (!manual_mode) usb_joystick_send();
	}
	void slider(unsigned int val) {
		if (val > 1023) val = 1023;
		usb_joystick_data[2] = (usb_joystick_data[2] & 0x00000FFF)
			| (val << 12) | (val << 22);
		if (!manual_mode) usb_joystick_send();
	}
        inline void hat(int dir) {
                uint32_t val = 0;
                if (dir < 0) val = 15;
                else if (dir < 23) val = 0;
                else if (dir < 68) val = 1;
                else if (dir < 113) val = 2;
                else if (dir < 158) val = 3;
                else if (dir < 203) val = 4;
                else if (dir < 245) val = 5;
                else if (dir < 293) val = 6;
                else if (dir < 338) val = 7;
		usb_joystick_data[1] = (usb_joystick_data[1] & 0xFFFFFFF0) | val;
                if (!manual_mode) usb_joystick_send();
        }
#elif JOYSTICK_SIZE == 64
	void button(unsigned int num, bool val) {
		if (--num >= 128) return;
		uint32_t *p = usb_joystick_data + (num >> 5);
		num &= 0x1F;
		if (val) *p |= (1 << num);
		else *p &= ~(1 << num);
		if (!manual_mode) usb_joystick_send();
	}
	void X(unsigned int position) { analog16(0, position); }
	void Y(unsigned int position) { analog16(1, position); }
	void Z(unsigned int position) { analog16(2, position); }
	void Xrotate(unsigned int position) { analog16(3, position); }
	void Yrotate(unsigned int position) { analog16(4, position); }
	void Zrotate(unsigned int position) { analog16(5, position); }
	void slider(unsigned int num, unsigned int position) {
		if (--num >= 17) return;
		analog16(num + 6, position);
	}
        inline void hat(unsigned int num, int angle) {
		uint32_t val=15;
		if (angle > 0 && angle < 23) val = 0;
		else if (angle < 68) val = 1;
		else if (angle < 113) val = 2;
		else if (angle < 158) val = 3;
		else if (angle < 203) val = 4;
		else if (angle < 245) val = 5;
		else if (angle < 293) val = 6;
		else if (angle < 338) val = 7;
		else if (angle < 360) val = 0;
		uint32_t *p = usb_joystick_data;
		switch(num) {
		  case 1:
			p[15] = (p[15] & 0xFFF0FFFF) | (val << 16); break;
		  case 2:
			p[15] = (p[15] & 0xFF0FFFFF) | (val << 20); break;
		  case 3:
			p[15] = (p[15] & 0xF0FFFFFF) | (val << 24); break;
		  case 4:
			p[15] = (p[15] & 0x0FFFFFFF) | (val << 28); break;
		  default:
			return;
		}
		if (!manual_mode) usb_joystick_send();
        }
#endif
	void useManualSend(bool mode) {
		manual_mode = mode;
	}
	void send_now(void) {
		usb_joystick_send();
	}
	private:
	static uint8_t manual_mode;
#if JOYSTICK_SIZE == 64
	void analog16(unsigned int num, unsigned int value) {
		if (value > 0xFFFF) value = 0xFFFF;
		uint16_t *p = (uint16_t *)(&usb_joystick_data[4]);
		p[num] = value;
                if (!manual_mode) usb_joystick_send();
	}
#endif
};
extern usb_joystick_class Joystick;

#endif // __cplusplus

#endif // JOYSTICK_INTERFACE

#endif // USBjoystick_h_

