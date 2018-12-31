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

// only 16 channels supported, because we don't handle sharing interrupts
#define DMA_MAX_CHANNELS 16

// The channel allocation bitmask is accessible from "C" namespace,
// so C-only code can reserve DMA channels
uint16_t dma_channel_allocated_mask = 0;

#ifdef CR
#warning "CR is defined as something?"
#endif


void DMAChannel::begin(bool force_initialization)
{
	uint32_t ch = 0;

	__disable_irq();
	if (!force_initialization && TCD && channel < DMA_MAX_CHANNELS
	  && (dma_channel_allocated_mask & (1 << channel))
	  && (uint32_t)TCD == (uint32_t)(0x400E9000 + channel * 32)) {
		// DMA channel already allocated
		__enable_irq();
		return;
	}
	while (1) {
		if (!(dma_channel_allocated_mask & (1 << ch))) {
			dma_channel_allocated_mask |= (1 << ch);
			__enable_irq();
			break;
		}
		if (++ch >= DMA_MAX_CHANNELS) {
			__enable_irq();
			TCD = (TCD_t *)0;
			channel = DMA_MAX_CHANNELS;
			return; // no more channels available
			// attempts to use this object will hardfault
		}
	}
	channel = ch;

	CCM_CCGR5 |= CCM_CCGR5_DMA(CCM_CCGR_ON);
	DMA_CR = DMA_CR_GRP1PRI | DMA_CR_EMLM | DMA_CR_EDBG;
	DMA_CERQ = ch;
	DMA_CERR = ch;
	DMA_CEEI = ch;
	DMA_CINT = ch;
	TCD = (TCD_t *)(0x400E9000 + ch * 32);
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

