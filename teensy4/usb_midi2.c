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

#include "usb_midi2.h"
#include "usb_midi.h"

#if defined(MIDI_INTERFACE)

uint8_t usb_midi2_alt_setting = 0;

// MIDI 2.0 UMP Specification Table 4: message size per Message Type.
static uint8_t ump_words_for_mt(uint8_t mt)
{
	switch (mt) {
	case 0x0: case 0x1: case 0x2:                               return 1;
	case 0x3: case 0x4: case 0x8: case 0x9: case 0xA: case 0xD: return 2;
	case 0xB: case 0xC:                                         return 3;
	case 0x5: case 0xE: case 0xF:                               return 4;
	default:                                                    return 1;
	}
}

int usb_midi2_read_message(uint32_t *words, uint8_t *count)
{
	static uint32_t buf[4];
	static uint8_t  have = 0;
	static uint8_t  need = 0;

	for (;;) {
		if (usb_midi_available() == 0) return 0;
		uint32_t w = usb_midi_read_message();
		if (have == 0) {
			need = ump_words_for_mt((uint8_t)((w >> 28) & 0x0F));
		}
		if (have < 4) buf[have++] = w;
		if (have >= need) {
			uint8_t i;
			for (i = 0; i < have; i++) words[i] = buf[i];
			*count = have;
			have = 0;
			return 1;
		}
	}
}

int usb_midi2_write_message(const uint32_t *words, uint8_t count)
{
	// Whole message or nothing: a UMP split mid-message by a TX timeout is
	// a framing error on the wire, worse than a dropped message.
	return usb_midi_write_packed_n(words, count);
}

#ifdef __cplusplus
usb_midi2_class usbMIDI2;
#endif

#endif // MIDI_INTERFACE
