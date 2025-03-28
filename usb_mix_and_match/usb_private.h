#ifndef usb_mix_and_match_h__
#define usb_mix_and_match_h__

#include <stdint.h>
#include "defines.h"

#ifdef __cplusplus
extern "C"{
#endif

/**************************************************************************
 *
 *  Configurable Options
 *
 **************************************************************************/

// You can change these to give your code its own name.  On Windows,
// these are only used before an INF file (driver install) is loaded.

#ifndef STR_MANUFACTURER
#define STR_MANUFACTURER        L"Teensyduino"
#endif

#ifndef STR_PRODUCT
#ifdef CORE_TEENSY_KEYBOARD
#define STR_PRODUCT1 L"Keyboard;"
#else
#define STR_PRODUCT1 L""
#endif
#ifdef CORE_TEENSY_MOUSE
#define STR_PRODUCT2 STR_PRODUCT1 L"Mouse;"
#else
#define STR_PRODUCT2 STR_PRODUCT1
#endif
#ifdef CORE_TEENSY_JOYSTICK
#define STR_PRODUCT3 STR_PRODUCT2 L"Joystick;"
#else
#define STR_PRODUCT3 STR_PRODUCT2
#endif
#ifdef CORE_TEENSY_MULTIMEDIA
#define STR_PRODUCT4 STR_PRODUCT3 L"Multimedia;"
#else
#define STR_PRODUCT4 STR_PRODUCT3
#endif
#ifdef CORE_TEENSY_DEBUG
#define STR_PRODUCT5 STR_PRODUCT4 L"Debug;"
#else
#define STR_PRODUCT5 STR_PRODUCT4
#endif
#ifdef CORE_TEENSY_SERIAL
#define STR_PRODUCT STR_PRODUCT5 L"Serial;"
#else
#define STR_PRODUCT STR_PRODUCT5
#endif
#endif
#ifndef STR_SERIAL
#define STR_SERIAL		L"Serial"
#endif

// Some operating systems, especially Windows, may cache USB device
// info.  Changes to the device name may not update on the same
// computer unless the vendor or product ID numbers change, or the
// "bcdDevice" revision code is increased.


// All USB serial devices are supposed to have a serial number
// (according to Microsoft).  On windows, a new COM port is created
// for every unique serial/vendor/product number combination.  If
// you program 2 identical boards with 2 different serial numbers
// and they are assigned COM7 and COM8, each will always get the
// same COM port number because Windows remembers serial numbers.
//
// On Mac OS-X, a device file is created automatically which
// incorperates the serial number, eg, /dev/cu-usbmodem12341
//
// Linux by default ignores the serial number, and creates device
// files named /dev/ttyACM0, /dev/ttyACM1... in the order connected.
// Udev rules (in /etc/udev/rules.d) can define persistent device
// names linked to this serial number, as well as permissions, owner
// and group settings.
#ifndef STR_SERIAL_NUMBER
#define STR_SERIAL_NUMBER       L"12345"
#endif

// Mac OS-X and Linux automatically load the correct drivers.  On
// Windows, even though the driver is supplied by Microsoft, an
// INF file is needed to load the driver.  These numbers need to
// match the INF file.
#define VENDOR_ID               0x16C0
#define PRODUCT_ID              0x0487

// When you write data, it goes into a USB endpoint buffer, which
// is transmitted to the PC when it becomes full, or after a timeout
// with no more writes.  Even if you write in exactly packet-size
// increments, this timeout is used to send a "zero length packet"
// that tells the PC no more data is expected and it should pass
// any buffered data to the application that may be waiting.  If
// you want data sent immediately, call usb_serial_flush_output().
#define TRANSMIT_FLUSH_TIMEOUT  3   /* in milliseconds */

// If the PC is connected but not "listening", this is the length
// of time before usb_serial_getchar() returns with an error.  This
// is roughly equivilant to a real UART simply transmitting the
// bits on a wire where nobody is listening, except you get an error
// code which you can ignore for serial-like discard of data, or
// use to know your data wasn't sent.
#define TRANSMIT_TIMEOUT        15   /* in milliseconds */


/**************************************************************************
 *
 *  Endpoint Buffer Configuration
 *
 **************************************************************************/

#define ENDPOINT0_SIZE          64
#define ENDPOINT_COUNTER0 1
#define INTERFACE_COUNTER0 0

#ifdef CORE_TEENSY_SERIAL
#define CDC_ACM_ENDPOINT        ENDPOINT_COUNTER0
#define CDC_ACM_SIZE            16
#define CDC_ACM_BUFFER          EP_SINGLE_BUFFER
#define CDC_RX_ENDPOINT         (ENDPOINT_COUNTER0 + 1)
#define CDC_RX_SIZE             64
#define CDC_RX_BUFFER           EP_DOUBLE_BUFFER
#define CDC_TX_ENDPOINT         (ENDPOINT_COUNTER0 + 2)
#define CDC_TX_BUFFER           EP_DOUBLE_BUFFER
#define CDC_TX_SIZE             64
#define CDC_INTERFACE INTERFACE_COUNTER0
#define ENDPOINT_COUNTER1 (ENDPOINT_COUNTER0 + 3)
#define INTERFACE_COUNTER1 (INTERFACE_COUNTER0 + 2)
#else
#define ENDPOINT_COUNTER1 (ENDPOINT_COUNTER0)
#define INTERFACE_COUNTER1 (INTERFACE_COUNTER0)
#endif


#ifdef CORE_TEENSY_KEYBOARD
#define KEYBOARD_INTERFACE      INTERFACE_COUNTER1
#define KEYBOARD_ENDPOINT       ENDPOINT_COUNTER1
#define KEYBOARD_SIZE           8
#define KEYBOARD_BUFFER         EP_DOUBLE_BUFFER
#define KEYBOARD_INTERVAL       1
#define ENDPOINT_COUNTER2 (ENDPOINT_COUNTER1 + 1)
#define INTERFACE_COUNTER2 (INTERFACE_COUNTER1 + 1)
#else
#define ENDPOINT_COUNTER2 (ENDPOINT_COUNTER1)
#define INTERFACE_COUNTER2 (INTERFACE_COUNTER1)
#endif

#ifdef CORE_TEENSY_MOUSE
#define MOUSE_INTERFACE         INTERFACE_COUNTER2
#define MOUSE_ENDPOINT          ENDPOINT_COUNTER2
#define MOUSE_SIZE              8
#define MOUSE_BUFFER            EP_DOUBLE_BUFFER
#define MOUSE_INTERVAL          2
#define ENDPOINT_COUNTER3 (ENDPOINT_COUNTER2 + 1)
#define INTERFACE_COUNTER3 (INTERFACE_COUNTER2 + 1)
#else
#define ENDPOINT_COUNTER3 (ENDPOINT_COUNTER2)
#define INTERFACE_COUNTER3 (INTERFACE_COUNTER2)
#endif

#ifdef CORE_TEENSY_DEBUG
#define DEBUG_INTERFACE		INTERFACE_COUNTER3
#define DEBUG_TX_ENDPOINT	ENDPOINT_COUNTER3
#define DEBUG_TX_SIZE		64
#define DEBUG_TX_BUFFER		EP_DOUBLE_BUFFER
#define DEBUG_TX_INTERVAL	1
#define DEBUG_RX_ENDPOINT	(ENDPOINT_COUNTER3 + 1)
#define DEBUG_RX_SIZE		32
#define DEBUG_RX_BUFFER		EP_DOUBLE_BUFFER
#define DEBUG_RX_INTERVAL	2
#define ENDPOINT_COUNTER1 (ENDPOINT_COUNTER3 + 2)
#define INTERFACE_COUNTER1 (INTERFACE_COUNTER3 + 1)
#else
#define ENDPOINT_COUNTER4 (ENDPOINT_COUNTER3)
#define INTERFACE_COUNTER4 (INTERFACE_COUNTER3)
#endif

#ifdef CORE_TEENSY_JOYSTICK
#define JOYSTICK_INTERFACE      INTERFACE_COUNTER4
#define JOYSTICK_ENDPOINT       6
#define JOYSTICK_SIZE           16
#define JOYSTICK_BUFFER         EP_DOUBLE_BUFFER
#define JOYSTICK_INTERVAL       1
#define ENDPOINT_COUNTER5 (ENDPOINT_COUNTER4 + 1)
#define INTERFACE_COUNTER5 (INTERFACE_COUNTER4 + 1)
#else
#define ENDPOINT_COUNTER5 (ENDPOINT_COUNTER4)
#define INTERFACE_COUNTER5 (INTERFACE_COUNTER4)
#endif

#ifdef CORE_TEENSY_MULTIMEDIA
#define KEYMEDIA_INTERFACE      INTERFACE_COUNTER5
#define KEYMEDIA_ENDPOINT       ENDPOINT_COUNTER5
#define KEYMEDIA_SIZE           8
#define KEYMEDIA_BUFFER         EP_DOUBLE_BUFFER
#define KEYMEDIA_INTERVAL       4
#define ENDPOINT_COUNTER6 (ENDPOINT_COUNTER5 + 1)
#define INTERFACE_COUNTER6 (INTERFACE_COUNTER5 + 1)
#else
#define ENDPOINT_COUNTER6 (ENDPOINT_COUNTER5)
#define INTERFACE_COUNTER6 (INTERFACE_COUNTER5)
#endif

#define NUM_ENDPOINTS ENDPOINT_COUNTER6
#define NUM_INTERFACES INTERFACE_COUNTER6

#if NUM_ENDPOINTS > 7
#error Too many endpoints. Remove USB devices
#endif


// setup
void usb_init(void);			// initialize everything
void usb_shutdown(void);		// shut off USB

// variables
// zero when we are not configured, non-zero when enumerated
extern volatile uint8_t usb_configuration;
extern volatile uint8_t usb_suspended;

// the time remaining before we transmit any partially full
// packet, or send a zero length packet.
extern volatile uint8_t transmit_flush_timer;
extern uint8_t transmit_previous_timeout;
#ifdef CORE_TEENSY_DEBUG
extern volatile uint8_t debug_flush_timer;
#endif

// serial port settings (baud rate, control signals, etc) set
// by the PC.  These are ignored, but kept in RAM because the
// CDC spec requires a read that returns the current settings.
#ifdef CORE_TEENSY_SERIAL
extern volatile uint8_t cdc_line_coding[7];
extern volatile uint8_t cdc_line_rtsdtr;
#endif

#ifdef CORE_TEENSY_KEYBOARD
extern uint8_t keyboard_report_data[];
extern uint8_t keyboard_idle_count;
extern volatile uint8_t keyboard_leds;
#endif

#ifdef CORE_TEENSY_MOUSE
extern uint8_t mouse_buttons;
#endif

#ifdef CORE_TEENSY_JOYSTICK
extern uint8_t joystick_report_data[12];
#endif

#ifdef CORE_TEENSY_MULTIMEDIA
extern uint8_t keymedia_report_data[8];
extern uint16_t keymedia_consumer_keys[4];
extern uint8_t keymedia_system_keys[3];
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif
