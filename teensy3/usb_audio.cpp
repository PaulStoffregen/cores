/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2016 PJRC.COM, LLC.
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

#include "usb_audio.h"
#include "HardwareSerial.h"
#include <string.h> // for memcpy()

#ifdef AUDIO_INTERFACE // defined by usb_dev.h -> usb_desc.h
#if F_CPU >= 20000000

bool AudioInputUSB::update_responsibility;
audio_block_t * AudioInputUSB::incoming_left;
audio_block_t * AudioInputUSB::incoming_right;
audio_block_t * AudioInputUSB::ready_left;
audio_block_t * AudioInputUSB::ready_right;
uint16_t AudioInputUSB::incoming_count;
uint8_t AudioInputUSB::underflow_flag;

#define DMABUFATTR __attribute__ ((section(".dmabuffers"), aligned (4)))
uint16_t usb_audio_receive_buffer[AUDIO_RX_SIZE/2] DMABUFATTR;
uint16_t usb_audio_transmit_buffer[AUDIO_TX_SIZE/2] DMABUFATTR;
uint32_t usb_audio_sync_feedback DMABUFATTR;

void AudioInputUSB::begin(void)
{
	incoming_count = 0;
	incoming_left = NULL;
	incoming_right = NULL;
	ready_left = NULL;
	ready_right = NULL;
	underflow_flag = 1;
	// update_responsibility = update_setup();
	// TODO: update responsibility is tough, partly because the USB
	// interrupts aren't sychronous to the audio library block size,
	// but also because the PC may stop transmitting data, which
	// means we no longer get receive callbacks from usb_dev.
	update_responsibility = false;
	usb_audio_sync_feedback = 722824;
	usb_audio_sync_feedback = 723700; // too fast?
	//usb_audio_sync_feedback = 722534; // too slow
}

static void copy_to_buffers(const uint32_t *src, int16_t *left, int16_t *right, unsigned int len)
{
	// TODO: optimize...
	while (len > 0) {
		uint32_t n = *src++;
		*left++ = n & 0xFFFF;
		*right++ = n >> 16;
		len--;
	}
}

// Called from the USB interrupt when an isochronous packet arrives
// we must completely remove it from the receive buffer before returning
//
void usb_audio_receive_callback(unsigned int len)
{
	unsigned int count, avail;
	audio_block_t *left, *right;
	const uint32_t *data;

	len >>= 2; // 1 sample = 4 bytes: 2 left, 2 right
	data = (const uint32_t *)usb_audio_receive_buffer;

	//serial_print(".");
	//serial_phex(usb_audio_receive_buffer[0]);

	count = AudioInputUSB::incoming_count;
	left = AudioInputUSB::incoming_left;
	right = AudioInputUSB::incoming_right;
	if (left == NULL) {
		left = AudioStream::allocate();
		if (left == NULL) return;
		AudioInputUSB::incoming_left = left;
	}
	if (right == NULL) {
		right = AudioStream::allocate();
		if (right == NULL) return;
		AudioInputUSB::incoming_right = right;
	}
	while (len > 0) {
		avail = AUDIO_BLOCK_SAMPLES - count;
		if (len < avail) {
			//serial_print(".");
			copy_to_buffers(data, left->data + count, right->data + count, len);
			AudioInputUSB::incoming_count = count + len;
			return;
		} else if (avail > 0) {
			//serial_print("^");
			copy_to_buffers(data, left->data + count, right->data + count, avail);
			data += avail;
			len -= avail;
			if (AudioInputUSB::ready_left || AudioInputUSB::ready_right) {
				// buffer overrun, PC sending too fast
				AudioInputUSB::incoming_count = count + avail;
				serial_print("!");
				return;
			}
			send:
			AudioInputUSB::ready_left = left;
			AudioInputUSB::ready_right = right;
			//if (AudioInputUSB::update_responsibility) AudioStream::update_all();
			left = AudioStream::allocate();
			if (left == NULL) {
				AudioInputUSB::incoming_left = NULL;
				AudioInputUSB::incoming_right = NULL;
				AudioInputUSB::incoming_count = 0;
				return;
			}
			right = AudioStream::allocate();
			if (right == NULL) {
				AudioStream::release(left);
				AudioInputUSB::incoming_left = NULL;
				AudioInputUSB::incoming_right = NULL;
				AudioInputUSB::incoming_count = 0;
				return;
			}
			AudioInputUSB::incoming_left = left;
			AudioInputUSB::incoming_right = right;
			if (AudioInputUSB::underflow_flag) {
				AudioInputUSB::underflow_flag = 0;
				memset(left->data + count, 0, AUDIO_BLOCK_SAMPLES);
				memset(right->data + count, 0, AUDIO_BLOCK_SAMPLES);
				count = AUDIO_BLOCK_SAMPLES/2;
				serial_print("*");
			} else {
				count = 0;
			}
		} else {
			if (AudioInputUSB::ready_left || AudioInputUSB::ready_right) return;
			goto send; // recover from buffer overrun
		}
	}
	AudioInputUSB::incoming_count = count;
}

void AudioInputUSB::update(void)
{
	audio_block_t *left, *right;

	__disable_irq();
	left = ready_left;
	ready_left = NULL;
	right = ready_right;
	ready_right = NULL;
	// TODO: use incoming_count for USB isochronous feedback
	uint16_t c = incoming_count;
	__enable_irq();
	//serial_phex(c);
	//serial_print(".");
	if (!left || !right) {
		underflow_flag = 1;
		serial_print("#"); // buffer underrun - PC sending too slow
	}
	if (left) {
		transmit(left, 0);
		release(left);
	}
	if (right) {
		transmit(right, 1);
		release(right);
	}
}




// Called from the USB interrupt when ready to transmit another
// isochronous packet.  If we place data into the transmit buffer,
// the return is the number of bytes.  Otherwise, return 0 means
// no data to transmit
unsigned int usb_audio_transmit_callback(void)
{
	return 0;
}


#endif // F_CPU
#endif // AUDIO_INTERFACE
