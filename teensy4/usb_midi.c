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
#include <string.h> // for memcpy()
#include "avr/pgmspace.h" // for PROGMEM, DMAMEM, FASTRUN
#include "debug/printf.h"
#include "core_pins.h"

#ifdef MIDI_INTERFACE // defined by usb_dev.h -> usb_desc.h

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


//static usb_packet_t *rx_packet=NULL;
//static usb_packet_t *tx_packet=NULL;
static uint8_t transmit_previous_timeout=0;
static uint8_t tx_noautoflush=0;
extern volatile uint8_t usb_high_speed;


#define TX_NUM   4
#define TX_SIZE  512 /* should be a multiple of MIDI_TX_SIZE_480 */
static transfer_t tx_transfer[TX_NUM] __attribute__ ((used, aligned(32)));
DMAMEM static uint8_t txbuffer[TX_SIZE * TX_NUM] __attribute__ ((aligned(32)));
static uint8_t tx_head=0;
static uint16_t tx_available=0;
static uint16_t tx_packet_size=0;

#define RX_NUM  6
static transfer_t rx_transfer[RX_NUM] __attribute__ ((used, aligned(32)));
DMAMEM static uint8_t rx_buffer[RX_NUM * MIDI_RX_SIZE_480] __attribute__ ((aligned(32)));
static uint16_t rx_count[RX_NUM];
static uint16_t rx_index[RX_NUM];
static uint16_t rx_packet_size=0;
static volatile uint8_t rx_head;
static volatile uint8_t rx_tail;
static uint8_t rx_list[RX_NUM + 1];
static volatile uint32_t rx_available;
static void rx_queue_transfer(int i);
static void rx_event(transfer_t *t);


void usb_midi_configure(void)
{
	printf("usb_midi_configure\n");
	if (usb_high_speed) {
		tx_packet_size = MIDI_TX_SIZE_480;
		rx_packet_size = MIDI_RX_SIZE_480;
	} else {
		tx_packet_size = MIDI_TX_SIZE_12;
		rx_packet_size = MIDI_RX_SIZE_12;
	}
	memset(tx_transfer, 0, sizeof(tx_transfer));
	tx_head = 0;
	tx_available = 0;
	memset(rx_transfer, 0, sizeof(rx_transfer));
	memset(rx_count, 0, sizeof(rx_count));
	memset(rx_index, 0, sizeof(rx_index));
	rx_head = 0;
	rx_tail = 0;
	rx_available = 0;
	usb_config_rx(MIDI_RX_ENDPOINT, rx_packet_size, 0, rx_event);
	usb_config_tx(MIDI_TX_ENDPOINT, tx_packet_size, 0, NULL); // TODO: is ZLP needed?
	int i;
	for (i=0; i < RX_NUM; i++) rx_queue_transfer(i);
	transmit_previous_timeout = 0;
	tx_noautoflush = 0;
}



// When the PC isn't listening, how long do we wait before discarding data?
#define TX_TIMEOUT_MSEC 40


void usb_midi_write_packed(uint32_t n)
{
	printf("usb_midi_write_packed\n");
	if (!usb_configuration) return;
	tx_noautoflush = 1;
	uint32_t head = tx_head;
	transfer_t *xfer = tx_transfer + head;
	uint32_t wait_begin_at = systick_millis_count;
	while (!tx_available) {
		uint32_t status = usb_transfer_status(xfer);
		if (!(status & 0x80)) {
			if (status & 0x68) {
				// TODO: what if status has errors???
			}
			tx_available = tx_packet_size;
			transmit_previous_timeout = 0;
			break;
		}
		if (systick_millis_count - wait_begin_at > TX_TIMEOUT_MSEC) {
			transmit_previous_timeout = 1;
		}
		if (transmit_previous_timeout) return;
		if (!usb_configuration) return;
		yield();
	}
	uint32_t *txdata = (uint32_t *)(txbuffer + (tx_head * TX_SIZE) + (TX_SIZE - tx_available));
	*txdata = n;
	tx_available -= 4;
	if (tx_available == 0) {
		uint8_t *txbuf = txbuffer + (tx_head * TX_SIZE);
		usb_prepare_transfer(xfer, txbuf, tx_packet_size, 0);
		arm_dcache_flush_delete(txbuf, TX_SIZE);
		usb_transmit(MIDI_TX_ENDPOINT, xfer);
		if (++head >= TX_NUM) head = 0;
		tx_head = head;
		usb_stop_sof_interrupts(MIDI_INTERFACE);
	} else {
		usb_start_sof_interrupts(MIDI_INTERFACE);
	}
	tx_noautoflush = 0;
}

