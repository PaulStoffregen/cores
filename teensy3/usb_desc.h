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

#ifndef _usb_desc_h_
#define _usb_desc_h_

// This header is NOT meant to be included when compiling
// user sketches in Arduino.  The low-level functions
// provided by usb_dev.c are meant to be called only by
// code which provides higher-level interfaces to the user.

#include <stdint.h>
#include <stddef.h>

#define ENDPOINT_UNUSED			0x00
#define ENDPOINT_TRANSIMIT_ONLY		0x15
#define ENDPOINT_RECEIVE_ONLY		0x19
#define ENDPOINT_TRANSMIT_AND_RECEIVE	0x1D

/*
 * Note: This works when using the Make system available at
 *       https://github.com/xxxajk/Arduino_Makefile_master
 *       because it can include the sketch directory for these settings.
 *       I hope the Arduino IDE team takes a clue from this.
 *
 *       Since this option is NOT available in the IDE, no harm can
 *       come to anyone who is only using the IDE. They simply won't be
 *       able to easily define a custom interface, until they use better
 *       tools, or the Arduino IDE team gets a clue.
 *
 * What follows is an example and recipe for using sketch_settings.h
 * which provides a modified version USB Serial.
 * All parameters are changable but for simplicity, only the
 * MANUFACTURER_NAME has been altered.
 *
[settings_demo.ino]
// Pull in the usb_serial code headers from teensyduino
#define USB_SERIAL
#include <Arduino.h>

void setup() {
	while(!Serial);
	Serial.println("It works!");
}

void loop() {}

[sketch_settings.h]
 #ifdef _usb_desc_h_
 #ifndef _usb_desc_h_seen_us
 #define _usb_desc_h_seen_us
 #define VENDOR_ID		0x16C0
 #define PRODUCT_ID		0x0483
 #define DEVICE_CLASS		2	// 2 = Communication Class
 #define MANUFACTURER_NAME	{'T','3','3','n','5','y','d','u','1','n','0'}
 #define MANUFACTURER_NAME_LEN	11
 #define PRODUCT_NAME		{'U','S','B',' ','S','e','r','i','a','l'}
 #define PRODUCT_NAME_LEN	10
 #define NUM_USB_BUFFERS	12
 #define NUM_INTERFACE		2
 #define CDC_STATUS_INTERFACE	0
 #define CDC_DATA_INTERFACE	1
 #define CDC_ACM_ENDPOINT	2
 #define CDC_RX_ENDPOINT       3
 #define CDC_TX_ENDPOINT       4
 #define CDC_ACM_SIZE          16
 #define CDC_RX_SIZE           64
 #define CDC_TX_SIZE           64
 #define ENDPOINT2_CONFIG	ENDPOINT_TRANSIMIT_ONLY
 #define ENDPOINT3_CONFIG	ENDPOINT_RECEIVE_ONLY
 #define ENDPOINT4_CONFIG	ENDPOINT_TRANSIMIT_ONLY
 #endif // _usb_desc_h_seen_us
 #endif // _usb_desc_h_
 *
 *
 */
#if defined(USB_CUSTOM)
#include <sketch_settings.h>
#else


/*
To modify a USB Type to have different interfaces, start in this
file.  Delete the XYZ_INTERFACE lines for any interfaces you
wish to remove, and copy them from another USB Type for any you
want to add.

Give each interface a unique number, and edit NUM_INTERFACE to
reflect the number of interfaces.

Within each interface, make sure it uses a unique set of endpoints.
Edit NUM_ENDPOINTS to be at least the largest endpoint number used.
Then edit the ENDPOINT*_CONFIG lines so each endpoint is configured
the proper way (transmit, receive, or both).

The CONFIG_DESC_SIZE and any XYZ_DESC_OFFSET numbers must be
edited to the correct sizes.  See usb_desc.c for the giant array
of bytes.  Someday these may be done automatically..... (but how?)

If you are using existing interfaces, the code in each file should
automatically adapt to the changes you specify.  If you need to
create a new type of interface, you'll need to write the code which
sends and receives packets, and presents an API to the user.

Finally, edit usb_inst.cpp, which creats instances of the C++
objects for each combination.

Some operating systems, especially Windows, may cache USB device
info.  Changes to the device name may not update on the same
computer unless the vendor or product ID numbers change, or the
"bcdDevice" revision code is increased.

If these instructions are missing steps or could be improved, please
let me know?  http://forum.pjrc.com/forums/4-Suggestions-amp-Bug-Reports
*/

