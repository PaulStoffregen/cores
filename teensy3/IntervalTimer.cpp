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

#include "IntervalTimer.h"

static void dummy_funct(void);

#if defined(KINETISK)
#define NUM_CHANNELS 4
static void (*funct_table[4])(void) = {dummy_funct, dummy_funct, dummy_funct, dummy_funct};

#elif defined(KINETISL)
#define NUM_CHANNELS 2
static void (*funct_table[2])(void) = {dummy_funct, dummy_funct};
uint8_t IntervalTimer::nvic_priorites[2] = {255, 255};
#endif


bool IntervalTimer::beginCycles(void (*funct)(), uint32_t cycles)
{
	if (channel) {
		channel->TCTRL = 0;
		channel->TFLG = 1;
	} else {
		SIM_SCGC6 |= SIM_SCGC6_PIT;
		__asm__ volatile("nop"); // solves timing problem on Teensy 3.5
		PIT_MCR = 1;
		channel = KINETISK_PIT_CHANNELS;
		while (1) {
			if (channel->TCTRL == 0) break;
			if (++channel >= KINETISK_PIT_CHANNELS + NUM_CHANNELS) {
				channel = NULL;
				return false;
			}
		}
	}
	int index = channel - KINETISK_PIT_CHANNELS;
	funct_table[index] = funct;
	channel->LDVAL = cycles;
	channel->TCTRL = 3;
#if defined(KINETISK)
	NVIC_SET_PRIORITY(IRQ_PIT_CH0 + index, nvic_priority);
	NVIC_ENABLE_IRQ(IRQ_PIT_CH0 + index);
#elif defined(KINETISL)
	nvic_priorites[index] = nvic_priority;
	if (nvic_priorites[0] <= nvic_priorites[1]) {
		NVIC_SET_PRIORITY(IRQ_PIT, nvic_priorites[0]);
	} else {
		NVIC_SET_PRIORITY(IRQ_PIT, nvic_priorites[1]);
	}
	NVIC_ENABLE_IRQ(IRQ_PIT);
#endif
	return true;
}


void IntervalTimer::end() {
	if (channel) {
		int index = channel - KINETISK_PIT_CHANNELS;
#if defined(KINETISK)
		NVIC_DISABLE_IRQ(IRQ_PIT_CH0 + index);
#elif defined(KINETISL)
		// TODO: disable IRQ_PIT, but only if both instances ended
#endif
		funct_table[index] = dummy_funct;
		channel->TCTRL = 0;
#if defined(KINETISL)
		nvic_priorites[index] = 255;
		if (nvic_priorites[0] <= nvic_priorites[1]) {
			NVIC_SET_PRIORITY(IRQ_PIT, nvic_priorites[0]);
		} else {
			NVIC_SET_PRIORITY(IRQ_PIT, nvic_priorites[1]);
		}
#endif
		channel = 0;
	}
}


#if defined(KINETISK)
void pit0_isr()
{
	PIT_TFLG0 = 1;
	funct_table[0]();
}

void pit1_isr() {
	PIT_TFLG1 = 1;
	funct_table[1]();
}

void pit2_isr() {
	PIT_TFLG2 = 1;
	funct_table[2]();
}

void pit3_isr() {
	PIT_TFLG3 = 1;
	funct_table[3]();
}

#elif defined(KINETISL)
void pit_isr() {
	if (PIT_TFLG0) {
		PIT_TFLG0 = 1;
		funct_table[0]();
	}
	if (PIT_TFLG1) {
		PIT_TFLG1 = 1;
		funct_table[1]();
	}
}
#endif

static void dummy_funct(void)
{
}

