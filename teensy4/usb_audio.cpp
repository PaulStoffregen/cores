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

#include <Arduino.h>
#include "usb_dev.h"
#include "usb_audio.h"
#include "debug/printf.h"
extern void debug_toggle(int pin);
extern void debug_pin_high(int pin);
extern void debug_pin_low(int pin);

#ifdef AUDIO_INTERFACE

bool AudioInputUSB::update_responsibility;
audio_block_t * AudioInputUSB::incoming[USB_AUDIO_RX_CHANNELS];
audio_block_t * AudioInputUSB::ready[USB_AUDIO_RX_CHANNELS];
uint16_t AudioInputUSB::incoming_count;
uint8_t AudioInputUSB::receive_flag;

struct usb_audio_features_struct AudioInputUSB::features = {0,0,FEATURE_MAX_VOLUME/2};

extern volatile uint8_t usb_high_speed;
static void rx_event(transfer_t *t);
static void tx_event(transfer_t *t);

/*static*/ transfer_t rx_transfer __attribute__ ((used, aligned(32)));
/*static*/ transfer_t sync_transfer __attribute__ ((used, aligned(32)));
/*static*/ transfer_t tx_transfer __attribute__ ((used, aligned(32)));
DMAMEM static uint8_t rx_buffer[AUDIO_RX_SIZE] __attribute__ ((aligned(32)));
DMAMEM static uint8_t tx_buffer[AUDIO_TX_SIZE] __attribute__ ((aligned(32)));
DMAMEM uint32_t usb_audio_sync_feedback __attribute__ ((aligned(32)));

uint8_t usb_audio_receive_setting=0;
uint8_t usb_audio_transmit_setting=0;
uint8_t usb_audio_sync_nbytes;
uint8_t usb_audio_sync_rshift;

uint32_t feedback_accumulator;

volatile uint32_t usb_audio_underrun_count;
volatile uint32_t usb_audio_overrun_count;


static void rx_event(transfer_t *t)
{
	if (t) {
		int len = AUDIO_RX_SIZE - ((rx_transfer.status >> 16) & 0x7FFF);
		printf("rx %u\n", len);
		usb_audio_receive_callback(len);
	}
	usb_prepare_transfer(&rx_transfer, rx_buffer, AUDIO_RX_SIZE, 0);
	arm_dcache_delete(&rx_buffer, AUDIO_RX_SIZE);
	usb_receive(AUDIO_RX_ENDPOINT, &rx_transfer);
}

static void sync_event(transfer_t *t)
{
	// USB 2.0 Specification, 5.12.4.2 Feedback, pages 73-75
	//printf("sync %x\n", sync_transfer.status); // too slow, can't print this much
	usb_audio_sync_feedback = feedback_accumulator >> usb_audio_sync_rshift;
	usb_prepare_transfer(&sync_transfer, &usb_audio_sync_feedback, usb_audio_sync_nbytes, 0);
	arm_dcache_flush(&usb_audio_sync_feedback, usb_audio_sync_nbytes);
	usb_transmit(AUDIO_SYNC_ENDPOINT, &sync_transfer);
}

void usb_audio_configure(void)
{
	printf("usb_audio_configure\n");
	usb_audio_underrun_count = 0;
	usb_audio_overrun_count = 0;

        // feedback_accumulator is (sample_rate_khz * 2^24).
        // using doubles makes it easy to get numerical perfection.
        // not sure if it's necessary or not.
        // floats don't give perfect answers.
        feedback_accumulator = (int)(((double)AUDIO_SAMPLE_RATE / 1000.0f * 0x1000000)+0.5);
	if (usb_high_speed) {
		usb_audio_sync_nbytes = 4;
		usb_audio_sync_rshift = 8;
	} else {
		usb_audio_sync_nbytes = 3;
		usb_audio_sync_rshift = 10;
	}
	memset(&rx_transfer, 0, sizeof(rx_transfer));
	usb_config_rx_iso(AUDIO_RX_ENDPOINT, AUDIO_RX_SIZE, 1, rx_event);
	rx_event(NULL);
	memset(&sync_transfer, 0, sizeof(sync_transfer));
	usb_config_tx_iso(AUDIO_SYNC_ENDPOINT, usb_audio_sync_nbytes, 1, sync_event);
	sync_event(NULL);
	memset(&tx_transfer, 0, sizeof(tx_transfer));
	usb_config_tx_iso(AUDIO_TX_ENDPOINT, AUDIO_TX_SIZE, 1, tx_event);
	tx_event(NULL);
}