#if defined(USB_SERIAL)
  #define PRODUCT_ID                            0x0483
  #define DEVICE_CLASS                          2	// 2 = Communication Class
  #define PRODUCT_NAME                          {'U','S','B',' ','S','e','r','i','a','l'}
  #define NUM_USB_BUFFERS                       12
  #define NUM_INTERFACE                         2
  #define CDC_STATUS_INTERFACE                  0
  #define CDC_DATA_INTERFACE                    1

#elif defined(USB_HID)
  #define PRODUCT_ID                            0x0482
  #define PRODUCT_NAME                          {'K','e','y','b','o','a','r','d','/','M','o','u','s','e','/','J','o','y','s','t','i','c','k'}
  #define NUM_USB_BUFFERS                       24
  #define NUM_INTERFACE                         4
  #define KEYBOARD_INTERFACE                    0	// Keyboard
  #define MOUSE_INTERFACE                       1	// Mouse
  #define SEREMU_INTERFACE                      2	// Serial emulation
  #define JOYSTICK_INTERFACE                    3	// Joystick

#elif defined(USB_SERIAL_HID)
  #define PRODUCT_ID                            0x0487
  #define DEVICE_CLASS                          0xEF
  #define DEVICE_SUBCLASS                       0x02
  #define DEVICE_PROTOCOL                       0x01
  #define PRODUCT_NAME                          {'S','e','r','i','a','l','/','K','e','y','b','o','a','r','d','/','M','o','u','s','e','/','J','o','y','s','t','i','c','k'}
  #define NUM_USB_BUFFERS                       30
  #define NUM_INTERFACE                         5
  #define CDC_IAD_DESCRIPTOR                    1
  #define CDC_STATUS_INTERFACE                  0
  #define CDC_DATA_INTERFACE                    1	// Serial
  #define KEYBOARD_INTERFACE                    2	// Keyboard
  #define MOUSE_INTERFACE                       3	// Mouse
  #define JOYSTICK_INTERFACE                    4	// Joystick

#elif defined(USB_MIDI)
  #define PRODUCT_ID                            0x0485
  #define PRODUCT_NAME                          {'T','e','e','n','s','y',' ','M','I','D','I'}
  #define NUM_USB_BUFFERS                       16
  #define NUM_INTERFACE                         2
  #define MIDI_INTERFACE                        0	// MIDI
  #define SEREMU_INTERFACE                      1	// Serial emulation

#elif defined(USB_RAWHID)
  #define PRODUCT_ID                            0x0486
  #define RAWHID_USAGE_PAGE                     0xFFAB  // recommended: 0xFF00 to 0xFFFF
  #define RAWHID_USAGE                          0x0200  // recommended: 0x0100 to 0xFFFF
  #define PRODUCT_NAME                          {'T','e','e','n','s','y','d','u','i','n','o',' ','R','a','w','H','I','D'}
  #define NUM_USB_BUFFERS                       12
  #define NUM_INTERFACE                         2
  #define RAWHID_INTERFACE                      0	// RawHID
  #define SEREMU_INTERFACE                      1	// Serial emulation

#elif defined(USB_FLIGHTSIM)
  #define PRODUCT_ID                            0x0488
  #define PRODUCT_NAME                          {'T','e','e','n','s','y',' ','F','l','i','g','h','t',' ','S','i','m',' ','C','o','n','t','r','o','l','s'}
  #define NUM_USB_BUFFERS                       20
  #define NUM_INTERFACE                         2
  #define FLIGHTSIM_INTERFACE                   0	// Flight Sim Control
  #define SEREMU_INTERFACE                      1	// Serial emulation

#endif

#endif /* USB_CUSTOM */

// ############################################################################
// ############################################################################
// ############################################################################
// Defaults for everything
// ############################################################################
// ############################################################################
// ############################################################################
#ifndef VENDOR_ID
        #define VENDOR_ID                       0x16C0
#endif

#ifndef MANUFACTURER_NAME
        #define MANUFACTURER_NAME               {'T','e','e','n','s','y','d','u','i','n','o'}
#endif


// ############################################################################
#ifndef CDC_ACM_SIZE
        #define CDC_ACM_SIZE                    16
