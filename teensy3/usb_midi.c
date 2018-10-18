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

#include "usb_dev.h"
#include "usb_midi.h"
#include "core_pins.h" // for yield()
#include "HardwareSerial.h"

#ifdef MIDI_INTERFACE // defined by usb_dev.h -> usb_desc.h
#if F_CPU >= 20000000

uint8_t usb_midi_msg_cable;
uint8_t usb_midi_msg_channel;
uint8_t usb_midi_msg_type;
uint8_t usb_midi_msg_data1;
uint8_t usb_midi_msg_data2;
// TODO: separate sysex buffers for each cable...
uint8_t usb_midi_msg_sysex[USB_MIDI_SYSEX_MAX];
uint16_t usb_midi_msg_sysex_len;
void (*usb_midi_handleNoteOff)(uint8_t ch, uint8_t note, uint8_t vel) = NULL;
void (*usb_midi_handleNoteOn)(uint8_t ch, uint8_t note, uint8_t vel) = NULL;
void (*usb_midi_handleVelocityChange)(uint8_t ch, uint8_t note, uint8_t vel) = NULL;
void (*usb_midi_handleControlChange)(uint8_t ch, uint8_t control, uint8_t value) = NULL;
void (*usb_midi_handleProgramChange)(uint8_t ch, uint8_t program) = NULL;
void (*usb_midi_handleAfterTouch)(uint8_t ch, uint8_t pressure) = NULL;
void (*usb_midi_handlePitchChange)(uint8_t ch, int pitch) = NULL;
void (*usb_midi_handleSysExPartial)(const uint8_t *data, uint16_t length, uint8_t complete) = NULL;
void (*usb_midi_handleSysExComplete)(uint8_t *data, unsigned int size) = NULL;
void (*usb_midi_handleTimeCodeQuarterFrame)(uint8_t data) = NULL;
void (*usb_midi_handleSongPosition)(uint16_t beats) = NULL;
void (*usb_midi_handleSongSelect)(uint8_t songnumber) = NULL;
void (*usb_midi_handleTuneRequest)(void) = NULL;
void (*usb_midi_handleClock)(void) = NULL;
void (*usb_midi_handleStart)(void) = NULL;
void (*usb_midi_handleContinue)(void) = NULL;
void (*usb_midi_handleStop)(void) = NULL;
void (*usb_midi_handleActiveSensing)(void) = NULL;
void (*usb_midi_handleSystemReset)(void) = NULL;
void (*usb_midi_handleRealTimeSystem)(uint8_t rtb) = NULL;


// Maximum number of transmit packets to queue so we don't starve other endpoints for memory
#define TX_PACKET_LIMIT 6
static usb_packet_t *rx_packet=NULL;
static usb_packet_t *tx_packet=NULL;
static uint8_t transmit_previous_timeout=0;
static uint8_t tx_noautoflush=0;


// When the PC isn't listening, how long do we wait before discarding data?
#define TX_TIMEOUT_MSEC 40
#if F_CPU == 256000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 1706)
#elif F_CPU == 240000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 1600)
#elif F_CPU == 216000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 1440)
#elif F_CPU == 192000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 1280)
#elif F_CPU == 180000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 1200)
#elif F_CPU == 168000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 1100)
#elif F_CPU == 144000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 932)
#elif F_CPU == 120000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 764)
#elif F_CPU == 96000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 596)
#elif F_CPU == 72000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 512)
#elif F_CPU == 48000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 428)
#elif F_CPU == 24000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 262)
#endif


void usb_midi_write_packed(uint32_t n)
{
	uint32_t index, wait_count=0;

	tx_noautoflush = 1;
	if (!tx_packet) {
        	while (1) {
                	if (!usb_configuration) {
				//serial_print("error1\n");
                        	return;
                	}
                	if (usb_tx_packet_count(MIDI_TX_ENDPOINT) < TX_PACKET_LIMIT) {
                        	tx_packet = usb_malloc();
                        	if (tx_packet) break;
                	}
                	if (++wait_count > TX_TIMEOUT || transmit_previous_timeout) {
                        	transmit_previous_timeout = 1;
				//serial_print("error2\n");
                        	return;
                	}
                	yield();
        	}
	}
	transmit_previous_timeout = 0;
	index = tx_packet->index;
	((uint32_t *)(tx_packet->buf))[index++] = n;
	if (index < MIDI_TX_SIZE/4) {
		tx_packet->index = index;
	} else {
		tx_packet->len = MIDI_TX_SIZE;
		usb_tx(MIDI_TX_ENDPOINT, tx_packet);
		tx_packet = NULL;
	}
	tx_noautoflush = 0;
}