void AudioInputUSB::begin(void)
{
	incoming_count = 0;
  for (unsigned int i = 0; i < USB_AUDIO_RX_CHANNELS; i++) {
    incoming[i] = NULL;
    ready[i] = NULL;
  }
  receive_flag = 0;
	// update_responsibility = update_setup();
	// TODO: update responsibility is tough, partly because the USB
	// interrupts aren't sychronous to the audio library block size,
	// but also because the PC may stop transmitting data, which
	// means we no longer get receive callbacks from usb.c
	update_responsibility = false;
}

/* 
   Copy data from *interleaved* int16 data in src, to deinterleaved data in channel data
   start copying into channel_data at offset, and copy len_frames frames.
*/
static void copy_to_buffers(const uint16_t *src, audio_block_t *channel_data[USB_AUDIO_RX_CHANNELS], uint32_t offset, unsigned int len_frames)
{
        int16_t *dest_ptrs[USB_AUDIO_RX_CHANNELS];

        for (unsigned int channel = 0; channel < USB_AUDIO_RX_CHANNELS; channel++)
                dest_ptrs[channel] = channel_data[channel]->data + offset;

        for (unsigned int frame = 0; frame < len_frames; frame++) {
                for (unsigned int channel = 0; channel < USB_AUDIO_RX_CHANNELS; channel++) {
                        *(dest_ptrs[channel]) = *src++;
                        dest_ptrs[channel]++;
                }
        }
}

// Called from the USB interrupt when an isochronous packet arrives
// we must completely remove it from the receive buffer before returning
//
static audio_block_t *channel_data[USB_AUDIO_RX_CHANNELS];
void usb_audio_receive_callback(unsigned int len_bytes)
{
        AudioInputUSB::receive_flag = 1;

        // 1 frame = 4 bytes: 2 left, 2 right for stereo
        // len_frames this is the number of frames coming in from the USB.
        uint32_t len_frames = len_bytes/USB_AUDIO_BYTES_PER_SAMPLE/USB_AUDIO_RX_CHANNELS;

        int allocate_errors = 0;
        for (unsigned int i = 0; i < USB_AUDIO_RX_CHANNELS; i++) {
                channel_data[i] = AudioInputUSB::incoming[i];
                if (channel_data[i] == NULL) {
                        channel_data[i] = AudioStream::allocate();
                        if (channel_data[i] == NULL) {
                                allocate_errors++;
                                break;
                        }
                        AudioInputUSB::incoming[i] = channel_data[i];
                }
        }
        if (allocate_errors) {
                // release any blocks allocated above.
                for (unsigned int i = 0; i < USB_AUDIO_RX_CHANNELS; i++) {
                        if (channel_data[i])
                                AudioStream::release(channel_data[i]);
                        channel_data[i] = NULL;
                }
                return;
        }

        // count_frames is the number of frames currently occupied in the output
        // buffers.  There can be up to AUDIO_BLOCK_SAMPLES occupied
        const uint16_t *data = (const uint16_t *)rx_buffer;
        uint32_t count_frames = AudioInputUSB::incoming_count;
        while (len_frames > 0) {
                // avail_frames: the number of empty frames to shove into each output's buffer.
                uint32_t avail_frames = AUDIO_BLOCK_SAMPLES - count_frames;
                if (len_frames < avail_frames) {
                        // copy all the frames from USB and deinterleave and copy to buffers.
                        // there's space in the outputs buffers, so do them all at once
                        copy_to_buffers(data, channel_data, count_frames, len_frames);
                        AudioInputUSB::incoming_count = count_frames + len_frames;
                        return;
                } else if (avail_frames > 0) {
                        // there's some space for new samples, but not enough for all the new samples.
                        copy_to_buffers(data, channel_data, count_frames, avail_frames);
                        data += avail_frames * USB_AUDIO_RX_CHANNELS; // skip data pointer ahead
                        len_frames -= avail_frames;
                        if (AudioInputUSB::all_ready()) {
                                // buffer overrun, PC sending too fast
                                AudioInputUSB::incoming_count = count_frames + avail_frames;
                                if (len_frames > 0) {
                                        usb_audio_overrun_count++;
                                        printf("!");
                                        //serial_phex(len_frames);
                                }
                                return;
                        }
                send:
                        for (unsigned int i = 0; i < USB_AUDIO_RX_CHANNELS; i++) {
                                AudioInputUSB::ready[i] = channel_data[i];
                        }
                        //if (AudioInputUSB::update_responsibility) AudioStream::update_all();
                        for (unsigned int i = 0; i < USB_AUDIO_RX_CHANNELS; i++) {
                                channel_data[i] = AudioStream::allocate();
                                if (channel_data[i] == NULL) {
                                        for (unsigned int j = 0; j < USB_AUDIO_RX_CHANNELS; j++) {
                                                AudioInputUSB::incoming[j] = NULL;
                                                AudioInputUSB::incoming_count = 0;
                                        }
                                        break;
                                }
                                AudioInputUSB::incoming[i] = channel_data[i];
                        }
                        count_frames = 0;
                } else {
                        if (AudioInputUSB::all_ready()) return;
                        goto send; // recover from buffer overrun
                }
        }
        AudioInputUSB::incoming_count = count_frames;
}

