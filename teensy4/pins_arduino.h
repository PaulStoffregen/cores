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

#ifndef pins_macros_for_arduino_compatibility_h
#define pins_macros_for_arduino_compatibility_h

#include <stdint.h>

// A0-A9 are always digital 14-23, for Arduino compatibility
#define PIN_A0  (14)
#define PIN_A1  (15)
#define PIN_A2  (16)
#define PIN_A3  (17)
#define PIN_A4  (18)
#define PIN_A5  (19)
#define PIN_A6  (20)
#define PIN_A7  (21)
#define PIN_A8  (22)
#define PIN_A9  (23)
#define PIN_A10 (24)
#define PIN_A11 (25)
#define PIN_A12 (26)
#define PIN_A13 (27)
static const uint8_t A0 = PIN_A0;
static const uint8_t A1 = PIN_A1;
static const uint8_t A2 = PIN_A2;
static const uint8_t A3 = PIN_A3;
static const uint8_t A4 = PIN_A4;
static const uint8_t A5 = PIN_A5;
static const uint8_t A6 = PIN_A6;
static const uint8_t A7 = PIN_A7;
static const uint8_t A8 = PIN_A8;
static const uint8_t A9 = PIN_A9;
static const uint8_t A10 = PIN_A10;
static const uint8_t A11 = PIN_A11;
static const uint8_t A12 = PIN_A12;
static const uint8_t A13 = PIN_A13;
#ifdef ARDUINO_TEENSY41
#define PIN_A14 (38)
#define PIN_A15 (39)
#define PIN_A16 (40)
#define PIN_A17 (41)
static const uint8_t A14 = PIN_A14;
static const uint8_t A15 = PIN_A15;
static const uint8_t A16 = PIN_A16;
static const uint8_t A17 = PIN_A17;
#endif

#define LED_BUILTIN   (13)

#define PIN_SPI_SS    (10)
#define PIN_SPI_MOSI  (11)
#define PIN_SPI_MISO  (12)
#define PIN_SPI_SCK   (13)
static const uint8_t SS = 10;
static const uint8_t MOSI = 11;
static const uint8_t MISO = 12;
static const uint8_t SCK = 13;

#define PIN_WIRE_SDA  (18)
#define PIN_WIRE_SCL  (19)
static const uint8_t SDA = 18;
static const uint8_t SCL = 19;

#define PIN_SERIAL_RX (0)
#define PIN_SERIAL_TX (1)


#if defined(ARDUINO_TEENSY40)
  #define NUM_DIGITAL_PINS  40
  #define NUM_ANALOG_INPUTS 14
#elif defined(ARDUINO_TEENSY41)
  #define NUM_DIGITAL_PINS  55
  #define NUM_ANALOG_INPUTS 18
#elif defined(ARDUINO_TEENSY_MICROMOD)
  #define NUM_DIGITAL_PINS  46
  #define NUM_ANALOG_INPUTS 14
#endif

#define NOT_AN_INTERRUPT -1


#if defined(__IMXRT1062__) && defined(ARDUINO_TEENSY40)
  #define analogInputToDigitalPin(p) (((p) <= 9) ? (p) + 14 : (( ((p) >= 14 && (p) <= 27)) ? (p) : -1))
  #define digitalPinHasPWM(p) ((p) <= 15 || (p) == 18 || (p) == 19 || ((p) >= 22 && (p) <= 25) || (p) == 28 || (p) == 29 || ((p) >= 33 && (p) <= 39))

#elif defined(__IMXRT1062__) && defined(ARDUINO_TEENSY41)
  #define analogInputToDigitalPin(p) (((p) <= 9) ? (p) + 14 : (( ((p) >= 14 && (p) <= 27)) || ((p) >= 38 && (p) <= 41) ? (p) : -1))
  #define digitalPinHasPWM(p) ((p) <= 15 || (p) == 18 || (p) == 19 || ((p) >= 22 && (p) <= 25) || (p) == 28 || (p) == 29 || (p) == 33 || (p) == 36 || (p) == 37 || ((p) >= 42 && (p) <= 47) || (p) == 51 || (p) == 54)

