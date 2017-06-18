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

#include "kinetis.h"
#include "ser_print.h"

#ifdef KINETISL

// Simple polling-only Serial1 support for Teensy-LC

// this is really only useful for extremely low-level troubleshooting

void ser_write(uint8_t c)
{
        while ((UART0_S1 & UART_S1_TDRE) == 0) /* wait */ ;
        UART0_D = c;
}

void ser_print(const char *p)
{
        while (*p) {
                char c = *p++;
                if (c == '\n') ser_write('\r');
                ser_write(c);
        }
}

static void ser_print_hex1(unsigned int n)
{
        n &= 15;
        if (n < 10) {
                ser_write('0' + n);
        } else {
                ser_write('A' - 10 + n);
        }
}

void ser_print_hex(unsigned int n)
{
	ser_print_hex1(n >> 4);
	ser_print_hex1(n);
}

void ser_print_hex32(unsigned int n)
{
	ser_print_hex(n >> 24);
	ser_print_hex(n >> 16);
	ser_print_hex(n >> 8);
	ser_print_hex(n);
}

#endif