int AudioInputUSB::all_ready(void) {
        int r = 0;
        // logical or || of (ready[x])
        for (unsigned int i = 0; i < USB_AUDIO_RX_CHANNELS; i++) {
                r += (ready[i]!=NULL);
        }
        return (r > 0);
}

void AudioInputUSB::update(void)
{
	audio_block_t *channels[USB_AUDIO_RX_CHANNELS];
	__disable_irq();
        for (unsigned int channel = 0; channel < USB_AUDIO_RX_CHANNELS; channel++) {
                channels[channel] = ready[channel];
                ready[channel] = NULL;
        }
	uint16_t c = incoming_count;
	uint8_t f = receive_flag;
	receive_flag = 0;
	__enable_irq();
	if (f) {
		int diff = AUDIO_BLOCK_SAMPLES/2 - (int)c;
		feedback_accumulator += diff * 1;
		//uint32_t feedback = (feedback_accumulator >> 8) + diff * 100;
		//usb_audio_sync_feedback = feedback;

		//printf(diff >= 0 ? "." : "^");
	}
	//serial_phex(c);
	//serial_print(".");
        for (unsigned int channel = 0, underrun = 0; channel < USB_AUDIO_RX_CHANNELS; channel++) {
                if (!channels[channel]) {
                        underrun ++;
                        usb_audio_underrun_count++;
                        //printf("#"); // buffer underrun - PC sending too slow
                        if (f) feedback_accumulator += 3500;
                        break;
                }
	}
        for (unsigned int channel = 0; channel < USB_AUDIO_RX_CHANNELS; channel++) {
                if (channels[channel]) {
                        transmit(channels[channel], channel);
                        release(channels[channel]);
                }
        }
}

















#if 1
bool AudioOutputUSB::update_responsibility;
audio_block_t * AudioOutputUSB::chan_1st[USB_AUDIO_TX_CHANNELS];
audio_block_t * AudioOutputUSB::chan_2nd[USB_AUDIO_TX_CHANNELS];
uint16_t AudioOutputUSB::offset_1st;

/*DMAMEM*/ uint16_t usb_audio_transmit_buffer[AUDIO_TX_SIZE/2] __attribute__ ((used, aligned(32)));


static void tx_event(transfer_t *t)
{
	int len = usb_audio_transmit_callback();
	usb_audio_sync_feedback = feedback_accumulator >> usb_audio_sync_rshift;
	usb_prepare_transfer(&tx_transfer, usb_audio_transmit_buffer, len, 0);
	arm_dcache_flush_delete(usb_audio_transmit_buffer, len);
	usb_transmit(AUDIO_TX_ENDPOINT, &tx_transfer);
}


void AudioOutputUSB::begin(void)
{
	update_responsibility = false;
        for (uint32_t i = 0; i < USB_AUDIO_TX_CHANNELS; i++) {
                chan_1st[i] = NULL;
        }
}

static void copy_from_buffers(uint16_t *dst, audio_block_t *channel_data[USB_AUDIO_TX_CHANNELS], uint32_t offset, unsigned int len_frames)
{
  // TODO: optimize...
  int16_t *src_ptrs[USB_AUDIO_TX_CHANNELS];
  
  for (uint32_t channel = 0; channel < USB_AUDIO_TX_CHANNELS; channel++)
    src_ptrs[channel] = channel_data[channel]->data + offset;
  
  while (len_frames > 0) {
    for (uint32_t channel = 0; channel < USB_AUDIO_TX_CHANNELS; channel++)
      *dst++ = *src_ptrs[channel]++;
    len_frames--;
  }
}


