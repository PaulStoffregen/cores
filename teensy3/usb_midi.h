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

#ifndef USBmidi_h_
#define USBmidi_h_

#include "usb_desc.h"

#if defined(MIDI_INTERFACE)

#include <inttypes.h>

/*
These were originally meant to allow programs written for
Francois Best's MIDI library to be easily used with
Teensy's usbMIDI which implements the same API.  However,
the MIDI library definitions have changed, so these names
now conflict.  They've never been documented (the PJRC web
page documents usbMIDI.getType() in numbers) so they are
now commented out so usbMIDI and the MIDI library can be
used together without conflict.
#define NoteOff 0
#define NoteOn 1
#define AfterTouchPoly 2
#define ControlChange 3
#define ProgramChange 4
#define AfterTouchChannel 5
#define PitchBend 6
#define SystemExclusive 7
*/

// maximum sysex length we can receive
#if defined(__MKL26Z64__) || defined(__MK20DX128__)
#define USB_MIDI_SYSEX_MAX  60
#else
#define USB_MIDI_SYSEX_MAX 290
#endif

// C language implementation
#ifdef __cplusplus
extern "C" {
#endif
void usb_midi_write_packed(uint32_t n);
void usb_midi_send_sysex(const uint8_t *data, uint32_t length, uint8_t cable);
void usb_midi_flush_output(void);
int usb_midi_read(uint32_t channel);
uint32_t usb_midi_available(void);
uint32_t usb_midi_read_message(void);
extern uint8_t usb_midi_msg_cable;
extern uint8_t usb_midi_msg_channel;
extern uint8_t usb_midi_msg_type;
extern uint8_t usb_midi_msg_data1;
extern uint8_t usb_midi_msg_data2;
extern uint8_t usb_midi_msg_sysex[USB_MIDI_SYSEX_MAX];
extern uint16_t usb_midi_msg_sysex_len;
extern void (*usb_midi_handleNoteOff)(uint8_t ch, uint8_t note, uint8_t vel);
extern void (*usb_midi_handleNoteOn)(uint8_t ch, uint8_t note, uint8_t vel);
extern void (*usb_midi_handleVelocityChange)(uint8_t ch, uint8_t note, uint8_t vel);
extern void (*usb_midi_handleControlChange)(uint8_t ch, uint8_t control, uint8_t value);
extern void (*usb_midi_handleProgramChange)(uint8_t ch, uint8_t program);
extern void (*usb_midi_handleAfterTouch)(uint8_t ch, uint8_t pressure);
extern void (*usb_midi_handlePitchChange)(uint8_t ch, int pitch);
extern void (*usb_midi_handleSysEx)(const uint8_t *data, uint16_t length, uint8_t complete);
extern void (*usb_midi_handleRealTimeSystem)(uint8_t rtb);
extern void (*usb_midi_handleTimeCodeQuarterFrame)(uint16_t data);

#ifdef __cplusplus
}
#endif

// To test receiving on Linux, run "aseqdump -l" to list sequencer devices.
//
//    Port    Client name                      Port name
//     0:0    System                           Timer
//     0:1    System                           Announce
//    14:0    Midi Through                     Midi Through Port-0
//    24:0    Teensy MIDI                      Teensy MIDI MIDI 1
//    28:0    AKM320                           AKM320 MIDI 1
//
// Then run "aseqdump -p 24:0" to view the MIDI messages.
//
//    Waiting for data. Press Ctrl+C to end.
//    Source  Event                  Ch  Data
//     24:0   Note on                 0, note 61, velocity 99
//     24:0   Note off                0, note 61, velocity 0
//     24:0   Note on                 0, note 62, velocity 99
//     24:0   Note off                0, note 62, velocity 0
//     24:0   Note on                 0, note 64, velocity 99
//     24:0   Note off                0, note 64, velocity 0

