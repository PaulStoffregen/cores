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
#include "usb_audio_interface.h"
#include "debug/printf.h"

#include <string>

#ifdef AUDIO_INTERFACE
namespace {	
	
	//variables used by USBAudioInInterface and AudioOutputUSB ==================
  #if (USB_AUDIO_NO_CHANNELS_12*AUDIO_NUM_SUBFRAMES_PER_POLLING_12) < (USB_AUDIO_NO_CHANNELS_480*AUDIO_NUM_SUBFRAMES_PER_POLLING_480)
    #define AUDIO_TX_SIZE         AUDIO_RX_SIZE_480
    #define AUDIO_RX_SIZE         AUDIO_RX_SIZE_480
  #else
    #define AUDIO_TX_SIZE         AUDIO_RX_SIZE_12
    #define AUDIO_RX_SIZE         AUDIO_RX_SIZE_12
  #endif

	uint16_t noTransmittedChannels=0;	//depending if usb_high_speed if true this is either USB_AUDIO_MAX_NO_CHANNELS or 2 as fall-back strategy
	float audioPollingIntervalSec=0;
	uint16_t audioPollingIntervaluS =0;
	uint32_t noSamplesPerPollingInterval=0;
	constexpr uint32_t samplingRate=uint32_t(AUDIO_SAMPLE_RATE);
	float expectedIsrIntervalCycles;

	//======================================================================

	//variables used by USBAudioInInterface ================================
	LastCall<7> lastCallReceiveIsr;
	float sumDiff=0.;
	float lastDiff=0.;	
	
	constexpr float targetNumRxBufferedSamples = TARGET_RX_BUFFER_TIME_S*AUDIO_SAMPLE_RATE;
	bool rxBufferReady= false;	                    //used to indicate if the reset after e.g. a buffer overrun is completed
	volatile bool rxBufferOverrun = false;			//changed in usb_audio_receive_callback
	volatile uint32_t rxMemoryUnderrunCounter=0;	//changed in usb_audio_receive_callback
	volatile uint16_t incoming_rx_bIdx=0;			//changed in usb_audio_receive_callback
	volatile uint16_t rxIncoming_count=0;			//changed in usb_audio_receive_callback
	volatile uint8_t receive_flag;					//changed in usb_audio_receive_callback

	uint16_t transmit_rx_bIdx=0;
	uint32_t feedback_accumulator;
	uint32_t feedback_accumulator_default;

	volatile uint32_t rxUsb_audio_underrun_count;	//changed in update
	volatile uint32_t rxUsb_audio_overrun_count;	//changed in update
	
	float getNumBufferedRxSamples(uint16_t incomingIdx, uint16_t transmitIdx, uint16_t incomingCount){
		float bufferedSamples= incomingCount;
		if(incomingIdx > transmitIdx+1 ){
			bufferedSamples+=(incomingIdx-(transmitIdx+1))*AUDIO_BLOCK_SAMPLES;
		}
		else if(incomingIdx < transmitIdx){
			bufferedSamples += incomingIdx*AUDIO_BLOCK_SAMPLES;
			if(transmitIdx +1 < USBAudioInInterface::ringRxBufferSize){
				bufferedSamples += (USBAudioInInterface::ringRxBufferSize-(transmitIdx +1))*AUDIO_BLOCK_SAMPLES;
			}
		}
		return bufferedSamples;
	}
	//========================================================================
}

struct usb_audio_features_struct USBAudioInInterface::features = {0,0,FEATURE_MAX_VOLUME/2};
USBAudioInInterface::SetBlockQuite USBAudioInInterface::setBlockQuite;
USBAudioInInterface::ReleaseBlock USBAudioInInterface::releaseBlock;
USBAudioInInterface::AllocateBlock USBAudioInInterface::allocateBlock;
USBAudioInInterface::AreBlocksReady USBAudioInInterface::areBlocksReady;
USBAudioInInterface::Copy_to_buffers USBAudioInInterface::copy_to_buffers;

extern volatile uint8_t usb_high_speed;
bool USBAudioInInterface::running=false;
static void rx_event(transfer_t *t);
static void tx_event(transfer_t *t);

/*static*/ transfer_t rx_transfer __attribute__ ((used, aligned(32)));
/*static*/ transfer_t sync_transfer __attribute__ ((used, aligned(32)));
/*static*/ transfer_t tx_transfer __attribute__ ((used, aligned(32)));
DMAMEM static uint8_t rx_buffer[AUDIO_RX_SIZE] __attribute__ ((aligned(32)));
DMAMEM uint32_t usb_audio_sync_feedback __attribute__ ((aligned(32)));

uint8_t usb_audio_receive_setting=0;	//set in usb.c
uint8_t usb_audio_transmit_setting=0;	//set in usb.c
uint8_t usb_audio_sync_nbytes;
uint8_t usb_audio_sync_rshift;


static void rx_event(transfer_t *t)
{
	if (t) {
		int len = AUDIO_RX_SIZE - ((rx_transfer.status >> 16) & 0x7FFF);
		//printf("rx %u\n", len);
		usb_audio_receive_callback(len);
	}
	usb_prepare_transfer(&rx_transfer, rx_buffer, AUDIO_RX_SIZE, 0);
	arm_dcache_delete(&rx_buffer, AUDIO_RX_SIZE);
	usb_receive(AUDIO_RX_ENDPOINT, &rx_transfer);
}