int AudioOutputUSB::allocate_tx_blocks(audio_block_t *blocks[USB_AUDIO_TX_CHANNELS])
{
  int alloc_errors = 0;
  // Try to allocate all blocks
  for (uint32_t channel = 0; channel < USB_AUDIO_TX_CHANNELS; channel++) {
    if (blocks[channel] == NULL) {
      blocks[channel] = allocate();
      if (blocks[channel] == NULL) {
        alloc_errors++;
        break;
      }
      memset(blocks[channel]->data, 0, sizeof(blocks[channel]->data));
    }
  }
  // Release on error
  if (alloc_errors) {
    for (uint32_t channel = 0; channel < USB_AUDIO_TX_CHANNELS; channel++) {
      if (blocks[channel]) {
        release(blocks[channel]);
        blocks[channel] = NULL;
      }
    }
  }
  return alloc_errors;
}

void AudioOutputUSB::update(void)
{
	audio_block_t *blocks[USB_AUDIO_TX_CHANNELS];

	// TODO: we shouldn't be writing to these......
	//left = receiveReadOnly(0); // input 0 = left channel
	//right = receiveReadOnly(1); // input 1 = right channel
  for (uint32_t channel = 0; channel < USB_AUDIO_TX_CHANNELS; channel++)
    blocks[channel] = receiveWritable(channel);

	if (usb_audio_transmit_setting == 0) {
    for (uint32_t channel = 0; channel < USB_AUDIO_TX_CHANNELS; channel++) {
      if (blocks[channel]) release(blocks[channel]);
      if (chan_1st[channel]) { release(chan_1st[channel]); chan_1st[channel] = NULL;}
      if (chan_2nd[channel]) { release(chan_2nd[channel]); chan_2nd[channel] = NULL;}
    }
		offset_1st = 0;
		return;
	}

  int alloc_errors = allocate_tx_blocks(blocks);
  if (alloc_errors)
    return;

	__disable_irq();
  
	if (chan_1st[0] == NULL) {
    for (uint32_t channel = 0; channel < USB_AUDIO_TX_CHANNELS; channel++)
      chan_1st[channel] = blocks[channel];
		offset_1st = 0;
	} else if (chan_2nd[0] == NULL) {
    for (uint32_t channel = 0; channel < USB_AUDIO_TX_CHANNELS; channel++)
      chan_2nd[channel] = blocks[channel];
	} else {
		// buffer overrun - PC is consuming too slowly
    audio_block_t *discard;
    for (uint32_t channel = 0; channel < USB_AUDIO_TX_CHANNELS; channel++) {
      discard = chan_1st[channel];
      chan_1st[channel] = chan_2nd[channel];
      chan_2nd[channel] = blocks[channel];
      release(discard);
    }
		offset_1st = 0; // TODO: discard part of this data?
		//serial_print("*");
	}
	__enable_irq();
}

void inject_ramp(uint32_t target, uint16_t *buffer) {
#ifdef INJECT_RECORD_RAMP
  static uint16_t ramp = 0;
  uint16_t *ptr = (uint16_t *)buffer;
  for (uint32_t i = 0; i < target; i++, ramp++) {
    for (uint32_t channel = 0; channel < USB_AUDIO_TX_CHANNELS; channel++) {
      uint16_t v = ramp;
      if (channel > 31)
        v >>=2;
      else if (channel >15)
        v >>=1;
      v &= 0x0FFF;
      *ptr++ = v + (channel << 12);
    }
  }
#endif  
}

