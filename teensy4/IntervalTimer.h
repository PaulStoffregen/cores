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

#ifdef __cplusplus
#ifndef __INTERVALTIMER_H__
#define __INTERVALTIMER_H__

#include <stddef.h>
#include "imxrt.h"
#if TEENSYDUINO >= 159
#include "inplace_function.h"
#endif

// IntervalTimer provides access to hardware timers which can run an
// interrupt function a precise timing intervals.
// https://www.pjrc.com/teensy/td_timing_IntervalTimer.html
// Up to 4 IntervalTimers may be in use simultaneously.  Many
// libraries use IntervalTimer, so some of these 4 possible
// instances may be in use by libraries.
class IntervalTimer {
private:
	static const int32_t MAX_PERIOD = UINT32_MAX / (24000000 / 1000000); // need to change to int32_t to avoid warnings
public:
	constexpr IntervalTimer() {
	}
	~IntervalTimer() {
		end();
	}
#if TEENSYDUINO >= 159
	using callback_t = teensy::inplace_function<void(void), 16>;
#else
	using callback_t = void (*)(void);
#endif
	// Start the hardware timer and begin calling the function.  The
	// interval is specified in microseconds, using integer or float
	// for precise timing.  Returns true is sucessful, or false if
	// all hardware timers are already in use.
	template <typename period_t>
	bool begin(callback_t funct, period_t period) {
		uint32_t cycles = cyclesFromPeriod(period);
		return cycles >= 17 ? beginCycles(funct, cycles) : false;
	}
	// Change the timer's interval.  The current interval is completed
	// as previously configured, and then the next interval begins with
	// with this new setting.
	template <typename period_t>
	void update(period_t period){
		uint32_t cycles = cyclesFromPeriod(period);
		if (cycles < 17) return;
		if (channel) channel->LDVAL = cycles;
	}
	// Stop calling the function. The hardware timer resource becomes available
	// for use by other IntervalTimer instances.
	void end();
	// Set the interrupt priority level, controlling which other interrupts this
	// timer is allowed to interrupt. Lower numbers are higher priority, with 0
	// the highest and 255 the lowest. Most other interrupts default to 128. As
	// a general guideline, interrupt routines that run longer should be given
	// lower priority (higher numerical values).
	void priority(uint8_t n) {
		nvic_priority = n;
		if (channel) {
			int index = channel - IMXRT_PIT_CHANNELS;
			nvic_priorites[index] = nvic_priority;
			uint8_t top_priority = nvic_priorites[0];
			for (uint8_t i=1; i < (sizeof(nvic_priorites)/sizeof(nvic_priorites[0])); i++) {
				if (top_priority > nvic_priorites[i]) top_priority = nvic_priorites[i];
			}
			NVIC_SET_PRIORITY(IRQ_PIT, top_priority);
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
	bool beginCycles(callback_t funct, uint32_t cycles);

	template <typename period_t>
	uint32_t cyclesFromPeriod(period_t period) {
		static_assert(std::is_arithmetic_v<period_t>, "Period must be arithmetic");

		if (period < 0 || period > MAX_PERIOD)
			return 0;
		if constexpr (std::is_integral_v<period_t>)       // handles all integral types
			return (24000000 / 1000000) * period - 1;
		if constexpr (std::is_floating_point_v<period_t>) // handles all float types
			return (float)(24000000 / 1000000) * period - 0.5f;

		//Can't fall through, arithmetic is either integral or floting_point
	}
};

#endif //__INTERVALTIMER_H__
#endif //__cplusplus