#elif defined(__IMXRT1062__) && defined(ARDUINO_TEENSY_MICROMOD)
  #define analogInputToDigitalPin(p) (((p) <= 9) ? (p) + 14 : (( ((p) >= 14 && (p) <= 27)) ? (p) : -1))
  #define digitalPinHasPWM(p) ((p) <= 15 || (p) == 18 || (p) == 19 || ((p) >= 22 && (p) <= 25) || (p) == 28 || (p) == 29 || (p) == 33 || (p) == 40 || (p) == 41 || (p) == 45)
#endif
  #define digitalPinToInterrupt(p)  ((p) < NUM_DIGITAL_PINS ? (p) : -1)


#define digitalPinToPCICR(p)    ((volatile uint8_t *)0)
#define digitalPinToPCICRbit(p) (0)
#define digitalPinToPCIFR(p)    ((volatile uint8_t *)0)
#define digitalPinToPCIFRbit(p) (0)
#define digitalPinToPCMSK(p)    ((volatile uint8_t *)0)
#define digitalPinToPCMSKbit(p) (0)


struct digital_pin_bitband_and_config_table_struct { // not really bitband, old name from Teensy3
	volatile uint32_t *reg;
	volatile uint32_t *mux;
	volatile uint32_t *pad;
	uint32_t mask;
};
extern const struct digital_pin_bitband_and_config_table_struct digital_pin_to_info_PGM[];
#define digitalPinToPort(pin)    (pin)
#define digitalPinToBitMask(pin) (digital_pin_to_info_PGM[(pin)].mask)
#define portOutputRegister(pin)  ((digital_pin_to_info_PGM[(pin)].reg + 0))
#define portSetRegister(pin)     ((digital_pin_to_info_PGM[(pin)].reg + 33))
#define portClearRegister(pin)   ((digital_pin_to_info_PGM[(pin)].reg + 34))
#define portToggleRegister(pin)  ((digital_pin_to_info_PGM[(pin)].reg + 35))
#define portInputRegister(pin)   ((digital_pin_to_info_PGM[(pin)].reg + 2))
#define portModeRegister(pin)    ((digital_pin_to_info_PGM[(pin)].reg + 1))
#define portConfigRegister(pin)  ((digital_pin_to_info_PGM[(pin)].mux))
#define portControlRegister(pin) ((digital_pin_to_info_PGM[(pin)].pad))
#define digitalPinToPortReg(pin) (portOutputRegister(pin))
#define digitalPinToBit(pin)     (__builtin_ctz(digitalPinToBitMask(pin)))


#define NOT_ON_TIMER 0
static inline uint8_t digitalPinToTimer(uint8_t) __attribute__((always_inline, unused));
static inline uint8_t digitalPinToTimer(uint8_t pin)
{
	// TODO: does anything meaningful use this?
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
#define SERIAL_PORT_HARDWARE3		Serial4
#define SERIAL_PORT_HARDWARE4		Serial5
#define SERIAL_PORT_HARDWARE5		Serial6
#define SERIAL_PORT_HARDWARE6		Serial7
#define SERIAL_PORT_HARDWARE_OPEN3	Serial4
#define SERIAL_PORT_HARDWARE_OPEN4	Serial5
#define SERIAL_PORT_HARDWARE_OPEN5	Serial6
#define SERIAL_PORT_HARDWARE_OPEN6	Serial7
#if defined(__IMXRT1052__)   
#define SERIAL_PORT_HARDWARE7		Serial8
#define SERIAL_PORT_HARDWARE_OPEN7	Serial8
#endif

#define SerialUSB			Serial

#endif // pins_macros_for_arduino_compatibility_h