static void sync_event(transfer_t *t)
{
	const uint32_t noRequestedBytes = feedback_accumulator/0x1000000* USB_AUDIO_NO_CHANNELS_480 * AUDIO_SUBSLOT_SIZE; //float fs = feedback_accumulator/(audioPollingIntervalSec*0x1000000);
	if(noRequestedBytes>AUDIO_RX_SIZE_480){
		//maximum amount
		feedback_accumulator =AUDIO_RX_SIZE_480 *0x1000000/(USB_AUDIO_NO_CHANNELS_480 * AUDIO_SUBSLOT_SIZE);
	}
	// USB 2.0 Specification, 5.12.4.2 Feedback, pages 73-75
	//printf("sync %x\n", sync_transfer.status); // too slow, can't print this much
	usb_audio_sync_feedback = feedback_accumulator >> usb_audio_sync_rshift;
	usb_prepare_transfer(&sync_transfer, &usb_audio_sync_feedback, usb_audio_sync_nbytes, 0);
	arm_dcache_flush(&usb_audio_sync_feedback, usb_audio_sync_nbytes);
	usb_transmit(AUDIO_SYNC_ENDPOINT, &sync_transfer);
}

USBAudioInInterface::Status USBAudioInInterface::getStatus() const{
	USBAudioInInterface::Status status;
	NVIC_DISABLE_IRQ(IRQ_SOFTWARE);
	status.usb_audio_underrun_count = rxUsb_audio_underrun_count;
	status.usb_audio_overrun_count = rxUsb_audio_overrun_count;
	status.audio_memory_underrun_count = rxMemoryUnderrunCounter;
	status.target_num_buffered_samples = targetNumRxBufferedSamples;
	status.num_transmitted_channels = noTransmittedChannels;
	status.ring_buffer_size = ringRxBufferSize;
	status.usb_rx_tx_buffer_size = AUDIO_RX_SIZE;
	status.receivingData=_streaming;
	status.bInterval_uS = audioPollingIntervaluS;
	status.usb_high_speed = usb_high_speed;
	NVIC_ENABLE_IRQ(IRQ_SOFTWARE);
	return status;
}

void USBAudioInInterface::releaseBlocks(uint16_t bufferIdx){
	for (uint16_t j =0; j< noTransmittedChannels; j++){
        USBAudioInInterface::releaseBlock(bufferIdx, j);
	}	
}

bool USBAudioInInterface::setBlocksQuite(uint32_t noBlocks){
	bool allocationSuccessful=true;
	for (uint16_t i =0; i< USBAudioInInterface::ringRxBufferSize; i++){
		for (uint16_t j =0; j< noTransmittedChannels; j++){
			if(i < noBlocks){
                if (!USBAudioInInterface::setBlockQuite(i, j)){
					//allocation failed
					allocationSuccessful=false;
					break;
                }
			}
			else {
                USBAudioInInterface::releaseBlock(i,j);
			}
		}
	}
	if(!allocationSuccessful){
		for (uint16_t i =0; i< USBAudioInInterface::ringRxBufferSize; i++){
			releaseBlocks(i);
		}	
	}
	return allocationSuccessful;
}

bool USBAudioInInterface::allocateChannels(uint16_t idx){
	for (uint16_t i =0; i< noTransmittedChannels; i++){
		if(!USBAudioInInterface::allocateBlock(idx,i)){
			//allocation failed	-> release all blocks that were allocated		
			releaseBlocks(idx);
			return false;
		}
	}
	return true;
}

USBAudioInInterface::USBAudioInInterface(
		SetBlockQuite sbq,
		ReleaseBlock rb,
		AllocateBlock ab,
		AreBlocksReady abr,
		Copy_to_buffers c_t_b,
		float kp,
		float ki) 
		: _kp(kp), _ki(ki) 
{
	USBAudioInInterface::setBlockQuite =sbq;
	USBAudioInInterface::releaseBlock = rb;
	USBAudioInInterface::allocateBlock = ab;
	USBAudioInInterface::areBlocksReady = abr;
	USBAudioInInterface::copy_to_buffers = c_t_b;
}


void USBAudioInInterface::begin(){
	__disable_irq();
	if(USBAudioInInterface::running){
		__enable_irq();
		return;
	}
	USBAudioInInterface::running=true;
	_bufferedSamplesSmooth=0;
	_bufferedSamples=0;
	rxIncoming_count = 0;
	receive_flag = 0;
	_streaming=false;
	_lastCallUpdate.reset(blockDuration*F_CPU_ACTUAL);
	lastCallReceiveIsr.reset(expectedIsrIntervalCycles);
	__enable_irq();

}


float USBAudioInInterface::getActualBIntervalUs() const {
	float toUS =1000000.f/F_CPU_ACTUAL;
	NVIC_DISABLE_IRQ(IRQ_SOFTWARE);
	float bInterval= (float)lastCallReceiveIsr.getLastDuration()*toUS;
	NVIC_ENABLE_IRQ(IRQ_SOFTWARE);
	return bInterval;
}


void USBAudioInInterface::stop(){
	__disable_irq();
	if(!USBAudioInInterface::running){
		__enable_irq();
		return;
	}
	USBAudioInInterface::running=false;
	_bufferedSamplesSmooth=0;
	_bufferedSamples=0;
	__enable_irq();
}


void USBAudioInInterface::tryIncreaseIdxIncoming(uint16_t& count){
	uint16_t idx = (incoming_rx_bIdx+1)%ringRxBufferSize;
	if(idx == transmit_rx_bIdx){
		return;
	}
	incoming_rx_bIdx=idx;
	if(!USBAudioInInterface::allocateChannels(incoming_rx_bIdx)){
		rxMemoryUnderrunCounter++;
		return;
	}
	count =0;	
}

