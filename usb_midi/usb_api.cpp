/* USB API for Teensy USB Development Board
 * http://www.pjrc.com/teensy/teensyduino.html
 * Copyright (c) 2008 PJRC.COM, LLC
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include "usb_common.h"
#include "usb_private.h"
#include "usb_api.h"
#include "wiring.h"


void usb_midi_class::sendSysEx_BufferHasTerm(uint16_t length, const uint8_t *data)
{
	while (length > 3) {
		send_raw(0x04, data[0], data[1], data[2]);
		data += 3;
		length -= 3;
	}
	if (length == 3) {
		send_raw(0x07, data[0], data[1], data[2]);
	} else if (length == 2) {
		send_raw(0x06, data[0], data[1], 0);
	} else if (length == 1) {
		send_raw(0x05, data[0], 0, 0);
	}
}

void usb_midi_class::sendSysEx_AddTermBytes(uint16_t length, const uint8_t *data)
{
	if (length == 0) {
		send_raw(0x06, 0xF0, 0xF7, 0);
		return;
	} else if (length == 1) {
		send_raw(0x07, 0xF0, data[0], 0xF7);
		return;
	} else {
		send_raw(0x04, 0xF0, data[0], data[1]);
		data += 2;
		length -= 2;
	}
	while (length >= 3) {
		send_raw(0x04, data[0], data[1], data[2]);
		data += 3;
		length -= 3;
	}
	if (length == 2) {
		send_raw(0x07, data[0], data[1], 0xF7);
	} else if (length == 1) {
		send_raw(0x06, data[0], 0xF7, 0);
	} else {
		send_raw(0x05, 0xF7, 0, 0);
	}
}

// This 4 byte input format is documented in the "Universal Serial Bus Device Class
// Definition for MIDI Devices" specification, version 1.0, Nov 1, 1999.  It can be
// downloaded from www.usb.org.  https://www.usb.org/sites/default/files/midi10.pdf
// If the USB-IF reorganizes their website and this link no longer works, Google
// search the name to find it.  This data format is shown on page 16 in Figure #8.
// Byte 0 (shown on the left hand side of Figure #8) is b0, Byte 1 is b1, etc.
void usb_midi_class::send_raw(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3)
{
	uint8_t intr_state, timeout;

	if (!usb_configuration) return;
	intr_state = SREG;
	cli();
	UENUM = MIDI_TX_ENDPOINT;
	timeout = UDFNUML + 2;
	while (1) {
		// are we ready to transmit?
		if (UEINTX & (1<<RWAL)) break;
		SREG = intr_state;
		if (UDFNUML == timeout) return;
		if (!usb_configuration) return;
		intr_state = SREG;
		cli();
		UENUM = MIDI_TX_ENDPOINT;
	}
	UEDATX = b0;
	UEDATX = b1;
	UEDATX = b2;
	UEDATX = b3;
	if (!(UEINTX & (1<<RWAL))) UEINTX = 0x3A;
	SREG = intr_state;
}

void usb_midi_class::send_now(void)
{
	uint8_t intr_state;

	if (!usb_configuration) return;
	intr_state = SREG;
	cli();
	UENUM = MIDI_TX_ENDPOINT;
	if (UEBCLX != MIDI_TX_SIZE) {
		UEINTX = 0x3A;
	}
	SREG = intr_state;
}



// Convert 10 bit linear measurements to a logarthmic scale
// suitable for sending as MIDI velocity numbers.  The
// "range" parameter should be probably be between 30 to 60,
// with 36 probably a good default.
//
// This function uses fast 16 bit unsigned integer math.  :-)
//
uint8_t usb_midi_class::analog2velocity(uint16_t val, uint8_t range)
{
#if 0
	if (val == 0) return 0;
	float scale = 1.0 + (20.0 / (float)range) * log10((float)val / 1023.0);
	if (scale < 0) return 0;
	return 127 * scale;
#else
	uint8_t i, e, b;
	uint16_t s=0;
	static const uint8_t PROGMEM table[] = {225,124,65,34,17,9,4,2,1};

	if (val == 0) return 0;
	if (val >= 1023) return 127;
	for (e=0; (val & 512) == 0; e++) val <<= 1;
	for (i=0; i<9; i++) {  // cordic algorithm
		uint16_t x = val + (val >> (i + 1));
		if (x < 1024) {
			val = x;
			s += pgm_read_byte(table + i);
		}
	}
	s += e * 385;
	s <<= 4;
	s += (range >> 1);
	s /= range;
	if (s >= 1024) return 0;
	s = 1024 - s;
	if (s > 511) {
		s -= 512;
		b = 64;
	} else if (s > 255) {
		s -= 256;
		b = 32;
	} else {
		b = 0;
	}
	return b + ((s * 127) >> 10);
#endif
}




uint32_t usb_midi_class::midiusb_available()
{
	uint8_t c, intr_state;

	intr_state = SREG;
	cli();
	if (!usb_configuration) {
		SREG = intr_state;
		return 0;
	}
	UENUM = MIDI_RX_ENDPOINT;
	retry:
	c = UEINTX;
	if (!(c & (1<<RWAL))) {
		if (c & (1<<RXOUTI)) {
			UEINTX = 0x6B;
			goto retry;
		}
		SREG = intr_state;
		return 0;
	}
	SREG = intr_state;
	return 4;
}

void usb_midi_class::midiusb_read(uint8_t *buf)
{
	uint8_t c, intr_state;

	intr_state = SREG;
	cli();
	if (!usb_configuration) {
		SREG = intr_state;
		buf[0] = 0;
		buf[1] = 0;
		buf[2] = 0;
		buf[3] = 0;
		return;
	}
	UENUM = MIDI_RX_ENDPOINT;
	retry:
	c = UEINTX;
	if (!(c & (1<<RWAL))) {
		if (c & (1<<RXOUTI)) {
			UEINTX = 0x6B;
			goto retry;
		}
		SREG = intr_state;
		buf[0] = 0;
		buf[1] = 0;
		buf[2] = 0;
		buf[3] = 0;
		return;
	}
	buf[0] = UEDATX;
	buf[1] = UEDATX;
	buf[2] = UEDATX;
	buf[3] = UEDATX;
	if (!(UEINTX & (1<<RWAL))) UEINTX = 0x6B;
	SREG = intr_state;
}


bool usb_midi_class::read(uint8_t channel)
{
	uint8_t c, intr_state;
	uint8_t b0, b1, b2, b3, type1, type2;

	intr_state = SREG;
	cli();
	if (!usb_configuration) {
		SREG = intr_state;
		return false;
	}
	UENUM = MIDI_RX_ENDPOINT;
	retry:
	c = UEINTX;
	if (!(c & (1<<RWAL))) {
		if (c & (1<<RXOUTI)) {
			UEINTX = 0x6B;
			goto retry;
		}
		SREG = intr_state;
		return false;
	}
	b0 = UEDATX;
	b1 = UEDATX;
	b2 = UEDATX;
	b3 = UEDATX;
	if (!(UEINTX & (1<<RWAL))) UEINTX = 0x6B;
	SREG = intr_state;

	type1 = b0 & 0x0F;
	type2 = b1 & 0xF0;
	c = (b1 & 0x0F) + 1;
	if (type1 >= 0x08 && type1 <= 0x0E) {
		if (channel && channel != c) {
			// ignore other channels when user wants single channel read
			return false;
		}
		if (type1 == 0x08 && type2 == 0x80) {
			msg_type = 0x80;			// 0x80 = usbMIDI.NoteOff
			if (handleNoteOff) (*handleNoteOff)(c, b2, b3);
		} else
		if (type1 == 0x09 && type2 == 0x90) {
			if (b3) {
				msg_type = 0x90;		// 0x90 = usbMIDI.NoteOn
				if (handleNoteOn) (*handleNoteOn)(c, b2, b3);
			} else {
				msg_type = 0x80;		// 0x80 = usbMIDI.NoteOff
				if (handleNoteOff) (*handleNoteOff)(c, b2, b3);
			}
		} else
		if (type1 == 0x0A && type2 == 0xA0) {
			msg_type = 0xA0;			// 0xA0 = usbMIDI.AfterTouchPoly
			if (handleVelocityChange) (*handleVelocityChange)(c, b2, b3);
		} else
		if (type1 == 0x0B && type2 == 0xB0) {
			msg_type = 0xB0;			// 0xB0 = usbMIDI.ControlChange
			if (handleControlChange) (*handleControlChange)(c, b2, b3);
		} else
		if (type1 == 0x0C && type2 == 0xC0) {
			msg_type = 0xC0;			// 0xC0 = usbMIDI.ProgramChange
			if (handleProgramChange) (*handleProgramChange)(c, b2);
		} else
		if (type1 == 0x0D && type2 == 0xD0) {
			msg_type = 0xD0;			// 0xD0 = usbMIDI.AfterTouchChannel
			if (handleAfterTouch) (*handleAfterTouch)(c, b2);
		} else
		if (type1 == 0x0E && type2 == 0xE0) {
			msg_type = 0xE0;			// 0xE0 = usbMIDI.PitchBend
			if (handlePitchChange) {
				int value = (b2 & 0x7F) | ((int)(b3 & 0x7F) << 7);
				value -= 8192; // 0 to 16383 --> -8192 to +8191
				(*handlePitchChange)(c, value);
			}
		} else {
			return false;
		}
		return_message:
		// only update these when returning true for a parsed message
		// all other return cases will preserve these user-visible values
		msg_channel = c;
		msg_data1 = b2;
		msg_data2 = b3;
		return true;
	}
	if (type1 == 0x02 || type1 == 0x03 || (type1 == 0x05 && type2 == 0x0F)) {
		// system common or system realtime message
		system_common_or_realtime:
		switch (b1) {
                  case 0xF1: // usbMIDI.TimeCodeQuarterFrame
                        if (handleTimeCodeQuarterFrame) {
                                (*handleTimeCodeQuarterFrame)(b2);
                        }
                        break;
                  case 0xF2: // usbMIDI.SongPosition
                        if (handleSongPosition) {
                                (*handleSongPosition)(
				  (uint16_t)(b2 & 0x7F) | (uint16_t)(b3 & 0x7F) << 7);
                        }
                        break;
                  case 0xF3: // usbMIDI.SongSelect
                        if (handleSongSelect) {
                                (*handleSongSelect)(b2);
                        }
                        break;
                  case 0xF6: // usbMIDI.TuneRequest
                        if (handleTuneRequest) {
                                (*handleTuneRequest)();
                        }
                        break;
                  case 0xF8: // usbMIDI.Clock
                        if (handleClock) {
                                (*handleClock)();
                        } else if (handleRealTimeSystem) {
                                (*handleRealTimeSystem)(0xF8);
                        }
                        break;
                  case 0xFA: // usbMIDI.Start
                        if (handleStart) {
                                (*handleStart)();
                        } else if (handleRealTimeSystem) {
                                (*handleRealTimeSystem)(0xFA);
                        }
                        break;
                  case 0xFB: // usbMIDI.Continue
                        if (handleContinue) {
                                (*handleContinue)();
                        } else if (handleRealTimeSystem) {
                                (*handleRealTimeSystem)(0xFB);
                        }
                        break;
                  case 0xFC: // usbMIDI.Stop
                        if (handleStop) {
                                (*handleStop)();
                        } else if (handleRealTimeSystem) {
                                (*handleRealTimeSystem)(0xFC);
                        }
                        break;
                  case 0xFE: // usbMIDI.ActiveSensing
                        if (handleActiveSensing) {
                                (*handleActiveSensing)();
                        } else if (handleRealTimeSystem) {
                                (*handleRealTimeSystem)(0xFE);
                        }
                        break;
                  case 0xFF: // usbMIDI.SystemReset
                        if (handleSystemReset) {
                                (*handleSystemReset)();
                        } else if (handleRealTimeSystem) {
                                (*handleRealTimeSystem)(0xFF);
                        }
                        break;
                  default:
                        return false; // unknown message, ignore it
                }
		msg_type = b1;
		goto return_message;
	}
	if (type1 == 0x04) {
		read_sysex_byte(b1);
		read_sysex_byte(b2);
		read_sysex_byte(b3);
		return false;
	}
	if (type1 >= 0x05 && type1 <= 0x07) {
		read_sysex_byte(b1);
		if (type1 >= 0x06) read_sysex_byte(b2);
		if (type1 == 0x07) read_sysex_byte(b3);
		uint16_t len = msg_sysex_len;
		msg_data1 = len;
		msg_data2 = len >> 8;
		msg_sysex_len = 0;
		msg_type = 0xF0;			// 0xF0 = usbMIDI.SystemExclusive
                if (handleSysExPartial) {
                        (*handleSysExPartial)(msg_sysex, len, 1);
                } else if (handleSysExComplete) {
                        (*handleSysExComplete)(msg_sysex, len);
                }
		return true;
	}
	if (type1 == 0x0F) {
		if (b1 >= 0xF8) {
			// From Sebastian Tomczak, seb.tomczak at gmail.com
			// http://little-scale.blogspot.com/2011/08/usb-midi-game-boy-sync-for-16.html
			goto system_common_or_realtime;
		}
		if (msg_sysex_len > 0) {
			// From David Sorlien, dsorlien at gmail.com, http://axe4live.wordpress.com
			// OSX sometimes uses Single Byte Unparsed to
			// send bytes in the middle of a SYSEX message.
			read_sysex_byte(b1);
		}
	}
	return false;
}

void usb_midi_class::read_sysex_byte(uint8_t b)
{
	if (handleSysExPartial && msg_sysex_len >= USB_MIDI_SYSEX_MAX) {
		// when buffer is full, send another chunk to partial handler.
		(*handleSysExPartial)(msg_sysex, msg_sysex_len, 0);
		msg_sysex_len = 0;
	}
	if (msg_sysex_len < USB_MIDI_SYSEX_MAX) {
		msg_sysex[msg_sysex_len++] = b;
	}
}





static volatile uint8_t prev_byte=0;

void usb_serial_class::begin(long speed)
{
	// make sure USB is initialized
	usb_init();
	uint16_t begin_wait = (uint16_t)millis();
	while (1) {
		if (usb_configuration) {
			delay(200);  // a little time for host to load a driver
			return;
		}
		if (usb_suspended) {
			uint16_t begin_suspend = (uint16_t)millis();
			while (usb_suspended) {
				// must remain suspended for a while, because
				// normal USB enumeration causes brief suspend
				// states, typically under 0.1 second
				if ((uint16_t)millis() - begin_suspend > 250) {
					return;
				}
			}
		}
		// ... or a timout (powered by a USB power adaptor that
		// wiggles the data lines to keep a USB device charging)
		if ((uint16_t)millis() - begin_wait > 2500) return;
	}
	prev_byte = 0;
}

void usb_serial_class::end()
{
	usb_shutdown();
	delay(25);
}



// number of bytes available in the receive buffer
int usb_serial_class::available()
{
        uint8_t c;

	c = prev_byte;  // assume 1 byte static volatile access is atomic
	if (c) return 1;
	c = readnext();
	if (c) {
		prev_byte = c;
		return 1;
	}
	return 0;
}

// get the next character, or -1 if nothing received
int usb_serial_class::read()
{
	uint8_t c;

	c = prev_byte;
	if (c) {
		prev_byte = 0;
		return c;
	}
	c = readnext();
	if (c) return c;
	return -1;
}

int usb_serial_class::peek()
{
	uint8_t c;

	c = prev_byte;
	if (c) return c;
	c = readnext();
	if (c) {
		prev_byte = c;
		return c;
	}
	return -1;
}

// get the next character, or 0 if nothing
uint8_t usb_serial_class::readnext(void)
{
        uint8_t c, intr_state;

        // interrupts are disabled so these functions can be
        // used from the main program or interrupt context,
        // even both in the same program!
        intr_state = SREG;
        cli();
        if (!usb_configuration) {
                SREG = intr_state;
                return 0;
        }
        UENUM = DEBUG_RX_ENDPOINT;
try_again:
        if (!(UEINTX & (1<<RWAL))) {
                // no packet in buffer
                SREG = intr_state;
                return 0;
        }
        // take one byte out of the buffer
        c = UEDATX;
	if (c == 0) {
		// if we see a zero, discard it and
		// discard the rest of this packet
		UEINTX = 0x6B;
		goto try_again;
	}
        // if this drained the buffer, release it
        if (!(UEINTX & (1<<RWAL))) UEINTX = 0x6B;
        SREG = intr_state;
        return c;
}

// discard any buffered input
void usb_serial_class::flush()
{
        uint8_t intr_state;

        if (usb_configuration) {
                intr_state = SREG;
                cli();
		UENUM = DEBUG_RX_ENDPOINT;
                while ((UEINTX & (1<<RWAL))) {
                        UEINTX = 0x6B;
                }
                SREG = intr_state;
        }
	prev_byte = 0;
}

// transmit a character.
#if ARDUINO >= 100
size_t usb_serial_class::write(uint8_t c)
#else
#define setWriteError() 
void usb_serial_class::write(uint8_t c)
#endif
{
        //static uint8_t previous_timeout=0;
        uint8_t timeout, intr_state;

        // if we're not online (enumerated and configured), error
        if (!usb_configuration) goto error;
        // interrupts are disabled so these functions can be
        // used from the main program or interrupt context,
        // even both in the same program!
        intr_state = SREG;
        cli();
        UENUM = DEBUG_TX_ENDPOINT;
        // if we gave up due to timeout before, don't wait again
#if 0
	// this seems to be causig a lockup... why????
        if (previous_timeout) {
                if (!(UEINTX & (1<<RWAL))) {
                        SREG = intr_state;
                        return;
                }
                previous_timeout = 0;
        }
#endif
        // wait for the FIFO to be ready to accept data
        timeout = UDFNUML + TRANSMIT_TIMEOUT;
        while (1) {
                // are we ready to transmit?
                if (UEINTX & (1<<RWAL)) break;
                SREG = intr_state;
                // have we waited too long?  This happens if the user
                // is not running an application that is listening
                if (UDFNUML == timeout) {
                        //previous_timeout = 1;
                        goto error;
                }
                // has the USB gone offline?
                if (!usb_configuration) goto error;
                // get ready to try checking again
                intr_state = SREG;
                cli();
                UENUM = DEBUG_TX_ENDPOINT;
        }
        // actually write the byte into the FIFO
        UEDATX = c;
        // if this completed a packet, transmit it now!
        if (!(UEINTX & (1<<RWAL))) {
		UEINTX = 0x3A;
        	debug_flush_timer = 0;
	} else {
        	debug_flush_timer = TRANSMIT_FLUSH_TIMEOUT;
	}
        SREG = intr_state;
#if ARDUINO >= 100
        return 1;
#endif
error:
#if ARDUINO >= 100
        setWriteError();
        return 0;
#else
	return;
#endif
}


// These are Teensy-specific extensions to the Serial object

// immediately transmit any buffered output.
// This doesn't actually transmit the data - that is impossible!
// USB devices only transmit when the host allows, so the best
// we can do is release the FIFO buffer for when the host wants it
void usb_serial_class::send_now(void)
{
        uint8_t intr_state;

        intr_state = SREG;
        cli();
        if (debug_flush_timer) {
                UENUM = DEBUG_TX_ENDPOINT;
		while ((UEINTX & (1<<RWAL))) {
			UEDATX = 0;
		}
                UEINTX = 0x3A;
                debug_flush_timer = 0;
        }
        SREG = intr_state;
}

uint32_t usb_serial_class::baud(void)
{
	return ((uint32_t)DEBUG_TX_SIZE * 10000 / DEBUG_TX_INTERVAL);
}

uint8_t usb_serial_class::stopbits(void)
{
	return 1;
}

uint8_t usb_serial_class::paritytype(void)
{
	return 0;
}

uint8_t usb_serial_class::numbits(void)
{
	return 8;
}

uint8_t usb_serial_class::dtr(void)
{
	return 1;
}

uint8_t usb_serial_class::rts(void)
{
	return 1;
}

usb_serial_class::operator bool()
{
	if (usb_configuration) return true;
	return false;
}



// Preinstantiate Objects //////////////////////////////////////////////////////

usb_serial_class	Serial = usb_serial_class();
usb_midi_class		usbMIDI = usb_midi_class();

