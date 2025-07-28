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

#include "DMAChannel.h"

#define DMA_MAX_CHANNELS 32

// The channel allocation bitmask is accessible from "C" namespace,
// so C-only code can reserve DMA channels
uint32_t dma_channel_allocated_mask = 0;

#ifdef CR
#warning "CR is defined as something?"
#endif

struct DMAOneTimeInit {
	DMAOneTimeInit() {
		CCM_CCGR5 |= CCM_CCGR5_DMA(CCM_CCGR_ON);
		DMA_CR = DMA_CR_GRP1PRI | DMA_CR_EMLM | DMA_CR_EDBG;
		auto dchpri = &DMA_DCHPRI3;
		// group 0 (channels 0-15) can be pre-empted, cannot pre-empt others
		for (int i=0; i < 16; i++) {
			dchpri[i + 3 - 2 * (i&3)] |= DMA_DCHPRI_ECP | DMA_DCHPRI_DPA;
		}
		// group 1 (channels 16-31) cannot be pre-empted, can pre-empt others
		for (int i=16; i < 32; i++) {
			dchpri[i + 3 - 2 * (i&3)] &= ~(DMA_DCHPRI_ECP | DMA_DCHPRI_DPA);
		}
	}
};

void DMAChannel::begin(bool force_initialization, bool preemptible)
{
	__disable_irq();
	if (!force_initialization && channel < DMA_MAX_CHANNELS
	  && (dma_channel_allocated_mask & (1 << channel))
	  && TCD == IMXRT_DMA_TCD+channel) {
		// DMA channel already allocated
		__enable_irq();
		return;
	}

	// prefer channels without shared IRQs
	uint32_t bestch = DMA_MAX_CHANNELS;
	uint32_t ch = preemptible ? 0 : 16;
	while (ch < DMA_MAX_CHANNELS) {
		if (!(dma_channel_allocated_mask & (1 << ch))) {
			if (!(dma_channel_allocated_mask & (1 << (ch ^ 16))))
				break;
			else if (bestch >= DMA_MAX_CHANNELS)
				bestch = ch;
		}
		++ch;
	}
	if (ch >= DMA_MAX_CHANNELS) {
		if (bestch < DMA_MAX_CHANNELS) {
			// no channels with free IRQs available, will have to share
			ch = bestch;
		} else { // no more channels available
			__enable_irq();
			TCD = (TCD_t *)0;
			channel = DMA_MAX_CHANNELS;
			return;
			// attempts to use this object will hardfault
		}
	}
	dma_channel_allocated_mask |= (1 << ch);
	__enable_irq();
	channel = ch;

	// static initialization will be done the first time this function runs
	static DMAOneTimeInit init;

	DMA_CERQ = ch;
	DMA_CERR = ch;
	DMA_CEEI = ch;
	DMA_CINT = ch;
	TCD = IMXRT_DMA_TCD+channel;
	uint32_t *p = (uint32_t *)TCD;
	*p++ = 0;
	*p++ = 0;
	*p++ = 0;
	*p++ = 0;
	*p++ = 0;
	*p++ = 0;
	*p++ = 0;
	*p++ = 0;
}

void DMAChannel::release(void)
{
	if (channel >= DMA_MAX_CHANNELS) return;
	DMA_CERQ = channel;
	detachInterrupt();
	__disable_irq();
	dma_channel_allocated_mask &= ~(1 << channel);
	__enable_irq();
	channel = DMA_MAX_CHANNELS;
	TCD = (TCD_t *)0;
}

static uint32_t priority(const DMAChannel &c)
{
	uint32_t n;
	n = *(uint32_t *)((uint32_t)&DMA_DCHPRI3 + (c.channel & 0xFC));
	n = __builtin_bswap32(n);
	return (n >> ((c.channel & 0x03) << 3)) & 0x0F;
}

static void swap(DMAChannel &c1, DMAChannel &c2)
{
	uint8_t c;
	DMABaseClass::TCD_t *t;

	c = c1.channel;
	c1.channel = c2.channel;
	c2.channel = c;
	t = c1.TCD;
	c1.TCD = c2.TCD;
	c2.TCD = t;
}