// Called from the USB interrupt when an isochronous packet arrives
// we must completely remove it from the receive buffer before returning
//
#if 1
void usb_audio_receive_callback(unsigned int len)
{	
	if(!USBAudioInInterface::running){
		return;
	}
	uint32_t t = ARM_DWT_CYCCNT;
	lastCallReceiveIsr.addCall(t);

	// Over-estimate of audio update() calls before the callback fires again:
	receive_flag = (audioPollingIntervaluS * samplingRate / AUDIO_BLOCK_SAMPLES / 1'000'000) + 1;

	if(!rxBufferReady){
		return;
	}
	
	len /= (AUDIO_SUBSLOT_SIZE* noTransmittedChannels); // 1 sample = AUDIO_SUBSLOT_SIZE bytes times noTransmittedChannels channels
	uint16_t count =  rxIncoming_count;
	const uint8_t *data = rx_buffer;
	while (len > 0){
		if(count == AUDIO_BLOCK_SAMPLES){
			//we filled the blocks -> try to increase the ring buffer index and allocate new blocks 
			USBAudioInInterface::tryIncreaseIdxIncoming(count);
		}
		if(count == AUDIO_BLOCK_SAMPLES){
			//we were not able to increase the buffer index in the ring index
			rxBufferOverrun=true;
			rxIncoming_count=count;
			return;
		}
		uint32_t avail = AUDIO_BLOCK_SAMPLES - count;
		uint32_t numToCopy = min(avail, len);
		USBAudioInInterface::copy_to_buffers(data, incoming_rx_bIdx, noTransmittedChannels, count, numToCopy);
		data+=noTransmittedChannels*numToCopy *AUDIO_SUBSLOT_SIZE;
		count+=numToCopy;
		len-=numToCopy;
	}
	if(count == AUDIO_BLOCK_SAMPLES){
		//maybe we can already provide the current incoming_rx_bIdx block and prevent a buffer underflow
		//if tryIncreaseIdxIncoming fails now, there is still the chance that it will succeed at the next ISR call
		USBAudioInInterface::tryIncreaseIdxIncoming(count);
	}
	rxIncoming_count=count;
}
#endif

float USBAudioInInterface::getBufferedSamples() const{
	NVIC_DISABLE_IRQ(IRQ_SOFTWARE);
	float b = _bufferedSamples;
	NVIC_ENABLE_IRQ(IRQ_SOFTWARE);
	return b;
}
float USBAudioInInterface::getBufferedSamplesSmooth() const{
	NVIC_DISABLE_IRQ(IRQ_SOFTWARE);
	float b = _bufferedSamplesSmooth;
	NVIC_ENABLE_IRQ(IRQ_SOFTWARE);
	return b;
}
float USBAudioInInterface::getRequestedSamplingFrequ() const{	
	NVIC_DISABLE_IRQ(IRQ_SOFTWARE);
	float fs = feedback_accumulator/(audioPollingIntervalSec*0x1000000);
	NVIC_ENABLE_IRQ(IRQ_SOFTWARE);
	return fs;
}
bool USBAudioInInterface::isBufferReady() {
	if(transmit_rx_bIdx == incoming_rx_bIdx){
		return false;
	}
    return USBAudioInInterface::areBlocksReady(transmit_rx_bIdx, noTransmittedChannels);
}
bool USBAudioInInterface::resetBuffer(double updateCurrentSmooth){
	//resetBuffer should be called from the update function
	//Here we prepare the buffer for the transmission after a buffer under- or overflow or at the beginning of a stream

	//first we estimate when the last USB samples arrived
	double timeSinceLastUSBPaket=0.;
	History<7> historyIsr = lastCallReceiveIsr.getHistory();	//important: a new history is needed that is consistent with incoming_rx_bIdx
	if(historyIsr.valid){
		//historyUpdate.valid is always true
		double lastIsrSmooth = lastCallReceiveIsr.getLastCall<2>(historyIsr, expectedIsrIntervalCycles);
		timeSinceLastUSBPaket = toUInt32Range(updateCurrentSmooth - lastIsrSmooth);
		timeSinceLastUSBPaket /= F_CPU_ACTUAL; //to seconds
		if(timeSinceLastUSBPaket > 1.5f*audioPollingIntervalSec || timeSinceLastUSBPaket < -0.5f){
			//normally this should not happen
			timeSinceLastUSBPaket = 0.5f*blockDuration;
		}
	}
	else {
		timeSinceLastUSBPaket = expectedIsrIntervalCycles*0.5/F_CPU_ACTUAL;
	}
	//=====================================================

	//now we set incoming_rx_bIdx, transmit_rx_bIdx and incoming_count
	float resetTimeSec = TARGET_RX_BUFFER_TIME_S+blockDuration-timeSinceLastUSBPaket;	//+blockDuration because we want to transmit one block after this function
	uint32_t resetSamples = uint32_t(resetTimeSec*AUDIO_SAMPLE_RATE);
	uint32_t noBufferedBlocks = resetSamples/AUDIO_BLOCK_SAMPLES;
	uint32_t count = resetSamples - noBufferedBlocks *AUDIO_BLOCK_SAMPLES;
	uint32_t bufferIdx = noBufferedBlocks;

	//We need to set incoming_count to back to the target value.
	//Otherwise we will nearly have an overrun at the next update call.
	//This would make it very difficult for the controller to work
	rxIncoming_count = count;
	incoming_rx_bIdx = uint16_t(bufferIdx);
	transmit_rx_bIdx =0;
	return USBAudioInInterface::allocateChannels(incoming_rx_bIdx);
}

