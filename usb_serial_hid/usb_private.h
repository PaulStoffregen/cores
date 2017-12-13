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

// You can change these to give your code its own name.  On Windows,
// these are only used before an INF file (driver install) is loaded.
  
#ifndef STR_MANUFACTURER
#define STR_MANUFACTURER        L"Teensyduino"
#endif
#ifndef STR_PRODUCT
#define STR_PRODUCT             L"Serial+Keyboard+Mouse+Joystick"
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

#define KEYBOARD_INTERFACE      2
#define KEYBOARD_ENDPOINT       1
#define KEYBOARD_SIZE           8
#define KEYBOARD_BUFFER         EP_DOUBLE_BUFFER
#define KEYBOARD_INTERVAL       1

#define CDC_ACM_ENDPOINT        2
#define CDC_ACM_SIZE            16
#define CDC_ACM_BUFFER          EP_SINGLE_BUFFER
#define CDC_RX_ENDPOINT         3
#define CDC_RX_SIZE             64
#define CDC_RX_BUFFER           EP_DOUBLE_BUFFER
#define CDC_TX_ENDPOINT         4
#define CDC_TX_BUFFER           EP_DOUBLE_BUFFER
#define CDC_TX_SIZE             64

#define MOUSE_INTERFACE         3
#define MOUSE_ENDPOINT          5
#define MOUSE_SIZE              8
#define MOUSE_BUFFER            EP_DOUBLE_BUFFER
#define MOUSE_INTERVAL          2

#define JOYSTICK_INTERFACE      4
#define JOYSTICK_ENDPOINT       6
#define JOYSTICK_SIZE           16
#define JOYSTICK_BUFFER         EP_DOUBLE_BUFFER
#define JOYSTICK_INTERVAL       1


// setup
void usb_init(void);			// initialize everything
void usb_shutdown(void);		// shut off USB

// zero when we are not configured, non-zero when enumerated
extern volatile uint8_t usb_configuration;
extern volatile uint8_t usb_suspended;

// the time remaining before we transmit any partially full
// packet, or send a zero length packet.
extern volatile uint8_t transmit_flush_timer;
extern uint8_t transmit_previous_timeout;

// serial port settings (baud rate, control signals, etc) set
// by the PC.  These are ignored, but kept in RAM because the
// CDC spec requires a read that returns the current settings.
extern volatile uint8_t cdc_line_coding[7];
extern volatile uint8_t cdc_line_rtsdtr;

extern uint8_t keyboard_report_data[];
extern uint8_t keyboard_idle_count;
extern volatile uint8_t keyboard_leds;
extern uint8_t mouse_buttons;
extern uint8_t joystick_report_data[12];


#ifdef __cplusplus
} // extern "C"
#endif

#endif