#endif
#ifndef CDC_RX_SIZE
        #define CDC_RX_SIZE                     64
#endif
#ifndef CDC_TX_SIZE
        #define CDC_TX_SIZE                     64
#endif

// ############################################################################
#ifndef SEREMU_TX_SIZE
        #define SEREMU_TX_SIZE                  64
#endif
#ifndef SEREMU_RX_SIZE
        #define SEREMU_RX_SIZE                  32
#endif
#ifndef SEREMU_TX_INTERVAL
        #define SEREMU_TX_INTERVAL              1
#endif
#ifndef SEREMU_RX_INTERVAL
        #define SEREMU_RX_INTERVAL              2
#endif

// ############################################################################
#ifndef KEYBOARD_SIZE
        #define KEYBOARD_SIZE                   8
#endif
#ifndef KEYBOARD_INTERVAL
        #define KEYBOARD_INTERVAL               1
#endif

// ############################################################################
#ifndef MOUSE_SIZE
        #define MOUSE_SIZE                      8
#endif
#ifndef MOUSE_INTERVAL
        #define MOUSE_INTERVAL                  1
#endif

// ############################################################################
#ifndef JOYSTICK_SIZE
        #define JOYSTICK_SIZE                   16
#endif
#ifndef JOYSTICK_INTERVAL
        #define JOYSTICK_INTERVAL               2
#endif

// ############################################################################
#ifndef MIDI_TX_SIZE
        #define MIDI_TX_SIZE                    64
#endif
#ifndef MIDI_RX_SIZE
        #define MIDI_RX_SIZE                    64
#endif

// ############################################################################
#ifndef RAWHID_TX_SIZE
        #define RAWHID_TX_SIZE                  64
#endif
#ifndef RAWHID_TX_INTERVAL
        #define RAWHID_TX_INTERVAL              1
#endif
#ifndef RAWHID_RX_SIZE
        #define RAWHID_RX_SIZE                  64
#endif
#ifndef RAWHID_RX_INTERVAL
        #define RAWHID_RX_INTERVAL              1
#endif

// ############################################################################
#ifndef FLIGHTSIM_TX_SIZE
        #define FLIGHTSIM_TX_SIZE               64
#endif
#ifndef FLIGHTSIM_TX_INTERVAL
        #define FLIGHTSIM_TX_INTERVAL           1
#endif
#ifndef FLIGHTSIM_RX_SIZE
        #define FLIGHTSIM_RX_SIZE               64
#endif
#ifndef FLIGHTSIM_RX_INTERVAL
        #define FLIGHTSIM_RX_INTERVAL           1
#endif



// ############################################################################
// ############################################################################
// ############################################################################
// This massive amount of macros does the following for any possible combination:
// 1: Calculates the entire size of the device descriptor
// 2: Calculates Total endpoints
// 3: Generates the endpoint size table macro
// 4: Generates the endpoint configuration table macro
// 5: Assigns an unique endpoint for each pipe
// ############################################################################
// ############################################################################
// ############################################################################
#ifdef CDC_IAD_DESCRIPTOR
        #define CDC_IAD_DESCRIPTOR_LEN          8
#else
        #define CDC_IAD_DESCRIPTOR_LEN          0
#endif

// ############################################################################
// ############################################################################
// ############################################################################
#ifdef CDC_DATA_INTERFACE
        #define CDC_DATA_INTERFACE_LEN          (9+5+5+4+5+7+9+7+7)
        #define CDC_DATA_INTERFACE_EPS          (1+1+2)
        #define CDC_DATA_INTERFACE_EPCF         ENDPOINT_UNUSED, ENDPOINT_TRANSIMIT_ONLY, ENDPOINT_RECEIVE_ONLY, ENDPOINT_TRANSIMIT_ONLY
        #define CDC_DATA_INTERFACE_EPSZ         64, CDC_ACM_SIZE, CDC_RX_SIZE, CDC_TX_SIZE
        #define CDC_ACM_ENDPOINT                2
        #define CDC_RX_ENDPOINT                 3
        #define CDC_TX_ENDPOINT                 4
#else
        #define CDC_DATA_INTERFACE_LEN          0
        #define CDC_DATA_INTERFACE_EPS          0
        #define CDC_DATA_INTERFACE_IF           0
        #define CDC_TX_ENDPOINT                 0
#endif

