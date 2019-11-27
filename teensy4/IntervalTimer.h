/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2018 PJRC.COM, LLC.
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

#ifndef __INTERVALTIMER_H__
#define __INTERVALTIMER_H__

#include <stddef.h>
#include "imxrt.h"

#ifdef __cplusplus
extern "C" {
#endif

class IntervalTimer {
private:
	static const uint32_t MAX_PERIOD = UINT32_MAX / (24000000 / 1000000);
public:
	constexpr IntervalTimer() {
	}
	~IntervalTimer() {
		end();
	}
	bool begin(void (*funct)(), unsigned int microseconds) {
		if (microseconds == 0 || microseconds > MAX_PERIOD) return false;
		uint32_t cycles = (24000000 / 1000000) * microseconds - 1;
		if (cycles < 36) return false;
		return beginCycles(funct, cycles);
	}
	bool begin(void (*funct)(), int microseconds) {
		if (microseconds < 0) return false;
		return begin(funct, (unsigned int)microseconds);
	}
	bool begin(void (*funct)(), unsigned long microseconds) {
		return begin(funct, (unsigned int)microseconds);
	}
	bool begin(void (*funct)(), long microseconds) {
		return begin(funct, (int)microseconds);
	}
	bool begin(void (*funct)(), float microseconds) {
		if (microseconds <= 0 || microseconds > MAX_PERIOD) return false;
		uint32_t cycles = (float)(24000000 / 1000000) * microseconds - 0.5;
		if (cycles < 36) return false;
		return beginCycles(funct, cycles);
	}
	bool begin(void (*funct)(), double microseconds) {
		return begin(funct, (float)microseconds);
	}
	void update(unsigned int microseconds) {
		if (microseconds == 0 || microseconds > MAX_PERIOD) return;
		uint32_t cycles = (24000000 / 1000000) * microseconds - 1;
		if (cycles < 36) return;
		if (channel) channel->LDVAL = cycles;
	}
	void update(int microseconds) {
		if (microseconds < 0) return;
		return update((unsigned int)microseconds);
	}
	void update(unsigned long microseconds) {
		return update((unsigned int)microseconds);
	}
	void update(long microseconds) {
		return update((int)microseconds);
	}
	void update(float microseconds) {
		if (microseconds <= 0 || microseconds > MAX_PERIOD) return;
		uint32_t cycles = (float)(24000000 / 1000000) * microseconds - 0.5;
		if (cycles < 36) return;
		if (channel) channel->LDVAL = cycles;
	}
	void update(double microseconds) {
		return update((float)microseconds);
	}
	void end();
	void priority(uint8_t n) {
		nvic_priority = n;
		if (channel) {
			int index = channel - IMXRT_PIT_CHANNELS;
			nvic_priorites[index] = nvic_priority;
			if (nvic_priorites[0] <= nvic_priorites[1]) {
				NVIC_SET_PRIORITY(IRQ_PIT, nvic_priorites[0]);
			} else {
				NVIC_SET_PRIORITY(IRQ_PIT, nvic_priorites[1]);
			}
		}
	}
	operator IRQ_NUMBER_t() {
		if (channel) {
			return IRQ_PIT;
		}
		return (IRQ_NUMBER_t)NVIC_NUM_INTERRUPTS;
	}
private:
//#define IMXRT_PIT_CHANNELS              ((IMXRT_PIT_CHANNEL_t *)(&(IMXRT_PIT.offset100)))
	IMXRT_PIT_CHANNEL_t *channel = nullptr;
	uint8_t nvic_priority = 128;
	static uint8_t nvic_priorites[4];
	bool beginCycles(void (*funct)(), uint32_t cycles);

};


#ifdef __cplusplus
}
#endif

#endif
