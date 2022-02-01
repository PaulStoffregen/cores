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

#ifndef AudioStream_h
#define AudioStream_h

// Debugging capabilities:
#define noDYNAMIC_AUDIO_DEBUG
#define SCOPE_PIN 25

#ifndef __ASSEMBLER__
#include <stdio.h>  // for NULL
#include <string.h> // for memcpy
#include "kinetis.h"
#endif

#if defined(DYNAMIC_AUDIO_DEBUG)
#define dbgPrintClanEntry(...) 	printClanEntry(__VA_ARGS__)
#define dbgPrintAclan(...)		printAclan(__VA_ARGS__)
#define dbgPrintClanList(...)	printClanList(__VA_ARGS__)
#undef SPRT
#undef SPRL
#undef SFSH
#define SPTF(...) Serial.printf(__VA_ARGS__) 
#define SPRT(...) Serial.print(__VA_ARGS__) 
#define SPRL(...) Serial.println(__VA_ARGS__) 
#define SFSH(...) Serial.flush(__VA_ARGS__) 
#else
#define dbgPrintClanEntry(...)
#define dbgPrintAclan(...)
#define dbgPrintClanList(...)
#define SPTF(...) 
#define SPRT(...) 
#define SPRL(...) 
#define SFSH(...) 
#endif // DYNAMIC_AUDIO_DEBUG

#if defined(SCOPE_PIN)
#define SCOPE_ENABLE() pinMode(SCOPE_PIN,OUTPUT)
#define SCOPE_HIGH() digitalWrite(SCOPE_PIN,scope_pin_value = 1)
#define SCOPE_LOW() digitalWrite(SCOPE_PIN,scope_pin_value = 0)
#define SCOPE_TOGGLE() digitalWrite(SCOPE_PIN,scope_pin_value = !scope_pin_value)
#else
#define SCOPE_ENABLE(...) 
#define SCOPE_HIGH(...) 
#define SCOPE_LOW(...) 
#define SCOPE_TOGGLE(...) 
#endif // defined(SCOPE_PIN)


// AUDIO_BLOCK_SAMPLES determines how many samples the audio library processes
// per update.  It may be reduced to achieve lower latency response to events,
// at the expense of higher interrupt and DMA setup overhead.
//
// Less than 32 may not work with some input & output objects.  Multiples of 16
// should be used, since some synthesis objects generate 16 samples per loop.
//
// Some parts of the audio library may have hard-coded dependency on 128 samples.
// Please report these on the forum with reproducible test cases.

#ifndef AUDIO_BLOCK_SAMPLES
#if defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MK64FX512__) || defined(__MK66FX1M0__)
#define AUDIO_BLOCK_SAMPLES  128
#elif defined(__MKL26Z64__)
#define AUDIO_BLOCK_SAMPLES  64
#endif
#endif

#ifndef AUDIO_SAMPLE_RATE_EXACT
#if defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MK64FX512__) || defined(__MK66FX1M0__)
#define AUDIO_SAMPLE_RATE_EXACT 44117.64706 // 48 MHz / 1088, or 96 MHz * 2 / 17 / 256
#elif defined(__MKL26Z64__)
//#define AUDIO_SAMPLE_RATE_EXACT 22058.82353 // 48 MHz / 2176, or 96 MHz * 1 / 17 / 256
#define AUDIO_SAMPLE_RATE_EXACT 44117.64706
#endif
#endif

#define AUDIO_SAMPLE_RATE AUDIO_SAMPLE_RATE_EXACT

// Macro to do a safe release of audio block(s), without the risk of
// an audio interrupt occurring between copying the pointers and the
// block release occurring. 
//
// By setting active=false, even if an audio interrupt does occur after
// the blocks have been released, the dying object will NOT update()
// and thus won't allocate any more blocks after SAFE_RELEASE has executed
#define SAFE_RELEASE(...) __disable_irq(); active = false; release(__VA_ARGS__,false)
#define SAFE_RELEASE_MANY(n,...) __disable_irq(); active = false; {audio_block_t* blx[]={__VA_ARGS__}; release(blx,n,false);}
#define SAFE_RELEASE_INPUTS() __disable_irq(); active = false; releaseInputQueue(false)
#define OFFSET_OF(t,m) ((int)(&(((t*)0)->m)))

#ifndef __ASSEMBLER__
class AudioStream;
class AudioConnection;
class AudioDebug;

typedef struct audio_block_struct {
	uint8_t  ref_count;
	uint8_t  reserved1;
	uint16_t memory_pool_index;
	int16_t  data[AUDIO_BLOCK_SAMPLES];
} audio_block_t;


