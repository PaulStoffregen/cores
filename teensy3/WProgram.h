#ifndef WProgram_h
#define WProgram_h

#ifndef _STDLIB_H_
#include <stdlib.h>
#endif
#ifndef _STRING_H_
#include <string.h>
#endif
#ifndef  _MATH_H_
#include <math.h>
#endif

// some libraries and sketches depend on this
// AVR stuff, assuming Arduino.h or WProgram.h
// automatically includes it...
#ifndef __PGMSPACE_H_
#include <avr/pgmspace.h>
#endif
//#include <avr/interrupt.h> //This file is blank?

#ifndef _avr_functions_h_
#include "avr_functions.h"
#endif

#ifndef Wiring_h
#include "wiring.h"
#endif

#ifndef HardwareSerial_h
#include "HardwareSerial.h"
#endif

#define DMAMEM __attribute__ ((section(".dmabuffers"), used))

#ifdef __cplusplus

#include "avr_emulation.h"

#include "usb_serial.h"
#include "usb_seremu.h"
#include "usb_keyboard.h"
#include "usb_mouse.h"
#include "usb_joystick.h"
#include "usb_midi.h"
#include "usb_rawhid.h"
#include "usb_flightsim.h"

//#include "WCharacter.h"
#ifndef String_class_h
#include "WString.h"
#endif
#ifndef elapsedMillis_h
#include "elapsedMillis.h"
#endif
#ifndef __INTERVALTIMER_H__
#include "IntervalTimer.h"
#endif

uint16_t makeWord(uint16_t w);
uint16_t makeWord(byte h, byte l);

#define word(...) makeWord(__VA_ARGS__)

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout = 1000000L);

void tone(uint8_t pin, uint16_t frequency, uint32_t duration = 0);
void noTone(uint8_t pin);

// WMath prototypes
uint32_t random(void);
uint32_t random(uint32_t howbig);
int32_t random(int32_t howsmall, int32_t howbig);
void randomSeed(uint32_t newseed);
void srandom(uint32_t newseed);
long map(long, long, long, long, long);

#endif // __cplusplus

#endif // WProgram_h
