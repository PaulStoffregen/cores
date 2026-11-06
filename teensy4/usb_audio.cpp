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

#include "usb_audio.h"

#ifdef AUDIO_INTERFACE


audio_block_t* AudioInputUSB::rxBuffer[USBAudioInInterface::ringRxBufferSize][USB_AUDIO_MAX_NO_CHANNELS];
audio_block_t* AudioOutputUSB::txBuffer[USBAudioOutInterface::ringTxBufferSize][USB_AUDIO_MAX_NO_CHANNELS];

void AudioInputUSB::update(void){
	int16_t bIdx = -1;
	uint16_t noChannels;
	_usbInterface.update(bIdx, noChannels);
	if(bIdx != -1){
		for (uint16_t i =0; i<noChannels; i++){
			transmit(rxBuffer[bIdx][i], i);
			release(rxBuffer[bIdx][i]);
			rxBuffer[bIdx][i]=NULL;
		}
		_usbInterface.incrementBufferIndex();
	}
}
AudioInputUSB::AudioInputUSB(float kp,float ki) 
	: AudioStream(0, NULL), _usbInterface(setBlockQuite,releaseBlock,allocateBlock,areBlocksReady,copy_to_buffers,kp, ki) {
		        
	for (uint16_t i =0; i< USBAudioInInterface::ringRxBufferSize; i++){
		for (uint16_t j =0; j< USB_AUDIO_MAX_NO_CHANNELS; j++){
			rxBuffer[i][j]=NULL;
		}
	}
	_usbInterface.begin();
}
void AudioInputUSB::begin(void){
}

float AudioInputUSB::getBufferedSamples() const{
	return _usbInterface.getBufferedSamples();
}
float AudioInputUSB::getBufferedSamplesSmooth() const{
	return _usbInterface.getBufferedSamplesSmooth();
}
float AudioInputUSB::getRequestedSamplingFrequ() const{
	return _usbInterface.getRequestedSamplingFrequ();
}
float AudioInputUSB::getActualBIntervalUs() const{
	return _usbInterface.getActualBIntervalUs();
}
USBAudioInInterface::Status AudioInputUSB::getStatus() const{
	return _usbInterface.getStatus();
}

float AudioInputUSB::volume(void){
	return _usbInterface.volume();
}
#if AUDIO_SUBSLOT_SIZE==2
void AudioInputUSB::copy_to_buffers(const uint8_t *src, uint16_t bIdx, uint16_t noChannels, unsigned int count, unsigned int len) {
	const uint16_t *src16Bit =(const uint16_t *)src;
	for (uint32_t i =0; i< len; i++){
		for (uint16_t j =0; j< noChannels; j++){
			rxBuffer[bIdx][j]->data[count +i]=*src16Bit++;
		}
	}
}
#endif

#if AUDIO_SUBSLOT_SIZE==3
void AudioInputUSB::copy_to_buffers(const uint8_t *src, uint16_t bIdx, uint16_t noChannels, unsigned int count, unsigned int len) {
	for (uint32_t i =0; i< len; i++){
		for (uint16_t j =0; j< noChannels; j++){
			++src;
			rxBuffer[bIdx][j]->data[count +i]=(*src++);
			rxBuffer[bIdx][j]->data[count +i] |=(*src++)<<8;
		}
	}
}
#endif
bool AudioInputUSB::setBlockQuite(uint16_t bIdx, uint16_t channel){        
	if(!rxBuffer[bIdx][channel]){
		rxBuffer[bIdx][channel] = AudioStream::allocate();
	}
	if(rxBuffer[bIdx][channel]){
		memset(rxBuffer[bIdx][channel]->data, 0, AUDIO_BLOCK_SAMPLES*sizeof(rxBuffer[bIdx][channel]->data[0]));
		return true;
	}
	return false;
}
void AudioInputUSB::releaseBlock(uint16_t bIdx, uint16_t channel){        
	if(rxBuffer[bIdx][channel]){
		AudioStream::release(rxBuffer[bIdx][channel]);
		rxBuffer[bIdx][channel]=NULL;
	}
}
bool AudioInputUSB::allocateBlock(uint16_t bIdx, uint16_t channel){        
	if(!rxBuffer[bIdx][channel]){
		rxBuffer[bIdx][channel] = AudioStream::allocate();
	}
	return rxBuffer[bIdx][channel] != NULL;
}
bool AudioInputUSB::areBlocksReady(uint16_t bIdx, uint16_t noChannels){
	for (uint16_t i =0; i<noChannels; i++){
		if(!rxBuffer[bIdx][i]){
			return false;
		}
	}
	return true;
}





