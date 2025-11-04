/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2019 PJRC.COM, LLC.
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

#include "core_pins.h"
#include "arm_math.h"	// micros() synchronization

//volatile uint32_t F_CPU = 396000000;
//volatile uint32_t F_BUS = 132000000;
volatile uint32_t systick_millis_count = 0;
volatile uint32_t systick_cycle_count = 0;
volatile uint32_t scale_cpu_cycles_to_microseconds = 0;
uint32_t systick_safe_read;	 // micros() synchronization

//The 24 MHz XTALOSC can be the external clock source of SYSTICK. 
//Hardware devides this down to 100KHz. (RM Rev2, 13.3.21 PG 986)
#define SYSTICK_EXT_FREQ 100000

#if 0
// moved to EventResponder.cpp
void systick_isr(void)
{
	systick_millis_count++;
	// MillisTimer::runFromTimer();
	//digitalWriteFast(12, HIGH);
	//delayMicroseconds(1);
	//digitalWriteFast(12, LOW);
}
#endif

#if 0
void millis_init(void)
{
	//printf("millis_init %08lX\n", SYST_CALIB);
	_VectorsRam[15] = systick_isr;
#ifdef SYSTICK_EXT_FREQ
	SYST_RVR = (SYSTICK_EXT_FREQ / 1000) - 1;
	SYST_CVR = 0;
	SYST_CSR = SYST_CSR_TICKINT | SYST_CSR_ENABLE;
#else
	SYST_RVR = (F_CPU / 1000) - 1;
	SYST_CVR = 0;
	SYST_CSR = SYST_CSR_CLKSOURCE | SYST_CSR_TICKINT | SYST_CSR_ENABLE;
#endif
	//SCB_SHPR3 = 0x20200000;  // Systick = priority 32
	//printf("RVR=%lu\r\n", SYST_RVR);
}
#endif

/*void yield(void)
{

}*/

// Wait for a number of milliseconds.  During this time, interrupts remain
// active, but the rest of your program becomes effectively stalled.  Usually
// delay() is used in very simple programs.  To achieve delay without waiting
// use millis() or elapsedMillis.  For shorter delay, use delayMicroseconds()
// or delayNanoseconds().
void delay(uint32_t msec)
{
	uint32_t start;

	if (msec == 0) return;
	start = micros();
	while (1) {
		while ((micros() - start) >= 1000) {
			if (--msec == 0) return;
			start += 1000;
		}
		yield();
	}
	// TODO...
}

// Returns the number of microseconds since your program started running.
// This 32 bit number will roll back to zero after about 71 minutes and
// 35 seconds.  For a simpler way to build delays or timeouts, consider
// using elapsedMicros.
uint32_t micros(void)
{
	uint32_t smc, scc;
	do {
		__LDREXW(&systick_safe_read);
		smc = systick_millis_count;
		scc = systick_cycle_count;
	} while ( __STREXW(1, &systick_safe_read));
	uint32_t cyccnt = ARM_DWT_CYCCNT;
	asm volatile("" : : : "memory");
	uint32_t ccdelta = cyccnt - scc;
	uint32_t frac = ((uint64_t)ccdelta * scale_cpu_cycles_to_microseconds) >> 32;
	if (frac > 1000) frac = 1000;
	uint32_t usec = 1000*smc + frac;
	return usec;
}

#if 0 // kept to compare test to cycle count micro()
uint32_t micros(void)
{
	uint32_t msec, tick, elapsed, istatus, usec;
	//static uint32_t prev_msec=0;
	//static uint32_t prev_istatus=0;
	//static uint32_t prev_tick=0;
	//static uint32_t prev_elapsed=0;
	static uint32_t prev_usec=0;
	static int doprint=180;

	__disable_irq();
	tick = SYST_CVR;
	msec = systick_millis_count;
	istatus = SCB_ICSR;     // bit 26 indicates if systick exception pending
#ifndef SYSTICK_EXT_FREQ
	const uint32_t fcpu = F_CPU;
#endif
	__enable_irq();
	istatus &= SCB_ICSR_PENDSTSET;
#ifdef SYSTICK_EXT_FREQ
	if ((istatus & SCB_ICSR_PENDSTSET) && (tick == 0 || tick > (SYSTICK_EXT_FREQ / 2000))) {
#else
	if ((istatus & SCB_ICSR_PENDSTSET) && (tick == 0 || tick > (fcpu / 2000))) {
#endif
		// systick generated an interrupt at the 1 -> 0 transition, and
		// we read it before an ISR could increment systick_millis_count
		msec++;
	}
#if defined(SYSTICK_EXT_FREQ) && SYSTICK_EXT_FREQ <= 1000000
	elapsed = (SYSTICK_EXT_FREQ / 1000) - tick;
	if (tick == 0) elapsed = 0;
	usec = msec * 1000 + elapsed * (1000000 / SYSTICK_EXT_FREQ);
#elif defined(SYSTICK_EXT_FREQ) && SYSTICK_EXT_FREQ > 1000000
	elapsed = (SYSTICK_EXT_FREQ / 1000) - tick;
	if (tick == 0) elapsed = 0;
	usec = msec * 1000 + elapsed / (SYSTICK_EXT_FREQ / 1000000);
#else
	elapsed = (fcpu / 1000) - tick;
	if (tick == 0) elapsed = 0;
	usec = msec * 1000 + elapsed / (fcpu / 1000000);
#endif
	//if (doprint) printf("%lu  %lu\r\n", msec, systick);
	if (usec < prev_usec && doprint) {
		//print("opps\r\n");
		//printf("opps then: msec=%lu, systick=%lu, elapsed=%lu, usec=%lu, i=%lx\n",
			//prev_msec, prev_tick, prev_elapsed, prev_usec, prev_istatus);
		//printf("      now: msec=%lu, systick=%lu, elapsed=%lu, usec=%lu, i=%lx\n",
			//msec, tick, elapsed, usec, istatus);
		if (doprint > 0) doprint--;
	}
	//prev_msec = msec;
	//prev_elapsed = elapsed;
	//prev_tick = tick;
	//prev_istatus = istatus;
	prev_usec = usec;
	return usec;
}
#endif