// ############################################################################
// ############################################################################
// ############################################################################
#ifdef MIDI_INTERFACE
        #define MIDI_INTERFACE_LEN              (9+7+6+6+9+9+9+5+9+5)
        #define MIDI_INTERFACE_EPS              2
        #ifdef CDC_DATA_INTERFACE_EPCF
                #define MIDI_INTERFACE_EPCF     CDC_DATA_INTERFACE_EPCF, ENDPOINT_TRANSIMIT_ONLY, ENDPOINT_RECEIVE_ONLY
                #define MIDI_INTERFACE_EPSZ     CDC_DATA_INTERFACE_EPSZ, MIDI_TX_SIZE, MIDI_RX_SIZE
                #define MIDI_TX_ENDPOINT (CDC_TX_ENDPOINT+1)
                #define MIDI_RX_ENDPOINT (CDC_TX_ENDPOINT+2)
        #else
                #define MIDI_INTERFACE_EPCF     ENDPOINT_TRANSIMIT_ONLY, ENDPOINT_RECEIVE_ONLY
                #define MIDI_INTERFACE_EPSZ     MIDI_TX_SIZE, MIDI_RX_SIZE
                #define MIDI_TX_ENDPOINT 1
                #define MIDI_RX_ENDPOINT 2
        #endif
#else
        #define MIDI_INTERFACE_LEN 0
        #define MIDI_INTERFACE_EPS 0
        #ifdef CDC_DATA_INTERFACE_EPCF
                #define MIDI_INTERFACE_EPCF CDC_DATA_INTERFACE_EPCF
                #define MIDI_INTERFACE_EPSZ CDC_DATA_INTERFACE_EPSZ
        #endif
        #define MIDI_RX_ENDPOINT CDC_TX_ENDPOINT
#endif

// ############################################################################
// ############################################################################
// ############################################################################
#ifdef KEYBOARD_INTERFACE
        #define KEYBOARD_INTERFACE_LEN  (9+9+7)
        #define KEYBOARD_INTERFACE_EPS 1
        #ifdef MIDI_INTERFACE_EPCF
                #define KEYBOARD_INTERFACE_EPCF MIDI_INTERFACE_EPCF, ENDPOINT_TRANSIMIT_ONLY
                #define KEYBOARD_INTERFACE_EPSZ MIDI_INTERFACE_EPSZ, KEYBOARD_SIZE
                #define KEYBOARD_ENDPOINT     (MIDI_RX_ENDPOINT + 1)
        #else
                #define KEYBOARD_INTERFACE_EPCF ENDPOINT_TRANSIMIT_ONLY
                #define KEYBOARD_INTERFACE_EPSZ KEYBOARD_SIZE
                #define KEYBOARD_ENDPOINT     1
        #endif
#else
        #define KEYBOARD_INTERFACE_LEN 0
        #define KEYBOARD_INTERFACE_EPS 0
        #ifdef MIDI_INTERFACE_EPCF
                #define KEYBOARD_INTERFACE_EPCF MIDI_INTERFACE_EPCF
                #define KEYBOARD_INTERFACE_EPSZ MIDI_INTERFACE_EPSZ
        #endif
        #define KEYBOARD_ENDPOINT     MIDI_RX_ENDPOINT
#endif

// ############################################################################
// ############################################################################
// ############################################################################
#ifdef MOUSE_INTERFACE
        #define MOUSE_INTERFACE_LEN (9+9+7)
        #define MOUSE_INTERFACE_EPS 1
        #ifdef KEYBOARD_INTERFACE_EPCF
                #define MOUSE_INTERFACE_EPCF KEYBOARD_INTERFACE_EPCF, ENDPOINT_TRANSIMIT_ONLY
                #define MOUSE_INTERFACE_EPSZ KEYBOARD_INTERFACE_EPSZ, MOUSE_SIZE
                #define MOUSE_ENDPOINT        (KEYBOARD_ENDPOINT + 1)
        #else
                #define MOUSE_INTERFACE_EPCF ENDPOINT_TRANSIMIT_ONLY
                #define MOUSE_INTERFACE_EPSZ MOUSE_SIZE
                #define MOUSE_ENDPOINT        1
        #endif
