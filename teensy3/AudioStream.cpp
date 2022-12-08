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
#include "AudioStream.h"

#if defined(__MKL26Z64__)
  #define MAX_AUDIO_MEMORY 6144
#elif defined(__MK20DX128__)
  #define MAX_AUDIO_MEMORY 12288
#elif defined(__MK20DX256__)
  #define MAX_AUDIO_MEMORY 49152
#elif defined(__MK64FX512__)
  #define MAX_AUDIO_MEMORY 163840
#elif defined(__MK66FX1M0__)
  #define MAX_AUDIO_MEMORY 229376
#endif

#define NUM_MASKS  (((MAX_AUDIO_MEMORY / AUDIO_BLOCK_SAMPLES / 2) + 31) / 32)

audio_block_t * AudioStream::memory_pool;
uint32_t AudioStream::memory_pool_available_mask[NUM_MASKS];
uint16_t AudioStream::memory_pool_first_mask;

uint16_t AudioStream::cpu_cycles_total = 0;
uint16_t AudioStream::cpu_cycles_total_max = 0;
uint16_t AudioStream::memory_used = 0;
uint16_t AudioStream::memory_used_max = 0;
AudioConnection* AudioStream::unused = NULL; // linked list of unused but not destructed connections




// Set up the pool of audio data blocks
// placing them all onto the free list
void AudioStream::initialize_memory(audio_block_t *data, unsigned int num)
{
	unsigned int i;
	unsigned int maxnum = MAX_AUDIO_MEMORY / AUDIO_BLOCK_SAMPLES / 2;

	//Serial.println("AudioStream initialize_memory");
	//delay(10);
	if (num > maxnum) num = maxnum;
	__disable_irq();
	memory_pool = data;
	memory_pool_first_mask = 0;
	for (i=0; i < NUM_MASKS; i++) {
		memory_pool_available_mask[i] = 0;
	}
	for (i=0; i < num; i++) {
		memory_pool_available_mask[i >> 5] |= (1 << (i & 0x1F));
	}
	for (i=0; i < num; i++) {
		data[i].memory_pool_index = i;
	}
	if (update_scheduled == false) {
		// if no hardware I/O has taken responsibility for update,
		// start a timer which will call update_all() at the correct rate
		IntervalTimer *timer = new IntervalTimer();
		if (timer) {
			float usec = 1e6 * AUDIO_BLOCK_SAMPLES / AUDIO_SAMPLE_RATE_EXACT;
			timer->begin(update_all, usec);
			update_setup();
		}
	}
	__enable_irq();
}

// Allocate 1 audio data block.  If successful
// the caller is the only owner of this new block
audio_block_t * AudioStream::allocate(void)
{
	uint32_t n, index, avail;
	uint32_t *p, *end;
	audio_block_t *block;
	uint32_t used;

	p = memory_pool_available_mask;
	end = p + NUM_MASKS;
	__disable_irq();
	index = memory_pool_first_mask;
	p += index;
	while (1) {
		if (p >= end) {
			__enable_irq();
			//Serial.println("alloc:null");
			return NULL;
		}
		avail = *p;
		if (avail) break;
		index++;
		p++;
	}
	n = __builtin_clz(avail);
	avail &= ~(0x80000000 >> n);
	*p = avail;
	if (!avail) index++;
	memory_pool_first_mask = index;
	used = memory_used + 1;
	memory_used = used;
	__enable_irq();
	index = p - memory_pool_available_mask;
	block = memory_pool + ((index << 5) + (31 - n));
	block->ref_count = 1;
	if (used > memory_used_max) memory_used_max = used;
	//Serial.print("alloc:");
	//Serial.println((uint32_t)block, HEX);
	return block;
}

// Release ownership of a data block.  If no
// other streams have ownership, the block is
// returned to the free pool
void AudioStream::release(audio_block_t *block)
{
	//if (block == NULL) return;
	uint32_t mask = (0x80000000 >> (31 - (block->memory_pool_index & 0x1F)));
	uint32_t index = block->memory_pool_index >> 5;

	__disable_irq();
	if (block->ref_count > 1) {
		block->ref_count--;
	} else {
		//Serial.print("reles:");
		//Serial.println((uint32_t)block, HEX);
		memory_pool_available_mask[index] |= mask;
		if (index < memory_pool_first_mask) memory_pool_first_mask = index;
		memory_used--;
	}
	__enable_irq();
}

