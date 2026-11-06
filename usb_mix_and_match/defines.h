#pragma once

#ifdef USB_MAM_SERIAL_1
#define CORE_TEENSY_SERIAL
#endif

#if defined USB_MAM_KEYBOARD_1 || defined USB_MAM_MOUSE_1 || defined USB_MAM_JOYSTICK_1
#define CORE_TEENSY_HID
#endif

#ifdef USB_MAM_KEYBOARD_1
#define CORE_TEENSY_KEYBOARD
#endif

#ifdef USB_MAM_JOYSTICK_1
#define CORE_TEENSY_JOYSTICK
#endif

#ifdef USB_MAM_MULTIMEDIA_1
#define CORE_TEENSY_MULTIMEDIA
#endif

#ifdef USB_MAM_MOUSE_1
#define CORE_TEENSY_MOUSE
#endif

#ifdef USB_MAM_DEBUG_1
#define CORE_TEENSY_DEBUG
#endif

#ifdef CORE_TEENSY_SERIAL
#ifdef CORE_TEENSY_DEBUG
#error CORE_TEENSY_SERIAL and CORE_TEENSY_DEBUG must not be defined at the same time
#endif
#endif

#ifdef CORE_TEENSY_MULTIMEDIA
#ifndef CORE_TEENSY_KEYBOARD
#error CORE_TEENSY_MULTIMEDIA requires CORE_TEENSY_KEYBOARD to be defined too
#endif
#endif