#else
        #define MOUSE_INTERFACE_LEN 0
        #define MOUSE_INTERFACE_EPS 0
        #ifdef KEYBOARD_INTERFACE_EPCF
                #define MOUSE_INTERFACE_EPCF KEYBOARD_INTERFACE_EPCF
                #define MOUSE_INTERFACE_EPSZ KEYBOARD_INTERFACE_EPSZ
        #endif
        #define MOUSE_ENDPOINT KEYBOARD_ENDPOINT
#endif


// ############################################################################
// ############################################################################
// ############################################################################
#ifdef RAWHID_INTERFACE
        #define RAWHID_INTERFACE_LEN (9+9+7+7)
        #define RAWHID_INTERFACE_EPS 2
        #ifdef MOUSE_INTERFACE_EPCF
                #define RAWHID_INTERFACE_EPCF MOUSE_INTERFACE_EPCF, ENDPOINT_TRANSIMIT_ONLY, ENDPOINT_RECEIVE_ONLY
                #define RAWHID_INTERFACE_EPSZ MOUSE_INTERFACE_EPSZ, RAWHID_TX_SIZE,RAWHID_RX_SIZE
                #define RAWHID_TX_ENDPOINT    (MOUSE_ENDPOINT + 1)
                #define RAWHID_RX_ENDPOINT    (MOUSE_ENDPOINT + 2)
        #else
                #define RAWHID_INTERFACE_EPCF ENDPOINT_TRANSIMIT_ONLY, ENDPOINT_RECEIVE_ONLY
                #define RAWHID_INTERFACE_EPSZ RAWHID_TX_SIZE, RAWHID_RX_SIZE
                #define RAWHID_TX_ENDPOINT    1
                #define RAWHID_RX_ENDPOINT    2
        #endif
#else
        #define RAWHID_INTERFACE_LEN 0
        #define RAWHID_INTERFACE_EPS 0
        #ifdef MOUSE_INTERFACE_EPCF
                #define RAWHID_INTERFACE_EPCF MOUSE_INTERFACE_EPCF
                #define RAWHID_INTERFACE_EPSZ MOUSE_INTERFACE_EPSZ
        #endif
                #define RAWHID_RX_ENDPOINT    MOUSE_ENDPOINT

#endif

// ############################################################################
// ############################################################################
// ############################################################################
#ifdef FLIGHTSIM_INTERFACE
        #define FLIGHTSIM_INTERFACE_LEN (9+9+7+7)
        #define FLIGHTSIM_INTERFACE_EPS 2
        #ifdef RAWHID_INTERFACE_EPCF
                #define FLIGHTSIM_INTERFACE_EPCF RAWHID_INTERFACE_EPCF, ENDPOINT_TRANSIMIT_ONLY, ENDPOINT_RECEIVE_ONLY
                #define FLIGHTSIM_INTERFACE_EPSZ RAWHID_INTERFACE_EPSZ, FLIGHTSIM_TX_SIZE, FLIGHTSIM_RX_SIZE
                #define FLIGHTSIM_TX_ENDPOINT	(RAWHID_RX_ENDPOINT + 1)
                #define FLIGHTSIM_RX_ENDPOINT	(RAWHID_RX_ENDPOINT + 2)
        #else
                #define FLIGHTSIM_INTERFACE_EPCF ENDPOINT_TRANSIMIT_ONLY, ENDPOINT_RECEIVE_ONLY
                #define FLIGHTSIM_INTERFACE_EPSZ FLIGHTSIM_TX_SIZE, FLIGHTSIM_RX_SIZE
                #define FLIGHTSIM_TX_ENDPOINT	1
                #define FLIGHTSIM_RX_ENDPOINT	2
        #endif
#else
        #define FLIGHTSIM_INTERFACE_LEN 0
        #define FLIGHTSIM_INTERFACE_EPS 0
        #ifdef RAWHID_INTERFACE_EPCF
                #define FLIGHTSIM_INTERFACE_EPCF RAWHID_INTERFACE_EPCF
                #define FLIGHTSIM_INTERFACE_EPSZ RAWHID_INTERFACE_EPSZ
        #endif
        #define FLIGHTSIM_RX_ENDPOINT	RAWHID_RX_ENDPOINT

#endif