void USBAudioInInterface::incrementBufferIndex(){
    __disable_irq();
    transmit_rx_bIdx = (transmit_rx_bIdx+1)%ringRxBufferSize;	//it is ok if transmit_rx_bIdx==incoming_rx_bIdx here
    __enable_irq();   
}
void USBAudioInInterface::update(int16_t& bIdx, uint16_t& noChannels)
{	
    bIdx = -1;    // -1 means that there is nothing to transmit
    noChannels =noTransmittedChannels;
	
	if(!USBAudioInInterface::running){
		return;
	}
	//update time measurement of update calls
	uint32_t clockCount = ARM_DWT_CYCCNT;
	_lastCallUpdate.addCall(clockCount);
	History<50> historyUpdate = _lastCallUpdate.getHistory();
	double updateCurrentSmooth= _lastCallUpdate.getLastCall<20>(historyUpdate, blockDuration*F_CPU_ACTUAL);	
	//=======================================

	//get all information related to the USB receive ISR
	__disable_irq();
		History<7> historyIsr = lastCallReceiveIsr.getHistory();
		bool bufferUnderflow = !isBufferReady();
		rxBufferReady = !bufferUnderflow && !rxBufferOverrun;
		if(rxBufferOverrun){
			rxUsb_audio_overrun_count++;
		}
		uint16_t ic = rxIncoming_count;
		uint16_t iIdx = incoming_rx_bIdx;
		// Check if USB receive callback is firing correctly.
		// Should never reach 0 if all is well.
		uint8_t f = receive_flag;
		if (receive_flag) receive_flag--;
	__enable_irq();
	//=======================================
	if(_streaming && !f){
		//the stream just stopped -> reset
		_streaming=false;
		lastCallReceiveIsr.reset(expectedIsrIntervalCycles);
		sumDiff = 0.;
		feedback_accumulator = feedback_accumulator_default;
	}
	
	if ((_streaming && !rxBufferReady) ||	//we are already streaming but encounter a buffer over- or underrun
		(!_streaming && f))	//we just start streaming -> we reset the buffer (fill it with the targeted number of samples)
	{
		_streaming = true;	//this is maybe the start of a stream
		if(bufferUnderflow && f){
			//we count under-runs only if we currently receive audio data from the host (f!=0)
			rxUsb_audio_underrun_count++;
		}
		float resetTimeSec = TARGET_RX_BUFFER_TIME_S+blockDuration;	//+blockDuration because we will transmit one block after this function and want TARGET_RX_BUFFER_TIME_S after this transmission
		uint32_t resetSamples = uint32_t(resetTimeSec*AUDIO_SAMPLE_RATE);
		uint32_t noBufferedBlocks = resetSamples/AUDIO_BLOCK_SAMPLES +1;
		if(setBlocksQuite(noBufferedBlocks)){
			__disable_irq();
			//this must all happen in one un-interrupted block
			rxBufferReady=resetBuffer(updateCurrentSmooth);	
			rxBufferOverrun=false;
			bufferUnderflow=false;
			ic = rxIncoming_count;
			iIdx = incoming_rx_bIdx;
			__enable_irq();
		}
		else {	
			//can only happen if we run out of audio blocks/memory		
			_streaming=false;
			rxMemoryUnderrunCounter++;
		}
	}
	//=======================================
	
	// If there was a receive event, we update the feedback for the USB host
	// Important: first compute the buffered samples before the block transmission and update of transmit_rx_bIdx below!!
	if (_streaming) {
		//we compute the mismatch of the the targeted number of buffered samples and the actual buffered samples
		float lastIsrSmooth = (float)lastCallReceiveIsr.getLastCall<2>(historyIsr, expectedIsrIntervalCycles);
		float timeSinceLastIsr = (float)toUInt32Range(updateCurrentSmooth - lastIsrSmooth);			
		timeSinceLastIsr /= F_CPU_ACTUAL; //to seconds
		
		_bufferedSamples= getNumBufferedRxSamples(iIdx, transmit_rx_bIdx, ic);
		_bufferedSamplesSmooth=_bufferedSamples + timeSinceLastIsr * AUDIO_SAMPLE_RATE;

		float diff= targetNumRxBufferedSamples -_bufferedSamplesSmooth;
		if (abs(lastDiff) <= abs(diff)){
			//we only add the current diff to the sum, if we the difference is not already decreasing
			sumDiff +=diff;
		}
		lastDiff = diff;
		feedback_accumulator = uint32_t(feedback_accumulator_default + double(_kp*diff)  + double(_ki*sumDiff) +0.5);
		//========================================================================================================
		
		//if buffer is ready, we transmit all channels and increase the transmit index in the ring buffer (indicated by bIdx!=-1)
		//then transmit_rx_bIdx needs to be increased (incrementBufferIndex gets called from outside after the blocks at ring buffer index transmit_rx_bIdx were transmitted and released.)
        bIdx = (int16_t)transmit_rx_bIdx; 
		//=========================================
	}
	
}

















#if 1

namespace {	

	
	uint16_t incoming_tx_bIdx=0;
	volatile uint16_t transmit_tx_bIdx=0;			//changed in usb_audio_transmit_callback
	volatile USBAudioOutInterface::BufferState txBufferState = USBAudioOutInterface::ready;			//0: buffer can be used, 1: buffer is full, 2: buffer overrun changed in usb_audio_transmit_callback	
	volatile float bufferedTxSamples=0.f;			//changed in usb_audio_transmit_callback
	volatile float bufferedTxSamplesSmooth=0.f;		//changed in usb_audio_transmit_callback
	volatile uint8_t transmit_flag;					//changed in usb_audio_transmit_callback
	volatile bool streamStart=true;					//changed in usb_audio_transmit_callback

	volatile uint32_t txUsb_audio_underrun_count =0;
	volatile uint32_t txUsb_audio_overrun_count =0;
	
	volatile uint32_t num_skipped_Samples=0;
	volatile uint32_t num_padded_Samples=0;
	volatile uint32_t num_send_one_less=0;
	volatile uint32_t num_send_one_more=0;

	
	LastCall<7> lastCallTransmitIsr;
	constexpr float targetNumTxBufferedSamples = TARGET_TX_BUFFER_TIME_S*AUDIO_SAMPLE_RATE;

