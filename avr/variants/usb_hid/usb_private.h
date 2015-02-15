#ifndef usb_serial_h__
#define usb_serial_h__

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

/**************************************************************************
 *
 *  Configurable Options
 *
 **************************************************************************/

#define VENDOR_ID               0x16C0
#define PRODUCT_ID              0x0482
#define TRANSMIT_FLUSH_TIMEOUT  4   /* in milliseconds */
#define TRANSMIT_TIMEOUT        25   /* in milliseconds */


/**************************************************************************
 *
 *  Endpoint Buffer Configuration
 *
 **************************************************************************/

// These buffer sizes are best for most applications, but perhaps if you
// want more buffering on some endpoint at the expense of others, this
// is where you can make such changes.  The AT90USB162 has only 176 bytes
// of DPRAM (USB buffers) and only endpoints 3 & 4 can double buffer.


// 0: control				32	64
// 1: debug IN				64	64x2
// 2: debug OUT				32	32x2
// 3: keyboard IN			8x2	8x2
// 4: mouse + joystick IN  (IDs)	16x2	16x2
// 5: joystick					16x2
// 6: 

#if defined(__AVR_ATmega32U4__) || defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__)

// Some operating systems, especially Windows, may cache USB device
// info.  Changes to the device name may not update on the same
// computer unless the vendor or product ID numbers change, or the
// "bcdDevice" revision code is increased.

#define STR_PRODUCT             L"Teensy Keyboard/Mouse/Joystick"
#define ENDPOINT0_SIZE          64

#define DEBUG_INTERFACE		2
#define DEBUG_TX_ENDPOINT	1
#define DEBUG_TX_SIZE		64
#define DEBUG_TX_BUFFER		EP_DOUBLE_BUFFER
#define DEBUG_TX_INTERVAL	1
#define DEBUG_RX_ENDPOINT	2
#define DEBUG_RX_SIZE		32
#define DEBUG_RX_BUFFER		EP_DOUBLE_BUFFER
#define DEBUG_RX_INTERVAL	2

#define KEYBOARD_INTERFACE	0
#define KEYBOARD_ENDPOINT	3
#define KEYBOARD_SIZE		8
#define KEYBOARD_BUFFER		EP_DOUBLE_BUFFER
#define KEYBOARD_INTERVAL	1

#define MOUSE_INTERFACE		1
#define MOUSE_ENDPOINT		4
#define MOUSE_SIZE		8
#define MOUSE_BUFFER		EP_DOUBLE_BUFFER
#define MOUSE_INTERVAL		1

#define JOYSTICK_INTERFACE	3
#define JOYSTICK_ENDPOINT	5
#define JOYSTICK_SIZE		16
#define JOYSTICK_BUFFER		EP_DOUBLE_BUFFER
#define JOYSTICK_INTERVAL	2

#define NUM_ENDPOINTS		7
#define NUM_INTERFACE		4

#elif defined(__AVR_AT90USB162__)

#define STR_PRODUCT             L"Teensy Keyboard/Mouse"
#define ENDPOINT0_SIZE          32

#define DEBUG_INTERFACE		2
#define DEBUG_TX_ENDPOINT	1
#define DEBUG_TX_SIZE		64
#define DEBUG_TX_BUFFER		EP_SINGLE_BUFFER
#define DEBUG_TX_INTERVAL	2
#define DEBUG_RX_ENDPOINT	2
#define DEBUG_RX_SIZE		32
#define DEBUG_RX_BUFFER		EP_SINGLE_BUFFER
#define DEBUG_RX_INTERVAL	8

#define KEYBOARD_INTERFACE	0
#define KEYBOARD_ENDPOINT	3
#define KEYBOARD_SIZE		8
#define KEYBOARD_BUFFER		EP_DOUBLE_BUFFER
#define KEYBOARD_INTERVAL	1

#define MOUSE_INTERFACE		1
#define MOUSE_ENDPOINT		4
#define MOUSE_SIZE		8
#define MOUSE_BUFFER		EP_DOUBLE_BUFFER
#define MOUSE_INTERVAL		8

#define NUM_ENDPOINTS		5
#define NUM_INTERFACE		3

#endif



// setup
void usb_init(void);			// initialize everything
void usb_shutdown(void);		// shut off USB

// variables
extern volatile uint8_t usb_configuration;
extern volatile uint8_t usb_suspended;
extern volatile uint8_t debug_flush_timer;
extern uint8_t keyboard_report_data[];
extern uint8_t keyboard_idle_count;
extern volatile uint8_t keyboard_leds;
extern uint8_t mouse_buttons;
#ifdef JOYSTICK_INTERFACE
extern uint8_t joystick_report_data[12];
#endif



#ifdef __cplusplus
} // extern "C"
#endif

#endif