AudioOutputUSB::AudioOutputUSB(void) :
	AudioStream(USB_AUDIO_MAX_NO_CHANNELS, inputQueueArray),
	_usbInterface(releaseBlocks, isBlockReady, copy_from_buffers)
	{
		begin();
		_usbInterface.begin();
	}
AudioOutputUSB::AudioOutputUSB(int nch) :
	AudioStream(nch, inputQueueArray),
	_usbInterface(releaseBlocks, isBlockReady, copy_from_buffers)
	{
		begin();
		_usbInterface.begin();
	}
void AudioOutputUSB::update(void){

	int16_t bIdx = -1;
	uint16_t noChannels;
	_usbInterface.update(bIdx, noChannels);
	if(bIdx < 0){
		//_usbInterface is not running for some reason
		for (uint16_t i =0; i< USB_AUDIO_MAX_NO_CHANNELS; i++){
			audio_block_t* b = receiveReadOnly(i);
			if(b){
				release(b);
			}
		}
	}
	for (uint16_t i =0; i< noChannels; i++){
		if(txBuffer[bIdx][i]){
			release(txBuffer[bIdx][i]);
		}
		txBuffer[bIdx][i]=receiveReadOnly(i);
		if(!txBuffer[bIdx][i]){
			if(!txBuffer[bIdx][i]){
				txBuffer[bIdx][i] = AudioStream::allocate();
			}
			if(txBuffer[bIdx][i]){
				memset(txBuffer[bIdx][i]->data, 0, AUDIO_BLOCK_SAMPLES*sizeof(txBuffer[bIdx][i]->data[0]));
			}
			else {
				//we ran out of audio memory
				releaseBlocks(bIdx, noChannels);
				break;
			}
		}
	}
	_usbInterface.incrementBufferIndex();
}
void AudioOutputUSB::begin(void){        
	for (uint16_t i =0; i< USBAudioOutInterface::ringTxBufferSize; i++){
		for (uint16_t j =0; j< USB_AUDIO_MAX_NO_CHANNELS; j++){
			txBuffer[i][j]=NULL;
		}
	}
}
float AudioOutputUSB::getBufferedSamples() const{
	return _usbInterface.getBufferedSamples();
}
float AudioOutputUSB::getBufferedSamplesSmooth() const{
	return _usbInterface.getBufferedSamplesSmooth();
}
float AudioOutputUSB::getActualBIntervalUs() const{
	return _usbInterface.getActualBIntervalUs();
}
USBAudioOutInterface::Status AudioOutputUSB::getStatus() const{
	return _usbInterface.getStatus();
}
#if AUDIO_SUBSLOT_SIZE==2
void AudioOutputUSB::copy_from_buffers(uint8_t *dst, uint16_t bIdx, uint16_t noChannels, unsigned int count, unsigned int len) {
	uint16_t* dst16Bit = (uint16_t*)dst;
	for (uint32_t i =0; i< len; i++){
		for (uint16_t j =0; j< noChannels; j++){
			*dst16Bit++ =txBuffer[bIdx][j]->data[count +i];
		}
	}
}
#endif

#if AUDIO_SUBSLOT_SIZE==3
void AudioOutputUSB::copy_from_buffers(uint8_t *dst, uint16_t bIdx, uint16_t noChannels, unsigned int count, unsigned int len) {
	for (uint32_t i =0; i< len; i++){
		for (uint16_t j =0; j< noChannels; j++){
			*dst++ =0;
			*dst++ =((txBuffer[bIdx][j]->data[count +i])) & 255;
			*dst++ =((txBuffer[bIdx][j]->data[count +i]) >> 8) & 255;
		}
	}
}
#endif

void AudioOutputUSB::releaseBlocks(uint16_t bIdx, uint16_t noChannels){  
	for (uint16_t i =0; i< noChannels; i++){
		if(txBuffer[bIdx][i]){
			AudioStream::release(txBuffer[bIdx][i]);
			txBuffer[bIdx][i]=NULL;
		}
	}
}

bool AudioOutputUSB::isBlockReady(uint16_t bIdx, uint16_t channel){
	return txBuffer[bIdx][channel]!=NULL;
}

#endif //AUDIO_INTERFACE