// Transmit an audio data block
// to all streams that connect to an output.  The block
// becomes owned by all the recepients, but also is still
// owned by this object.  Normally, a block must be released
// by the caller after it's transmitted.  This allows the
// caller to transmit to same block to more than 1 output,
// and then release it once after all transmit calls.
void AudioStream::transmit(audio_block_t *block, unsigned char index)
{
	for (AudioConnection *c = destination_list; c != NULL; c = c->next_dest) {
		if (c->src_index == index) {
			if (c->dst->inputQueue[c->dest_index] == NULL) {
				c->dst->inputQueue[c->dest_index] = block;
				block->ref_count++;
			}
		}
	}
}


// Receive block from an input.  The block's data
// may be shared with other streams, so it must not be written
audio_block_t * AudioStream::receiveReadOnly(unsigned int index)
{
	audio_block_t *in;

	if (index >= num_inputs) return NULL;
	in = inputQueue[index];
	inputQueue[index] = NULL;
	return in;
}

// Receive block from an input.  The block will not
// be shared, so its contents may be changed.
audio_block_t * AudioStream::receiveWritable(unsigned int index)
{
	audio_block_t *in, *p;

	if (index >= num_inputs) return NULL;
	in = inputQueue[index];
	inputQueue[index] = NULL;
	if (in && in->ref_count > 1) {
		p = allocate();
		if (p) memcpy(p->data, in->data, sizeof(p->data));
		in->ref_count--;
		in = p;
	}
	return in;
}

/**************************************************************************************/
// Constructor with no parameters: leave unconnected
AudioConnection::AudioConnection()
	: src(NULL), dst(NULL),
	  src_index(0), dest_index(0),
	  isConnected(false)

{
	// we are unused right now, so
	// link ourselves at the start of the unused list
	next_dest = AudioStream::unused;
	AudioStream::unused = this;
}


// Destructor
AudioConnection::~AudioConnection()
{
	AudioConnection** pp;
	
	disconnect(); // disconnect ourselves: puts us on the unused list
	// Remove ourselves from the unused list
	pp = &AudioStream::unused;
	while (*pp && *pp != this)
		pp = &((*pp)->next_dest);
	if (*pp) // found ourselves
		*pp = next_dest; // remove ourselves from the unused list
}

/**************************************************************************************/
int AudioConnection::connect(void)
{
	int result = 1;
	AudioConnection *p;
	AudioConnection **pp;
	AudioStream* s;

	do 
	{
		if (isConnected) // already connected
		{
			break;
		}
		
		if (!src || !dst) // NULL src or dst - [old] Stream object destroyed
		{
			result = 3;
			break;
		}
			
		if (dest_index >= dst->num_inputs) // input number too high
		{
			result = 2;
			break;
		}
			
		__disable_irq();
		
		// First check the destination's input isn't already in use
		s = AudioStream::first_update; // first AudioStream in the stream list
		while (s) // go through all AudioStream objects
		{
			p = s->destination_list;	// first patchCord in this stream's list
			while (p)
			{
				if (p->dst == dst && p->dest_index == dest_index) // same destination - it's in use!
				{
					__enable_irq();
					return 4;
				}
				p = p->next_dest;
			}
			s = s->next_update;
		}
		
		// Check we're on the unused list
		pp = &AudioStream::unused;
		while (*pp && *pp != this)
		{
			pp = &((*pp)->next_dest);
		}
		if (!*pp) // never found ourselves - fail
		{
			result = 5;
			break;
		}
			
		// Now try to add this connection to the source's destination list
		p = src->destination_list; // first AudioConnection
		if (p == NULL) 
		{
			src->destination_list = this;
		} 
		else 
		{
			while (p->next_dest)  // scan source Stream's connection list for duplicates
			{
				
				if (&p->src == &this->src && &p->dst == &this->dst
					&& p->src_index == this->src_index && p->dest_index == this->dest_index) 
				{
					//Source and destination already connected through another connection, abort
					__enable_irq();
					return 6;
				}
				p = p->next_dest;
			}			
			
			p->next_dest = this; // end of list, can link ourselves in
		}
		
		*pp = next_dest;  // remove ourselves from the unused list
		next_dest = NULL; // we're last in the source's destination list
		
		src->numConnections++;
		src->active = true;

		dst->numConnections++;
		dst->active = true;

		isConnected = true;
		
		result = 0;
	} while (0);
	
	__enable_irq();
	
	return result;
}