class AudioConnection
{
public:
	AudioConnection();
	AudioConnection(AudioStream &source, AudioStream &destination);
	AudioConnection(AudioStream &source, unsigned char sourceOutput,
		AudioStream &destination, unsigned char destinationInput);
	friend class AudioStream;
	~AudioConnection(); 
	int disconnect(void);
	int connect(void);
	int connect(AudioStream &source, AudioStream &destination) {return connect(source,0,destination,0);};
	int connect(AudioStream &source, unsigned char sourceOutput,
		AudioStream &destination, unsigned char destinationInput);
protected:
	AudioStream* src;	// can't use references as... 
	AudioStream* dst;	// ...they can't be re-assigned!
	unsigned char src_index;
	unsigned char dest_index;
	AudioConnection *next_dest; // linked list of connections from one source
	bool isConnected;
	friend void NULLifConnected(AudioStream* strm,AudioConnection** ppC);
	friend void unlinkFromUpdateList();
	friend class AudioDebug;
};


#define AudioMemory(num) ({ \
	static DMAMEM audio_block_t data[num]; \
	AudioStream::initialize_memory(data, num); \
})

// Deal with counting CPU usage for individual objects and the audio engine overall.
// Some architectures don't have ARM_DWT_CYCCNT, so we fall back to using micros().
#if defined(KINETISK)
// Use ARM_DWT_CYCCNT
#define CYCLE_COUNTER_START(...) ARM_DEMCR |= ARM_DEMCR_TRCENA; ARM_DWT_CTRL |= ARM_DWT_CTRL_CYCCNTENA;
#define CYCLE_COUNTER_VALUE ARM_DWT_CYCCNT
#define CYCLE_COUNTER_SHIFT(x) ((x) >> 4)
#define CYCLE_COUNTER_APPROX_PERCENT(n) (((n) + (F_CPU / 32 / AUDIO_SAMPLE_RATE * AUDIO_BLOCK_SAMPLES / 100)) / (F_CPU / 16 / AUDIO_SAMPLE_RATE * AUDIO_BLOCK_SAMPLES / 100))
#elif defined(KINETISL)
// No ARM_DWT_CYCCNT, use micros()
#define CYCLE_COUNTER_START(...) 
#define CYCLE_COUNTER_VALUE micros()
#define CYCLE_COUNTER_SHIFT(x) (x)
#define CYCLE_COUNTER_APPROX_PERCENT(n) ((n) * (int)(AUDIO_SAMPLE_RATE) + (int)(AUDIO_SAMPLE_RATE/2)) / (AUDIO_BLOCK_SAMPLES * 10000)
#endif

#define AudioProcessorUsage() (CYCLE_COUNTER_APPROX_PERCENT(AudioStream::cpu_cycles_total))
#define AudioProcessorUsageMax() (CYCLE_COUNTER_APPROX_PERCENT(AudioStream::cpu_cycles_total_max))
#define AudioProcessorUsageMaxReset() (AudioStream::cpu_cycles_total_max = AudioStream::cpu_cycles_total)
#define AudioMemoryUsage() (AudioStream::memory_used)
#define AudioMemoryUsageMax() (AudioStream::memory_used_max)
#define AudioMemoryUsageMaxReset() (AudioStream::memory_used_max = AudioStream::memory_used)

