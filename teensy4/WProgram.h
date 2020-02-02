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

#ifndef WProgram_h
#define WProgram_h

#include <stdlib.h>
#include <string.h>
#include <math.h>

// some libraries and sketches depend on this
// AVR stuff, assuming Arduino.h or WProgram.h
// automatically includes it...
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#include "avr_functions.h"
#include "wiring.h"
#include "HardwareSerial.h"

#ifdef __cplusplus

#include "avr_emulation.h"
#include "usb_serial.h"
#include "usb_seremu.h"
#include "usb_keyboard.h"
#include "usb_mouse.h"
#include "usb_joystick.h"
#include "usb_midi.h"
#include "usb_rawhid.h"
//#include "usb_flightsim.h"
//#include "usb_mtp.h"
//#include "usb_audio.h"
#include "usb_touch.h"
//#include "usb_undef.h" // do not allow usb_desc.h stuff to leak to user programs

#include "WCharacter.h"
#include "WString.h"
#include "elapsedMillis.h"
#include "IntervalTimer.h"

uint16_t makeWord(uint16_t w);
uint16_t makeWord(byte h, byte l);

#define word(...) makeWord(__VA_ARGS__)

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout = 1000000L);

void tone(uint8_t pin, uint16_t frequency, uint32_t duration = 0);
void noTone(uint8_t pin);

// WMath prototypes
int32_t random(void);
uint32_t random(uint32_t howbig);
int32_t random(int32_t howsmall, int32_t howbig);
void randomSeed(uint32_t newseed);
void srandom(unsigned int newseed);

#include "pins_arduino.h"

#endif // __cplusplus


// Fast memcpy
#ifdef __cplusplus
extern "C" {
extern void *memcpy (void *dst, const void *src, size_t count);
}
#else
extern void *memcpy (void *dst, const void *src, size_t count);
#endif


#endif // WProgram_h
