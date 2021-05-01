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

#if defined(__IMXRT1062__)
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
AudioStream* AudioStream::first_clan = NULL; // linked list of unused but not destructed AudioStream objects

void software_isr(void);
bool AudioStream::serialStarted = false;

/************************************************************************************/
/* General utilities																*/
/************************************************************************************/
// Link item into list, e.g. listLinkIn(&first_update,&AudioStream,&AudioStream.next_update);
// Before: first_update -----> <something or NULL>
// After:  first_update -> <first linked in> [ -> <more linked in> ] -> <something or NULL>
// NOTE: ppItemNext may NOT be &(pItem->next_update)
//       ppAfter may be &first_update OR &<<some AudioStream>.next_update>
// Will also work for clan list
static void listLinkIn(AudioStream** ppAfter,AudioStream* pItem,AudioStream** ppItemNext)
{
Serial.print("\nLink ");
Serial.print((uint32_t) ppAfter,HEX);
Serial.print("->");
Serial.print((uint32_t) *ppAfter,HEX);
Serial.print(" item ");
Serial.print((uint32_t) pItem,HEX);
Serial.print(" via ");
Serial.print((uint32_t) ppItemNext,HEX);
Serial.print("->");
Serial.println((uint32_t) *ppItemNext,HEX);	
Serial.flush();

	*ppItemNext = *ppAfter;
	*ppAfter = pItem;
}

// Unlink item from list, e.g. listUnlink(&first_update,&AudioStream.next_update);
// After:  first_update -> <first linked in> [ -> <more linked in> ] -> <something or NULL>
// Before: first_update -----> <something or NULL>
// NOTE: ppItemNext might NOT be &((*ppAfter)->next_update)
//       ppAfter may be &first_update OR &<<some AudioStream>.next_update>
// Will also work for clan list
// 
// Unlinked item's "next" pointer is set to NULL
static AudioStream* listUnlink(AudioStream** ppAfter,AudioStream** ppItemNext)
{
	AudioStream* pItem;
Serial.print("\nUnlink ");
Serial.print((uint32_t) ppAfter,HEX);
Serial.print("->");
Serial.flush();
Serial.print((uint32_t) *ppAfter,HEX);
Serial.print(" from ");
Serial.flush();
Serial.print((uint32_t) ppItemNext,HEX);
Serial.print("->");
Serial.flush();
Serial.print((uint32_t) *ppItemNext,HEX);
Serial.flush();

	pItem = *ppAfter;
	*ppAfter = *ppItemNext;
	*ppItemNext = NULL; // remove the item's stale link

Serial.print(": unlinked ");
Serial.print((uint32_t) pItem,HEX);
Serial.flush();
	
	return pItem;
}


// Link clan into clan list.
// Clan list order is unimportant, so we just link it in at the start;
// however, we allow passing in any clan member to specify the clan to add.
AudioStream* AudioStream::clanListLinkIn(AudioStream* pItem)
{
	AudioStream* pHead = pItem->clan_head; // find the clan head
	listLinkIn(&first_clan,pHead,&pHead->next_clan);
	
	return pHead;
}

extern void printClanEntry(AudioStream* m,int indent, AudioStream** ppHead,AudioStream** ppNC,AudioStream** ppNU);
extern void printAclan(AudioStream* m,AudioStream** ppNC);
extern void printClanList(void);
// Unlink clan from clan list, e.g. listUnlink(&AudioStream);
// Assumes clan is well-formed, i.e. that clan members have valid pointers to 
// their clan head. However, there is no need to pass the clan head's address, we
// find this ourselves, and we also deal with finding the source pointer to
// the clan, and with incorrect attempts to unlink an item / clan that is
// not actually in the list.
// 
// Only the clan head needs a valid next_clan
//
// Returns pointer to clan head, so it can be linked back in later
AudioStream* AudioStream::clanListUnlink(AudioStream* pItem)
{
	AudioStream* pHead = pItem->clan_head; // find the clan head
	AudioStream** ppClanHead;
Serial.print("Clan unlink: ");
printAclan(pHead,NULL);
Serial.flush();

	// find where we are in the clan list
	for (ppClanHead = &first_clan; NULL != *ppClanHead && *ppClanHead != pHead; ppClanHead = &(*ppClanHead)->next_clan)
		;
Serial.print(" pointed to by: ");
Serial.print((uint32_t) ppClanHead,HEX);
Serial.flush();
	if (NULL != *ppClanHead) // then we are indeed in the clan list
	{
		listUnlink(ppClanHead,&pHead->next_clan); // unlink
		
Serial.println(": clan unlinked!");
Serial.flush();
	}
	else
	{
Serial.println(": not in list!");
Serial.flush();
	}
	
	return pHead;
}


