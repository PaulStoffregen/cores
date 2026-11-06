/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2026 PJRC.COM, LLC.
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

#ifndef USBmidi2_h_
#define USBmidi2_h_

#include "usb_desc.h"

#if defined(MIDI_INTERFACE)

#include <inttypes.h>

// MIDI 2.0 Universal MIDI Packet (UMP) raw I/O for the USB MIDI 2.0
// device class. See teensy4/usb_desc.c for the Alternate Setting 1
// descriptor and teensy4/usb.c for the SET/GET_INTERFACE handlers.
// Application-level UMP processing (parsing, MIDI-CI, Property
// Exchange, Stream Discovery, Flex Data) is intentionally outside
// the core. This file exposes only the wire-level primitives.

// C language implementation
#ifdef __cplusplus
extern "C" {
#endif
// 0 = Alternate Setting 0 (MIDI 1.0 wire format)
// 1 = Alternate Setting 1 (MIDI 2.0 UMP wire format)
// Updated by SET_INTERFACE in usb.c.
extern uint8_t usb_midi2_alt_setting;

// Read one UMP message from the endpoint into words[0..count-1].
// Returns 1 when a full message was assembled, 0 when no data is
// available or only a partial message has arrived. count is set to
// the message size (1, 2, 3 or 4 words) per MIDI 2.0 UMP Specification
// Table 4.
int usb_midi2_read_message(uint32_t *words, uint8_t *count);

// Write count UMP words to the endpoint without protocol translation.
// count must match the size declared by the message type.
int usb_midi2_write_message(const uint32_t *words, uint8_t count);
#ifdef __cplusplus
}
#endif

// C++ interface
#ifdef __cplusplus
class usb_midi2_class
{
public:
	void begin(void) { }
	void end(void) { }
	uint8_t altSetting(void) __attribute__((always_inline)) {
		return usb_midi2_alt_setting;
	}
	int read(uint32_t *words, uint8_t *count) __attribute__((always_inline)) {
		return usb_midi2_read_message(words, count);
	}
	int write(const uint32_t *words, uint8_t count) __attribute__((always_inline)) {
		return usb_midi2_write_message(words, count);
	}
};
extern usb_midi2_class usbMIDI2;
#endif // __cplusplus

#endif // MIDI_INTERFACE

#endif // USBmidi2_h_