	float getNumBufferedTxSamples(USBAudioOutInterface::BufferState txBufferState, uint32_t target, uint16_t incomingIdx, uint16_t transmitIdx, uint16_t outgoingCount){
		float bufferedSamples= AUDIO_BLOCK_SAMPLES-outgoingCount;
		if(txBufferState > USBAudioOutInterface::ready){
			//buffer full or overrund
			bufferedSamples +=(AUDIO_BLOCK_SAMPLES *(USBAudioOutInterface::ringTxBufferSize-1));
			return bufferedSamples -target;	//-target because it's assumed that target number of samples will be transmitted after this function call
		}
		if(incomingIdx > transmitIdx+1 ){
			bufferedSamples+=(incomingIdx-(transmitIdx+1))*AUDIO_BLOCK_SAMPLES;
		}
		else if(incomingIdx < transmitIdx){
			bufferedSamples += incomingIdx*AUDIO_BLOCK_SAMPLES;
			if(transmitIdx +1 < USBAudioOutInterface::ringTxBufferSize){
				bufferedSamples += (USBAudioOutInterface::ringTxBufferSize-(transmitIdx +1))*AUDIO_BLOCK_SAMPLES;
			}
		}
		return bufferedSamples-target;	//-target because it's assumed that target number of samples will be transmitted after this function call
	}
	
	void updateDevCounter(float bufferDiff, uint32_t& devCounter, int8_t& sign){
		const float thrs =2.f;	//acts as hysteresis, small deviations of targeted number of samples in the buffer are ignored
		if (bufferDiff > thrs){
			if(sign != 1){
				devCounter=1;
				sign=1;
			}
			else {
				devCounter++;
			}
		}
		else if (bufferDiff < -thrs){
			if(sign != -1){
				devCounter=1;
				sign =-1;
			}
			else {
				devCounter++;
			}
		}
	}

	void updateTarget(int8_t sign, uint32_t& devCounter, uint32_t& target){
		if(sign == -1){
			devCounter=0;
			num_send_one_less++;
			//we run out of samples -> slow transmission down
            target--;
		}
		else if(sign ==1){
			devCounter=0;
			num_send_one_more++;
			//we run out of buffer space -> speed transmission down
			target++;
		}
	}
#ifndef ASYNC_TX_ENDPOINT
	void updateBufferOffset(int8_t sign, uint32_t& devCounter, uint16_t& offset){
		if(sign == -1 && offset > 0){
			devCounter=0;
			num_padded_Samples++;
			//one sample is transmitted twice
			offset--;
		}
		else if(sign ==1 && offset < AUDIO_BLOCK_SAMPLES){
			devCounter=0;
			num_skipped_Samples++;
			//we skip one sample in the buffer
			offset++;
		}
	}
#endif
	uint32_t getTransmissionTarget(){
		// Depending on the sampling frequency and the bInterval, we compute the number of samples that need to be transmitted.
		//
		// At 44.1 kHz and 1ms bInterval this function returns 9 times 44 samples and then 45 samples;
		// at e.g. 188.4 kHz and 1ms bInterval the output is more 'complex': 
		// three times 188, once 189, two times 188, once 189,... cycle starts again 
		//
		// This function does not take into account the current number of buffered samples, i.e. it does not change the target 
		// number of samples in order to prevent buffer over- and under-runs.
		// It's just a version of the Bresenham-Algorithm

		const uint32_t N = samplingRate * audioPollingIntervaluS;
		const uint32_t denominator = 1'000'000;

		//target is first set to the default number of samples we send per frame.
		//e.g. if samplingRate=44100 and audioPollingIntervaluS=1000 then base = 44
		uint32_t target = N / denominator;	

		//rem is the reminder of the devision 'N / denominator'. It represents the fractional samples (but multiplied by denominator).
		uint32_t rem  = N % denominator;        
		
		//we accumulate the 'fractional' samples by means of the errorAccumulator. 0 <=errorAccumulator < denominator
		static uint32_t errorAccumulator = 0;                   
		errorAccumulator+=rem;
		
		if (errorAccumulator >= denominator)
		{
			errorAccumulator -= denominator;
			target += 1;
		}
		return target;
	}
	
	void resetTransmissionIndex(float virtualSamples, uint16_t incomingIdx, uint16_t& idx, uint16_t& count, uint16_t numSentSamples){
		uint16_t targetNoSamples =uint16_t(targetNumTxBufferedSamples+numSentSamples-virtualSamples  + 0.f);	//+numSentSamples because we will immediatelly transmit 'numSentSamples' samples
		uint16_t targetNumTxBufferedBlocks = uint16_t(targetNoSamples/AUDIO_BLOCK_SAMPLES);
		count = AUDIO_BLOCK_SAMPLES-(targetNoSamples-targetNumTxBufferedBlocks*AUDIO_BLOCK_SAMPLES);
		idx = (incomingIdx -(targetNumTxBufferedBlocks+1)+USBAudioOutInterface::ringTxBufferSize)%USBAudioOutInterface::ringTxBufferSize;
	}

	void resetStatusCounter(){
		num_skipped_Samples=0;
		num_padded_Samples=0;
		num_send_one_less=0;
		num_send_one_more=0;
		txUsb_audio_underrun_count=0;
		txUsb_audio_overrun_count=0;
	}
}
double USBAudioOutInterface::updateCurrentSmooth=-1.;
uint16_t USBAudioOutInterface::outgoing_count;
bool USBAudioOutInterface::running=false;

USBAudioOutInterface::ReleaseBlocks USBAudioOutInterface::releaseBlocks;
USBAudioOutInterface::IsBlockReady USBAudioOutInterface::isBlockReady;
USBAudioOutInterface::Copy_from_buffers USBAudioOutInterface::copy_from_buffer;

/*DMAMEM*/ uint8_t usb_audio_transmit_buffer[AUDIO_TX_SIZE] __attribute__ ((used, aligned(32)));

