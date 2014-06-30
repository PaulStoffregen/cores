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

#include "WProgram.h"

#if F_CPU >= 20000000

#ifdef USB_SERIAL
usb_serial_class Serial;
#endif

#ifdef USB_HID
usb_keyboard_class Keyboard;
usb_mouse_class Mouse;
usb_joystick_class Joystick;
uint8_t usb_joystick_class::manual_mode = 0;
usb_seremu_class Serial;
#endif

#ifdef USB_SERIAL_HID
usb_serial_class Serial;
usb_keyboard_class Keyboard;
usb_mouse_class Mouse;
usb_joystick_class Joystick;
uint8_t usb_joystick_class::manual_mode = 0;
#endif

#ifdef USB_MIDI
usb_midi_class usbMIDI;
usb_seremu_class Serial;
#endif

#ifdef USB_RAWHID
usb_rawhid_class RawHID;
usb_seremu_class Serial;
#endif

#ifdef USB_FLIGHTSIM
FlightSimClass FlightSim;
usb_seremu_class Serial;
#endif


#else // F_CPU < 20 MHz

#if defined(USB_SERIAL) || defined(USB_SERIAL_HID)
usb_serial_class Serial;
#else
usb_seremu_class Serial;
#endif

#endif // F_CPU

void serialEvent() __attribute__((weak));
void serialEvent() {}