void DMAPriorityOrder(DMAChannel &ch1, DMAChannel &ch2)
{
	if (priority(ch1) < priority(ch2)) swap(ch1, ch2);
}

void DMAPriorityOrder(DMAChannel &ch1, DMAChannel &ch2, DMAChannel &ch3)
{
	if (priority(ch2) < priority(ch3)) swap(ch2, ch3);
	if (priority(ch1) < priority(ch2)) swap(ch1, ch2);
	if (priority(ch2) < priority(ch3)) swap(ch2, ch3);
}

void DMAPriorityOrder(DMAChannel &ch1, DMAChannel &ch2, DMAChannel &ch3, DMAChannel &ch4)
{
	if (priority(ch3) < priority(ch4)) swap(ch3, ch4);
	if (priority(ch2) < priority(ch3)) swap(ch2, ch3);
	if (priority(ch1) < priority(ch2)) swap(ch1, ch2);
	if (priority(ch3) < priority(ch4)) swap(ch2, ch3);
	if (priority(ch2) < priority(ch3)) swap(ch1, ch2);
	if (priority(ch3) < priority(ch4)) swap(ch2, ch3);
}

extern "C" void unused_interrupt_vector(void);
typedef void (*isr_t)(void);
static isr_t dma_handlers[DMA_MAX_CHANNELS];

// converts DMA channel to equivalent interrupt vector
#define CHANNEL_TO_IRQ(a) ((a & 15) + IRQ_DMA_CH0)
// converts interrupt vector to CPU exception
#define IRQ_TO_EXCEPTION(a) (a + 16)

#define CHANNEL_TO_EXCEPTION(a) (IRQ_TO_EXCEPTION(CHANNEL_TO_IRQ(a)))

static void dma_isr(void) {
	// which CPU exception brought us here?
	uint32_t ipsr;
	asm volatile("mrs %0, ipsr\n" : "=r" (ipsr));

	if (ipsr >= IRQ_TO_EXCEPTION(IRQ_DMA_CH0) &&
	  ipsr <= IRQ_TO_EXCEPTION(IRQ_DMA_CH15)) {
		/* Two DMA channels share each interrupt: X and X+16
		* Check the group 0 channel first (X)
		* then the group 1 channel (X+16)
		*/
		uint32_t INT = DMA_INT;
		int ch = ipsr - CHANNEL_TO_EXCEPTION(0);
		// did the group 0 channel trigger?
		if (INT & (1 << ch)) {
			if (dma_handlers[ch]) // call registered handler
				(*dma_handlers[ch])();
			else // else manually clear the interrupt
				DMA_CINT = ch;
		}
		// did the group 1 channel trigger?
		if (INT & ((1<<16) << ch)) {
			ch += 16;
			if (dma_handlers[ch])
				(*dma_handlers[ch])();
			else
				DMA_CINT = ch;
		}
		asm volatile("dsb");
	}
}

void DMAChannel::attachInterrupt(isr_t isr) {
	uint8_t irq = CHANNEL_TO_IRQ(channel);
	dma_handlers[channel] = isr;
	_VectorsRam[IRQ_TO_EXCEPTION(irq)] = dma_isr;
	NVIC_ENABLE_IRQ(irq);
}

void DMAChannel::attachInterrupt(isr_t isr, uint8_t prio) {
	// since two channels share each interrupt, use whichever priority is lower
	uint8_t irq = CHANNEL_TO_IRQ(channel);
	if (dma_handlers[channel ^ 16] == (isr_t)0 || NVIC_GET_PRIORITY(irq) > prio) {
		NVIC_SET_PRIORITY(irq, prio);
	}
	attachInterrupt(isr);
}

void DMAChannel::detachInterrupt(void) {
	if (channel >= DMA_MAX_CHANNELS)
		return;

	// if the shared channel isn't using the interrupt, disable it
	if (dma_handlers[channel ^ 16] == (isr_t)0) {
		uint8_t irq = IRQ_TO_EXCEPTION(channel);
		NVIC_DISABLE_IRQ(irq);
		// restore default priority and handler
		NVIC_SET_PRIORITY(irq, 128);
		_VectorsRam[IRQ_TO_EXCEPTION(irq)] = unused_interrupt_vector;
	}
	dma_handlers[channel] = (isr_t)0;
}