static void tx_event(transfer_t *t)
{
	int len = usb_audio_transmit_callback();
	usb_audio_sync_feedback = feedback_accumulator >> usb_audio_sync_rshift;
	usb_prepare_transfer(&tx_transfer, usb_audio_transmit_buffer, len, 0);
	arm_dcache_flush_delete(usb_audio_transmit_buffer, len);
	usb_transmit(AUDIO_TX_ENDPOINT, &tx_transfer);
}
USBAudioOutInterface::USBAudioOutInterface(ReleaseBlocks rbs, IsBlockReady ibr, Copy_from_buffers c_f_b) {
		USBAudioOutInterface::releaseBlocks=rbs;
		USBAudioOutInterface::isBlockReady=ibr;
		USBAudioOutInterface::copy_from_buffer = c_f_b;
}
float USBAudioOutInterface::getActualBIntervalUs() const {
	float toUS =1000000.f/F_CPU_ACTUAL;
	NVIC_DISABLE_IRQ(IRQ_SOFTWARE);
	float bInterval= (float)lastCallTransmitIsr.getLastDuration()*toUS;
	NVIC_ENABLE_IRQ(IRQ_SOFTWARE);
	return bInterval;
}
void USBAudioOutInterface::begin(){
	__disable_irq();
	if(USBAudioOutInterface::running){
		__enable_irq();
		return;
	}
	outgoing_count = 0;
	lastCallTransmitIsr.reset(expectedIsrIntervalCycles);		
	_lastCallUpdate.reset(blockDuration*F_CPU_ACTUAL);
	USBAudioOutInterface::running=true;
	bufferedTxSamplesSmooth=0;
	bufferedTxSamples=0;
	__enable_irq();

}
void USBAudioOutInterface::stop(){
	__disable_irq();
	if(!USBAudioOutInterface::running){
		__enable_irq();
		return;
	}
	USBAudioOutInterface::running=false;
	bufferedTxSamplesSmooth=0;
	bufferedTxSamples=0;
	__enable_irq();
}

USBAudioOutInterface::Status USBAudioOutInterface::getStatus() const{
	USBAudioOutInterface::Status status;
	NVIC_DISABLE_IRQ(IRQ_SOFTWARE);
	status.usb_audio_underrun_count = txUsb_audio_underrun_count;
	status.usb_audio_overrun_count = txUsb_audio_overrun_count;
	status.target_num_buffered_samples = targetNumTxBufferedSamples;
	status.num_transmitted_channels = noTransmittedChannels;
	status.ring_buffer_size = ringTxBufferSize;
	status.usb_rx_tx_buffer_size = AUDIO_TX_SIZE;
	status.transmittingData=_streaming;
	status.bInterval_uS = audioPollingIntervaluS;
	status.num_skipped_Samples = num_skipped_Samples;
	status.num_padded_Samples = num_padded_Samples;
	status.num_send_one_less = num_send_one_less;
	status.num_send_one_more = num_send_one_more;
	status.usb_high_speed = usb_high_speed;
	NVIC_ENABLE_IRQ(IRQ_SOFTWARE);
	return status;
}

void USBAudioOutInterface::update(int16_t& bIdx, uint16_t& noChannels)
{	
	noChannels=noTransmittedChannels;
	if(!running){
		bIdx = -1;
		return;
	}
	//update time measurement of update calls
	uint32_t t = ARM_DWT_CYCCNT;
	_lastCallUpdate.addCall(t);
	History<50> historyUpdate = _lastCallUpdate.getHistory();	
	_updateCurrentSmoothPending= _lastCallUpdate.getLastCall<20>(historyUpdate, blockDuration*F_CPU_ACTUAL);
	//=======================================
	
	__disable_irq();
		streamStart=transmit_flag && !_streaming;	
		_streaming=transmit_flag != 0;		
		if (transmit_flag) transmit_flag--;
		if(txBufferState < overrun && incoming_tx_bIdx == transmit_tx_bIdx){
			txBufferState=overrun;
		}
		if(txBufferState == overrun){	
			//only set in case of buffer overrun. Normally updateCurrentSmooth should only be set in combination with the incoming_tx_bIdx incrementation
			updateCurrentSmooth= _updateCurrentSmoothPending;
		}
		BufferState s = txBufferState;
	__enable_irq();
	if(!_streaming){
		resetStatusCounter();
		bufferedTxSamplesSmooth=0.f;
		bufferedTxSamples=0.f;
	}
	if(s == overrun){
		txUsb_audio_overrun_count++;
	}
	bIdx=incoming_tx_bIdx;
}

void USBAudioOutInterface::incrementBufferIndex(){
	__disable_irq();
		updateCurrentSmooth= _updateCurrentSmoothPending;
		incoming_tx_bIdx=(incoming_tx_bIdx+1)%ringTxBufferSize;
		if(txBufferState < full && incoming_tx_bIdx == transmit_tx_bIdx){
			txBufferState = full;
		}
	__enable_irq();
}
void USBAudioOutInterface::tryIncreaseIdxTransmission(uint16_t& tBIdx, uint16_t& offset){
	while (offset >= AUDIO_BLOCK_SAMPLES){
		USBAudioOutInterface::releaseBlocks(tBIdx, noTransmittedChannels);			
		uint16_t idxCandidate =(tBIdx+1)%ringTxBufferSize;
		if(idxCandidate != incoming_tx_bIdx){
			tBIdx = idxCandidate;
			offset -=AUDIO_BLOCK_SAMPLES;
		}
		else {
			offset = AUDIO_BLOCK_SAMPLES;	 //we make sure that offset is never larger than AUDIO_BLOCK_SAMPLES!
			break;
		}
	}
}
float USBAudioOutInterface::getBufferedSamples() const{
	NVIC_DISABLE_IRQ(IRQ_SOFTWARE);
	float b = bufferedTxSamples;
	NVIC_ENABLE_IRQ(IRQ_SOFTWARE);
	return b;
}
float USBAudioOutInterface::getBufferedSamplesSmooth() const{
	NVIC_DISABLE_IRQ(IRQ_SOFTWARE);
	float b = bufferedTxSamplesSmooth;
	NVIC_ENABLE_IRQ(IRQ_SOFTWARE);
	return b;
}