void usb_midi_flush_output(void)
{
	//printf("usb_midi_flush_output\n");
	if (tx_noautoflush == 0 && tx_available > 0) {
		printf(" tx, %d %d\n", tx_packet_size, tx_available);
		uint32_t head = tx_head;
		transfer_t *xfer = tx_transfer + head;
		uint8_t *txbuf = txbuffer + (head * TX_SIZE);
		uint32_t len = tx_packet_size - tx_available;
		usb_prepare_transfer(xfer, txbuf, len, 0);
		arm_dcache_flush_delete(txbuf, TX_SIZE);
		usb_transmit(MIDI_TX_ENDPOINT, xfer);
		if (++head >= TX_NUM) head = 0;
		tx_head = head;
		tx_available = 0;
		usb_stop_sof_interrupts(MIDI_INTERFACE);
	}
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






static void rx_queue_transfer(int i)
{
	NVIC_DISABLE_IRQ(IRQ_USB1);
	void *buffer = rx_buffer + i * MIDI_RX_SIZE_480;
	usb_prepare_transfer(rx_transfer + i, buffer, rx_packet_size, i);
	arm_dcache_delete(buffer, rx_packet_size);
	usb_receive(MIDI_RX_ENDPOINT, rx_transfer + i);
	NVIC_ENABLE_IRQ(IRQ_USB1);
}



// called by USB interrupt when any packet is received
static void rx_event(transfer_t *t)
{
	int len = rx_packet_size - ((t->status >> 16) & 0x7FFF);
	len &= 0xFFFC; // MIDI packets must be multiple of 4 bytes
	int i = t->callback_param;
	printf("rx event, len=%d, i=%d\n", len, i);
	if (len > 0) {
		uint32_t head = rx_head;
		rx_count[i] = len;
		rx_index[i] = 0;
		if (++head > RX_NUM) head = 0;
		rx_list[head] = i;
		rx_head = head;
		rx_available += len;
	} else {
		// received a zero length packet
		rx_queue_transfer(i);
	}
}


uint32_t usb_midi_available(void)
{
	return rx_available / 4;
}

uint32_t usb_midi_read_message(void)
{
	uint32_t n = 0;
	NVIC_DISABLE_IRQ(IRQ_USB1);
	uint32_t tail = rx_tail;
	if (tail != rx_head) {
		if (++tail > RX_NUM) tail = 0;
		uint32_t i = rx_list[tail];
		//uint32_t avail = (rx_count[i] - rx_index[i]) / 4;
		void *p = rx_buffer + i * MIDI_RX_SIZE_480 + rx_index[i];
		n = *(uint32_t *)p;
		rx_available -= 4;
		rx_index[i] += 4;
		if (rx_index[i] >= rx_count[i]) {
			rx_tail = tail;
			rx_queue_transfer(i);
		}
	}
	NVIC_ENABLE_IRQ(IRQ_USB1);
	return n;
}

int usb_midi_read(uint32_t channel)
{
	uint32_t n, ch, type1, type2, b1;
	
	n = usb_midi_read_message();
	if (n == 0) return 0;
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


#endif // MIDI_INTERFACE