// ############################################################################
// ############################################################################
// ############################################################################
#ifdef SEREMU_INTERFACE
        #define SEREMU_INTERFACE_LEN (9+9+7+7)
        #define SEREMU_INTERFACE_EPS 2
        #ifdef FLIGHTSIM_INTERFACE_EPCF
                #define SEREMU_INTERFACE_EPCF FLIGHTSIM_INTERFACE_EPCF, ENDPOINT_TRANSIMIT_ONLY, ENDPOINT_RECEIVE_ONLY
                #define SEREMU_INTERFACE_EPSZ FLIGHTSIM_INTERFACE_EPSZ, SEREMU_TX_SIZE, SEREMU_RX_SIZE
                #define SEREMU_TX_ENDPOINT    (FLIGHTSIM_RX_ENDPOINT + 1)
                #define SEREMU_RX_ENDPOINT    (FLIGHTSIM_RX_ENDPOINT + 2)
        #else
                #define SEREMU_INTERFACE_EPCF ENDPOINT_TRANSIMIT_ONLY, ENDPOINT_RECEIVE_ONLY
                #define SEREMU_INTERFACE_EPSZ SEREMU_TX_SIZE, SEREMU_RX_SIZE
                #define SEREMU_TX_ENDPOINT    1
                #define SEREMU_RX_ENDPOINT    2
        #endif
#else
        #define SEREMU_INTERFACE_LEN 0
        #define SEREMU_INTERFACE_EPS 0
        #ifdef FLIGHTSIM_INTERFACE_EPCF
                #define SEREMU_INTERFACE_EPCF FLIGHTSIM_INTERFACE_EPCF
                #define SEREMU_INTERFACE_EPSZ FLIGHTSIM_INTERFACE_EPSZ
        #endif
        #define SEREMU_RX_ENDPOINT    FLIGHTSIM_RX_ENDPOINT

#endif

// ############################################################################
// ############################################################################
// ############################################################################
#ifdef JOYSTICK_INTERFACE
        #define JOYSTICK_INTERFACE_LEN (9+9+7)
        #define JOYSTICK_INTERFACE_EPS 1
        #ifdef SEREMU_INTERFACE_ECF
                #define JOYSTICK_INTERFACE_EPCF SEREMU_INTERFACE_EPCF, ENDPOINT_TRANSIMIT_ONLY
                #define JOYSTICK_INTERFACE_EPSZ SEREMU_INTERFACE_EPSZ, JOYSTICK_SIZE
                #define JOYSTICK_ENDPOINT     (SEREMU_RX_ENDPOINT + 1)
        #else
                #define JOYSTICK_INTERFACE_EPCF ENDPOINT_TRANSIMIT_ONLY
                #define JOYSTICK_INTERFACE_EPSZ JOYSTICK_SIZE
                #define JOYSTICK_ENDPOINT     1
        #endif
#else
        #define JOYSTICK_INTERFACE_LEN 0
        #define JOYSTICK_INTERFACE_EPS 0
        #ifdef SEREMU_INTERFACE_EPCF
                #define JOYSTICK_INTERFACE_EPCF SEREMU_INTERFACE_EPCF
                #define JOYSTICK_INTERFACE_EPSZ SEREMU_INTERFACE_EPSZ
        #endif
        #define JOYSTICK_ENDPOINT     SEREMU_RX_ENDPOINT

#endif



// ############################################################################
// ############################################################################
// ############################################################################
#ifdef USB_CUSTOM_INTERFACE
        #ifndef USB_CUSTOM_INTERFACE_LEN
                #error "USB_CUSTOM_INTERFACE_LEN not defined in sketch_settings.h"
        #endif
        #ifndef USB_CUSTOM_INTERFACE_EPS
                #error "USB_CUSTOM_INTERFACE_EPS not defined in sketch_settings.h"
        #endif

        #ifdef USB_CUSTOM_INTERFACE_EPCFG
                #ifdef JOYSTICK_INTERFACE_EPCF
                        #define USB_INTERFACE_EPCF JOYSTICK_INTERFACE_EPCF, USB_CUSTOM_INTERFACE_EPCFG
                        #define USB_INTERFACE_EPSZ JOYSTICK_INTERFACE_EPSZ, USB_CUSTOM_INTERFACE_EPSZ
                #else
                        #define USB_INTERFACE_EPCF USB_CUSTOM_INTERFACE_EPCFG
                        #define USB_INTERFACE_EPSZ USB_CUSTOM_INTERFACE_EPSZ
                #endif
        #else
                #ifdef JOYSTICK_INTERFACE_EPCF
                        #define USB_INTERFACE_EPCF JOYSTICK_INTERFACE_EPCF
                        #define USB_INTERFACE_EPSZ JOYSTICK_INTERFACE_EPSZ
                #else
                        #define USB_INTERFACE_EPCF
                        #define USB_INTERFACE_EPSZ
                #endif
        #endif