// C++ interface
#ifdef __cplusplus
class usb_midi_class
{
        public:
        void begin(void) { }
        void end(void) { }
        void sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
		send(0x80, note, velocity, channel, cable);
	};
        void sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
		send(0x90, note, velocity, channel, cable);
	};
        void sendPolyPressure(uint8_t note, uint8_t pressure, uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
		send(0xA0, note, pressure, channel, cable);
	};
	void sendAfterTouch(uint8_t note, uint8_t pressure, uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
		send(0xA0, note, pressure, channel, cable);
	};
        void sendControlChange(uint8_t control, uint8_t value, uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
		send(0xB0, control, value, channel, cable);
	};
        void sendProgramChange(uint8_t program, uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
		send(0xC0, program, 0, channel, cable);
	};
        void sendAfterTouch(uint8_t pressure, uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
		send(0xD0, pressure, 0, channel, cable);
	};
        void sendPitchBend(uint16_t value, uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
		// MIDI 4.3 takes -8192 to +8191.  We take 0 to 16383
		// MIDI 4.3 also has version that takes float -1.0 to +1.0
		send(0xE0, value, value >> 7, channel, cable);
	};
        void sendSysEx(uint32_t length, const uint8_t *data, bool hasTerm=false, uint8_t cable=0) __attribute__((always_inline)) {
		if (cable >= MIDI_NUM_CABLES) return;
		if (hasTerm) {
			if (length > 2) {
				usb_midi_send_sysex(data + 1, length - 2, cable);
			}
		} else {
			usb_midi_send_sysex(data, length, cable);
		}
	};
	void sendRealTime(uint8_t type, uint8_t cable=0) __attribute__((always_inline)) __attribute__((always_inline)) {
		switch (type) {
			case 0xF8: // Clock
			case 0xFA: // Start
			case 0xFB: // Continue
			case 0xFC: // Stop
			case 0xFE: // ActiveSensing
			case 0xFF: // SystemReset
				send(type, 0, 0, 0, cable);
				break;
			default: // Invalid Real Time marker
				break;
		}
	};
	void sendTimeCodeQuarterFrame(uint8_t type, uint8_t value, uint8_t cable=0) __attribute__((always_inline)) __attribute__((always_inline)) {
		send(0xF1, ((type & 0x07) << 4) | (value & 0x0F), 0, 0, cable);
	};
        //void sendTimeCodeQuarterFrame(uint8_t data, uint8_t cable=0) __attribute__((always_inline)) {
		// MIDI 4.3 has this, but we can't implement with cable param
		//send(0xF1, data, 0, 0, cable);
	//};
	void sendSongPosition(uint16_t beats, uint8_t cable=0) __attribute__((always_inline)) {
		send(0xF2, beats, beats >> 7, 0, cable);
	};
	void sendSongSelect(uint8_t song, uint8_t cable=0) __attribute__((always_inline)) {
		send(0xF4, song, 0, 0, cable);
	};
	void sendTuneRequest(uint8_t cable=0) __attribute__((always_inline)) {
		send(0xF6, 0, 0, 0, cable);
	};
	void beginRpn(uint16_t number, uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
		sendControlChange(101, number >> 7, channel, cable);
		sendControlChange(100, number, channel, cable);
	};
	void sendRpnValue(uint16_t value, uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
		sendControlChange(6, value >> 7, channel, cable);
		sendControlChange(38, value, channel, cable);
	};
	void sendRpnValue(uint8_t msb, uint8_t lsb, uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
		sendControlChange(6, msb, channel, cable);
		sendControlChange(38, lsb, channel, cable);
	};
	void sendRpnIncrement(uint8_t amount, uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
		sendControlChange(96, amount, channel, cable);
	};
	void sendRpnDecrement(uint8_t amount, uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
		sendControlChange(97, amount, channel, cable);
	};
	void endRpn(uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
		sendControlChange(101, 0x7F, channel, cable);
		sendControlChange(100, 0x7F, channel, cable);
	};
	void beginNrpn(uint16_t number, uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
		sendControlChange(99, number >> 7, channel, cable);
		sendControlChange(98, number, channel, cable);
	}
	void sendNrpnValue(uint16_t value, uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
		sendControlChange(6, value >> 7, channel, cable);
		sendControlChange(38, value, channel, cable);
	}
	void sendNrpnValue(uint8_t msb, uint8_t lsb, uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
		sendControlChange(6, msb, channel, cable);
		sendControlChange(38, lsb, channel, cable);
	}
	void sendNrpnIncrement(uint8_t amount, uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
		sendControlChange(96, amount, channel, cable);
	}
	void sendNrpnDecrement(uint8_t amount, uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
		sendControlChange(97, amount, channel, cable);
	}
	void endNrpn(uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
		sendControlChange(99, 0x7F, channel, cable);
		sendControlChange(98, 0x7F, channel, cable);
	}
	void send(uint8_t type, uint8_t data1, uint8_t data2, uint8_t channel, uint8_t cable) __attribute__((always_inline)) {
		if (cable >= MIDI_NUM_CABLES) return;
		if (type < 0xF0) {
			if (type < 0x80) return;
			type &= 0xF0;
			usb_midi_write_packed((type << 8) | (type >> 4) | ((cable & 0x0F) << 4)
			  | (((channel - 1) & 0x0F) << 8) | ((data1 & 0x7F) << 16)
			  | ((data2 & 0x7F) << 24));
		} else {
			usb_midi_write_packed((type << 8) | 0x0F | ((cable & 0x0F) << 4)
			  | ((data1 & 0x7F) << 16) | ((data2 & 0x7F) << 24));
		}
	};
        void send_now(void) __attribute__((always_inline)) {
		usb_midi_flush_output();
	};
        uint8_t analog2velocity(uint16_t val, uint8_t range);
        bool read(uint8_t channel=0) __attribute__((always_inline)) {
		return usb_midi_read(channel);
	};
        inline uint8_t getType(void) __attribute__((always_inline)) {
                return usb_midi_msg_type;
        };
        inline uint8_t getCable(void) __attribute__((always_inline)) {
                return usb_midi_msg_cable;
        };
        inline uint8_t getChannel(void) __attribute__((always_inline)) {
                return usb_midi_msg_channel;
        };
        inline uint8_t getData1(void) __attribute__((always_inline)) {
                return usb_midi_msg_data1;
        };
        inline uint8_t getData2(void) __attribute__((always_inline)) {
                return usb_midi_msg_data2;
        };
        inline uint8_t * getSysExArray(void) __attribute__((always_inline)) {
                return usb_midi_msg_sysex;
        };
        inline void setHandleNoteOff(void (*fptr)(uint8_t channel, uint8_t note, uint8_t velocity)) {
                usb_midi_handleNoteOff = fptr;
        };
        inline void setHandleNoteOn(void (*fptr)(uint8_t channel, uint8_t note, uint8_t velocity)) {
                usb_midi_handleNoteOn = fptr;
        };
        inline void setHandleVelocityChange(void (*fptr)(uint8_t channel, uint8_t note, uint8_t velocity)) {
                usb_midi_handleVelocityChange = fptr;
        };
        inline void setHandleControlChange(void (*fptr)(uint8_t channel, uint8_t control, uint8_t value)) {
                usb_midi_handleControlChange = fptr;
        };
        inline void setHandleProgramChange(void (*fptr)(uint8_t channel, uint8_t program)) {
                usb_midi_handleProgramChange = fptr;
        };
        inline void setHandleAfterTouch(void (*fptr)(uint8_t channel, uint8_t pressure)) {
                usb_midi_handleAfterTouch = fptr;
        };
        inline void setHandlePitchChange(void (*fptr)(uint8_t channel, int pitch)) {
                usb_midi_handlePitchChange = fptr;
        };
        inline void setHandleSysEx(void (*fptr)(const uint8_t *data, uint16_t length, bool complete)) {
                usb_midi_handleSysEx = (void (*)(const uint8_t *, uint16_t, uint8_t))fptr;
        }
        inline void setHandleRealTimeSystem(void (*fptr)(uint8_t realtimebyte)) {
                usb_midi_handleRealTimeSystem = fptr;
        };
        inline void setHandleTimeCodeQuarterFrame(void (*fptr)(uint16_t data)) {
                usb_midi_handleTimeCodeQuarterFrame = fptr;
        };
	private:
};

extern usb_midi_class usbMIDI;


#endif // __cplusplus

#endif // MIDI_INTERFACE

#endif // USBmidi_h_

