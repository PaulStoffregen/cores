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

#include "usb_dev.h"
#include "usb_seremu.h"
#include "core_pins.h" // for yield()
//#include "HardwareSerial.h"

#ifdef SEREMU_INTERFACE // defined by usb_dev.h -> usb_desc.h

volatile uint8_t usb_seremu_transmit_flush_timer=0;

//static volatile uint8_t tx_noautoflush=0;

#define TRANSMIT_FLUSH_TIMEOUT	5   /* in milliseconds */


// get the next character, or -1 if nothing received
int usb_seremu_getchar(void)
{
	return -1;
}

// peek at the next character, or -1 if nothing received
int usb_seremu_peekchar(void)
{
	return -1;
}

// number of bytes available in the receive buffer
int usb_seremu_available(void)
{
	return 0;
}


// discard any buffered input
void usb_seremu_flush_input(void)
{
}



// When the PC isn't listening, how long do we wait before discarding data?  If this is
// too short, we risk losing data during the stalls that are common with ordinary desktop
// software.  If it's too long, we stall the user's program when no software is running.
#define TX_TIMEOUT_MSEC 30

// When we've suffered the transmit timeout, don't wait again until the computer
// begins accepting data.  If no software is running to receive, we'll just discard
// data as rapidly as Serial.print() can generate it, until there's something to
// actually receive it.
static uint8_t transmit_previous_timeout=0;


// transmit a character.  0 returned on success, -1 on error
int usb_seremu_putchar(uint8_t c)
{
	return usb_seremu_write(&c, 1);
}


int usb_seremu_write(const void *buffer, uint32_t size)
{
	return 0;
}

int usb_seremu_write_buffer_free(void)
{
	return 1;
}

void usb_seremu_flush_output(void)
{
}

void usb_seremu_flush_callback(void)
{
}

#endif // SEREMU_INTERFACE