class AudioStream
{
public:
	AudioStream(unsigned char ninput, audio_block_t **iqueue) :
		num_inputs(ninput), inputQueue(iqueue) 
		{
			if (!serialStarted)
			{
#if defined(DYNAMIC_AUDIO_DEBUG)
				Serial.begin(115200);
				while (!Serial)
					;
#endif // defined(DYNAMIC_AUDIO_DEBUG)
				serialStarted = true;
			}
			// at construction time we...
			active = false;				// ...are inactive
			destination_list = NULL;	// ...have no destinations...
			clan_head = this;
			next_clan = first_clan;		// ...are in a new clan...
			first_clan = this;
			next_update = NULL;			// ...with only us in it
			
			if (NULL == inputQueue)		// could be a failed malloc()
				num_inputs = 0;			// prevent use of queues
			else
			{
				for (int i=0; i < num_inputs; i++) 
					inputQueue[i] = NULL;
			}
			// add to a simple list, for update_all
			// TODO: replace with a proper data flow analysis in update_all

			cpu_cycles = 0;
			cpu_cycles_max = 0;
			numConnections = 0;
		}
	virtual ~AudioStream();
	static void initialize_memory(audio_block_t *data, unsigned int num);
	void NULLifConnected(AudioConnection** ppC);
	int processorUsage(void) { return CYCLE_COUNTER_APPROX_PERCENT(cpu_cycles); }
	int processorUsageMax(void) { return CYCLE_COUNTER_APPROX_PERCENT(cpu_cycles_max); }
	void processorUsageMaxReset(void) { cpu_cycles_max = cpu_cycles; }
	bool isActive(void) { return active; }
	bool isClanActive(void) { return clan_head->clanActive; }
	bool areAllClansActive(void) { return allClansActive; }
	void setClanActive(bool state) { clan_head->clanActive = state; }	
	static void setAllClansActive(bool state) { allClansActive = state; }	
	uint16_t cpu_cycles;
	uint16_t cpu_cycles_max;
	static uint16_t cpu_cycles_total;
	static uint16_t cpu_cycles_total_max;
	static uint16_t memory_used;
	static uint16_t memory_used_max;
	static audio_block_t silentBlock;	// lots of objects use this - let's provide one
protected:
	static bool serialStarted;
	bool active;
	bool clanActive;
	static bool allClansActive;
	unsigned char num_inputs;
	static audio_block_t * allocate(void);
	static void release(audio_block_t * block, bool enableIRQ = true);
	static void release(audio_block_t** blocks, int numBlocks, bool enableIRQ = true);
	void releaseInputQueue(bool enableIRQ = true);
	void transmit(audio_block_t *block, unsigned char index = 0);
	audio_block_t * receiveReadOnly(unsigned int index = 0);
	audio_block_t * receiveWritable(unsigned int index = 0);
	bool update_setup(void);
	static void update_stop(void);
	static void update_all(void) { NVIC_SET_PENDING(IRQ_SOFTWARE); }
	void destructorDisableNVIC(void) {destructorDisabledNVIC = true; NVIC_DISABLE_IRQ(IRQ_SOFTWARE);}
	friend void software_isr(void);
	friend class AudioConnection;
	friend class AudioDebug;
	uint8_t numConnections;
private:
	bool destructorDisabledNVIC;
	static AudioConnection* unused; // linked list of unused but not destructed connections
	AudioConnection *destination_list;
	audio_block_t **inputQueue;
	static AudioStream* update_owner;
	inline void updateOne(void);
	virtual void update(void) = 0;
	void linkIntoUpdateList(const AudioConnection* pC);
	
	
	// Update list: AudioStream objects on this list are examined during every audio
	// interrupt, and if active the update code is called
	static AudioStream *first_update; // for update_all
	AudioStream *next_update; // for update_all
	AudioStream* updateListMergeInto(AudioStream** ppAfter,AudioStream* newHead,AudioStream* pItem);
	AudioStream* updateListUnlinkFrom(AudioStream** ppAfter,AudioStream** ppItemNext);
	AudioStream* updateTailItem(AudioStream* pItem) {while (NULL != pItem && NULL != pItem->next_update) pItem=pItem->next_update; return pItem;}
	void unlinkFromActiveUpdateList(bool fromDestructor = false);
	
	// Clan list: AudioStream objects on this list are NOT yet on the update list,
	// because no connection has yet been made which allows us to determine where
	// they should be in that list.
	//
	// Within a clan the next_update links are used to create an ordering based on
	// connections between clan members. If a clan object is its own head, and
	// has a NULL next_update, then it is an orphan (only member of its clan)
	static AudioStream *first_clan; // first object with no place in the update list
	AudioStream *next_clan; 		// next clan
	AudioStream *clan_head; 		// first object in this object's clan list	
	AudioStream* clanListUnlink(AudioStream* pItem); // unlink whole clan from clan list
	AudioStream* clanListLinkIn(AudioStream* pItem); // link whole clan into clan list
	void unlinkItemFromClanUpdateList(); // remove single AudioStream object from clan
	
	static audio_block_t *memory_pool;
	static unsigned int num_blocks_in_pool;
	static uint32_t memory_pool_available_mask[];
	static uint16_t memory_pool_first_mask;
};

class AudioDebug
{
	public:
		// info on connections
		AudioStream* getSrc(AudioConnection& c) { return c.src;};
		AudioStream* getDst(AudioConnection& c) { return c.dst;};
		unsigned char getSrcN(AudioConnection& c) { return c.src_index;};
		unsigned char getDstN(AudioConnection& c) { return c.dest_index;};
		AudioConnection* getNext(AudioConnection& c) { return c.next_dest;};
		bool isConnected(AudioConnection& c) { return c.isConnected;};
		AudioConnection* unusedList() { return AudioStream::unused;};
		
		// info on streams
		AudioConnection* dstList(AudioStream& s) { return s.destination_list;};
		audio_block_t ** inqList(AudioStream& s) { return s.inputQueue;};
		uint8_t 	 	 getNumInputs(AudioStream& s) { return s.num_inputs;}
		AudioStream*     firstUpdate(AudioStream& s) { return s.first_update;}
		AudioStream* 	 nextUpdate(AudioStream& s) { return s.next_update;}
		AudioStream*     firstClan(AudioStream& s) { return s.first_clan;}
		AudioStream**    pFirstClan(AudioStream& s) { return &s.first_clan;}
		AudioStream* 	 nextClan(AudioStream& s) { return s.next_clan;}
		AudioStream* 	 clanHead(AudioStream& s) { return s.clan_head;}
		uint8_t 	 	 getNumConnections(AudioStream& s) { return s.numConnections;}
		bool 	 	 	 isActive(AudioStream& s) { return s.active;}
		void 			 zapClans() { AudioStream::first_clan = NULL;}
		
};
#endif // __ASSEMBLER__
#endif // AudioStream_h
