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


#include "usb_desc.h"
#ifdef AUDIO_INTERFACE

#include "util/LastCall.h"

#define FEATURE_MAX_VOLUME 0xFF  // volume accepted from 0 to 0xFF
#define TARGET_RX_BUFFER_TIME_S 0.0018f	//targeted buffered time (latency) in seconds
#define MICROFRAME_US 125 // defined by the USB standard

#ifdef __cplusplus
extern "C" {
#endif
extern void usb_audio_configure();
extern uint8_t usb_audio_receive_setting;
extern uint8_t usb_audio_transmit_setting;
extern void usb_audio_receive_callback(unsigned int len);
extern unsigned int usb_audio_transmit_callback(void);
extern int usb_audio_set_feature(void *stp, uint8_t *buf);
extern int usb_audio_get_feature(void *stp, uint8_t *data, uint32_t *datalen);
#ifdef __cplusplus
}
#endif

// audio features supported
struct usb_audio_features_struct {
  int change;  // set to 1 when any value is changed
  int mute;    // 1=mute, 0=unmute
  int volume;  // volume from 0 to FEATURE_MAX_VOLUME, maybe should be float from 0.0 to 1.0
};

#ifdef __cplusplus

class USBAudioInInterface
{
public:
	struct Status {
		uint32_t usb_audio_underrun_count;		//How often did we run out of audio samples. (usb host sends audio data too slowly)
		uint32_t usb_audio_overrun_count;		//How often did we run out of buffer space.  (usb host sends audio data too fast)
		uint32_t audio_memory_underrun_count;	//How often did we run out audio blocks.  (Increase N in AudioMemory(N) if that happens)
		float target_num_buffered_samples;		//How many samples do want to be in the buffer directly after an 'update' call (the more samples, the more stable. Should at least be: (bInterval_uS*e-6) * AUDIO_SAMPLE_RATE)
		uint16_t num_transmitted_channels;		//How many audio channels do we receive (might be smaller than expected in case the 12Mbit/s bandwidth limits the number of channels)
		uint16_t ring_buffer_size;				//Number of audio blocks per channel in the ring buffer (received audio data from the host is stored in this buffer)
		uint16_t usb_rx_tx_buffer_size;			//=AUDIO_RX_SIZE_480 or AUDIO_RX_SIZE_12 (bytes, must be larger than AUDIO_SAMPLE_RATE * bInterval_uS*1e-6 * USB_AUDIO_NO_CHANNELS_480 * AUDIO_SUBSLOT_SIZE 
		uint16_t bInterval_uS;					//polling interval as requested by the Teensy (125, 250, 500 or 1000)
		bool receivingData;						//Teensy is currently receiving data (There was at least one 'usb_audio_receive_callback' since the last 'update' call)
		uint8_t usb_high_speed;					// 1 for high speed, 0 otherwise
	};
	typedef bool (*SetBlockQuite) (uint16_t bIdx, uint16_t channel);
	typedef void (*ReleaseBlock)(uint16_t bIdx, uint16_t channel);
	typedef bool (*AllocateBlock)(uint16_t bIdx, uint16_t channel);
	typedef bool (*AreBlocksReady)(uint16_t bIdx, uint16_t noChannels);
	typedef void (*Copy_to_buffers)(const uint8_t *src, uint16_t bIdx, uint16_t noChannels, unsigned int count, unsigned int len);
    constexpr static float blockDuration = AUDIO_BLOCK_SAMPLES/float(AUDIO_SAMPLE_RATE);
	//no buffered blocks computation
	//
	// +3:
	// +1 we round the number of needed blocks up
	// +1 because we store the block that is ready for transmission in the buffer
	// +1 just to have one block in reserve (prevents buffer overflows and comes at more or less no additional cost (at normal operation no additional latency + no additional memory needed))
	// *2: because to be symmetrically protected against buffer overflow (a high TARGET_RX_BUFFER_TIME_S only prevents buffer underflows)
	constexpr static uint16_t ringRxBufferSize = uint16_t(TARGET_RX_BUFFER_TIME_S / USBAudioInInterface::blockDuration) *2 +3;	
	
	USBAudioInInterface(
		SetBlockQuite sbq,
		ReleaseBlock rb,
		AllocateBlock ab,
		AreBlocksReady abr,
		Copy_to_buffers c_t_b,
		float kp =400.f,
		float ki =.2f );
	void begin();
	void stop();
    void update(int16_t& bIdx, uint16_t& noChannels);
    void incrementBufferIndex();
	float getBufferedSamples() const;
	float getBufferedSamplesSmooth() const;
	float getRequestedSamplingFrequ() const;
	float getActualBIntervalUs() const;
	Status getStatus() const;
	friend void usb_audio_receive_callback(unsigned int len);
	friend int usb_audio_set_feature(void *stp, uint8_t *buf);
	friend int usb_audio_get_feature(void *stp, uint8_t *data, uint32_t *datalen);
	static struct usb_audio_features_struct features;
	float volume(void) {
		if (features.mute) return 0.0;
		return (float)(features.volume) * (1.0 / (float)FEATURE_MAX_VOLUME);
	}

private:
	uint32_t _bufferedSamples=0;
	float _kp =400.f;
	float _ki =.2f;
	float _bufferedSamplesSmooth=0;
	bool _streaming= false;
	LastCall<50> _lastCallUpdate;
	static bool setBlocksQuite(uint32_t noBlocks);
	static bool allocateChannels(uint16_t idx);
	static bool resetBuffer(double updateCurrentSmooth);
	static bool isBufferReady();
	static void tryIncreaseIdxIncoming(uint16_t& count);
	static void releaseBlocks(uint16_t bufferIdx);
	static bool running;

