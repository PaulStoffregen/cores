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

#pragma once

#include <Printable.h>
#include <WString.h>

class CrashReportClass: public Printable {
public:
	virtual size_t printTo(Print& p) const;
	static void clear();
	operator bool();
	static void breadcrumb(unsigned int num, unsigned int value) {
		// crashreport_breadcrumbs_struct occupies exactly 1 cache row
		volatile struct crashreport_breadcrumbs_struct *bc =
			(struct crashreport_breadcrumbs_struct *)0x2027FFC0;
		if (num >= 1 && num <= 6) {
			num--;
			bc->value[num] = value;
			bc->bitmask |= (1 << num);
			bc->checksum = checksum(bc, 28);
			arm_dcache_flush((void *)bc, sizeof(struct crashreport_breadcrumbs_struct));
		}
	}
	static uint32_t checksum(volatile const void *data, int len) {
		volatile const uint16_t *p = (volatile const uint16_t *)data;
		uint32_t a=1, b=0; // Adler Fletcher kinda, len < 720 bytes
		while (len > 0) {
			a += *p++;
			b += a;
			len -= 2;
		}
		a = a & 65535;
		b = b & 65535;
		return a | (b << 16);
	}
};

extern CrashReportClass CrashReport;