#else
        #define USB_CUSTOM_INTERFACE_LEN 0
        #define USB_CUSTOM_INTERFACE_EPS 0
        #ifdef JOYSTICK_INTERFACE_EPCF
                #define USB_INTERFACE_EPCF JOYSTICK_INTERFACE_EPCF
                #define USB_INTERFACE_EPSZ JOYSTICK_INTERFACE_EPSZ
        #endif
#endif
// WHEW!




// Let GCC calculate the endpoint counts for us
#define TOTAL_NUM_ENDPOINTS ( \
        CDC_DATA_INTERFACE_EPS + MIDI_INTERFACE_EPS + KEYBOARD_INTERFACE_EPS + \
        MOUSE_INTERFACE_EPS + RAWHID_INTERFACE_EPS + FLIGHTSIM_INTERFACE_EPS + \
        SEREMU_INTERFACE_EPS + JOYSTICK_INTERFACE_EPS + USB_CUSTOM_INTERFACE_EPS)

#if (TOTAL_NUM_ENDPOINTS > 15)
#error "Total endpoint count is more than 15, too many interfaces."
#endif
#if TOTAL_NUM_ENDPOINTS
// This macro can be used throughout the code to 'disable' the teensyduino USB code
#define NUM_ENDPOINTS TOTAL_NUM_ENDPOINTS
#endif

#ifdef NUM_ENDPOINTS

// Why count manually when compiler can do this for us!
#define MANUFACTURER_NAME_LEN sizeof((char [])MANUFACTURER_NAME)
#define PRODUCT_NAME_LEN sizeof((char [])PRODUCT_NAME)
#define MAIN_DEVICE_DESCRIPTOR_LEN              9

// Let GCC calculate Descriptor offsets for us.
// Length numbers are from the sections in the descriptor.
// These values are in this exact order
#define CDC_IAD_DESCRIPTOR_OFFSET               (MAIN_DEVICE_DESCRIPTOR_LEN)
#define CDC_DATA_INTERFACE_OFFSET               (CDC_IAD_DESCRIPTOR_OFFSET + CDC_IAD_DESCRIPTOR_LEN)
#define MIDI_INTERFACE_OFFSET                   (CDC_DATA_INTERFACE_OFFSET + CDC_DATA_INTERFACE_LEN)
#define KEYBOARD_DESC_OFFSET                    (MIDI_INTERFACE_OFFSET + MIDI_INTERFACE_LEN)
#define MOUSE_DESC_OFFSET                       (KEYBOARD_DESC_OFFSET + KEYBOARD_INTERFACE_LEN)
#define RAWHID_DESC_OFFSET                      (MOUSE_DESC_OFFSET + MOUSE_INTERFACE_LEN)
#define FLIGHTSIM_DESC_OFFSET                   (RAWHID_DESC_OFFSET + RAWHID_INTERFACE_LEN)
#define SEREMU_DESC_OFFSET                      (FLIGHTSIM_DESC_OFFSET + FLIGHTSIM_INTERFACE_LEN)
#define JOYSTICK_DESC_OFFSET                    (SEREMU_DESC_OFFSET + SEREMU_INTERFACE_LEN)
#define USB_CUSTOM_OFFSET                       (JOYSTICK_DESC_OFFSET + JOYSTICK_INTERFACE_LEN)

#define CONFIG_DESC_SIZE (USB_CUSTOM_OFFSET + USB_CUSTOM_INTERFACE_LEN)


// Every composite device uses this size for EndPoint Zero.
#define EP0_SIZE		64

// NUM_ENDPOINTS = number of non-zero endpoints (0 to 15)
extern const uint8_t usb_endpoint_config_table[NUM_ENDPOINTS];
extern const uint16_t usb_endpoint_size_table[NUM_ENDPOINTS];

typedef struct {
	uint16_t	wValue;
	uint16_t	wIndex;
	const uint8_t	*addr;
	uint16_t	length;
} usb_descriptor_list_t;

extern const usb_descriptor_list_t usb_descriptor_list[];
#ifndef MAX_USB_IO_SIZE
#define MAX_USB_IO_SIZE 64
#endif
#endif


#endif
