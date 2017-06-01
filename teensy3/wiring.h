/*
  wiring.h - Partial implementation of the Wiring API for the ATmega8.
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2005-2006 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  $Id: wiring.h 387 2008-03-08 21:30:00Z mellis $
*/

#ifndef Wiring_h
#define Wiring_h

//#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include "binary.h"
#include "core_id.h"
#include "core_pins.h"

// type_traits interferes with min() and other defines
// include it early, so we can define these later
// for Arduino compatibility
#ifdef __cplusplus
#include <type_traits>
// when the input number is an integer type, do all math as 32 bit signed long
template <class T, class A, class B, class C, class D>
T map(T _x, A _in_min, B _in_max, C _out_min, D _out_max, typename std::enable_if<std::is_integral<T>::value >::type* = 0)
{
	long x = _x, in_min = _in_min, in_max = _in_max, out_min = _out_min, out_max = _out_max;
	// Arduino's traditional algorithm
	//return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	// st42's suggestion: https://github.com/arduino/Arduino/issues/2466#issuecomment-69873889
	if ((in_max - in_min) > (out_max - out_min)) {
		return (x - in_min) * (out_max - out_min+1) / (in_max - in_min+1) + out_min;
	} else {
		return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}
}
// when the input is a float or double, do all math using the input's type
template <class T, class A, class B, class C, class D>
T map(T x, A in_min, B in_max, C out_min, D out_max, typename std::enable_if<std::is_floating_point<T>::value >::type* = 0)
{
	return (x - (T)in_min) * ((T)out_max - (T)out_min) / ((T)in_max - (T)in_min) + (T)out_min;
}
#endif

#ifdef __cplusplus
extern "C"{
#endif

#ifdef PI
#undef PI
#endif
#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif
#ifndef M_SQRT2
#define M_SQRT2 1.4142135623730950488016887
#endif

#define SERIAL  0
#define DISPLAY 1

// undefine stdlib's abs if encountered
#ifdef abs
#undef abs
#endif

#if __cplusplus >= 201103L && defined(__STRICT_ANSI__)
#define typeof(a) decltype(a)
#endif

#define min(a, b) ({ \
  typeof(a) _a = (a); \
  typeof(b) _b = (b); \
  (_a < _b) ? _a : _b; \
})
#define max(a, b) ({ \
  typeof(a) _a = (a); \
  typeof(b) _b = (b); \
  (_a > _b) ? _a : _b; \
})
#define abs(x) ({ \
  typeof(x) _x = (x); \
  (_x > 0) ? _x : -_x; \
})
#define constrain(amt, low, high) ({ \
  typeof(amt) _amt = (amt); \
  typeof(low) _low = (low); \
  typeof(high) _high = (high); \
  (_amt < _low) ? _low : ((_amt > _high) ? _high : _amt); \
})
#define round(x) ({ \
  typeof(x) _x = (x); \
  (_x>=0) ? (long)(_x+0.5) : (long)(_x-0.5); \
})
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ({ \
  typeof(x) _x = (x); \
  _x * _x; \
})

extern double exp10(double x);
extern float exp10f(float x);
extern long double exp10l(long double x);
extern double pow10(double x);
extern float pow10f(float x);
extern long double pow10l(long double x);

#define stricmp(a, b) strcasecmp(a, b)

#define sei() __enable_irq()
#define cli() __disable_irq()
#define interrupts() __enable_irq()
#define noInterrupts() __disable_irq()

#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )
#define clockCyclesToMicroseconds(a) ( (a) / clockCyclesPerMicrosecond() )
#define microsecondsToClockCycles(a) ( (a) * clockCyclesPerMicrosecond() )

#define lowByte(w) ((uint8_t)((w) & 0xFF))
#define highByte(w) ((uint8_t)((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) ((bitvalue) ? bitSet((value), (bit)) : bitClear((value), (bit)))

typedef unsigned int word;

#define bit(b) (1UL << (b))

typedef uint8_t byte;

uint32_t pulseIn(uint8_t pin, uint8_t state, uint32_t timeout);
void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, byte val);

//void tone(uint8_t pin, uint16_t frequency, uint32_t duration);
//void noTone(uint8_t pin);

//void attachInterrupt(uint8_t, void (*)(void), uint8_t mode);
//void detachInterrupt(uint8_t);

void setup(void);
void loop(void);

#ifdef __cplusplus
} // extern "C"
#endif

// fix C++ boolean issue
// https://github.com/arduino/Arduino/pull/2151
#ifdef __cplusplus
typedef bool boolean;
#else
typedef uint8_t boolean;
#define false 0
#define true (!false)
#endif

#endif
