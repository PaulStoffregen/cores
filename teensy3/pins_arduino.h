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

#ifndef pins_macros_for_arduino_compatibility_h
#define pins_macros_for_arduino_compatibility_h

#include <stdint.h>

// A0-A9 are always digital 14-23, for Arduino compatibility
const static uint8_t A0 = 14;
const static uint8_t A1 = 15;
const static uint8_t A2 = 16;
const static uint8_t A3 = 17;
const static uint8_t A4 = 18;
const static uint8_t A5 = 19;
const static uint8_t A6 = 20;
const static uint8_t A7 = 21;
const static uint8_t A8 = 22;
const static uint8_t A9 = 23;
#if defined(__MK20DX128__)
const static uint8_t A10 = 34;
const static uint8_t A11 = 35;
const static uint8_t A12 = 36;
const static uint8_t A13 = 37;
#elif defined(__MK20DX256__)
const static uint8_t A10 = 34;
const static uint8_t A11 = 35;
const static uint8_t A12 = 36;
const static uint8_t A13 = 37;
const static uint8_t A14 = 40;
const static uint8_t A15 = 26;
const static uint8_t A16 = 27;
const static uint8_t A17 = 28;
const static uint8_t A18 = 29;
const static uint8_t A19 = 30;
const static uint8_t A20 = 31;
#elif defined(__MKL26Z64__)
const static uint8_t A10 = 24;
const static uint8_t A11 = 25;
const static uint8_t A12 = 26;
#elif defined(__MK64FX512__) || defined(__MK66FX1M0__)
const static uint8_t A10 = 40;
const static uint8_t A11 = 41;
const static uint8_t A12 = 31;
const static uint8_t A13 = 32;
const static uint8_t A14 = 33;
const static uint8_t A15 = 34;
const static uint8_t A16 = 35;
const static uint8_t A17 = 36;
const static uint8_t A18 = 37;
const static uint8_t A19 = 38;
const static uint8_t A20 = 39;
const static uint8_t A21 = 42;
const static uint8_t A22 = 43;
#endif

const static uint8_t SS = 10;
const static uint8_t MOSI = 11;
const static uint8_t MISO = 12;
const static uint8_t SCK = 13;
const static uint8_t LED_BUILTIN = 13;
const static uint8_t SDA = 18;
const static uint8_t SCL = 19;


#define NUM_DIGITAL_PINS  CORE_NUM_DIGITAL
#define NUM_ANALOG_INPUTS CORE_NUM_ANALOG


#define NOT_AN_INTERRUPT -1


#if defined(__MK20DX128__)
  #define analogInputToDigitalPin(p) (((p) <= 9) ? (p) + 14 : (((p) <= 13) ? (p) + 24 : -1))
  #define digitalPinHasPWM(p) (((p) >= 3 && (p) <= 6) || (p) == 9 || (p) == 10 || ((p) >= 20 && (p) <= 23))
  #define digitalPinToInterrupt(p)  ((p) < NUM_DIGITAL_PINS ? (p) : -1)
#elif defined(__MK20DX256__)
  #define analogInputToDigitalPin(p) (((p) <= 9) ? (p) + 14 : (((p) <= 13) ? (p) + 24 : (((p) == 14) ? 40 : (((p) <= 20) ? (p) + 11 : -1))))
  #define digitalPinHasPWM(p) (((p) >= 3 && (p) <= 6) || (p) == 9 || (p) == 10 || ((p) >= 20 && (p) <= 23) || (p) == 25 || (p) == 32)
  #define digitalPinToInterrupt(p)  ((p) < NUM_DIGITAL_PINS ? (p) : -1)
#elif defined(__MKL26Z64__)
  #define analogInputToDigitalPin(p) (((p) <= 9) ? (p) + 14 : (((p) <= 12) ? (p) + 14 : -1))
  #define digitalPinHasPWM(p) ((p) == 3 || (p) == 4 || (p) == 6 || (p) == 9 || (p) == 10 || (p) == 16 || (p) == 17 || (p) == 20 || (p) == 22 || (p) == 23)
  #define digitalPinToInterrupt(p)  ((((p) >= 2 && (p) <= 15) || ((p) >= 20 && (p) <= 23)) ? (p) : -1)
#elif defined(__MK64FX512__) || defined(__MK66FX1M0__)
  #define analogInputToDigitalPin(p) (((p) <= 9) ? (p) + 14 : (((p) >= 12 && (p) <= 20) ? (p) + 19 : -1))
  #define digitalPinHasPWM(p) (((p) >= 2 && (p) <= 10) || (p) == 14 || ((p) >= 20 && (p) <= 23) || (p) == 29 || (p) == 30 || ((p) >= 35 && (p) <= 38))
  #define digitalPinToInterrupt(p)  ((p) < NUM_DIGITAL_PINS ? (p) : -1)
