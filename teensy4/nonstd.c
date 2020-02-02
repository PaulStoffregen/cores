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

#include "avr_functions.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>


char * ultoa(unsigned long val, char *buf, int radix)
{
	unsigned digit;
	int i=0, j;
	char t;

	while (1) {
		digit = val % radix;
		buf[i] = ((digit < 10) ? '0' + digit : 'A' + digit - 10);
		val /= radix;
		if (val == 0) break;
		i++;
	}
	buf[i + 1] = 0;
	for (j=0; j < i; j++, i--) {
		t = buf[j];
		buf[j] = buf[i];
		buf[i] = t;
	}
	return buf;
}

char * ltoa(long val, char *buf, int radix)
{
	if (val >= 0) {
		return ultoa(val, buf, radix);
	} else {
		buf[0] = '-';
		ultoa(-val, buf + 1, radix);
		return buf;
	}
}

#define DTOA_UPPER 0x04

char * fcvtf(float, int, int *, int *);
int isnanf (float x);
int isinff (float x);

char * dtostrf(float val, int width, unsigned int precision, char *buf)
{
	int decpt, sign, reqd, pad;
	const char *s, *e;
	char *p;

	int awidth = abs(width);
	if (isnanf(val)) {
		int ndigs = (val<0) ? 4 : 3;
		awidth = (awidth > ndigs) ? awidth - ndigs : 0;
		if (width<0) {
			while (awidth) {
				*buf++ = ' ';
				awidth--;
			}
		}
		if (copysignf(1.0f, val)<0) *buf++ = '-';
		if (DTOA_UPPER) {
			*buf++ = 'N';  *buf++ = 'A';  *buf++ = 'N';
		} else {
			*buf++ = 'n';  *buf++ = 'a';  *buf++ = 'n';
		}
		while (awidth) {
			*buf++ = ' ';
			awidth--;
		}
		*buf = 0;
		return buf;
	}
	if (isinff(val)) {
		int ndigs = (val<0) ? 4 : 3;
		awidth = (awidth > ndigs) ? awidth - ndigs : 0;
		if (width<0) {
			while (awidth) {
				*buf++ = ' ';
				awidth--;
			}
		}
		if (val<0) *buf++ = '-';
		if (DTOA_UPPER) {
			*buf++ = 'I';  *buf++ = 'N';  *buf++ = 'F';
		} else {
			*buf++ = 'i';  *buf++ = 'n';  *buf++ = 'f';
		}
		while (awidth) {
			*buf++ = ' ';
			awidth--;
		}
		*buf = 0;
		return buf;
	}

	s = fcvtf(val, precision, &decpt, &sign);

	// if only 1 digit in output
	if (precision == 0 && decpt == 0) {
		// round and move decimal point
		s = (*s < '5') ? "0" : "1";
		decpt++;
	}

	// if all zeros, limit to precision
	if (-decpt  > (int)precision) {
		s = "0";
		decpt = -precision;
	}

	reqd = strlen(s);

	// add 1 for decimal point
	if (reqd > decpt) reqd++;

	// add 1 for zero in front of decimal point
	if (decpt == 0) reqd++;

	// if leading zeros after decimal point
	if (decpt < 0 && precision > 0) {
		// ensure enough trailing zeros, add 2 for '0.'
		reqd = precision + 2;

		if (strlen(s) > precision + decpt) {
			// bug in fcvtf. e.g. 0.012, precision 2 should return 1 instead of 12.
			// However, 1.2, precision 0 returns correct value. So shift values so
			// that decimal point is after the first digit, then convert again

			int newPrecision = precision;
			int newDecimalPoint;

			// shift decimal point
			while (newPrecision > 0) {
				val *= 10.0;
				newPrecision--;
			}

			// round after accounting for leading 0's
			s = fcvtf(val, newPrecision, &newDecimalPoint, &sign);

			// if rounded up to new digit (e.g. 0.09 to 0.1), move decimal point
			if (newDecimalPoint - decpt == precision + 1) decpt++;
		}
	}

	// add 1 for sign if negative
	if (sign) reqd++;

	p = buf;
	e = p + reqd;
	pad = width - reqd;
	if (pad > 0) {
		e += pad;
		while (pad-- > 0) *p++ = ' ';
	}
	if (sign) *p++ = '-';
	if (decpt == 0 && precision > 0) {
		*p++ = '0';
		*p++ = '.';
	}
	else if (decpt < 0 && precision > 0) {
		*p++ = '0';
		*p++ = '.';
		// print leading zeros
		while ( decpt < 0 ) {
			decpt++;
			*p++ = '0';
		}
	}
	// print digits
	while (p < e) {
		*p++ = *s++;
		if (p == e) break;
		if (--decpt == 0) *p++ = '.';
	}
	if (width < 0) {
		pad = (reqd + width) * -1;
		while (pad-- > 0) *p++ = ' ';
	}
	*p = 0;

	//char format[20];
	//sprintf(format, "%%%d.%df", width, precision);
	//sprintf(buf, format, val);
	return buf;
}

