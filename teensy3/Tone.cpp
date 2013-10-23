/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2013 PJRC.COM, LLC.
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
#include "pins_arduino.h"
#include "HardwareSerial.h"
#include "IntervalTimer.h"

#if 1
// IntervalTimer based tone.  This allows tone() to share the timers with other
// libraries, rather than permanently hogging one PIT timer even for projects
// which never use tone().  Someday this single-tone implementation might be
// changed to allow multiple simultaneous tones.

static uint32_t tone_toggle_count;
static volatile uint8_t *tone_reg;
static uint8_t tone_pin=255;
static uint16_t tone_frequency=0;
IntervalTimer tone_timer;

void tone_interrupt(void);

void tone(uint8_t pin, uint16_t frequency, uint32_t duration)
{
	uint32_t count;
	volatile uint32_t *config;
	float usec;

	if (pin >= CORE_NUM_DIGITAL) return;
	if (duration) {
		count = (frequency * duration / 1000) * 2;
	} else {
		count = 0xFFFFFFFF;
	}
	usec = (float)500000.0 / (float)frequency;
	config = portConfigRegister(pin);

	// TODO: IntervalTimer really needs an API to disable and enable
	// the interrupt on a single timer.
	__disable_irq();
	if (pin == tone_pin) {
		if (frequency == tone_frequency) {
			// same pin, same frequency, so just update the
			// duration.  Users will call repetitively call
			// tone() with the same setting, expecting a
			// continuous output with no glitches or phase
			// changes or jitter at each call.
			tone_toggle_count = count;
		} else {
			// same pin, but a new frequency.
			tone_reg[0] = 1; // clear pin
			tone_timer.begin(tone_interrupt, usec);
		}
	} else {
		if (tone_pin < CORE_NUM_DIGITAL) {
			tone_reg[0] = 1; // clear pin
		}
		tone_pin = pin;
		tone_reg = portClearRegister(pin);
		tone_reg[0] = 1; // clear pin
		tone_reg[384] = 1; // output mode;
		*config = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
		tone_toggle_count = count;
		tone_timer.begin(tone_interrupt, usec);
	}
	__enable_irq();
}


void tone_interrupt(void)
{
	if (tone_toggle_count) {
		tone_reg[128] = 1; // toggle
		if (tone_toggle_count < 0xFFFFFFFF) tone_toggle_count--;
	} else {
		tone_timer.end();
		tone_reg[0] = 0; // clear
		tone_pin = 255;
		tone_frequency = 0;
	}
}

void noTone(uint8_t pin)
{
	if (pin >= CORE_NUM_DIGITAL) return;
	__disable_irq();
	if (pin == tone_pin) {
		tone_timer.end();
		tone_reg[0] = 0; // clear
		tone_pin = 255;
		tone_frequency = 0;
	}
	__enable_irq();
}
#endif



#if 0
// Old PIT timer based tone().  This implementation is slightly more efficient,
// but it consumes one of the PIT timers, even for projects which never use tone().

static uint32_t tone_toggle_count;
static volatile uint8_t *tone_reg;
static uint8_t tone_pin;

void init_tone(void)
{
	if (SIM_SCGC6 & SIM_SCGC6_PIT) return;
	SIM_SCGC6 |= SIM_SCGC6_PIT; // TODO: use bitband for atomic read-mod-write
	PIT_MCR = 0;
	PIT_TCTRL3 = 0;		// disabled
	tone_pin = 255;
	NVIC_ENABLE_IRQ(IRQ_PIT_CH3);
}

void tone(uint8_t pin, uint16_t frequency, uint32_t duration)
{
	uint32_t count, load;
	volatile uint32_t *config;

	init_tone();
	if (pin >= CORE_NUM_DIGITAL) return;
	if (duration) {
		count = (frequency * duration / 1000) * 2;
	} else {
		count = 0xFFFFFFFF;
	}
	load = (F_BUS / 2) / frequency;
	config = portConfigRegister(pin);
	__disable_irq();
	if (pin != tone_pin) {
		if (tone_pin < CORE_NUM_DIGITAL) {
			tone_reg[0] = 1; // clear pin
		}
		tone_pin = pin;
		tone_reg = portClearRegister(pin);
		tone_reg[0] = 1; // clear pin
		tone_reg[384] = 1; // output mode;
		*config = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
	}
	tone_toggle_count = count;
	if (PIT_LDVAL3 != load) {
		PIT_TCTRL3 = 0;
		PIT_LDVAL3 = load;
		PIT_TCTRL3 = 3;
	}
	__enable_irq();
}

void pit3_isr(void)
{
	PIT_TFLG3 = 1;

	if (tone_toggle_count) {
		tone_reg[128] = 1; // toggle
		if (tone_toggle_count < 0xFFFFFFFF) tone_toggle_count--;
	} else {
		PIT_TCTRL3 = 0;
		PIT_LDVAL3 = 0;
		tone_reg[0] = 0; // clear
		tone_pin = 255;
	}
}

void noTone(uint8_t pin)
{
	if (pin >= CORE_NUM_DIGITAL) return;
	__disable_irq();
	if (pin == tone_pin) {
		PIT_TCTRL3 = 0;
		PIT_LDVAL3 = 0;
		tone_reg[0] = 0; // clear
		tone_pin = 255;
	}
	__enable_irq();
}
#endif