#endif

#define digitalPinToPCICR(p)    ((volatile uint8_t *)0)
#define digitalPinToPCICRbit(p) (0)
#define digitalPinToPCIFR(p)    ((volatile uint8_t *)0)
#define digitalPinToPCIFRbit(p) (0)
#define digitalPinToPCMSK(p)    ((volatile uint8_t *)0)
#define digitalPinToPCMSKbit(p) (0)


#if defined(KINETISK)
struct digital_pin_bitband_and_config_table_struct {
        volatile uint32_t *reg;
        volatile uint32_t *config;
};
extern const struct digital_pin_bitband_and_config_table_struct digital_pin_to_info_PGM[];
// compatibility macros
#define digitalPinToPort(pin) (pin)
#define digitalPinToBitMask(pin) (1)
#define portOutputRegister(pin) ((volatile uint8_t *)(digital_pin_to_info_PGM[(pin)].reg + 0))
#define portSetRegister(pin)    ((volatile uint8_t *)(digital_pin_to_info_PGM[(pin)].reg + 32))
#define portClearRegister(pin)  ((volatile uint8_t *)(digital_pin_to_info_PGM[(pin)].reg + 64))
#define portToggleRegister(pin) ((volatile uint8_t *)(digital_pin_to_info_PGM[(pin)].reg + 96))
#define portInputRegister(pin)  ((volatile uint8_t *)(digital_pin_to_info_PGM[(pin)].reg + 128))
#define portModeRegister(pin)   ((volatile uint8_t *)(digital_pin_to_info_PGM[(pin)].reg + 160))
#define portConfigRegister(pin) ((volatile uint32_t *)(digital_pin_to_info_PGM[(pin)].config))
#define digitalPinToPortReg(pin) (portOutputRegister(pin))
#define digitalPinToBit(pin) (1)

#elif defined(KINETISL)
struct digital_pin_bitband_and_config_table_struct {
        volatile uint8_t *reg;
        volatile uint32_t *config;
	uint8_t mask;
};
extern const struct digital_pin_bitband_and_config_table_struct digital_pin_to_info_PGM[];
// compatibility macros
#define digitalPinToPort(pin) (pin)
#define digitalPinToBitMask(pin) (digital_pin_to_info_PGM[(pin)].mask)
#define portOutputRegister(pin) ((digital_pin_to_info_PGM[(pin)].reg + 0))
#define portSetRegister(pin)    ((digital_pin_to_info_PGM[(pin)].reg + 4))
#define portClearRegister(pin)  ((digital_pin_to_info_PGM[(pin)].reg + 8))
#define portToggleRegister(pin) ((digital_pin_to_info_PGM[(pin)].reg + 12))
#define portInputRegister(pin)  ((digital_pin_to_info_PGM[(pin)].reg + 16))
#define portModeRegister(pin)   ((digital_pin_to_info_PGM[(pin)].reg + 20))
#define portConfigRegister(pin) ((digital_pin_to_info_PGM[(pin)].config))
#define digitalPinToPortReg(pin) (portOutputRegister(pin))
//#define digitalPinToBit(pin) (1)

#endif



#define NOT_ON_TIMER 0
static inline uint8_t digitalPinToTimer(uint8_t) __attribute__((always_inline, unused));
static inline uint8_t digitalPinToTimer(uint8_t pin)
{
	if (pin >= 3 && pin <= 6) return pin - 2;
	if (pin >= 9 && pin <= 10) return pin - 4;
	if (pin >= 20 && pin <= 23) return pin - 13;
	return NOT_ON_TIMER;
}

// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use. For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN Hardware serial ports which are open for use. Their RX & TX
// pins are NOT connected to anything by default.
//
#if F_CPU >= 20000000 && !defined(USB_DISABLED)
#define SERIAL_PORT_MONITOR		Serial
#else
#define SERIAL_PORT_MONITOR		Serial1
#endif
#define SERIAL_PORT_USBVIRTUAL		Serial
#define SERIAL_PORT_HARDWARE		Serial1
#define SERIAL_PORT_HARDWARE1		Serial2
#define SERIAL_PORT_HARDWARE2		Serial3
#define SERIAL_PORT_HARDWARE_OPEN	Serial1
#define SERIAL_PORT_HARDWARE_OPEN1	Serial2
#define SERIAL_PORT_HARDWARE_OPEN2	Serial3

#define SerialUSB			Serial

#endif
