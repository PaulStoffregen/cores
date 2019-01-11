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

#ifndef USBaudio_h_
#define USBaudio_h_

#include "usb_desc.h"
#ifdef AUDIO_INTERFACE

#define FEATURE_MAX_VOLUME 0xFFF  // volume accepted from 0 to 0xFFF

#ifdef __cplusplus
extern "C" {
#endif
extern uint16_t usb_audio_receive_buffer[];
extern uint16_t usb_audio_transmit_buffer[];
extern void usb_audio_receive_callback(unsigned int len);
extern unsigned int usb_audio_transmit_callback(void);
int usb_audio_set_feature(void *stp, uint8_t *buf);
int usb_audio_get_feature(void *stp, uint8_t *data, uint32_t *datalen);

extern uint32_t usb_audio_sync_feedback;
extern uint8_t usb_audio_receive_setting;
extern uint8_t usb_audio_transmit_setting;
#ifdef __cplusplus
}

// audio features supported
struct usb_audio_features_struct {
  int change;  // set to 1 when any value is changed
  int mute;    // 1=mute, 0=unmute
  int volume;  // volume from 0 to FEATURE_MAX_VOLUME, maybe should be float from 0.0 to 1.0
};

#include "AudioStream.h"

class AudioInputUSB : public AudioStream
{
public:
	AudioInputUSB(void) : AudioStream(0, NULL) { begin(); }
	virtual void update(void);
	void begin(void);
	friend void usb_audio_receive_callback(unsigned int len);
	friend int usb_audio_set_feature(void *stp, uint8_t *buf);
	friend int usb_audio_get_feature(void *stp, uint8_t *data, uint32_t *datalen);
	static struct usb_audio_features_struct features;
	float volume(void) {
		if (features.mute) return 0.0;
		return (float)(features.volume) * (1.0 / (float)FEATURE_MAX_VOLUME);
	}
private:
	static bool update_responsibility;
	static audio_block_t *incoming_left;
	static audio_block_t *incoming_right;
	static audio_block_t *ready_left;
	static audio_block_t *ready_right;
	static uint16_t incoming_count;
	static uint8_t receive_flag;
};

class AudioOutputUSB : public AudioStream
{
public:
	AudioOutputUSB(void) : AudioStream(2, inputQueueArray) { begin(); }
	virtual void update(void);
	void begin(void);
	friend unsigned int usb_audio_transmit_callback(void);
private:
	static bool update_responsibility;
	static audio_block_t *left_1st;
	static audio_block_t *left_2nd;
	static audio_block_t *right_1st;
	static audio_block_t *right_2nd;
	static uint16_t offset_1st;
	audio_block_t *inputQueueArray[2];
};

#endif // __cplusplus
#endif // AUDIO_INTERFACE
#endif // USBaudio_h_
