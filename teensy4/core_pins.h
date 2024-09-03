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

#pragma once
#include "imxrt.h"
#include "pins_arduino.h"

#define HIGH			1
#define LOW			0
#define INPUT			0
#define OUTPUT			1
#define INPUT_PULLUP		2
#define INPUT_PULLDOWN		3
#define OUTPUT_OPENDRAIN	4
#define INPUT_DISABLE		5
#define LSBFIRST		0
#define MSBFIRST		1
#define _BV(n)			(1<<(n))
#define CHANGE			4
#define FALLING			2
#define RISING			3


#if defined(__IMXRT1062__) && defined(__has_include) && __has_include("teensy4_custom_variant.h")
#include "teensy4_custom_variant.h"
#pragma message("using teensy4 custom variant!")
#elif defined(__IMXRT1062__) && defined(ARDUINO_TEENSY40)
#include "variants/teensy_40.h"
#elif defined(__IMXRT1062__) && defined(ARDUINO_TEENSY41)
#include "variants/teensy_41.h"
#elif defined(__IMXRT1062__) && defined(ARDUINO_TEENSY_MICROMOD)
#include "variants/teensy_mm.h"
#else
#error "failed to determine teensy variant"
#endif


// verify the included files defined required things!
#if !defined(PINS_TO_PWM_INFO)
#error "teensy cores requires PWM pins to be defined in 'PINS_TO_PWM_INFO'"
#elif !defined(PINS_TO_ANALOG_CHANNELS)
#error "teensy cores requires analog pins to be defined in 'PINS_TO_ANALOG_CHANNELS'"
#elif !defined(PINS_TO_DIGITAL_INFO)
#error "teensy cores requires digital pins to be configured in 'PINS_TO_DIGITAL_INFO'"
#endif