void usb_midi_send_sysex_buffer_has_term(const uint8_t *data, uint32_t length, uint8_t cable)
{
	cable = (cable & 0x0F) << 4;
        while (length > 3) {
                usb_midi_write_packed(0x04 | cable | (data[0] << 8) | (data[1] << 16) | (data[2] << 24));
                data += 3;
                length -= 3;
        }
        if (length == 3) {
                usb_midi_write_packed(0x07 | cable | (data[0] << 8) | (data[1] << 16) | (data[2] << 24));
        } else if (length == 2) {
                usb_midi_write_packed(0x06 | cable | (data[0] << 8) | (data[1] << 16));
        } else if (length == 1) {
                usb_midi_write_packed(0x05 | cable | (data[0] << 8));
        }
}

void usb_midi_send_sysex_add_term_bytes(const uint8_t *data, uint32_t length, uint8_t cable)
{
	cable = (cable & 0x0F) << 4;

	if (length == 0) {
		usb_midi_write_packed(0x06 | cable | (0xF0 << 8) | (0xF7 << 16));
		return;
	} else if (length == 1) {
		usb_midi_write_packed(0x07 | cable | (0xF0 << 8) | (data[0] << 16) | (0xF7 << 24));
		return;
	} else {
		usb_midi_write_packed(0x04 | cable | (0xF0 << 8) | (data[0] << 16) | (data[1] << 24));
		data += 2;
		length -= 2;
	}
	while (length >= 3) {
		usb_midi_write_packed(0x04 | cable | (data[0] << 8) | (data[1] << 16) | (data[2] << 24));
		data += 3;
		length -= 3;
	}
	if (length == 2) {
		usb_midi_write_packed(0x07 | cable | (data[0] << 8) | (data[1] << 16) | (0xF7 << 24));
	} else if (length == 1) {
                usb_midi_write_packed(0x06 | cable | (data[0] << 8) | (0xF7 << 16));
	} else {
                usb_midi_write_packed(0x05 | cable | (0xF7 << 8));
	}
}

void usb_midi_flush_output(void)
{
	if (tx_noautoflush == 0 && tx_packet && tx_packet->index > 0) {
		tx_packet->len = tx_packet->index * 4;
		usb_tx(MIDI_TX_ENDPOINT, tx_packet);
		tx_packet = NULL;
	}
}

void static sysex_byte(uint8_t b)
{
	if (usb_midi_handleSysExPartial && usb_midi_msg_sysex_len >= USB_MIDI_SYSEX_MAX) {
		// when buffer is full, send another chunk to partial handler.
		(*usb_midi_handleSysExPartial)(usb_midi_msg_sysex, usb_midi_msg_sysex_len, 0);
		usb_midi_msg_sysex_len = 0;
	}
	if (usb_midi_msg_sysex_len < USB_MIDI_SYSEX_MAX) {
		usb_midi_msg_sysex[usb_midi_msg_sysex_len++] = b;
	}
}

uint32_t usb_midi_available(void)
{
	uint32_t index;

	if (!rx_packet) {
		if (!usb_configuration) return 0;
		rx_packet = usb_rx(MIDI_RX_ENDPOINT);
		if (!rx_packet) return 0;
		if (rx_packet->len == 0) {
			usb_free(rx_packet);
			rx_packet = NULL;
			return 0;
		}
	}
	index = rx_packet->index;
	return rx_packet->len - index;
}

uint32_t usb_midi_read_message(void)
{
	uint32_t n, index;

	if (!rx_packet) {
		if (!usb_configuration) return 0;
		rx_packet = usb_rx(MIDI_RX_ENDPOINT);
		if (!rx_packet) return 0;
		if (rx_packet->len == 0) {
			usb_free(rx_packet);
			rx_packet = NULL;
			return 0;
		}
	}
	index = rx_packet->index;
	n = ((uint32_t *)rx_packet->buf)[index/4];
	index += 4;
	if (index < rx_packet->len) {
		rx_packet->index = index;
	} else {
		usb_free(rx_packet);
		rx_packet = usb_rx(MIDI_RX_ENDPOINT);
	}
	return n;
}