// Called from the USB interrupt when ready to transmit another
// isochronous packet.
// the return is the number of bytes to transmit
unsigned int usb_audio_transmit_callback(void)
{	
	//compute the number of samples we want to transmit (at 44.1kHz and a bInterval of 1ms that is either 44 or 45 samples)
	uint32_t target = getTransmissionTarget();
	if(!USBAudioOutInterface::running){
		//Some hosts (Linux, Windows) would tolerate zero length data packages.
		//However, sometimes there are troubles with MacOs.
		//So we better always send the expected number of samples.
		const uint32_t numBytes =target*noTransmittedChannels*AUDIO_SUBSLOT_SIZE;
		uint8_t *data = usb_audio_transmit_buffer;
		memset(data, 0, numBytes);
		return target * noTransmittedChannels*AUDIO_SUBSLOT_SIZE;
	}

	// data transmitted: may get multiple blocks before it happens again
	transmit_flag = (audioPollingIntervaluS * samplingRate / AUDIO_BLOCK_SAMPLES / 1'000'000) + 1;

	//time measurement (needed for the computation of virtual samples)
	uint32_t current =ARM_DWT_CYCCNT;
	lastCallTransmitIsr.addCall(current);
	//================================================================

	
	const uint16_t iBIdx = incoming_tx_bIdx;	//we are not allowed to change incoming_tx_bIdx 
	uint16_t tBIdx = transmit_tx_bIdx;
	uint16_t offset = USBAudioOutInterface::outgoing_count;

	//============================================================
	const uint32_t devCounterThrs =10;
	static uint32_t devCounter=0;	//how often in a row there were too many or too few samples, if counter reaches 'devCounterThrs', we take some action (hysteresis)
	static int8_t sign =0;			//-1... too few samples in the buffer, 0... state not known, 1... too many samples in the buffer
	float virtualSamples =0.f;
	if(USBAudioOutInterface::updateCurrentSmooth !=-1.){
		
		History<7> historyIsr = lastCallTransmitIsr.getHistory();
		float lastIsrSmooth = (float)lastCallTransmitIsr.getLastCall<2>(historyIsr, expectedIsrIntervalCycles);
		float timeSinceLastUpdate = (float)toUInt32Range(lastIsrSmooth - USBAudioOutInterface::updateCurrentSmooth);
		timeSinceLastUpdate /= F_CPU_ACTUAL; //to seconds
		if (timeSinceLastUpdate > 1.5f*USBAudioOutInterface::blockDuration || timeSinceLastUpdate < -0.5f*USBAudioOutInterface::blockDuration){
			//something really went wrong since update is normally called eveey blockDuration seconds
			//-> we use the average value to prevent serious problems
			timeSinceLastUpdate =0.5f*USBAudioOutInterface::blockDuration;
		}		
		virtualSamples =timeSinceLastUpdate * AUDIO_SAMPLE_RATE;
		
		bufferedTxSamples= getNumBufferedTxSamples(txBufferState, target, iBIdx, tBIdx, offset);
		bufferedTxSamplesSmooth=bufferedTxSamples +  virtualSamples;
		updateDevCounter(bufferedTxSamplesSmooth -targetNumTxBufferedSamples, devCounter, sign);		
	}

	if(txBufferState == USBAudioOutInterface::overrun || streamStart){
		streamStart=false;
		devCounter=0;
		resetTransmissionIndex(virtualSamples, iBIdx, tBIdx, offset, noSamplesPerPollingInterval);		
		USBAudioOutInterface::releaseBlocks(tBIdx, noTransmittedChannels);		
		txBufferState=USBAudioOutInterface::ready;
	}
#ifdef ASYNC_TX_ENDPOINT
    if(devCounter == devCounterThrs){
        updateTarget(sign, devCounter, target);
    }	
#endif
	uint32_t len=0;
	uint8_t *data = usb_audio_transmit_buffer;

	while (len < target) {
		uint32_t num = target - len;
		uint32_t avail = AUDIO_BLOCK_SAMPLES - offset;
		if( avail==0 ||	!USBAudioOutInterface::isBlockReady(tBIdx,0)){
			//Something went wrong. We either did not receive a block, or a buffer underrun occured.
			//We will reset the buffer indices and offsets and transmit zeros.
			if( avail==0){
				devCounter=0;	//only reset in case of an underrun and not if USBAudioOutInterface did not receive data in 'update'
				txUsb_audio_underrun_count++;
				resetTransmissionIndex(virtualSamples, iBIdx, tBIdx, offset, num);		
			}
			const uint32_t numBytes = num*noTransmittedChannels*AUDIO_SUBSLOT_SIZE;
			memset(data, 0, numBytes);
		}
		else {
			if (num > avail){
				num = avail;
			}
			USBAudioOutInterface::copy_from_buffer(data, tBIdx, noTransmittedChannels, offset, num);	
		}
		data += num*noTransmittedChannels*AUDIO_SUBSLOT_SIZE;
		len+=num;
		offset+=num;	//num can be larger than 'AUDIO_BLOCK_SAMPLES' in case of 'avail==0 ||	!USBAudioOutInterface::isBlockReady(tBIdx,0)'
#ifndef ASYNC_TX_ENDPOINT
		if(devCounter == devCounterThrs){
			updateBufferOffset(sign, devCounter, offset);
		}
#endif
		if (offset >= AUDIO_BLOCK_SAMPLES) {
			USBAudioOutInterface::tryIncreaseIdxTransmission(tBIdx,offset);
		}
	}
	transmit_tx_bIdx=tBIdx;
	USBAudioOutInterface::outgoing_count = offset;

	return target * noTransmittedChannels*AUDIO_SUBSLOT_SIZE;
}
#endif





