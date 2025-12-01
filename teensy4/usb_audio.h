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

#pragma once

#include "usb_audio_interface.h"

#ifdef AUDIO_INTERFACE

#include "AudioStream.h"

class AudioInputUSB : public AudioStream
{
public:
	
	AudioInputUSB(float kp =400.f,float ki =.2f );
	virtual void update(void);
	void begin(void);
	float getBufferedSamples() const;
	float getBufferedSamplesSmooth() const;
	float getRequestedSamplingFrequ() const;
	float getActualBIntervalUs() const;
	USBAudioInInterface::Status getStatus() const;
	float volume(void);

private:
	static void copy_to_buffers(const uint8_t *src, uint16_t bIdx, uint16_t noChannels, unsigned int count, unsigned int len);
    static bool setBlockQuite(uint16_t bIdx, uint16_t channel);
    static void releaseBlock(uint16_t bIdx, uint16_t channel);
    static bool allocateBlock(uint16_t bIdx, uint16_t channel);
    static bool areBlocksReady(uint16_t bIdx, uint16_t noChannels);

    static audio_block_t* rxBuffer[USBAudioInInterface::ringRxBufferSize][USB_AUDIO_MAX_NO_CHANNELS];
    USBAudioInInterface _usbInterface;
};


#if USB_AUDIO_NO_CHANNELS_480 >= 4
class AudioInputUSBQuad : public AudioInputUSB { public: AudioInputUSBQuad(float kp =400.f,float ki =.2f) : AudioInputUSB(kp, ki) {} };
#if USB_AUDIO_NO_CHANNELS_480 >= 6
class AudioInputUSBHex : public AudioInputUSB { public: AudioInputUSBHex(float kp =400.f,float ki =.2f) : AudioInputUSB(kp, ki) {} };
#if USB_AUDIO_NO_CHANNELS_480 >= 8
class AudioInputUSBOct : public AudioInputUSB { public: AudioInputUSBOct(float kp =400.f,float ki =.2f) : AudioInputUSB(kp, ki) {} };
#endif // USB_AUDIO_NO_CHANNELS_480 >= 8
#endif // USB_AUDIO_NO_CHANNELS_480 >= 6
#endif // USB_AUDIO_NO_CHANNELS_480 >= 4


class AudioOutputUSB : public AudioStream
{
public:
	AudioOutputUSB(void);
	AudioOutputUSB(int nch);
	virtual void update(void);
	void begin(void);
    
	float getBufferedSamples() const;
	float getBufferedSamplesSmooth() const;
	float getActualBIntervalUs() const;
	USBAudioOutInterface::Status getStatus() const;    

private:

    static void copy_from_buffers(uint8_t *dst, uint16_t bIdx, uint16_t noChannels, unsigned int count, unsigned int len);
	static void releaseBlocks(uint16_t bIdx, uint16_t noChannels);
    static bool isBlockReady(uint16_t bIdx, uint16_t channel);

	static audio_block_t* txBuffer[USBAudioOutInterface::ringTxBufferSize][USB_AUDIO_MAX_NO_CHANNELS];
	audio_block_t *inputQueueArray[USB_AUDIO_MAX_NO_CHANNELS];
    USBAudioOutInterface _usbInterface;
};

#if USB_AUDIO_NO_CHANNELS_480 >= 4
class AudioOutputUSBQuad : public AudioOutputUSB { public: AudioOutputUSBQuad(void) : AudioOutputUSB(4) {} };
#if USB_AUDIO_NO_CHANNELS_480 >= 6
class AudioOutputUSBHex : public AudioOutputUSB { public: AudioOutputUSBHex(void) : AudioOutputUSB(6) {} };
#if USB_AUDIO_NO_CHANNELS_480 >= 8
class AudioOutputUSBOct : public AudioOutputUSB { public: AudioOutputUSBOct(void) : AudioOutputUSB(8) {} };
#endif // USB_AUDIO_NO_CHANNELS_480 >= 8
#endif // USB_AUDIO_NO_CHANNELS_480 >= 6
#endif // USB_AUDIO_NO_CHANNELS_480 >= 4

#endif // AUDIO_INTERFACE