int usb_midi_read(uint32_t channel)
{
	uint32_t n, index, ch, type1, type2, b1;

	if (!rx_packet) {
		if (!usb_configuration) return 0;
		rx_packet = usb_rx(MIDI_RX_ENDPOINT);
		if (!rx_packet) return 0;
		if (rx_packet->len == 0) {
			usb_free(rx_packet);
			rx_packet = NULL;
			return 0;
		}
	}
	index = rx_packet->index;
	n = ((uint32_t *)rx_packet->buf)[index/4];
	//serial_print("midi rx, n=");
	//serial_phex32(n);
	//serial_print("\n");
	index += 4;
	if (index < rx_packet->len) {
		rx_packet->index = index;
	} else {
		usb_free(rx_packet);
		rx_packet = usb_rx(MIDI_RX_ENDPOINT);
	}
	type1 = n & 15;
	type2 = (n >> 12) & 15;
	b1 = (n >> 8) & 0xFF;
	ch = (b1 & 15) + 1;
	usb_midi_msg_cable = (n >> 4) & 15;
	if (type1 >= 0x08 && type1 <= 0x0E) {
		if (channel && channel != ch) {
			// ignore other channels when user wants single channel read
			return 0;
		}
		if (type1 == 0x08 && type2 == 0x08) {
			usb_midi_msg_type = 0x80;		// 0x80 = usbMIDI.NoteOff
			if (usb_midi_handleNoteOff)
				(*usb_midi_handleNoteOff)(ch, (n >> 16), (n >> 24));
		} else
		if (type1 == 0x09 && type2 == 0x09) {
			if ((n >> 24) > 0) {
				usb_midi_msg_type = 0x90;	// 0x90 = usbMIDI.NoteOn
				if (usb_midi_handleNoteOn)
					(*usb_midi_handleNoteOn)(ch, (n >> 16), (n >> 24));
			} else {
				usb_midi_msg_type = 0x80;	// 0x80 = usbMIDI.NoteOff
				if (usb_midi_handleNoteOff)
					(*usb_midi_handleNoteOff)(ch, (n >> 16), (n >> 24));
			}
		} else
		if (type1 == 0x0A && type2 == 0x0A) {
			usb_midi_msg_type = 0xA0;		// 0xA0 = usbMIDI.AfterTouchPoly
			if (usb_midi_handleVelocityChange)
				(*usb_midi_handleVelocityChange)(ch, (n >> 16), (n >> 24));
		} else
		if (type1 == 0x0B && type2 == 0x0B) {
			usb_midi_msg_type = 0xB0;		// 0xB0 = usbMIDI.ControlChange
			if (usb_midi_handleControlChange)
				(*usb_midi_handleControlChange)(ch, (n >> 16), (n >> 24));
		} else
		if (type1 == 0x0C && type2 == 0x0C) {
			usb_midi_msg_type = 0xC0;		// 0xC0 = usbMIDI.ProgramChange
			if (usb_midi_handleProgramChange)
				(*usb_midi_handleProgramChange)(ch, (n >> 16));
		} else
		if (type1 == 0x0D && type2 == 0x0D) {
			usb_midi_msg_type = 0xD0;		// 0xD0 = usbMIDI.AfterTouchChannel
			if (usb_midi_handleAfterTouch)
				(*usb_midi_handleAfterTouch)(ch, (n >> 16));
		} else
		if (type1 == 0x0E && type2 == 0x0E) {
			usb_midi_msg_type = 0xE0;		// 0xE0 = usbMIDI.PitchBend
			if (usb_midi_handlePitchChange) {
				int value = ((n >> 16) & 0x7F) | ((n >> 17) & 0x3F80);
				value -= 8192; // 0 to 16383 --> -8192 to +8191
				(*usb_midi_handlePitchChange)(ch, value);
			}
		} else {
			return 0;
		}
		return_message:
		usb_midi_msg_channel = ch;
		usb_midi_msg_data1 = (n >> 16);
		usb_midi_msg_data2 = (n >> 24);
		return 1;
	}
	if (type1 == 0x02 || type1 == 0x03 || (type1 == 0x05 && b1 >= 0xF1 && b1 != 0xF7)) {
		// system common or system realtime message
		system_common_or_realtime:
		switch (b1) {
		  case 0xF1: // usbMIDI.TimeCodeQuarterFrame
			if (usb_midi_handleTimeCodeQuarterFrame) {
				(*usb_midi_handleTimeCodeQuarterFrame)(n >> 16);
			}
			break;
		  case 0xF2: // usbMIDI.SongPosition
			if (usb_midi_handleSongPosition) {
				(*usb_midi_handleSongPosition)(
				  ((n >> 16) & 0x7F) | ((n >> 17) & 0x3F80));
			}
			break;
		  case 0xF3: // usbMIDI.SongSelect
			if (usb_midi_handleSongSelect) {
				(*usb_midi_handleSongSelect)(n >> 16);
			}
			break;
		  case 0xF6: // usbMIDI.TuneRequest
			if (usb_midi_handleTuneRequest) {
				(*usb_midi_handleTuneRequest)();
			}
			break;
		  case 0xF8: // usbMIDI.Clock
			if (usb_midi_handleClock) {
				(*usb_midi_handleClock)();
			} else if (usb_midi_handleRealTimeSystem) {
				(*usb_midi_handleRealTimeSystem)(0xF8);
			}
			break;
		  case 0xFA: // usbMIDI.Start
			if (usb_midi_handleStart) {
				(*usb_midi_handleStart)();
			} else if (usb_midi_handleRealTimeSystem) {
				(*usb_midi_handleRealTimeSystem)(0xFA);
			}
			break;
		  case 0xFB: // usbMIDI.Continue
			if (usb_midi_handleContinue) {
				(*usb_midi_handleContinue)();
			} else if (usb_midi_handleRealTimeSystem) {
				(*usb_midi_handleRealTimeSystem)(0xFB);
			}
			break;
		  case 0xFC: // usbMIDI.Stop
			if (usb_midi_handleStop) {
				(*usb_midi_handleStop)();
			} else if (usb_midi_handleRealTimeSystem) {
				(*usb_midi_handleRealTimeSystem)(0xFC);
			}
			break;
		  case 0xFE: // usbMIDI.ActiveSensing
			if (usb_midi_handleActiveSensing) {
				(*usb_midi_handleActiveSensing)();
			} else if (usb_midi_handleRealTimeSystem) {
				(*usb_midi_handleRealTimeSystem)(0xFE);
			}
			break;
		  case 0xFF: // usbMIDI.SystemReset
			if (usb_midi_handleSystemReset) {
				(*usb_midi_handleSystemReset)();
			} else if (usb_midi_handleRealTimeSystem) {
				(*usb_midi_handleRealTimeSystem)(0xFF);
			}
			break;
		  default:
			return 0; // unknown message, ignore it
		}
		usb_midi_msg_type = b1;
		goto return_message;
	}
	if (type1 == 0x04) {
		sysex_byte(n >> 8);
		sysex_byte(n >> 16);
		sysex_byte(n >> 24);
		return 0;
	}
	if (type1 >= 0x05 && type1 <= 0x07) {
		sysex_byte(b1);
		if (type1 >= 0x06) sysex_byte(n >> 16);
		if (type1 == 0x07) sysex_byte(n >> 24);
		uint16_t len = usb_midi_msg_sysex_len;
		usb_midi_msg_data1 = len;
		usb_midi_msg_data2 = len >> 8;
		usb_midi_msg_sysex_len = 0;
		usb_midi_msg_type = 0xF0;			// 0xF0 = usbMIDI.SystemExclusive
		if (usb_midi_handleSysExPartial) {
			(*usb_midi_handleSysExPartial)(usb_midi_msg_sysex, len, 1);
		} else if (usb_midi_handleSysExComplete) {
			(*usb_midi_handleSysExComplete)(usb_midi_msg_sysex, len);
		}
		return 1;
	}
	if (type1 == 0x0F) {
		if (b1 >= 0xF8) {
			// From Sebastian Tomczak, seb.tomczak at gmail.com
			// http://little-scale.blogspot.com/2011/08/usb-midi-game-boy-sync-for-16.html
			goto system_common_or_realtime;
		}
		if (b1 == 0xF0 || usb_midi_msg_sysex_len > 0) {
			// From David Sorlien, dsorlien at gmail.com, http://axe4live.wordpress.com
			// OSX sometimes uses Single Byte Unparsed to
			// send bytes in the middle of a SYSEX message.
			sysex_byte(b1);
		}
	}
	return 0;
}


#endif // F_CPU
#endif // MIDI_INTERFACE