void usb_audio_configure(void)
{
	rxUsb_audio_underrun_count = 0;
	rxUsb_audio_overrun_count = 0;
	rxMemoryUnderrunCounter=0;
	sumDiff=0.;
	lastDiff=0.;
	rxBufferReady= false;
	incoming_rx_bIdx=0;
	transmit_rx_bIdx=0;
	if (usb_high_speed) {
		noTransmittedChannels   = USB_AUDIO_NO_CHANNELS_480;
		audioPollingIntervalSec = AUDIO_POLLING_INTERVAL_480_SEC;
		audioPollingIntervaluS  = AUDIO_NUM_SUBFRAMES_PER_POLLING_480 * MICROFRAME_US;
		usb_audio_sync_nbytes   = 4;
		usb_audio_sync_rshift   = 8;
	} else {
		noTransmittedChannels   = USB_AUDIO_NO_CHANNELS_12;
		audioPollingIntervalSec = AUDIO_POLLING_INTERVAL_12_SEC;
		audioPollingIntervaluS  = AUDIO_NUM_SUBFRAMES_PER_POLLING_12 * MICROFRAME_US;
		usb_audio_sync_nbytes   = 3;
		usb_audio_sync_rshift   = 10;
	}

	noSamplesPerPollingInterval = (samplingRate*audioPollingIntervaluS)/1'000'000;

	feedback_accumulator_default = uint32_t((samplingRate *audioPollingIntervalSec) * 0x1000000 +0.5f);
	feedback_accumulator = feedback_accumulator_default;

	memset(&rx_transfer, 0, sizeof(rx_transfer));
	usb_config_rx_iso(AUDIO_RX_ENDPOINT, AUDIO_RX_SIZE, 1, rx_event);
	rx_event(NULL);
	memset(&sync_transfer, 0, sizeof(sync_transfer));
	usb_config_tx_iso(AUDIO_SYNC_ENDPOINT, usb_audio_sync_nbytes, 1, sync_event);
	sync_event(NULL);
	memset(&tx_transfer, 0, sizeof(tx_transfer));
	usb_config_tx_iso(AUDIO_TX_ENDPOINT, AUDIO_TX_SIZE, 1, tx_event);
	tx_event(NULL);
	expectedIsrIntervalCycles = audioPollingIntervalSec *F_CPU_ACTUAL;
	lastCallReceiveIsr.reset(expectedIsrIntervalCycles);

	//AudioOutputUSB	==============================
	resetStatusCounter();
	//=================================================
}






struct setup_struct {
  //union {
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
  //};
};

int usb_audio_get_feature(void *stp, uint8_t *data, uint32_t *datalen)
{

	struct setup_struct setup = *((struct setup_struct *)stp);
	if(setup.bmRequestType != 0xA1){
		//was not a get feature request directed to the feature unit
		return 0;
	}
	
	if (setup.bRequest==0x02) { // -> request = RANGE
		if (setup.bCS==0x01) { // mute
			data[0] =1; //only one sub-range (LSB of 2 bytes)
			data[1] =0; //only one sub-range (MSB of 2 bytes)
			data[2] =0;	//unmute
			data[3] = 1; //mute
			data[4] = 1; //resolution
			*datalen = 5;
			return 1;
		}
		else if (setup.bCS==0x02) { // volume
			//Have a look at the UAC2 specification page 102, section 5.2.5.7.2 Volume Control
			const int16_t maxVol = FEATURE_MAX_VOLUME;
			data[0] = 1; //only one sub-range (LSB of 2 bytes)
			data[1] = 0; //only one sub-range (MSB of 2 bytes)
			data[2] = 0;	// min level is 0 (LSB)
			data[3] = 0; 	// min level is 0 (MSB)
			data[4] = maxVol & 0xFF;  		// max level, for range of 0 to MAX (LSB)
			data[5] = (maxVol>>8) & 0xFF;	// max level, for range of 0 to MAX (MSB)
			data[6] = 1;	// increment vol by by 1 (LSB)
			data[7] = 0;	// increment vol by by 1 (MSB)
			*datalen = 8;
			return 1;
		}
		else { // pass over SET_MEM, etc.
			return 0;
		}
	}
	if (setup.bRequest==0x01) { // -> request = CUR
		if (setup.bCS==0x01) { // mute
			data[0] = USBAudioInInterface::features.mute;  // 1=mute, 0=unmute
			*datalen = 1;
			return 1;
		}
		else if (setup.bCS==0x02) { // volume
			const int16_t vol = (int16_t)USBAudioInInterface::features.volume;
			data[0] = vol & 0xFF;	//(LSB)
			data[1] = (vol>>8) & 0xFF; //(MSB)
			*datalen = 2;
			return 1;
		}
		else { // pass over SET_MEM, etc.
			return 0;
		}
	}
	return 0;
}

int usb_audio_set_feature(void *stp, uint8_t *buf) 
{
	struct setup_struct setup = *((struct setup_struct *)stp);
	if (setup.bmRequestType==0x21) { // SET FEATURE should check bRequest, bChannel and UnitID
			if (setup.bCS==0x01) { // mute
				if (setup.bRequest==0x01) { // CUR
					// if(Serial){
					// 	Serial.println("set mute");
					// }
					USBAudioInInterface::features.mute = buf[0]; // 1=mute,0=unmute
					USBAudioInInterface::features.change = 1;
					return 1;
				}
			}
			else if (setup.bCS==0x02) { // volume
				if (setup.bRequest==0x01) { // CUR
					//Have a look at the UAC2 specification page 102, section 5.2.5.7.2 Volume Control
					//volume uses two bytes
					const int16_t *volPtr =(const int16_t *)buf;
					USBAudioInInterface::features.volume = *volPtr;
					USBAudioInInterface::features.change = 1;
					return 1;
				}
			}
	}
	return 0;
}


#endif // AUDIO_INTERFACE