// Called from the USB interrupt when ready to transmit another
// isochronous packet.  If we place data into the transmit buffer,
// the return is the number of bytes.  Otherwise, return 0 means
// no data to transmit
unsigned int usb_audio_transmit_callback(void)
{
	static uint32_t count=AUDIO_BASEFRAMES_EXTRA>>1;
	uint32_t target, len_frames=0;
	audio_block_t *blocks[USB_AUDIO_TX_CHANNELS];

  target = AUDIO_BASEFRAMES;
	if (++count < AUDIO_BASEFRAMES_EXTRA) {   // TODO: dynamic adjust to match USB rate
	} else {
    // for 44.1, every 10 usb frames, add an extra to the target
		count = 0;
    if (AUDIO_BASEFRAMES_EXTRA > 0)
      target++;
	}
	while (len_frames < target) {
    uint32_t num_frames = target - len_frames;
		if (AudioOutputUSB::chan_1st[0] == NULL) {
			// buffer underrun - PC is consuming too quickly
			memset(usb_audio_transmit_buffer + len_frames, 0, num_frames * USB_AUDIO_BYTES_PER_TX_FRAME);
			//serial_print("%");
			break;
		}
    for (uint32_t channel = 0; channel < USB_AUDIO_TX_CHANNELS; channel++) {
      blocks[channel] = AudioOutputUSB::chan_1st[channel];
    }
		uint32_t offset = AudioOutputUSB::offset_1st;

		uint32_t avail_frames = AUDIO_BLOCK_SAMPLES - offset;
		if (num_frames > avail_frames) num_frames = avail_frames;

		copy_from_buffers(usb_audio_transmit_buffer + len_frames*USB_AUDIO_TX_CHANNELS,
                      blocks, offset, num_frames);
		len_frames += num_frames;
		offset += num_frames;
		if (offset >= AUDIO_BLOCK_SAMPLES) {
      for (uint32_t channel = 0; channel < USB_AUDIO_TX_CHANNELS; channel++) {
        AudioStream::release(blocks[channel]);
        AudioOutputUSB::chan_1st[channel] = AudioOutputUSB::chan_2nd[channel];
        AudioOutputUSB::chan_2nd[channel] = NULL;
      }
      AudioOutputUSB::offset_1st = 0;
		} else {
			AudioOutputUSB::offset_1st = offset;
		}
	}
  uint32_t nbytes = target * USB_AUDIO_BYTES_PER_TX_FRAME;

  inject_ramp(target, usb_audio_transmit_buffer);
  return nbytes;
}
#endif




struct setup_struct {
  union {
    struct {
	uint8_t bmRequestType;
	uint8_t bRequest;
	union {
		struct {
			uint8_t bChannel;  // 0=main, 1=left, 2=right
			uint8_t bCS;       // Control Selector
		};
		uint16_t wValue;
	};
	union {
		struct {
			uint8_t bIfEp;     // type of entity
			uint8_t bEntityId; // UnitID, TerminalID, etc.
		};
		uint16_t wIndex;
	};
	uint16_t wLength;
    };
  };
};

int usb_audio_get_feature(void *stp, uint8_t *data, uint32_t *datalen)
{
	struct setup_struct setup = *((struct setup_struct *)stp);
	if (setup.bmRequestType==0xA1) { // should check bRequest, bChannel, and UnitID
			if (setup.bCS==0x01) { // mute
				data[0] = AudioInputUSB::features.mute;  // 1=mute, 0=unmute
				*datalen = 1;
				return 1;
			}
			else if (setup.bCS==0x02) { // volume
				if (setup.bRequest==0x81) { // GET_CURR
					data[0] = AudioInputUSB::features.volume & 0xFF;
					data[1] = (AudioInputUSB::features.volume>>8) & 0xFF;
				}
				else if (setup.bRequest==0x82) { // GET_MIN
					//serial_print("vol get_min\n");
					data[0] = 0;     // min level is 0
					data[1] = 0;
				}
				else if (setup.bRequest==0x83) { // GET_MAX
					data[0] = FEATURE_MAX_VOLUME;  // max level, for range of 0 to MAX
					data[1] = 0;
				}
				else if (setup.bRequest==0x84) { // GET_RES
					data[0] = 1; // increment vol by by 1
					data[1] = 0;
				}
				else { // pass over SET_MEM, etc.
					return 0;
				}
				*datalen = 2;
				return 1;
			}
	}
	return 0;
}

int usb_audio_set_feature(void *stp, uint8_t *buf) 
{
	struct setup_struct setup = *((struct setup_struct *)stp);
	if (setup.bmRequestType==0x21) { // should check bRequest, bChannel and UnitID
			if (setup.bCS==0x01) { // mute
				if (setup.bRequest==0x01) { // SET_CUR
					AudioInputUSB::features.mute = buf[0]; // 1=mute,0=unmute
					AudioInputUSB::features.change = 1;
					return 1;
				}
			}
			else if (setup.bCS==0x02) { // volume
				if (setup.bRequest==0x01) { // SET_CUR
					AudioInputUSB::features.volume = buf[0];
					AudioInputUSB::features.change = 1;
					return 1;
				}
			}
	}
	return 0;
}


#endif // AUDIO_INTERFACE
