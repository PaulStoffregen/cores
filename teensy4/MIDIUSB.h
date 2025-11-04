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

#ifndef MIDIUSB_h
#define MIDIUSB_h

// For compatibility with Arduino's MIDIUSB library

#include "usb_midi.h"

#ifdef __cplusplus
#if !defined(USB_MIDI) && !defined(USB_MIDI4) && !defined(USB_MIDI16) && !defined(USB_MIDI_SERIAL) && !defined(USB_MIDI4_SERIAL) && !defined(USB_MIDI16_SERIAL) && !defined(USB_MIDI_AUDIO_SERIAL) && !defined(USB_MIDI16_AUDIO_SERIAL) && !defined(USB_EVERYTHING)
#error "Please select MIDI in Tools > USB Type to use MIDIUSB.h"
#endif

typedef struct {
 union {
  struct {
	uint8_t header;
	uint8_t byte1;
	uint8_t byte2;
	uint8_t byte3;
  };
	uint32_t word;
 };
} midiEventPacket_t;


class MIDI_
{
public:
	constexpr MIDI_(void) { }
	uint32_t available(void) {
		return usb_midi_available();
	}
	midiEventPacket_t read(void) {
		midiEventPacket_t event;
		event.word = usb_midi_read_message();
		return event;
	}
	void flush(void) {
		usb_midi_flush_output();
	}
	void sendMIDI(midiEventPacket_t event) {
		usb_midi_write_packed(event.word);
	}
	size_t write(const uint8_t *buffer, size_t size) {
		// TODO - is this really needed?
		return 0;
	}
	operator bool() {
		// TODO - is this really needed?
		return true;
	}
};
extern MIDI_ MidiUSB;

#endif // __cplusplus
#endif // MIDIUSB_h