// Similar to linking into list, but merges clans if needed
// e.g. updateListMergeInto(&first_update,&AudioStream);
// Before: first_update -----> <something or NULL>
// After:  first_update -> <first linked in> [ -> <more linked in> ] -> <something or NULL>
// NOTE: ppAfter may be &first_update OR &<<some AudioStream>.next_update>
//
// For merging, it makes no sense to link in part of a clan, so we find the head
// and tail ourselves to avoid mayhem.
// 
// pItem may be:
// * already in ppAfter's update list: do nothing
// * a clan head being merged into:
// 		* another clan: figure out the new clan head and update all members
//		* the active update list: NULL the clan head pointers
AudioStream* AudioStream::updateListMergeInto(AudioStream** ppAfter,AudioStream* newHead,AudioStream* pItem)
{
	AudioStream* pHead = pItem->clan_head; // find the clan head
	AudioStream* pTail;
	
Serial.print("Merge item: ");	
printClanEntry(pItem,0,NULL,NULL,NULL);
Serial.println("from:");
printAclan(pItem->clan_head,NULL);
Serial.print("after: ");	
Serial.println((uint32_t) ppAfter,HEX);	
Serial.print("before: ");	
printClanEntry(*ppAfter,0,NULL,NULL,NULL);
Serial.print("new head: ");	
Serial.println((uint32_t) newHead,HEX);	
Serial.flush();

	
	if (ppAfter == &first_update ||
		(NULL != *ppAfter &&  NULL == (*ppAfter)->clan_head)) // merging into active update list
	{
		if (NULL != pHead) // and we have a clan head, so we're not already in it!
		{
			for (pTail = pHead; NULL != pTail && NULL != pTail->next_update; pTail = pTail->next_update)
			{
				pTail->clan_head = NULL; // we have no more need of the clan
				pTail->active = true;
			}
			pTail->clan_head = NULL; // do the last entry
			pTail->active = true;
			
Serial.println("Merged to active updates");	
			listLinkIn(ppAfter,pHead,&pTail->next_update);
		}
		pTail = first_update;
	}
	else // merging into clan: *ppAfter MUST be clanned with the new head, we can't link in before it!
	{
		if (newHead != pHead) // different clan heads, it's a real merge
		{
			for (pTail = pHead; NULL != pTail && NULL != pTail->next_update; pTail = pTail->next_update)
				pTail->clan_head = newHead; // we have a new clan allegiance
			pTail->clan_head = newHead; // do the last entry
				
			listLinkIn(ppAfter,pHead,&pTail->next_update);
		}
		// else we share the same clan head, no merge needed
		pTail = newHead;
Serial.println("Merged clan is:");	
printAclan(newHead,NULL);
	}
	
	return pTail; // clan head, or first_update
}

// Unlink item from update list, e.g. updateListUnlinkFrom(&first_update,&AudioStream.next_update);
// Before: first_update -> <first linked in> [ -> <more linked in> ] -> <something or NULL>
// After:  first_update -----> <something or NULL>
// NOTE: ppItemNext might NOT be &((*ppAfter)->next_update)
//       ppAfter may be &first_update OR &<<some AudioStream>.next_update>
// 
// Unlinked item's "next" pointer is set to NULL. All the unlinked items have
// their clan_head set to the first item in the list.
AudioStream* AudioStream::updateListUnlinkFrom(AudioStream** ppAfter,AudioStream** ppItemNext)
{
	AudioStream* pItem = listUnlink(ppAfter,ppItemNext); // first of the items to be unlinked
	
	for (AudioStream* pI = pItem; NULL != pI; pI=pI->next_update)
		pI->clan_head = pItem;
	
	return pItem;
}

/************************************************************************************/
/* Data blocks 																		*/
/************************************************************************************/

// Set up the pool of audio data blocks
// placing them all onto the free list
FLASHMEM void AudioStream::initialize_memory(audio_block_t *data, unsigned int num)
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
void AudioStream::release(audio_block_t *block, bool enableIRQ /* = true */)
{
	if (block == NULL) 
		return;
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
	
	if (enableIRQ)
		__enable_irq();
}