int AudioConnection::connect(AudioStream &source, unsigned char sourceOutput,
		AudioStream &destination, unsigned char destinationInput)
{
	int result = 1;
	
	if (!isConnected)
	{
		src = &source;
		dst = &destination;
		src_index = sourceOutput;
		dest_index = destinationInput;
		
		result = connect();
	}
	return result;
}

int AudioConnection::disconnect(void)
{
	AudioConnection *p;

	if (!isConnected) return 1;
	if (dest_index >= dst->num_inputs) return 2; // should never happen!
	__disable_irq();
	
	// Remove destination from source list
	p = src->destination_list;
	if (p == NULL) {
//>>> PAH re-enable the IRQ
		__enable_irq();
		return 3;
	} else if (p == this) {
		if (p->next_dest) {
			src->destination_list = next_dest;
		} else {
			src->destination_list = NULL;
		}
	} else {
		while (p)
		{
			if (p->next_dest == this) // found the parent of the disconnecting object
			{
				p-> next_dest = this->next_dest; // skip parent's link past us
				break;
			}
			else
				p = p->next_dest; // carry on down the list
		}
	}
//>>> PAH release the audio buffer properly
	//Remove possible pending src block from destination
	if(dst->inputQueue[dest_index] != NULL) {
		AudioStream::release(dst->inputQueue[dest_index]);
		// release() re-enables the IRQ. Need it to be disabled a little longer
		__disable_irq();
		dst->inputQueue[dest_index] = NULL;
	}

	//Check if the disconnected AudioStream objects should still be active
	src->numConnections--;
	if (src->numConnections == 0) {
		src->active = false;
	}

	dst->numConnections--;
	if (dst->numConnections == 0) {
		dst->active = false;
	}
	
	isConnected = false;
	next_dest = dst->unused;
	dst->unused = this;

	__enable_irq();
	
	return 0;
}


// When an object has taken responsibility for calling update_all()
// at each block interval (approx 2.9ms), this variable is set to
// true.  Objects that are capable of calling update_all(), typically
// input and output based on interrupts, must check this variable in
// their constructors.
bool AudioStream::update_scheduled = false;

bool AudioStream::update_setup(void)
{
	if (update_scheduled) return false;
	NVIC_SET_PRIORITY(IRQ_SOFTWARE, 208); // 255 = lowest priority
	NVIC_ENABLE_IRQ(IRQ_SOFTWARE);
	update_scheduled = true;
	return true;
}

void AudioStream::update_stop(void)
{
	NVIC_DISABLE_IRQ(IRQ_SOFTWARE);
	update_scheduled = false;
}

AudioStream * AudioStream::first_update = NULL;

void software_isr(void) // AudioStream::update_all()
{
	AudioStream *p;

#if defined(KINETISK)
	ARM_DEMCR |= ARM_DEMCR_TRCENA;
	ARM_DWT_CTRL |= ARM_DWT_CTRL_CYCCNTENA;
	uint32_t totalcycles = ARM_DWT_CYCCNT;
#elif defined(KINETISL)
	uint32_t totalcycles = micros();
#endif
	//digitalWriteFast(2, HIGH);
	for (p = AudioStream::first_update; p; p = p->next_update) {
		if (p->active) {
			uint32_t cycles = ARM_DWT_CYCCNT;
			p->update();
			// TODO: traverse inputQueueArray and release
			// any input blocks that weren't consumed?
			cycles = (ARM_DWT_CYCCNT - cycles) >> 4;
			p->cpu_cycles = cycles;
			if (cycles > p->cpu_cycles_max) p->cpu_cycles_max = cycles;
		}
	}
	//digitalWriteFast(2, LOW);
#if defined(KINETISK)
	totalcycles = (ARM_DWT_CYCCNT - totalcycles) >> 4;
#elif defined(KINETISL)
	totalcycles = micros() - totalcycles;
#endif
	AudioStream::cpu_cycles_total = totalcycles;
	if (totalcycles > AudioStream::cpu_cycles_total_max)
		AudioStream::cpu_cycles_total_max = totalcycles;
}