	static SetBlockQuite setBlockQuite;
	static ReleaseBlock releaseBlock;
	static AllocateBlock allocateBlock;
	static AreBlocksReady areBlocksReady;
	static Copy_to_buffers copy_to_buffers;
};

#define TARGET_TX_BUFFER_TIME_S 0.0035f	//targeted buffered time (latency) in seconds
class USBAudioOutInterface {
public:
	enum BufferState{ready, full, overrun};
	struct Status {
		uint32_t usb_audio_underrun_count;	//How often did we run out of audio samples. (usb host requests audio data too fast)
		uint32_t usb_audio_overrun_count;	//How often did we run out of buffer space.  (usb host requests audio data too slowly)
		float target_num_buffered_samples;	//How many samples do want to be in the buffer directly after an 'usb_audio_transmit_callback' call (the more samples, the more stable. Should at least be: AUDIO_BLOCK_SAMPLES)
		uint16_t num_transmitted_channels;	//How many audio channels do we transmit (might be smaller than expected in case the 12Mbit/s bandwidth limits the number of channels)
		uint16_t ring_buffer_size;			//Number of audio blocks per channel in the ring buffer (audio blocks from the Teensy are stored in this buffer, before the data is sent to the host.)
		uint16_t usb_rx_tx_buffer_size;		//=AUDIO_TX_SIZE_480 or AUDIO_TX_SIZE_12 (bytes, must be larger than AUDIO_SAMPLE_RATE * bInterval_uS*1e-6 * USB_AUDIO_NO_CHANNELS_480 * AUDIO_SUBSLOT_SIZE 
		uint16_t bInterval_uS;				//polling interval as requested by the Teensy (125, 250, 500 or 1000)
		uint32_t num_skipped_Samples;		//only used if not ASYNC_TX_ENDPOINT (->adaptive endpoint)	In usb_audio_transmit_callback: how often was a sample skipped to prevent a buffer overrun.
		uint32_t num_padded_Samples;		//only used if not ASYNC_TX_ENDPOINT (->sdaptive endpoint)	In usb_audio_transmit_callback: how often was a sample padded to prevent a buffer underrun.
		uint32_t num_send_one_less;			//only used if ASYNC_TX_ENDPOINT (-> asynchronous endpoint)	In usb_audio_transmit_callback: how often was a sample less than initially planned sent to prevent a buffer underrun.
		uint32_t num_send_one_more;			//only used if ASYNC_TX_ENDPOINT (-> asynchronous endpoint)	In usb_audio_transmit_callback: how often was a sample more than initially planned sent to prevent a buffer overrun.
		bool transmittingData;				//Teensy is currently sending data to the host (There was at least one 'usb_audio_transmit_callback' since the last 'update' call)
		uint8_t usb_high_speed;				// 1 for high speed, 0 otherwise
	};

	typedef void (*ReleaseBlocks)(uint16_t bIdx, uint16_t noChannels);
	typedef bool (*IsBlockReady)(uint16_t bIdx, uint16_t channel);
	typedef void (*Copy_from_buffers)(uint8_t *dst, uint16_t bIdx, uint16_t noChannels, unsigned int count, unsigned int len);
    
	constexpr static float blockDuration = AUDIO_BLOCK_SAMPLES/float(AUDIO_SAMPLE_RATE);
	constexpr static uint16_t ringTxBufferSize = uint16_t(TARGET_TX_BUFFER_TIME_S / USBAudioInInterface::blockDuration) *2 +3;	

	USBAudioOutInterface(ReleaseBlocks rbs, IsBlockReady ibr, Copy_from_buffers c_f_b);
	void begin(void);
	void stop(void);
	void update(int16_t& bIdx, uint16_t& noChannels);
	void incrementBufferIndex();
	friend unsigned int usb_audio_transmit_callback(void);
	float getBufferedSamples() const;
	float getBufferedSamplesSmooth() const;
	float getActualBIntervalUs() const;
	Status getStatus() const;
private:
	static void tryIncreaseIdxTransmission(uint16_t& tBIdx, uint16_t& offset);
	bool _streaming= false;
	double _updateCurrentSmoothPending;
	LastCall<50> _lastCallUpdate;
	static double updateCurrentSmooth;
	static uint16_t outgoing_count;
	static bool running;
	
	static ReleaseBlocks releaseBlocks;
	static IsBlockReady isBlockReady;
	static Copy_from_buffers copy_from_buffer;
};

#endif // __cplusplus

#endif // AUDIO_INTERFACE