#ifdef __cplusplus
extern "C" {
#endif

//TODO:
//#define analogInputToDigitalPin(p)
//#define digitalPinHasPWM(p)
#define digitalPinToInterrupt(p)  ((p) < NUM_DIGITAL_PINS ? (p) : -1)

// Cause a digital pin to output either HIGH or LOW.  The pin must
// have been configured with pinMode() as either OUTPUT or
// OUTPUT_OPENDRAIN mode.
void digitalWrite(uint8_t pin, uint8_t val);
static inline void digitalWriteFast(uint8_t pin, uint8_t val) __attribute__((always_inline, unused));
// Cause a digital pin to output either HIGH or LOW.  The pin must
// have been configured with pinMode().  This fast version of
// digitalWrite has minimal overhead when the pin number is a
// constant.  Successive digitalWriteFast without delays can be
// too quick in many applications!
static inline void digitalWriteFast(uint8_t pin, uint8_t val)
{
	if (__builtin_constant_p(pin)) {
		if (val) {
			if (pin == 0) {
				CORE_PIN0_PORTSET = CORE_PIN0_BITMASK;
#if CORE_NUM_DIGITAL > 1
			} else if (pin == 1) {
				CORE_PIN1_PORTSET = CORE_PIN1_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 2
			} else if (pin == 2) {
				CORE_PIN2_PORTSET = CORE_PIN2_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 3
			} else if (pin == 3) {
				CORE_PIN3_PORTSET = CORE_PIN3_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 4
			} else if (pin == 4) {
				CORE_PIN4_PORTSET = CORE_PIN4_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 5
			} else if (pin == 5) {
				CORE_PIN5_PORTSET = CORE_PIN5_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 6
			} else if (pin == 6) {
				CORE_PIN6_PORTSET = CORE_PIN6_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 7
			} else if (pin == 7) {
				CORE_PIN7_PORTSET = CORE_PIN7_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 8
			} else if (pin == 8) {
				CORE_PIN8_PORTSET = CORE_PIN8_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 9
			} else if (pin == 9) {
				CORE_PIN9_PORTSET = CORE_PIN9_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 10
			} else if (pin == 10) {
				CORE_PIN10_PORTSET = CORE_PIN10_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 11
			} else if (pin == 11) {
				CORE_PIN11_PORTSET = CORE_PIN11_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 12
			} else if (pin == 12) {
				CORE_PIN12_PORTSET = CORE_PIN12_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 13
			} else if (pin == 13) {
				CORE_PIN13_PORTSET = CORE_PIN13_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 14
			} else if (pin == 14) {
				CORE_PIN14_PORTSET = CORE_PIN14_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 15
			} else if (pin == 15) {
				CORE_PIN15_PORTSET = CORE_PIN15_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 16
			} else if (pin == 16) {
				CORE_PIN16_PORTSET = CORE_PIN16_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 17
			} else if (pin == 17) {
				CORE_PIN17_PORTSET = CORE_PIN17_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 18
			} else if (pin == 18) {
				CORE_PIN18_PORTSET = CORE_PIN18_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 19
			} else if (pin == 19) {
				CORE_PIN19_PORTSET = CORE_PIN19_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 20
			} else if (pin == 20) {
				CORE_PIN20_PORTSET = CORE_PIN20_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 21
			} else if (pin == 21) {
				CORE_PIN21_PORTSET = CORE_PIN21_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 22
			} else if (pin == 22) {
				CORE_PIN22_PORTSET = CORE_PIN22_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 23
			} else if (pin == 23) {
				CORE_PIN23_PORTSET = CORE_PIN23_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 24
			} else if (pin == 24) {
				CORE_PIN24_PORTSET = CORE_PIN24_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 25
			} else if (pin == 25) {
				CORE_PIN25_PORTSET = CORE_PIN25_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 26
			} else if (pin == 26) {
				CORE_PIN26_PORTSET = CORE_PIN26_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 27
			} else if (pin == 27) {
				CORE_PIN27_PORTSET = CORE_PIN27_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 28
			} else if (pin == 28) {
				CORE_PIN28_PORTSET = CORE_PIN28_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 29
			} else if (pin == 29) {
				CORE_PIN29_PORTSET = CORE_PIN29_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 30
			} else if (pin == 30) {
				CORE_PIN30_PORTSET = CORE_PIN30_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 31
			} else if (pin == 31) {
				CORE_PIN31_PORTSET = CORE_PIN31_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 32
			} else if (pin == 32) {
				CORE_PIN32_PORTSET = CORE_PIN32_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 33
			} else if (pin == 33) {
				CORE_PIN33_PORTSET = CORE_PIN33_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 34
			} else if (pin == 34) {
				CORE_PIN34_PORTSET = CORE_PIN34_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 35
			} else if (pin == 35) {
				CORE_PIN35_PORTSET = CORE_PIN35_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 36
			} else if (pin == 36) {
				CORE_PIN36_PORTSET = CORE_PIN36_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 37
			} else if (pin == 37) {
				CORE_PIN37_PORTSET = CORE_PIN37_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 38
			} else if (pin == 38) {
				CORE_PIN38_PORTSET = CORE_PIN38_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 39
			} else if (pin == 39) {
				CORE_PIN39_PORTSET = CORE_PIN39_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 40
			} else if (pin == 40) {
				CORE_PIN40_PORTSET = CORE_PIN40_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 41
			} else if (pin == 41) {
				CORE_PIN41_PORTSET = CORE_PIN41_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 42
			} else if (pin == 42) {
				CORE_PIN42_PORTSET = CORE_PIN42_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 43
			} else if (pin == 43) {
				CORE_PIN43_PORTSET = CORE_PIN43_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 44
			} else if (pin == 44) {
				CORE_PIN44_PORTSET = CORE_PIN44_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 45
			} else if (pin == 45) {
				CORE_PIN45_PORTSET = CORE_PIN45_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 46
			} else if (pin == 46) {
				CORE_PIN46_PORTSET = CORE_PIN46_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 47
			} else if (pin == 47) {
				CORE_PIN47_PORTSET = CORE_PIN47_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 48
			} else if (pin == 48) {
				CORE_PIN48_PORTSET = CORE_PIN48_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 49
			} else if (pin == 49) {
				CORE_PIN49_PORTSET = CORE_PIN49_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 50
			} else if (pin == 50) {
				CORE_PIN50_PORTSET = CORE_PIN50_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 51
			} else if (pin == 51) {
				CORE_PIN51_PORTSET = CORE_PIN51_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 52
			} else if (pin == 52) {
				CORE_PIN52_PORTSET = CORE_PIN52_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 53
			} else if (pin == 53) {
				CORE_PIN53_PORTSET = CORE_PIN53_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 54
			} else if (pin == 54) {
				CORE_PIN54_PORTSET = CORE_PIN54_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 55
			} else if (pin == 55) {
				CORE_PIN55_PORTSET = CORE_PIN55_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 56
			} else if (pin == 56) {
				CORE_PIN56_PORTSET = CORE_PIN56_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 57
			} else if (pin == 57) {
				CORE_PIN57_PORTSET = CORE_PIN57_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 58
			} else if (pin == 58) {
				CORE_PIN58_PORTSET = CORE_PIN58_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 59
			} else if (pin == 59) {
				CORE_PIN59_PORTSET = CORE_PIN59_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 60
			} else if (pin == 60) {
				CORE_PIN60_PORTSET = CORE_PIN60_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 61
			} else if (pin == 61) {
				CORE_PIN61_PORTSET = CORE_PIN61_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 62
			} else if (pin == 62) {
				CORE_PIN62_PORTSET = CORE_PIN62_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 63
			} else if (pin == 63) {
				CORE_PIN63_PORTSET = CORE_PIN63_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 64
			} else if (pin == 64) {
				CORE_PIN64_PORTSET = CORE_PIN64_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 65
			} else if (pin == 65) {
				CORE_PIN65_PORTSET = CORE_PIN65_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 66
			} else if (pin == 66) {
				CORE_PIN66_PORTSET = CORE_PIN66_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 67
			} else if (pin == 67) {
				CORE_PIN67_PORTSET = CORE_PIN67_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 68
			} else if (pin == 68) {
				CORE_PIN68_PORTSET = CORE_PIN68_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 69
			} else if (pin == 69) {
				CORE_PIN69_PORTSET = CORE_PIN69_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 70
			} else if (pin == 70) {
				CORE_PIN70_PORTSET = CORE_PIN70_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 71
			} else if (pin == 71) {
				CORE_PIN71_PORTSET = CORE_PIN71_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 72
			} else if (pin == 72) {
				CORE_PIN72_PORTSET = CORE_PIN72_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 73
			} else if (pin == 73) {
				CORE_PIN73_PORTSET = CORE_PIN73_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 74
			} else if (pin == 74) {
				CORE_PIN74_PORTSET = CORE_PIN74_BITMASK;
#endif
			}
		} else {
			if (pin == 0) {
				CORE_PIN0_PORTCLEAR = CORE_PIN0_BITMASK;
#if CORE_NUM_DIGITAL > 1
			} else if (pin == 1) {
				CORE_PIN1_PORTCLEAR = CORE_PIN1_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 2
			} else if (pin == 2) {
				CORE_PIN2_PORTCLEAR = CORE_PIN2_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 3
			} else if (pin == 3) {
				CORE_PIN3_PORTCLEAR = CORE_PIN3_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 4
			} else if (pin == 4) {
				CORE_PIN4_PORTCLEAR = CORE_PIN4_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 5
			} else if (pin == 5) {
				CORE_PIN5_PORTCLEAR = CORE_PIN5_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 6
			} else if (pin == 6) {
				CORE_PIN6_PORTCLEAR = CORE_PIN6_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 7
			} else if (pin == 7) {
				CORE_PIN7_PORTCLEAR = CORE_PIN7_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 8
			} else if (pin == 8) {
				CORE_PIN8_PORTCLEAR = CORE_PIN8_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 9
			} else if (pin == 9) {
				CORE_PIN9_PORTCLEAR = CORE_PIN9_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 10
			} else if (pin == 10) {
				CORE_PIN10_PORTCLEAR = CORE_PIN10_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 11
			} else if (pin == 11) {
				CORE_PIN11_PORTCLEAR = CORE_PIN11_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 12
			} else if (pin == 12) {
				CORE_PIN12_PORTCLEAR = CORE_PIN12_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 13
			} else if (pin == 13) {
				CORE_PIN13_PORTCLEAR = CORE_PIN13_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 14
			} else if (pin == 14) {
				CORE_PIN14_PORTCLEAR = CORE_PIN14_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 15
			} else if (pin == 15) {
				CORE_PIN15_PORTCLEAR = CORE_PIN15_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 16
			} else if (pin == 16) {
				CORE_PIN16_PORTCLEAR = CORE_PIN16_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 17
			} else if (pin == 17) {
				CORE_PIN17_PORTCLEAR = CORE_PIN17_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 18
			} else if (pin == 18) {
				CORE_PIN18_PORTCLEAR = CORE_PIN18_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 19
			} else if (pin == 19) {
				CORE_PIN19_PORTCLEAR = CORE_PIN19_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 20
			} else if (pin == 20) {
				CORE_PIN20_PORTCLEAR = CORE_PIN20_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 21
			} else if (pin == 21) {
				CORE_PIN21_PORTCLEAR = CORE_PIN21_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 22
			} else if (pin == 22) {
				CORE_PIN22_PORTCLEAR = CORE_PIN22_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 23
			} else if (pin == 23) {
				CORE_PIN23_PORTCLEAR = CORE_PIN23_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 24
			} else if (pin == 24) {
				CORE_PIN24_PORTCLEAR = CORE_PIN24_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 25
			} else if (pin == 25) {
				CORE_PIN25_PORTCLEAR = CORE_PIN25_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 26
			} else if (pin == 26) {
				CORE_PIN26_PORTCLEAR = CORE_PIN26_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 27
			} else if (pin == 27) {
				CORE_PIN27_PORTCLEAR = CORE_PIN27_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 28
			} else if (pin == 28) {
				CORE_PIN28_PORTCLEAR = CORE_PIN28_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 29
			} else if (pin == 29) {
				CORE_PIN29_PORTCLEAR = CORE_PIN29_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 30
			} else if (pin == 30) {
				CORE_PIN30_PORTCLEAR = CORE_PIN30_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 31
			} else if (pin == 31) {
				CORE_PIN31_PORTCLEAR = CORE_PIN31_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 32
			} else if (pin == 32) {
				CORE_PIN32_PORTCLEAR = CORE_PIN32_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 33
			} else if (pin == 33) {
				CORE_PIN33_PORTCLEAR = CORE_PIN33_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 34
			} else if (pin == 34) {
				CORE_PIN34_PORTCLEAR = CORE_PIN34_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 35
			} else if (pin == 35) {
				CORE_PIN35_PORTCLEAR = CORE_PIN35_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 36
			} else if (pin == 36) {
				CORE_PIN36_PORTCLEAR = CORE_PIN36_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 37
			} else if (pin == 37) {
				CORE_PIN37_PORTCLEAR = CORE_PIN37_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 38
			} else if (pin == 38) {
				CORE_PIN38_PORTCLEAR = CORE_PIN38_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 39
			} else if (pin == 39) {
				CORE_PIN39_PORTCLEAR = CORE_PIN39_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 40
			} else if (pin == 40) {
				CORE_PIN40_PORTCLEAR = CORE_PIN40_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 41
			} else if (pin == 41) {
				CORE_PIN41_PORTCLEAR = CORE_PIN41_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 42
			} else if (pin == 42) {
				CORE_PIN42_PORTCLEAR = CORE_PIN42_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 43
			} else if (pin == 43) {
				CORE_PIN43_PORTCLEAR = CORE_PIN43_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 44
			} else if (pin == 44) {
				CORE_PIN44_PORTCLEAR = CORE_PIN44_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 45
			} else if (pin == 45) {
				CORE_PIN45_PORTCLEAR = CORE_PIN45_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 46
			} else if (pin == 46) {
				CORE_PIN46_PORTCLEAR = CORE_PIN46_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 47
			} else if (pin == 47) {
				CORE_PIN47_PORTCLEAR = CORE_PIN47_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 48
			} else if (pin == 48) {
				CORE_PIN48_PORTCLEAR = CORE_PIN48_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 49
			} else if (pin == 49) {
				CORE_PIN49_PORTCLEAR = CORE_PIN49_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 50
			} else if (pin == 50) {
				CORE_PIN50_PORTCLEAR = CORE_PIN50_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 51
			} else if (pin == 51) {
				CORE_PIN51_PORTCLEAR = CORE_PIN51_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 52
			} else if (pin == 52) {
				CORE_PIN52_PORTCLEAR = CORE_PIN52_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 53
			} else if (pin == 53) {
				CORE_PIN53_PORTCLEAR = CORE_PIN53_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 54
			} else if (pin == 54) {
				CORE_PIN54_PORTCLEAR = CORE_PIN54_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 55
			} else if (pin == 55) {
				CORE_PIN55_PORTCLEAR = CORE_PIN55_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 56
			} else if (pin == 56) {
				CORE_PIN56_PORTCLEAR = CORE_PIN56_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 57
			} else if (pin == 57) {
				CORE_PIN57_PORTCLEAR = CORE_PIN57_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 58
			} else if (pin == 58) {
				CORE_PIN58_PORTCLEAR = CORE_PIN58_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 59
			} else if (pin == 59) {
				CORE_PIN59_PORTCLEAR = CORE_PIN59_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 60
			} else if (pin == 60) {
				CORE_PIN60_PORTCLEAR = CORE_PIN60_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 61
			} else if (pin == 61) {
				CORE_PIN61_PORTCLEAR = CORE_PIN61_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 62
			} else if (pin == 62) {
				CORE_PIN62_PORTCLEAR = CORE_PIN62_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 63
			} else if (pin == 63) {
				CORE_PIN63_PORTCLEAR = CORE_PIN63_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 64
			} else if (pin == 64) {
				CORE_PIN64_PORTCLEAR = CORE_PIN64_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 65
			} else if (pin == 65) {
				CORE_PIN65_PORTCLEAR = CORE_PIN65_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 66
			} else if (pin == 66) {
				CORE_PIN66_PORTCLEAR = CORE_PIN66_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 67
			} else if (pin == 67) {
				CORE_PIN67_PORTCLEAR = CORE_PIN67_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 68
			} else if (pin == 68) {
				CORE_PIN68_PORTCLEAR = CORE_PIN68_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 69
			} else if (pin == 69) {
				CORE_PIN69_PORTCLEAR = CORE_PIN69_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 70
			} else if (pin == 70) {
				CORE_PIN70_PORTCLEAR = CORE_PIN70_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 71
			} else if (pin == 71) {
				CORE_PIN71_PORTCLEAR = CORE_PIN71_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 72
			} else if (pin == 72) {
				CORE_PIN72_PORTCLEAR = CORE_PIN72_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 73
			} else if (pin == 73) {
				CORE_PIN73_PORTCLEAR = CORE_PIN73_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 74
			} else if (pin == 74) {
				CORE_PIN74_PORTCLEAR = CORE_PIN74_BITMASK;
#endif
			}
		}
	} else {
		if(val) *portSetRegister(pin) = digitalPinToBitMask(pin);
		else *portClearRegister(pin) = digitalPinToBitMask(pin);
	}
}

// Read the signal at a digital pin.  The pin must have previously been
// configured with pinMode() as INPUT, INPUT_PULLUP, or INPUT_PULLDOWN.
// The return value is either HIGH or LOW.
uint8_t digitalRead(uint8_t pin);
static inline uint8_t digitalReadFast(uint8_t pin) __attribute__((always_inline, unused));
// Read the signal at a digital pin.  The pin must have previously been
// configured with pinMode() as INPUT, INPUT_PULLUP, or INPUT_PULLDOWN.  The
// return value is either HIGH or LOW.  This fast version of digitalRead()
// has minimal overhead when the pin number is a constant.
static inline uint8_t digitalReadFast(uint8_t pin)
{
	if (__builtin_constant_p(pin)) {
		if (pin == 0) {
			return (CORE_PIN0_PINREG & CORE_PIN0_BITMASK) ? 1 : 0;
#if CORE_NUM_DIGITAL > 1
		} else if (pin == 1) {
			return (CORE_PIN1_PINREG & CORE_PIN1_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 2
		} else if (pin == 2) {
			return (CORE_PIN2_PINREG & CORE_PIN2_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 3
		} else if (pin == 3) {
			return (CORE_PIN3_PINREG & CORE_PIN3_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 4
		} else if (pin == 4) {
			return (CORE_PIN4_PINREG & CORE_PIN4_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 5
		} else if (pin == 5) {
			return (CORE_PIN5_PINREG & CORE_PIN5_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 6
		} else if (pin == 6) {
			return (CORE_PIN6_PINREG & CORE_PIN6_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 7
		} else if (pin == 7) {
			return (CORE_PIN7_PINREG & CORE_PIN7_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 8
		} else if (pin == 8) {
			return (CORE_PIN8_PINREG & CORE_PIN8_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 9
		} else if (pin == 9) {
			return (CORE_PIN9_PINREG & CORE_PIN9_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 10
		} else if (pin == 10) {
			return (CORE_PIN10_PINREG & CORE_PIN10_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 11
		} else if (pin == 11) {
			return (CORE_PIN11_PINREG & CORE_PIN11_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 12
		} else if (pin == 12) {
			return (CORE_PIN12_PINREG & CORE_PIN12_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 13
		} else if (pin == 13) {
			return (CORE_PIN13_PINREG & CORE_PIN13_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 14
		} else if (pin == 14) {
			return (CORE_PIN14_PINREG & CORE_PIN14_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 15
		} else if (pin == 15) {
			return (CORE_PIN15_PINREG & CORE_PIN15_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 16
		} else if (pin == 16) {
			return (CORE_PIN16_PINREG & CORE_PIN16_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 17
		} else if (pin == 17) {
			return (CORE_PIN17_PINREG & CORE_PIN17_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 18
		} else if (pin == 18) {
			return (CORE_PIN18_PINREG & CORE_PIN18_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 19
		} else if (pin == 19) {
			return (CORE_PIN19_PINREG & CORE_PIN19_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 20
		} else if (pin == 20) {
			return (CORE_PIN20_PINREG & CORE_PIN20_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 21
		} else if (pin == 21) {
			return (CORE_PIN21_PINREG & CORE_PIN21_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 22
		} else if (pin == 22) {
			return (CORE_PIN22_PINREG & CORE_PIN22_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 23
		} else if (pin == 23) {
			return (CORE_PIN23_PINREG & CORE_PIN23_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 24
		} else if (pin == 24) {
			return (CORE_PIN24_PINREG & CORE_PIN24_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 25
		} else if (pin == 25) {
			return (CORE_PIN25_PINREG & CORE_PIN25_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 26
		} else if (pin == 26) {
			return (CORE_PIN26_PINREG & CORE_PIN26_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 27
		} else if (pin == 27) {
			return (CORE_PIN27_PINREG & CORE_PIN27_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 28
		} else if (pin == 28) {
			return (CORE_PIN28_PINREG & CORE_PIN28_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 29
		} else if (pin == 29) {
			return (CORE_PIN29_PINREG & CORE_PIN29_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 30
		} else if (pin == 30) {
			return (CORE_PIN30_PINREG & CORE_PIN30_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 31
		} else if (pin == 31) {
			return (CORE_PIN31_PINREG & CORE_PIN31_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 32
		} else if (pin == 32) {
			return (CORE_PIN32_PINREG & CORE_PIN32_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 33
		} else if (pin == 33) {
			return (CORE_PIN33_PINREG & CORE_PIN33_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 34
		} else if (pin == 34) {
			return (CORE_PIN34_PINREG & CORE_PIN34_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 35
		} else if (pin == 35) {
			return (CORE_PIN35_PINREG & CORE_PIN35_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 36
		} else if (pin == 36) {
			return (CORE_PIN36_PINREG & CORE_PIN36_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 37
		} else if (pin == 37) {
			return (CORE_PIN37_PINREG & CORE_PIN37_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 38
		} else if (pin == 38) {
			return (CORE_PIN38_PINREG & CORE_PIN38_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 39
		} else if (pin == 39) {
			return (CORE_PIN39_PINREG & CORE_PIN39_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 40
		} else if (pin == 40) {
			return (CORE_PIN40_PINREG & CORE_PIN40_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 41
		} else if (pin == 41) {
			return (CORE_PIN41_PINREG & CORE_PIN41_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 42
		} else if (pin == 42) {
			return (CORE_PIN42_PINREG & CORE_PIN42_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 43
		} else if (pin == 43) {
			return (CORE_PIN43_PINREG & CORE_PIN43_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 44
		} else if (pin == 44) {
			return (CORE_PIN44_PINREG & CORE_PIN44_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 45
		} else if (pin == 45) {
			return (CORE_PIN45_PINREG & CORE_PIN45_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 46
		} else if (pin == 46) {
			return (CORE_PIN46_PINREG & CORE_PIN46_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 47
		} else if (pin == 47) {
			return (CORE_PIN47_PINREG & CORE_PIN47_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 48
		} else if (pin == 48) {
			return (CORE_PIN48_PINREG & CORE_PIN48_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 49
		} else if (pin == 49) {
			return (CORE_PIN49_PINREG & CORE_PIN49_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 50
		} else if (pin == 50) {
			return (CORE_PIN50_PINREG & CORE_PIN50_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 51
		} else if (pin == 51) {
			return (CORE_PIN51_PINREG & CORE_PIN51_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 52
		} else if (pin == 52) {
			return (CORE_PIN52_PINREG & CORE_PIN52_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 53
		} else if (pin == 53) {
			return (CORE_PIN53_PINREG & CORE_PIN53_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 54
		} else if (pin == 54) {
			return (CORE_PIN54_PINREG & CORE_PIN54_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 55
			} else if (pin == 55) {
				return (CORE_PIN55_PINREG & CORE_PIN55_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 56
			} else if (pin == 56) {
				return (CORE_PIN56_PINREG & CORE_PIN56_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 57
			} else if (pin == 57) {
				return (CORE_PIN57_PINREG & CORE_PIN57_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 58
			} else if (pin == 58) {
				return (CORE_PIN58_PINREG & CORE_PIN58_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 59
			} else if (pin == 59) {
				return (CORE_PIN59_PINREG & CORE_PIN59_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 60
			} else if (pin == 60) {
				return (CORE_PIN60_PINREG & CORE_PIN60_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 61
			} else if (pin == 61) {
				return (CORE_PIN61_PINREG & CORE_PIN61_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 62
			} else if (pin == 62) {
				return (CORE_PIN62_PINREG & CORE_PIN62_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 63
			} else if (pin == 63) {
				return (CORE_PIN63_PINREG & CORE_PIN63_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 64
			} else if (pin == 64) {
				return (CORE_PIN64_PINREG & CORE_PIN64_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 65
			} else if (pin == 65) {
				return (CORE_PIN65_PINREG & CORE_PIN65_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 66
			} else if (pin == 66) {
				return (CORE_PIN66_PINREG & CORE_PIN66_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 67
			} else if (pin == 67) {
				return (CORE_PIN67_PINREG & CORE_PIN67_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 68
			} else if (pin == 68) {
				return (CORE_PIN68_PINREG & CORE_PIN68_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 69
			} else if (pin == 69) {
				return (CORE_PIN69_PINREG & CORE_PIN69_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 70
			} else if (pin == 70) {
				return (CORE_PIN70_PINREG & CORE_PIN70_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 71
			} else if (pin == 71) {
				return (CORE_PIN71_PINREG & CORE_PIN71_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 72
			} else if (pin == 72) {
				return (CORE_PIN72_PINREG & CORE_PIN72_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 73
			} else if (pin == 73) {
				return (CORE_PIN73_PINREG & CORE_PIN73_BITMASK) ? 1 : 0;
#endif
#if CORE_NUM_DIGITAL > 74
			} else if (pin == 74) {
				return (CORE_PIN74_PINREG & CORE_PIN74_BITMASK) ? 1 : 0;
#endif

		} else {
			return 0;
		}
	} else {
		return (*portInputRegister(pin) & digitalPinToBitMask(pin)) ? 1 : 0;
	}
}

// Cause a digital pin's output to change state.  If it was HIGH,
// the pin outputs LOW, and if it was LOW the pin outputs HIGH.  The
// pin must have been configured to OUTPUT mode with pinMode().
void digitalToggle(uint8_t pin);
static inline void digitalToggleFast(uint8_t pin) __attribute__((always_inline, unused));
// Cause a digital pin's output to change state.  This fast version
// of digitalToggle() has minimal overhead when the pin number is a
// constant.  Without additional delay, successive digitalToggleFast()
// can cause the pin to oscillate too quickly for many applications.
static inline void digitalToggleFast(uint8_t pin)
{
	if (__builtin_constant_p(pin)) {
		if (pin == 0) {
			CORE_PIN0_PORTTOGGLE = CORE_PIN0_BITMASK;
#if CORE_NUM_DIGITAL > 1
		} else if (pin == 1) {
			CORE_PIN1_PORTTOGGLE = CORE_PIN1_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 2
		} else if (pin == 2) {
			CORE_PIN2_PORTTOGGLE = CORE_PIN2_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 3
		} else if (pin == 3) {
			CORE_PIN3_PORTTOGGLE = CORE_PIN3_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 4
		} else if (pin == 4) {
			CORE_PIN4_PORTTOGGLE = CORE_PIN4_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 5
		} else if (pin == 5) {
			CORE_PIN5_PORTTOGGLE = CORE_PIN5_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 6
		} else if (pin == 6) {
			CORE_PIN6_PORTTOGGLE = CORE_PIN6_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 7
		} else if (pin == 7) {
			CORE_PIN7_PORTTOGGLE = CORE_PIN7_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 8
		} else if (pin == 8) {
			CORE_PIN8_PORTTOGGLE = CORE_PIN8_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 9
		} else if (pin == 9) {
			CORE_PIN9_PORTTOGGLE = CORE_PIN9_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 10
		} else if (pin == 10) {
			CORE_PIN10_PORTTOGGLE = CORE_PIN10_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 11
		} else if (pin == 11) {
			CORE_PIN11_PORTTOGGLE = CORE_PIN11_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 12
		} else if (pin == 12) {
			CORE_PIN12_PORTTOGGLE = CORE_PIN12_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 13
		} else if (pin == 13) {
			CORE_PIN13_PORTTOGGLE = CORE_PIN13_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 14
		} else if (pin == 14) {
			CORE_PIN14_PORTTOGGLE = CORE_PIN14_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 15
		} else if (pin == 15) {
			CORE_PIN15_PORTTOGGLE = CORE_PIN15_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 16
		} else if (pin == 16) {
			CORE_PIN16_PORTTOGGLE = CORE_PIN16_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 17
		} else if (pin == 17) {
			CORE_PIN17_PORTTOGGLE = CORE_PIN17_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 18
		} else if (pin == 18) {
			CORE_PIN18_PORTTOGGLE = CORE_PIN18_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 19
		} else if (pin == 19) {
			CORE_PIN19_PORTTOGGLE = CORE_PIN19_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 20
		} else if (pin == 20) {
			CORE_PIN20_PORTTOGGLE = CORE_PIN20_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 21
		} else if (pin == 21) {
			CORE_PIN21_PORTTOGGLE = CORE_PIN21_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 22
		} else if (pin == 22) {
			CORE_PIN22_PORTTOGGLE = CORE_PIN22_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 23
		} else if (pin == 23) {
			CORE_PIN23_PORTTOGGLE = CORE_PIN23_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 24
		} else if (pin == 24) {
			CORE_PIN24_PORTTOGGLE = CORE_PIN24_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 25
		} else if (pin == 25) {
			CORE_PIN25_PORTTOGGLE = CORE_PIN25_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 26
		} else if (pin == 26) {
			CORE_PIN26_PORTTOGGLE = CORE_PIN26_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 27
		} else if (pin == 27) {
			CORE_PIN27_PORTTOGGLE = CORE_PIN27_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 28
		} else if (pin == 28) {
			CORE_PIN28_PORTTOGGLE = CORE_PIN28_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 29
		} else if (pin == 29) {
			CORE_PIN29_PORTTOGGLE = CORE_PIN29_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 30
		} else if (pin == 30) {
			CORE_PIN30_PORTTOGGLE = CORE_PIN30_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 31
		} else if (pin == 31) {
			CORE_PIN31_PORTTOGGLE = CORE_PIN31_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 32
		} else if (pin == 32) {
			CORE_PIN32_PORTTOGGLE = CORE_PIN32_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 33
		} else if (pin == 33) {
			CORE_PIN33_PORTTOGGLE = CORE_PIN33_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 34
		} else if (pin == 34) {
			CORE_PIN34_PORTTOGGLE = CORE_PIN34_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 35
		} else if (pin == 35) {
			CORE_PIN35_PORTTOGGLE = CORE_PIN35_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 36
		} else if (pin == 36) {
			CORE_PIN36_PORTTOGGLE = CORE_PIN36_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 37
		} else if (pin == 37) {
			CORE_PIN37_PORTTOGGLE = CORE_PIN37_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 38
		} else if (pin == 38) {
			CORE_PIN38_PORTTOGGLE = CORE_PIN38_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 39
		} else if (pin == 39) {
			CORE_PIN39_PORTTOGGLE = CORE_PIN39_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 40
		} else if (pin == 40) {
			CORE_PIN40_PORTTOGGLE = CORE_PIN40_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 41
		} else if (pin == 41) {
			CORE_PIN41_PORTTOGGLE = CORE_PIN41_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 42
		} else if (pin == 42) {
			CORE_PIN42_PORTTOGGLE = CORE_PIN42_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 43
		} else if (pin == 43) {
			CORE_PIN43_PORTTOGGLE = CORE_PIN43_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 44
		} else if (pin == 44) {
			CORE_PIN44_PORTTOGGLE = CORE_PIN44_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 45
		} else if (pin == 45) {
			CORE_PIN45_PORTTOGGLE = CORE_PIN45_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 46
		} else if (pin == 46) {
			CORE_PIN46_PORTTOGGLE = CORE_PIN46_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 47
		} else if (pin == 47) {
			CORE_PIN47_PORTTOGGLE = CORE_PIN47_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 48
		} else if (pin == 48) {
			CORE_PIN48_PORTTOGGLE = CORE_PIN48_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 49
		} else if (pin == 49) {
			CORE_PIN49_PORTTOGGLE = CORE_PIN49_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 50
		} else if (pin == 50) {
			CORE_PIN50_PORTTOGGLE = CORE_PIN50_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 51
		} else if (pin == 51) {
			CORE_PIN51_PORTTOGGLE = CORE_PIN51_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 52
		} else if (pin == 52) {
			CORE_PIN52_PORTTOGGLE = CORE_PIN52_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 53
		} else if (pin == 53) {
			CORE_PIN53_PORTTOGGLE = CORE_PIN53_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 54
		} else if (pin == 54) {
			CORE_PIN54_PORTTOGGLE = CORE_PIN54_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 55
			} else if (pin == 55) {
				CORE_PIN55_PORTTOGGLE = CORE_PIN55_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 56
			} else if (pin == 56) {
				CORE_PIN56_PORTTOGGLE = CORE_PIN56_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 57
			} else if (pin == 57) {
				CORE_PIN57_PORTTOGGLE = CORE_PIN57_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 58
			} else if (pin == 58) {
				CORE_PIN58_PORTTOGGLE = CORE_PIN58_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 59
			} else if (pin == 59) {
				CORE_PIN59_PORTTOGGLE = CORE_PIN59_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 60
			} else if (pin == 60) {
				CORE_PIN60_PORTTOGGLE = CORE_PIN60_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 61
			} else if (pin == 61) {
				CORE_PIN61_PORTTOGGLE = CORE_PIN61_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 62
			} else if (pin == 62) {
				CORE_PIN62_PORTTOGGLE = CORE_PIN62_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 63
			} else if (pin == 63) {
				CORE_PIN63_PORTTOGGLE = CORE_PIN63_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 64
			} else if (pin == 64) {
				CORE_PIN64_PORTTOGGLE = CORE_PIN64_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 65
			} else if (pin == 65) {
				CORE_PIN65_PORTTOGGLE = CORE_PIN65_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 66
			} else if (pin == 66) {
				CORE_PIN66_PORTTOGGLE = CORE_PIN66_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 67
			} else if (pin == 67) {
				CORE_PIN67_PORTTOGGLE = CORE_PIN67_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 68
			} else if (pin == 68) {
				CORE_PIN68_PORTTOGGLE = CORE_PIN68_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 69
			} else if (pin == 69) {
				CORE_PIN69_PORTTOGGLE = CORE_PIN69_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 70
			} else if (pin == 70) {
				CORE_PIN70_PORTTOGGLE = CORE_PIN70_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 71
			} else if (pin == 71) {
				CORE_PIN71_PORTTOGGLE = CORE_PIN71_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 72
			} else if (pin == 72) {
				CORE_PIN72_PORTTOGGLE = CORE_PIN72_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 73
			} else if (pin == 73) {
				CORE_PIN73_PORTTOGGLE = CORE_PIN73_BITMASK;
#endif
#if CORE_NUM_DIGITAL > 74
			} else if (pin == 74) {
				CORE_PIN74_PORTTOGGLE = CORE_PIN74_BITMASK;
#endif
		}
	} else {
		digitalToggle(pin);
	}
}

// Configure a digital pin.  The mode can be INPUT, INPUT_PULLUP,
// INPUT_PULLDOWN, OUTPUT, OUTPUT_OPENDRAIN or INPUT_DISABLE. Use
// INPUT_DISABLE to minimize power consumption for unused pins
// and pins with analog voltages.
void pinMode(uint8_t pin, uint8_t mode);
void init_pins(void);
// Causes a PWM capable pin to output a pulsing waveform with specific
// duty cycle.  PWM is useful for varying the average power delivered to
// LEDs, motors and other devices.  Unless analogWriteResolution() was
// used, the range is 0 (pin stays LOW) to 256 (pin stays HIGH).  The
// PWM frequency may be configured with analogWriteFrequency().
void analogWrite(uint8_t pin, int value);
uint32_t analogWriteRes(uint32_t bits);
// Configure PWM resolution for the analogWrite() function.  For example, 12
// bits gives a range of 0 to 4096.  This function returns the prior
// resolution, allowing you to temporarily change resolution, call analogWrite()
// and then restore the resolution, so other code or libraries using analogWrite()
// are not impacted.
static inline uint32_t analogWriteResolution(uint32_t bits) { return analogWriteRes(bits); }
// Configure the PWM carrier frequency used by a specific PWM pin.  The frequency
// is a floating point number, so you are not limited to integer frequency.  You can
// have 261.63 Hz (musical note C4), if you like.  analogWriteFrequency() should
// be called before analogWrite().  If the pin is already in PWM mode, the result is
// unpredictagle.  Because groups of PWM pins are controlled by the same timer, changing
// a pin may affect others in the same group.
// See https://www.pjrc.com/teensy/td_pulse.html for details.
void analogWriteFrequency(uint8_t pin, float frequency);
// Run a function when a pin changes or has a specific input.  The function runs
// as an interrupt, so care should be taken to minimize time spent.  The mode
// may be RISING, FALLING, CHANGE, HIGH or LOW.  For best compatibility with
// Arduino boards, the first parameter should be specified as
// digitalPinToInterrupt(pin), even though not required by Teensy.
void attachInterrupt(uint8_t pin, void (*function)(void), int mode);
// Remove a previously configured attachInterrupt() function from a pin.
void detachInterrupt(uint8_t pin);
void _init_Teensyduino_internal_(void);
// Read the voltage at an analog pin.  The pin may be specified as the actual
// pin number, or names A0 to A17.  Unless analogReadResolution() was used, the
// return value is a number from 0 to 1023, representing 0 to 3.3 volts.
int analogRead(uint8_t pin);
// On Teensy 4, analogRead() always uses the 3.3V power as its reference.  This
// function has no effect, but is provided to allow programs developed for
// Arduino boards to compile.
void analogReference(uint8_t type);
void analogReadRes(unsigned int bits);
// Configure the number of bits resolution returned by analogRead().
static inline void analogReadResolution(unsigned int bits) { analogReadRes(bits); }
// Configure the number readings used (and averaged) internally when reading analog
// voltage with analogRead().  Possible configurations are 1, 4, 8, 16, 32.  More
// readings averaged gives better results, but takes longer.
void analogReadAveraging(unsigned int num);
void analog_init(void);
// Teensy 4 boards to not have capacitive touch sensing hardware.  This function
// is not implemented for Teensy 4.
int touchRead(uint8_t pin);
// Read a group of 32 fuse bits.  The input must be a fuse bits register name.
uint32_t IMXRTfuseRead(volatile uint32_t *fuses);
// Write to fuse bits.  This is a PERMANENT IRREVERSIBLE operation.  Writing can
// only change fuse bits which are 0 to 1.  User programs should only write to
// fuse registers HW_OCOTP_GP1, HW_OCOTP_GP2, HW_OCOTP_GP30, HW_OCOTP_GP31,
// HW_OCOTP_GP32 and HW_OCOTP_GP33.  On Lockable Teensy, writing to the wrong
// fuses can PERMANENTLY BRICK your hardware.  After writing 1 or more fuse bit
// registers, call IMXRTfuseReload() for changes to become visible.
void IMXRTfuseWrite(volatile uint32_t *fuses, uint32_t value);
// Reloads the fuse bits buffer memory from actual fuse hardware.
void IMXRTfuseReload();

// Transmit 8 bits to a shift register connected to 2 digital pins.  bitOrder
// may be MSBFIRST or LSBFIRST.
static inline void shiftOut(uint8_t, uint8_t, uint8_t, uint8_t) __attribute__((always_inline, unused));
extern void _shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value) __attribute__((noinline));
extern void shiftOut_lsbFirst(uint8_t dataPin, uint8_t clockPin, uint8_t value) __attribute__((noinline));
extern void shiftOut_msbFirst(uint8_t dataPin, uint8_t clockPin, uint8_t value) __attribute__((noinline));

static inline void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value)
{
        if (__builtin_constant_p(bitOrder)) {
                if (bitOrder == LSBFIRST) {
                        shiftOut_lsbFirst(dataPin, clockPin, value);
                } else {
                        shiftOut_msbFirst(dataPin, clockPin, value);
                }
        } else {
                _shiftOut(dataPin, clockPin, bitOrder, value);
        }
}

// Receive 8 bits from a shift register connected to 2 digital pins.  bitOrder
// may be MSBFIRST or LSBFIRST.
static inline uint8_t shiftIn(uint8_t, uint8_t, uint8_t) __attribute__((always_inline, unused));
extern uint8_t _shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder) __attribute__((noinline));
extern uint8_t shiftIn_lsbFirst(uint8_t dataPin, uint8_t clockPin) __attribute__((noinline));
extern uint8_t shiftIn_msbFirst(uint8_t dataPin, uint8_t clockPin) __attribute__((noinline));

static inline uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder)
{
        if (__builtin_constant_p(bitOrder)) {
                if (bitOrder == LSBFIRST) {
                        return shiftIn_lsbFirst(dataPin, clockPin);
                } else {
                        return shiftIn_msbFirst(dataPin, clockPin);
                }
        } else {
                return _shiftIn(dataPin, clockPin, bitOrder);
        }
}

void _reboot_Teensyduino_(void) __attribute__((noreturn));
void _restart_Teensyduino_(void) __attribute__((noreturn));

// Define a set of flags to know which things yield should check when called. 
extern uint8_t yield_active_check_flags;

#define YIELD_CHECK_USB_SERIAL      0x01  // check the USB for Serial.available()
#define YIELD_CHECK_HARDWARE_SERIAL 0x02  // check Hardware Serial ports available
#define YIELD_CHECK_EVENT_RESPONDER 0x04  // User has created eventResponders that use yield
#define YIELD_CHECK_USB_SERIALUSB1  0x08  // Check for SerialUSB1
#define YIELD_CHECK_USB_SERIALUSB2  0x10  // Check for SerialUSB2

// Allow other functions to run.  Typically these will be serial event handlers
// and functions call by certain libraries when lengthy operations complete.
void yield(void);

void delay(uint32_t msec);

extern volatile uint32_t F_CPU_ACTUAL;
extern volatile uint32_t F_BUS_ACTUAL;
extern volatile uint32_t scale_cpu_cycles_to_microseconds;
extern volatile uint32_t systick_millis_count;

static inline uint32_t millis(void) __attribute__((always_inline, unused));
// Returns the number of milliseconds since your program started running.
// This 32 bit number will roll back to zero after about 49.7 days.  For a
// simpler way to build delays or timeouts, consider using elapsedMillis.
static inline uint32_t millis(void)
{
	return systick_millis_count;
}

uint32_t micros(void);

static inline void delayMicroseconds(uint32_t) __attribute__((always_inline, unused));
// Wait for a number of microseconds.  During this time, interrupts remain
// active, but the rest of your program becomes effectively stalled.  For shorter
// delay, use delayNanoseconds().
static inline void delayMicroseconds(uint32_t usec)
{
	uint32_t begin = ARM_DWT_CYCCNT;
	uint32_t cycles = F_CPU_ACTUAL / 1000000 * usec;
	// TODO: check if cycles is large, do a wait with yield calls until it's smaller
	while (ARM_DWT_CYCCNT - begin < cycles) ; // wait
}

static inline void delayNanoseconds(uint32_t) __attribute__((always_inline, unused));
// Wait for a number of nanoseconds.  During this time, interrupts remain
// active, but the rest of your program becomes effectively stalled.
static inline void delayNanoseconds(uint32_t nsec)
{
	uint32_t begin = ARM_DWT_CYCCNT;
	uint32_t cycles =   ((F_CPU_ACTUAL>>16) * nsec) / (1000000000UL>>16);
	while (ARM_DWT_CYCCNT - begin < cycles) ; // wait
}


unsigned long rtc_get(void);
void rtc_set(unsigned long t);
void rtc_compensate(int adjust);

void tempmon_init(void);
float tempmonGetTemp(void);
void tempmon_Start();
void tempmon_Stop();
void tempmon_PwrDwn();

#ifdef __cplusplus
}

// DateTimeFields represents calendar date & time with 7 fields, hour (0-23), min
// (0-59), sec (0-59), wday (0-6, 0=Sunday), mday (1-31), mon (0-11), year
// (70-206, 70=1970, 206=2106).  These 7 fields follow C standard "struct tm"
// convention, but are stored with only 8 bits to conserve memory.
typedef struct  {
	uint8_t sec;   // 0-59
	uint8_t min;   // 0-59
	uint8_t hour;  // 0-23
	uint8_t wday;  // 0-6, 0=sunday
	uint8_t mday;  // 1-31
	uint8_t mon;   // 0-11
	uint8_t year;  // 70-206, 70=1970, 206=2106
} DateTimeFields;
// Convert a "unixtime" number into 7-field DateTimeFields
void breakTime(uint32_t time, DateTimeFields &tm);  // break 32 bit time into DateTimeFields
// Convert 7-field DateTimeFields to a "unixtime" number.  The wday field is not used.
uint32_t makeTime(const DateTimeFields &tm); // convert DateTimeFields to 32 bit time

class teensy3_clock_class
{
public:
        static unsigned long get(void) __attribute__((always_inline)) { return rtc_get(); }
        static void set(unsigned long t) __attribute__((always_inline)) { rtc_set(t); }
        static void compensate(int adj) __attribute__((always_inline)) { rtc_compensate(adj); }
};
extern teensy3_clock_class Teensy3Clock;

#endif // __cplusplus