// Release ownership of multiple data blocks.  If no
// other streams have ownership, the blocks are
// returned to the free pool
void AudioStream::release(audio_block_t** blocks, int numBlocks, bool enableIRQ /* = true */)
{
	while (numBlocks--)
	{
		release(*blocks,false); // NULL pointers are allowed, nothing will happen...
		blocks++;
	}
	if (enableIRQ)
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

/************************************************************************************/
/* Connections 																		*/
/************************************************************************************/

// Full constructor with 4 parameters
AudioConnection::AudioConnection(AudioStream &source, unsigned char sourceOutput,
		AudioStream &destination, unsigned char destinationInput)
{
	// we are effectively unused right now, so
	// link ourselves at the start of the unused list
	next_dest = AudioStream::unused;
	AudioStream::unused = this;
	
	isConnected = false;	  
	connect(source,sourceOutput,destination,destinationInput); 
}

// Simplified constructor assuming channel 0 at both ends
AudioConnection::AudioConnection(AudioStream &source, AudioStream &destination)
{
	next_dest = AudioStream::unused;
	AudioStream::unused = this;
	
	isConnected = false;	  
	connect(source, 0, destination,0);
}

// construct the patchCord, but leave it unconnected
AudioConnection::AudioConnection()
{
	next_dest = AudioStream::unused;
	AudioStream::unused = this;
	
	isConnected = false;	  
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
		if (dest_index >= dst->num_inputs) // input number too high
		{
			result = 2;
			break;
		}
		if (!src || !dst) // NULL src or dst - [old] Stream object destroyed
		{
			result = 3;
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
		
		// deal with connecting up previously-unused AudioStream objects:
		src->linkIntoUpdateList(this);
		dst->linkIntoUpdateList(this); // unnecessary?
		
		src->numConnections++;
		//src->active = true;

		dst->numConnections++;
		//dst->active = true;

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
		int cr;
		
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
		/*  this is the old, buggy code
		while (p) {
			if (p == this) {
				if (p->next_dest) {
					p = next_dest; // just destroys our working pointer!
					break;
				} else {
					p = NULL;
					break;
				}
			}
			p = p->next_dest;
		}
		*/
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
		//src->active = false;
		src->unlinkFromUpdateList();
	}

	dst->numConnections--;
	if (dst->numConnections == 0) {
		//dst->active = false;
		dst->unlinkFromUpdateList();
	}
	
	isConnected = false;
	
	// link now-unused connection into "unused" list
	next_dest = dst->unused;
	dst->unused = this;

	__enable_irq();
	
	return 0;
}


/************************************************************************************/
/* Audio streams																	*/
/************************************************************************************/
// Link a new AudioStream object into the update list. This will occur when
// its first connection is made to an object already in the list, OR to 
// an object which isn't in the update list but is a member of a clan.
static int AudioStream::simples = 0;
void AudioStream::linkIntoUpdateList(const AudioConnection* pC)
{
Serial.print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
printClanList();
	
	if (!active) // not yet linked in
	{
		AudioStream** ppS;	
		int i;
		
		/* // original link-in code: links in first, or at end
		if (first_update == NULL) {
			first_update = this;
		} else {
			AudioStream *p;
			for (p=first_update; p->next_update; p = p->next_update) 
				;
			p->next_update = this;
		}
		next_update = NULL;
		*/
		// If the object to link is a non-orphan clan member, then we actually want to
		// link the entire clan in, in order.
		AudioStream* tail = this;		
		
if (simples & 1) {		
Serial.print("from ");		
Serial.print((uint32_t) tail,HEX);		
Serial.print(" head = ");		
Serial.print((uint32_t) clan_head,HEX);
		while (tail->next_update)
			tail = tail->next_update;
Serial.print(" tail = ");		
Serial.println((uint32_t) tail,HEX);
Serial.flush();
		// tail now points to the last member of our clan
		// [this->]clan_head is the first member
}//#endif		

		// Scan the global update list looking for a place to link in
		for (ppS = &first_update; *ppS != NULL; ppS = &((*ppS)->next_update))
		{
			if (*ppS == pC->src) // found the connection's source, we must be destination
			{
				ppS = &(*ppS)->next_update; // link in after our source
				active = true;
				break;
			}
			if (*ppS == pC->dst) // found the connection's destination, we must be source
			{
				active = true;
				break;
			}
		}
		
		if (active) // no longer a clan, link in to main update list
		{
			AudioStream* pS = clanListUnlink(this); // unlink ourselves
			//listLinkIn(ppS,clan_head,&tail->next_update);
			updateListMergeInto(ppS,NULL,this);
Serial.println("...active");
		}
		
		if (!active && // neither source nor destination is in update list, we're still in limbo
		 pC->src->clan_head != pC->dst->clan_head) // and in different clans, which need merging
		{
			AudioStream* ourDFU, *otherDFU; // storage for "dummy first_update" pointers
			AudioStream* linkItem; // actual "link here" item
						
if (!(simples & 2)) {
			pC->src->next_update = pC->dst; // but we know this order is vaguely sane
} else {
			// if we want to relink, one clan will absorb another: do the housekeeping
			if (this == pC->src) // if we're the source
			{
				ourDFU 	 = clanListUnlink(this); // remove ourselves from the clan list
				otherDFU = clanListUnlink(pC->dst);
				
				if (pC->dst == otherDFU) // we're the source and other clan head is destination
				{
Serial.println("Source before other Head:");
					updateListMergeInto(&updateTailItem(ourDFU)->next_update,ourDFU,otherDFU);
					linkItem = ourDFU;
				}
				else // other clan member, but not head, is destination
				{
					AudioStream* pAfter;
					
Serial.println("Source within other clan:");
					// find the preceding object, to link in after it and before our destination
					for (pAfter = otherDFU; NULL != pAfter && pC->dst != pAfter->next_update; pAfter = pAfter->next_update)
						;
					updateListMergeInto(&pAfter,otherDFU,ourDFU);
					linkItem = otherDFU;
				}
				
				clanListLinkIn(linkItem); // link new clan back into clan list
			}
			else // we'd better be the destination, or something's gone Horribly Wrong...
			{
				ourDFU 	 = clanListUnlink(this); // remove ourselves from the clan list
				//otherDFU = clanListUnlink(pC->src);
				
				// simpler case: if we're the destination, we can't be the new clan head
				// and we shouldn't need to unlink and re-link the clan head, either
				AudioStream* pAfter;
				
				// find the preceding object, to link in after it and before our destination
				for (pAfter = otherDFU; NULL != pAfter && pC->src != pAfter->next_update; pAfter = pAfter->next_update)
					;
				updateListMergeInto(&pAfter,otherDFU,ourDFU);
				//linkItem = otherDFU;
				
				//clanListLinkIn(linkItem); // link new clan back into clan list
			}

}
		}
		else
		{
Serial.println("...already clanned up");
		}
Serial.println("...done");
Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
printClanList();
Serial.flush();
			
			//*** THIS COULD BE THE WRONG PLACE! Maybe in update_setup()? *****
			/*
			if (NULL == first_update) // first connection ever: bootstrap the update list
			{
				first_update = pC->src;
				pC->src->active = true;
				pC->dst->active = true;
			}
			*/
		
	}
}

// Unlink an AudioStream object from the update list. This will occur when
// its last connection is severed. Also inactivates the object, assuming it
// was found in the update list. Safe to call if already unlinked.
void AudioStream::unlinkFromUpdateList()
{
	AudioStream** ppS;
Serial.println("Unlink!");
	
	if (NULL == clan_head) // we are in the main update list
		ppS = &first_update;
	else
	{
		for (ppS = &first_clan; *ppS != NULL; ppS = &((*ppS)->next_clan))
			if ((*ppS)->clan_head == clan_head)
				break;
	}
	
	for (/* ppS = &first_update */; *ppS != NULL; ppS = &((*ppS)->next_update))
	{
		if (*ppS == this) // found the link to us
		{
			*ppS = (*ppS)->next_update; // unlink from update list or clan
			
			next_update = NULL;
			active = false;
			clan_head = this;
			next_clan = first_clan;
			first_clan = this;
			break;
		}
	}
}

// Unlink an AudioStream object from the clan list. This will occur when
// its last connection is severed. Also inactivates the object, assuming it
// was found in the update list. Safe to call if already unlinked.
void AudioStream::unlinkFromClanList()
{
	AudioStream** ppS;
	
	// Go down clan list to find clan whose head is the same as ours
	for (ppS = &first_clan; *ppS != NULL; ppS = &((*ppS)->next_clan))
		if ((*ppS) == clan_head)
			break;
	
	if (NULL != *ppS)
	{
		// found our clan: now go along the next_update list  
		// to unlink ourselves from it
		for (; *ppS != NULL; ppS = &((*ppS)->next_update))
		{
			if (*ppS == this) // found the link to us
			{
				*ppS = (*ppS)->next_update;
				next_update = NULL;
				break;
			}
		}
		
		// are we the clan head?
		if (clan_head == this)
		{
			AudioStream* pH = *ppS;
			
			// tell clan members they have a new head
			for (; *ppS != NULL; ppS = &((*ppS)->next_update))
				(*ppS)->clan_head = pH;
		}
	}
}


// For any AudioConnection object in the linked list starting at ppC,
// NULL out its src or dst pointers if they point to "this"
void AudioStream::NULLifConnected(AudioConnection** ppC) //!< list of connections that might refer to this
{
	AudioConnection** ppN;
	
Serial.print(" [disconnect ");
Serial.flush();
	while (*ppC != NULL)
	{
		AudioConnection* pC = *ppC;	// easier to get our head round!
		
Serial.print((uint32_t) pC,HEX);
Serial.flush();

		if (pC->dst == this)
		{
			pC->disconnect();	// disconnect this connection
			pC->dst = NULL;		// can never re-connect, source will no longer exist
Serial.print("=dst ");
Serial.flush();
		}
		if (pC->src == this) // dying AudioStream is source for this connection...
		{
			pC->disconnect();	// disconnect this connection
			pC->src = NULL;		// can never re-connect, source will no longer exist
Serial.print("=src ");
Serial.flush();
		}
		if (pC == *ppC) // link didn't change, so we weren't disconnected...
			ppC = &((*ppC)->next_dest); // ...can follow link 
if (*ppC != NULL)
{	
Serial.print(", ");
Serial.flush();
}
	}	
Serial.print("] ");
Serial.flush();
}

// Destructor: quite a lot of housekeeping to do
AudioStream::~AudioStream()
{
	AudioStream** ppS; // iterating pointer
	AudioConnection** ppC;
	
Serial.print("\nDestructor: (");
Serial.print((uint32_t) this,HEX);
Serial.print(")...");
Serial.flush();

	SAFE_RELEASE(inputQueue,num_inputs,false);	// release input blocks and disable interrupts
	
	// run through all AudioStream objects in the update list,
	// except for ourselves
	for (ppS = &first_update; *ppS != NULL; ppS = &((*ppS)->next_update))
	{
		AudioStream* pS = *ppS;	// easier to get our head round!
Serial.println();
Serial.print((uint32_t) pS,HEX);
Serial.print("...");
Serial.flush();
		// run through all the AudioConnections from this AudioStream
		if (pS != this)
			NULLifConnected(&(pS->destination_list));
	}
	
	// now we can disconnect our own destinations
	NULLifConnected(&destination_list);
	
	// there may be unused AudioConnections which refer to this: "disconnect" those
	// (they're already disconnected, but that's safe, and we do want to NULL
	// the residual src or dst pointers)
Serial.print("\nUnused: ");
Serial.flush();
	NULLifConnected(&unused);
	
	unlinkFromUpdateList();	// unlink ourselves
	unlinkFromClanList(); // from wherever
Serial.print("unlink\n\n");
Serial.flush();
	
	__enable_irq();
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
	
	if (NULL == first_update) // first connection ever: bootstrap the update list
	{
		AudioStream** ppH;
		
		first_update = clan_head; // our clan head should be the first updated object
Serial.print((uint32_t) first_update,HEX);
Serial.println(" set as first_update");
Serial.flush();
		
		// unlink this clan from the clan list
		for (ppH = &first_clan; *ppH != NULL; ppH = &((*ppH)->next_clan))
			if ((*ppH)->clan_head == clan_head)
			{
				*ppH = next_clan;
				break;
			}
		
		// remove clan links for update list: no longer needed
		for (ppH = &first_update; *ppH != NULL; ppH = &((*ppH)->next_update))
		{
			(*ppH)->next_clan = (*ppH)->clan_head = NULL;
			(*ppH)->active = true;
		}
		
	}
	attachInterruptVector(IRQ_SOFTWARE, software_isr);
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

	uint32_t totalcycles = ARM_DWT_CYCCNT;
	//digitalWriteFast(2, HIGH);
	for (p = AudioStream::first_update; p; p = p->next_update) {
		if (p->active) {
			uint32_t cycles = ARM_DWT_CYCCNT;
			p->update();
			// TODO: traverse inputQueueArray and release
			// any input blocks that weren't consumed?
			cycles = (ARM_DWT_CYCCNT - cycles) >> 6;
			p->cpu_cycles = cycles;
			if (cycles > p->cpu_cycles_max) p->cpu_cycles_max = cycles;
		}
	}
	//digitalWriteFast(2, LOW);
	totalcycles = (ARM_DWT_CYCCNT - totalcycles) >> 6;
	AudioStream::cpu_cycles_total = totalcycles;
	if (totalcycles > AudioStream::cpu_cycles_total_max)
		AudioStream::cpu_cycles_total_max = totalcycles;

	asm("DSB");
}

