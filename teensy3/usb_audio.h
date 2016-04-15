#ifndef USBaudio_h_
#define USBaudio_h_

#include "usb_desc.h"
#ifdef AUDIO_INTERFACE

#ifdef __cplusplus
extern "C" {
#endif
extern uint16_t usb_audio_receive_buffer[];
extern uint16_t usb_audio_transmit_buffer[];
extern void usb_audio_receive_callback(unsigned int len);
extern unsigned int usb_audio_transmit_callback(void);
extern uint32_t usb_audio_sync_feedback;
#ifdef __cplusplus
}

#include "AudioStream.h"

class AudioInputUSB : public AudioStream
{
public:
	AudioInputUSB(void) : AudioStream(0, NULL) { begin(); }
	virtual void update(void);
	void begin(void);
	friend void usb_audio_receive_callback(unsigned int len);
private:
	static bool update_responsibility;
	static audio_block_t *incoming_left;
	static audio_block_t *incoming_right;
	static audio_block_t *ready_left;
	static audio_block_t *ready_right;
	static uint16_t incoming_count;
	static uint8_t underflow_flag;
};

#endif // __cplusplus
#endif // AUDIO_INTERFACE
#endif // USBaudio_h_
