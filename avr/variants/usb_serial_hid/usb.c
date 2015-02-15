/* USB Serial for Teensy USB Development Board
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2008 PJRC.COM, LLC
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#include "usb_common.h"
#include "usb_private.h"


/**************************************************************************
 *
 *  Endpoint Buffer Configuration
 *
 **************************************************************************/


static const uint8_t PROGMEM endpoint_config_table[] = {
	EP_TYPE_INTERRUPT_IN,  EP_SIZE(KEYBOARD_SIZE) | KEYBOARD_BUFFER,
	EP_TYPE_INTERRUPT_IN,  EP_SIZE(CDC_ACM_SIZE) | CDC_ACM_BUFFER,
	EP_TYPE_BULK_OUT,      EP_SIZE(CDC_RX_SIZE) | CDC_RX_BUFFER,
	EP_TYPE_BULK_IN,       EP_SIZE(CDC_TX_SIZE) | CDC_TX_BUFFER,
	EP_TYPE_INTERRUPT_IN,  EP_SIZE(MOUSE_SIZE) | MOUSE_BUFFER,
	EP_TYPE_INTERRUPT_IN,  EP_SIZE(JOYSTICK_SIZE) | JOYSTICK_BUFFER,
};


/**************************************************************************
 *
 *  Descriptor Data
 *
 **************************************************************************/

// Descriptors are the data that your computer reads when it auto-detects
// this USB device (called "enumeration" in USB lingo).  The most commonly
// changed items are editable at the top of this file.  Changing things
// in here should only be done by those who've read chapter 9 of the USB
// spec and relevant portions of any USB class specifications!

static const uint8_t PROGMEM device_descriptor[] = {
	18,					// bLength
	1,					// bDescriptorType
	0x00, 0x02,				// bcdUSB
	0xEF,					// bDeviceClass
	0x02,					// bDeviceSubClass
	0x01,					// bDeviceProtocol
	ENDPOINT0_SIZE,				// bMaxPacketSize0
	LSB(VENDOR_ID), MSB(VENDOR_ID),		// idVendor
	LSB(PRODUCT_ID), MSB(PRODUCT_ID),	// idProduct
	0x02, 0x01,				// bcdDevice
	1,					// iManufacturer
	2,					// iProduct
	3,					// iSerialNumber
	1					// bNumConfigurations
};

// Keyboard Protocol 1, HID 1.11 spec, Appendix B, page 59-60
static const uint8_t PROGMEM keyboard_hid_report_desc[] = {
        0x05, 0x01,             //  Usage Page (Generic Desktop),
        0x09, 0x06,             //  Usage (Keyboard),
        0xA1, 0x01,             //  Collection (Application),
        0x75, 0x01,             //  Report Size (1),
        0x95, 0x08,             //  Report Count (8),
        0x05, 0x07,             //  Usage Page (Key Codes),
        0x19, 0xE0,             //  Usage Minimum (224),
        0x29, 0xE7,             //  Usage Maximum (231),
        0x15, 0x00,             //  Logical Minimum (0),
        0x25, 0x01,             //  Logical Maximum (1),
        0x81, 0x02,             //  Input (Data, Variable, Absolute), ;Modifier byte
        0x95, 0x08,             //  Report Count (8),
        0x75, 0x01,             //  Report Size (1),
        0x15, 0x00,             //  Logical Minimum (0),
        0x25, 0x01,             //  Logical Maximum (1),
        0x05, 0x0C,             //  Usage Page (Consumer),
        0x09, 0xE9,             //  Usage (Volume Increment),
        0x09, 0xEA,             //  Usage (Volume Decrement),
        0x09, 0xE2,             //  Usage (Mute),
        0x09, 0xCD,             //  Usage (Play/Pause),
        0x09, 0xB5,             //  Usage (Scan Next Track),
        0x09, 0xB6,             //  Usage (Scan Previous Track),
        0x09, 0xB7,             //  Usage (Stop),
        0x09, 0xB8,             //  Usage (Eject),
        0x81, 0x02,             //  Input (Data, Variable, Absolute), ;Media keys
        0x95, 0x05,             //  Report Count (5),
        0x75, 0x01,             //  Report Size (1),
        0x05, 0x08,             //  Usage Page (LEDs),
        0x19, 0x01,             //  Usage Minimum (1),
        0x29, 0x05,             //  Usage Maximum (5),
        0x91, 0x02,             //  Output (Data, Variable, Absolute), ;LED report
        0x95, 0x01,             //  Report Count (1),
        0x75, 0x03,             //  Report Size (3),
        0x91, 0x03,             //  Output (Constant),                 ;LED report padding
        0x95, 0x06,             //  Report Count (6),
        0x75, 0x08,             //  Report Size (8),
        0x15, 0x00,             //  Logical Minimum (0),
        0x25, 0x7F,             //  Logical Maximum(104),
        0x05, 0x07,             //  Usage Page (Key Codes),
        0x19, 0x00,             //  Usage Minimum (0),
        0x29, 0x7F,             //  Usage Maximum (104),
        0x81, 0x00,             //  Input (Data, Array),                ;Normal keys
        0xc0                    // End Collection
};

// Mouse Protocol 1, HID 1.11 spec, Appendix B, page 59-60, with wheel extension
static const uint8_t PROGMEM mouse_hid_report_desc[] = {
        0x05, 0x01,                     // Usage Page (Generic Desktop)
        0x09, 0x02,                     // Usage (Mouse)
        0xA1, 0x01,                     // Collection (Application)
        0x05, 0x09,                     //   Usage Page (Button)
        0x19, 0x01,                     //   Usage Minimum (Button #1)
        0x29, 0x03,                     //   Usage Maximum (Button #3)
        0x15, 0x00,                     //   Logical Minimum (0)
        0x25, 0x01,                     //   Logical Maximum (1)
        0x95, 0x03,                     //   Report Count (3)
        0x75, 0x01,                     //   Report Size (1)
        0x81, 0x02,                     //   Input (Data, Variable, Absolute)
        0x95, 0x01,                     //   Report Count (1)
        0x75, 0x05,                     //   Report Size (5)
        0x81, 0x03,                     //   Input (Constant)
        0x05, 0x01,                     //   Usage Page (Generic Desktop)
        0x09, 0x30,                     //   Usage (X)
        0x09, 0x31,                     //   Usage (Y)
        0x15, 0x81,                     //   Logical Minimum (-127)
        0x25, 0x7F,                     //   Logical Maximum (127)
        0x75, 0x08,                     //   Report Size (8),
        0x95, 0x02,                     //   Report Count (2),
        0x81, 0x06,                     //   Input (Data, Variable, Relative)
        0x09, 0x38,                     //   Usage (Wheel)
        0x95, 0x01,                     //   Report Count (1),
        0x81, 0x06,                     //   Input (Data, Variable, Relative)
        0xC0                            // End Collection
};

static const uint8_t PROGMEM joystick_hid_report_desc[] = {
        0x05, 0x01,                     // Usage Page (Generic Desktop)
        0x09, 0x04,                     // Usage (Joystick)
        0xA1, 0x01,                     // Collection (Application)
        0x15, 0x00,                     // Logical Minimum (0)
        0x25, 0x01,                     // Logical Maximum (1)
        0x75, 0x01,                     // Report Size (1)
        0x95, 0x20,                     // Report Count (32)
        0x05, 0x09,                     // Usage Page (Button)
        0x19, 0x01,                     // Usage Minimum (Button #1)
        0x29, 0x20,                     // Usage Maximum (Button #32)
        0x81, 0x02,                     // Input (variable,absolute)
        0x15, 0x00,                     // Logical Minimum (0)
        0x25, 0x07,                     // Logical Maximum (7)
        0x35, 0x00,                     // Physical Minimum (0)
        0x46, 0x3B, 0x01,               // Physical Maximum (315)
        0x75, 0x04,                     // Report Size (4)
        0x95, 0x01,                     // Report Count (1)
        0x65, 0x14,                     // Unit (20)
        0x05, 0x01,                     // Usage Page (Generic Desktop)
        0x09, 0x39,                     // Usage (Hat switch)
        0x81, 0x42,                     // Input (variable,absolute,null_state)
        0x05, 0x01,                     // Usage Page (Generic Desktop)
        0x09, 0x01,                     // Usage (Pointer)
        0xA1, 0x00,                     // Collection ()
        0x15, 0x00,                     //   Logical Minimum (0)
        0x26, 0xFF, 0x03,               //   Logical Maximum (1023)
        0x75, 0x0A,                     //   Report Size (10)
        0x95, 0x04,                     //   Report Count (4)
        0x09, 0x30,                     //   Usage (X)
        0x09, 0x31,                     //   Usage (Y)
        0x09, 0x32,                     //   Usage (Z)
        0x09, 0x35,                     //   Usage (Rz)
        0x81, 0x02,                     //   Input (variable,absolute)
        0xC0,                           // End Collection
        0x15, 0x00,                     // Logical Minimum (0)
        0x26, 0xFF, 0x03,               // Logical Maximum (1023)
        0x75, 0x0A,                     // Report Size (10)
        0x95, 0x02,                     // Report Count (2)
        0x09, 0x36,                     // Usage (Slider)
        0x09, 0x36,                     // Usage (Slider)
        0x81, 0x02,                     // Input (variable,absolute)
        0xC0                            // End Collection
};

#define KEYBOARD_HID_DESC_OFFSET        ( 9+8 + 9+5+5+4+5+7+9+7+7 + 9 )
#define MOUSE_HID_DESC_OFFSET           ( 9+8 + 9+5+5+4+5+7+9+7+7 + 9+9+7 + 9 )
#define JOYSTICK_HID_DESC_OFFSET	( 9+8 + 9+5+5+4+5+7+9+7+7 + 9+9+7 + 9+9+7 + 9 )
#define CONFIG1_DESC_SIZE		( 9+8 + 9+5+5+4+5+7+9+7+7 + 9+9+7 + 9+9+7 + 9+9+7 )

static const uint8_t PROGMEM config1_descriptor[CONFIG1_DESC_SIZE] = {
	// configuration descriptor, USB spec 9.6.3, page 264-266, Table 9-10
	9, 					// bLength;
	2,					// bDescriptorType;
	LSB(CONFIG1_DESC_SIZE),			// wTotalLength
	MSB(CONFIG1_DESC_SIZE),
	5,					// bNumInterfaces
	1,					// bConfigurationValue
	0,					// iConfiguration
	0xC0,					// bmAttributes
	50,					// bMaxPower
        // interface association descriptor, USB ECN, Table 9-Z
        8,                                      // bLength
        11,                                     // bDescriptorType
        0,                                      // bFirstInterface
        2,                                      // bInterfaceCount
        0x02,                                   // bFunctionClass
        0x02,                                   // bFunctionSubClass
        0x01,                                   // bFunctionProtocol
        4,                                      // iFunction

	// interface descriptor, USB spec 9.6.5, page 267-269, Table 9-12
	9,					// bLength
	4,					// bDescriptorType
	0,					// bInterfaceNumber
	0,					// bAlternateSetting
	1,					// bNumEndpoints
	0x02,					// bInterfaceClass
	0x02,					// bInterfaceSubClass
	0x01,					// bInterfaceProtocol
	0,					// iInterface
	// CDC Header Functional Descriptor, CDC Spec 5.2.3.1, Table 26
	5,					// bFunctionLength
	0x24,					// bDescriptorType
	0x00,					// bDescriptorSubtype
	0x10, 0x01,				// bcdCDC
	// Call Management Functional Descriptor, CDC Spec 5.2.3.2, Table 27
	5,					// bFunctionLength
	0x24,					// bDescriptorType
	0x01,					// bDescriptorSubtype
	0x00,					// bmCapabilities
	1,					// bDataInterface
	// Abstract Control Management Functional Descriptor, CDC Spec 5.2.3.3, Table 28
	4,					// bFunctionLength
	0x24,					// bDescriptorType
	0x02,					// bDescriptorSubtype
	0x06,					// bmCapabilities
	// Union Functional Descriptor, CDC Spec 5.2.3.8, Table 33
	5,					// bFunctionLength
	0x24,					// bDescriptorType
	0x06,					// bDescriptorSubtype
	0,					// bMasterInterface
	1,					// bSlaveInterface0
	// endpoint descriptor, USB spec 9.6.6, page 269-271, Table 9-13
	7,					// bLength
	5,					// bDescriptorType
	CDC_ACM_ENDPOINT | 0x80,		// bEndpointAddress
	0x03,					// bmAttributes (0x03=intr)
	CDC_ACM_SIZE, 0,			// wMaxPacketSize
	64,					// bInterval
	// interface descriptor, USB spec 9.6.5, page 267-269, Table 9-12
	9,					// bLength
	4,					// bDescriptorType
	1,					// bInterfaceNumber
	0,					// bAlternateSetting
	2,					// bNumEndpoints
	0x0A,					// bInterfaceClass
	0x00,					// bInterfaceSubClass
	0x00,					// bInterfaceProtocol
	0,					// iInterface
	// endpoint descriptor, USB spec 9.6.6, page 269-271, Table 9-13
	7,					// bLength
	5,					// bDescriptorType
	CDC_RX_ENDPOINT,			// bEndpointAddress
	0x02,					// bmAttributes (0x02=bulk)
	CDC_RX_SIZE, 0,				// wMaxPacketSize
	0,					// bInterval
	// endpoint descriptor, USB spec 9.6.6, page 269-271, Table 9-13
	7,					// bLength
	5,					// bDescriptorType
	CDC_TX_ENDPOINT | 0x80,			// bEndpointAddress
	0x02,					// bmAttributes (0x02=bulk)
	CDC_TX_SIZE, 0,				// wMaxPacketSize
	0,					// bInterval

        // interface descriptor, USB spec 9.6.5, page 267-269, Table 9-12
        9,                                      // bLength
        4,                                      // bDescriptorType
        KEYBOARD_INTERFACE,                     // bInterfaceNumber
        0,                                      // bAlternateSetting
        1,                                      // bNumEndpoints
        0x03,                                   // bInterfaceClass (0x03 = HID)
        0x01,                                   // bInterfaceSubClass (0x01 = Boot)
        0x01,                                   // bInterfaceProtocol (0x01 = Keyboard)
        0,                                      // iInterface
        // HID interface descriptor, HID 1.11 spec, section 6.2.1
        9,                                      // bLength
        0x21,                                   // bDescriptorType
        0x11, 0x01,                             // bcdHID
        0,                                      // bCountryCode
        1,                                      // bNumDescriptors
        0x22,                                   // bDescriptorType
        sizeof(keyboard_hid_report_desc),       // wDescriptorLength
        0,
        // endpoint descriptor, USB spec 9.6.6, page 269-271, Table 9-13
        7,                                      // bLength
        5,                                      // bDescriptorType
        KEYBOARD_ENDPOINT | 0x80,               // bEndpointAddress
        0x03,                                   // bmAttributes (0x03=intr)
        KEYBOARD_SIZE, 0,                       // wMaxPacketSize
        KEYBOARD_INTERVAL,                      // bInterval

        // interface descriptor, USB spec 9.6.5, page 267-269, Table 9-12
        9,                                      // bLength
        4,                                      // bDescriptorType
        MOUSE_INTERFACE,                        // bInterfaceNumber
        0,                                      // bAlternateSetting
        1,                                      // bNumEndpoints
        0x03,                                   // bInterfaceClass (0x03 = HID)
        0x01,                                   // bInterfaceSubClass (0x01 = Boot)
        0x02,                                   // bInterfaceProtocol (0x02 = Mouse)
        0,                                      // iInterface
        // HID interface descriptor, HID 1.11 spec, section 6.2.1
        9,                                      // bLength
        0x21,                                   // bDescriptorType
        0x11, 0x01,                             // bcdHID
        0,                                      // bCountryCode
        1,                                      // bNumDescriptors
        0x22,                                   // bDescriptorType
        sizeof(mouse_hid_report_desc),          // wDescriptorLength
        0,
        // endpoint descriptor, USB spec 9.6.6, page 269-271, Table 9-13
        7,                                      // bLength
        5,                                      // bDescriptorType
        MOUSE_ENDPOINT | 0x80,                  // bEndpointAddress
        0x03,                                   // bmAttributes (0x03=intr)
        MOUSE_SIZE, 0,                          // wMaxPacketSize
        MOUSE_INTERVAL,                         // bInterval

        // interface descriptor, USB spec 9.6.5, page 267-269, Table 9-12
        9,                                      // bLength
        4,                                      // bDescriptorType
        JOYSTICK_INTERFACE,                     // bInterfaceNumber
        0,                                      // bAlternateSetting
        1,                                      // bNumEndpoints
        0x03,                                   // bInterfaceClass (0x03 = HID)
        0x00,                                   // bInterfaceSubClass
        0x00,                                   // bInterfaceProtocol
        0,                                      // iInterface
        // HID interface descriptor, HID 1.11 spec, section 6.2.1
        9,                                      // bLength
        0x21,                                   // bDescriptorType
        0x11, 0x01,                             // bcdHID
        0,                                      // bCountryCode
        1,                                      // bNumDescriptors
        0x22,                                   // bDescriptorType
        sizeof(joystick_hid_report_desc),       // wDescriptorLength
        0,
        // endpoint descriptor, USB spec 9.6.6, page 269-271, Table 9-13
        7,                                      // bLength
        5,                                      // bDescriptorType
        JOYSTICK_ENDPOINT | 0x80,               // bEndpointAddress
        0x03,                                   // bmAttributes (0x03=intr)
        12, 0,                                  // wMaxPacketSize
        JOYSTICK_INTERVAL                       // bInterval
};

// If you're desperate for a little extra code memory, these strings
// can be completely removed if iManufacturer, iProduct, iSerialNumber
// in the device desciptor are changed to zeros.
struct usb_string_descriptor_struct {
	uint8_t bLength;
	uint8_t bDescriptorType;
	int16_t wString[];
};
static const struct usb_string_descriptor_struct PROGMEM string0 = {
	4,
	3,
	{0x0409}
};
static const struct usb_string_descriptor_struct PROGMEM string1 = {
	sizeof(STR_MANUFACTURER),
	3,
	STR_MANUFACTURER
};
static const struct usb_string_descriptor_struct PROGMEM string2 = {
	sizeof(STR_PRODUCT),
	3,
	STR_PRODUCT
};
static const struct usb_string_descriptor_struct PROGMEM string3 = {
	sizeof(STR_SERIAL_NUMBER),
	3,
	STR_SERIAL_NUMBER
};
static const struct usb_string_descriptor_struct PROGMEM string4 = {
	sizeof(STR_SERIAL),
	3,
	STR_SERIAL
};

// This table defines which descriptor data is sent for each specific
// request from the host (in wValue and wIndex).
static const struct descriptor_list_struct {
	uint16_t	wValue;
	uint16_t	wIndex;
	const uint8_t	*addr;
	uint8_t		length;
} PROGMEM descriptor_list[] = {
	{0x0100, 0x0000, device_descriptor, sizeof(device_descriptor)},
	{0x0200, 0x0000, config1_descriptor, sizeof(config1_descriptor)},
        {0x2200, KEYBOARD_INTERFACE, keyboard_hid_report_desc, sizeof(keyboard_hid_report_desc)},
        {0x2100, KEYBOARD_INTERFACE, config1_descriptor+KEYBOARD_HID_DESC_OFFSET, 9},
        {0x2200, MOUSE_INTERFACE, mouse_hid_report_desc, sizeof(mouse_hid_report_desc)},
        {0x2100, MOUSE_INTERFACE, config1_descriptor+MOUSE_HID_DESC_OFFSET, 9},
        {0x2200, JOYSTICK_INTERFACE, joystick_hid_report_desc, sizeof(joystick_hid_report_desc)},
        {0x2100, JOYSTICK_INTERFACE, config1_descriptor+JOYSTICK_HID_DESC_OFFSET, 9},
	{0x0300, 0x0000, (const uint8_t *)&string0, 4},
	{0x0301, 0x0409, (const uint8_t *)&string1, sizeof(STR_MANUFACTURER)},
	{0x0302, 0x0409, (const uint8_t *)&string2, sizeof(STR_PRODUCT)},
	{0x0303, 0x0409, (const uint8_t *)&string3, sizeof(STR_SERIAL_NUMBER)},
	{0x0304, 0x0409, (const uint8_t *)&string4, sizeof(STR_SERIAL)},
};
#define NUM_DESC_LIST (sizeof(descriptor_list)/sizeof(struct descriptor_list_struct))


/**************************************************************************
 *
 *  Variables - these are the only non-stack RAM usage
 *
 **************************************************************************/

// zero when we are not configured, non-zero when enumerated
volatile uint8_t usb_configuration USBSTATE;
volatile uint8_t usb_suspended USBSTATE;

// the time remaining before we transmit any partially full
// packet, or send a zero length packet.
volatile uint8_t transmit_flush_timer=0;
volatile uint8_t reboot_timer=0;
uint8_t transmit_previous_timeout=0;

// serial port settings (baud rate, control signals, etc) set
// by the PC.  These are ignored, but kept in RAM because the
// CDC spec requires a read that returns the current settings.
volatile uint8_t cdc_line_coding[7]={0x00, 0xE1, 0x00, 0x00, 0x00, 0x00, 0x08};
volatile uint8_t cdc_line_rtsdtr USBSTATE;

// byte0: which modifier keys are currently pressed
//  1=left ctrl,    2=left shift,   4=left alt,    8=left gui
//  16=right ctrl, 32=right shift, 64=right alt, 128=right gui
// byte1: media keys (TODO: document these)
// bytes2-7: which keys are currently pressed, up to 6 keys may be down at once
uint8_t keyboard_report_data[8] USBSTATE;

// protocol setting from the host.  We use exactly the same report
// either way, so this variable only stores the setting since we
// are required to be able to report which setting is in use.
static uint8_t keyboard_protocol USBSTATE;

// the idle configuration, how often we send the report to the
// host (ms * 4) even when it hasn't changed
static uint8_t keyboard_idle_config USBSTATE;

// count until idle timeout
uint8_t keyboard_idle_count USBSTATE;

// 1=num lock, 2=caps lock, 4=scroll lock, 8=compose, 16=kana
volatile uint8_t keyboard_leds USBSTATE;

// which buttons are currently pressed
uint8_t mouse_buttons USBSTATE;

// protocol setting from the host.  We use exactly the same report
// either way, so this variable only stores the setting since we
// are required to be able to report which setting is in use.
static uint8_t mouse_protocol USBSTATE;

// joystick data
uint8_t joystick_report_data[12] USBSTATE;



/**************************************************************************
 *
 *  Public Functions - these are the API intended for the user
 *
 **************************************************************************/


// initialize USB serial
void usb_init(void)
{
	uint8_t u;

	u = USBCON;
	if ((u & (1<<USBE)) && !(u & (1<<FRZCLK))) return;
	HW_CONFIG();
        USB_FREEZE();				// enable USB
        PLL_CONFIG();				// config PLL
        while (!(PLLCSR & (1<<PLOCK))) ;	// wait for PLL lock
        USB_CONFIG();				// start USB clock
        UDCON = 0;				// enable attach resistor
	usb_configuration = 0;
	usb_suspended = 0;
	cdc_line_rtsdtr = 0;
        keyboard_report_data[0] = 0;
        keyboard_report_data[1] = 0;
        keyboard_report_data[2] = 0;
        keyboard_report_data[3] = 0;
        keyboard_report_data[4] = 0;
        keyboard_report_data[5] = 0;
        keyboard_report_data[6] = 0;
        keyboard_report_data[7] = 0;
        keyboard_protocol = 1;
        keyboard_idle_config = 125;
        keyboard_idle_count = 0;
        keyboard_leds = 0;
        mouse_buttons = 0;
        mouse_protocol = 1;
        joystick_report_data[0] = 0;
        joystick_report_data[1] = 0;
        joystick_report_data[2] = 0;
        joystick_report_data[3] = 0;
        joystick_report_data[4] =  0x0F;
        joystick_report_data[5] =  0x20;
        joystick_report_data[6] =  0x80;
        joystick_report_data[7] =  0x00;
        joystick_report_data[8] =  0x02;
        joystick_report_data[9] =  0x08;
        joystick_report_data[10] = 0x20;
        joystick_report_data[11] = 0x80;
	UDINT = 0;
        UDIEN = (1<<EORSTE)|(1<<SOFE)|(1<<SUSPE);
}


void usb_shutdown(void)
{
	UDIEN = 0;	// disable interrupts
	UDCON = 1;	// disconnect attach resistor
	USBCON = 0;	// shut off USB periperal
	PLLCSR = 0;	// shut off PLL
	usb_configuration = 0;
	usb_suspended = 1;
}


// Public API functions moved to usb_api.cpp

/**************************************************************************
 *
 *  Private Functions - not intended for general user consumption....
 *
 **************************************************************************/


// USB Device Interrupt - handle all device-level events
// the transmit buffer flushing is triggered by the start of frame
//
ISR(USB_GEN_vect)
{
	uint8_t intbits, t, i;
	static uint8_t div4=0;

        intbits = UDINT;
        UDINT = 0;
        if (intbits & (1<<EORSTI)) {
		// USB Reset
		UENUM = 0;
		UECONX = 1;
		UECFG0X = EP_TYPE_CONTROL;
		UECFG1X = EP_SIZE(ENDPOINT0_SIZE) | EP_SINGLE_BUFFER;
		UEIENX = (1<<RXSTPE);
		usb_configuration = 0;
		cdc_line_rtsdtr = 0;
	}
	if (intbits & (1<<SOFI)) {
		// Start Of Frame
		if (usb_configuration) {
			t = transmit_flush_timer;
			if (t) {
				transmit_flush_timer = --t;
				if (!t) {
					UENUM = CDC_TX_ENDPOINT;
					UEINTX = 0x3A;
				}
			}
			t = reboot_timer;
			if (t) {
				reboot_timer = --t;
				if (!t) _reboot_Teensyduino_();
			}
                	if (keyboard_idle_config && (++div4 & 3) == 0) {
                        	UENUM = KEYBOARD_ENDPOINT;
                        	if (UEINTX & (1<<RWAL)) {
                                	keyboard_idle_count++;
                                	if (keyboard_idle_count == keyboard_idle_config) {
                                        	keyboard_idle_count = 0;
                                        	//len = keyboard_protocol ? sizeof(keyboard_keys) : 8;
                                        	for (i=0; i < 8; i++) {
                                                	UEDATX = keyboard_report_data[i];
                                        	}
                                        	UEINTX = 0x3A;
                                	}
                        	}
                	}
		}
	}
	// in active state
	if (intbits & (1<<SUSPI)) {
		// USB Suspend (inactivity for 3ms)
		UDIEN = (1<<WAKEUPE);
		usb_configuration = 0;
		usb_suspended = 1;
		#if (F_CPU >= 8000000L)
		// WAKEUPI does not work with USB clock freeze 
		// when CPU is running less than 8 MHz.
		// Is this a hardware bug?
		USB_FREEZE();			// shut off USB
		PLLCSR = 0;			// shut off PLL
		#endif
		// to properly meet the USB spec, current must
		// reduce to less than 2.5 mA, which means using
		// powerdown mode, but that breaks the Arduino
		// user's paradigm....
	}
	if (usb_suspended && (intbits & (1<<WAKEUPI))) {
		// USB Resume (pretty much any activity)
		#if (F_CPU >= 8000000L)
		PLL_CONFIG();
		while (!(PLLCSR & (1<<PLOCK))) ;
		USB_CONFIG();
		#endif
		UDIEN = (1<<EORSTE)|(1<<SOFE)|(1<<SUSPE);
		usb_suspended = 0;
		return;
	}
}


// Misc functions to wait for ready and send/receive packets
static inline void usb_wait_in_ready(void)
{
	while (!(UEINTX & (1<<TXINI))) ;
}
static inline void usb_send_in(void)
{
	UEINTX = ~(1<<TXINI);
}
static inline void usb_wait_receive_out(void)
{
	while (!(UEINTX & (1<<RXOUTI))) ;
}
static inline void usb_ack_out(void)
{
	UEINTX = ~(1<<RXOUTI);
}



// USB Endpoint Interrupt - endpoint 0 is handled here.  The
// other endpoints are manipulated by the user-callable
// functions, and the start-of-frame interrupt.
//
ISR(USB_COM_vect)
{
        uint8_t intbits;
	const uint8_t *list;
        const uint8_t *cfg;
	uint8_t i, n, len, en;
	volatile uint8_t *p;
	uint8_t bmRequestType;
	uint8_t bRequest;
	uint16_t wValue;
	uint16_t wIndex;
	uint16_t wLength;
	uint16_t desc_val;
	const uint8_t *desc_addr;
	uint8_t	desc_length;

	UENUM = 0;
	intbits = UEINTX;
	if (intbits & (1<<RXSTPI)) {
		bmRequestType = UEDATX;
		bRequest = UEDATX;
		read_word_lsbfirst(wValue, UEDATX);
		read_word_lsbfirst(wIndex, UEDATX);
		read_word_lsbfirst(wLength, UEDATX);
                UEINTX = ~((1<<RXSTPI) | (1<<RXOUTI) | (1<<TXINI));
                if (bRequest == GET_DESCRIPTOR) {
			list = (const uint8_t *)descriptor_list;
			for (i=0; ; i++) {
				if (i >= NUM_DESC_LIST) {
					UECONX = (1<<STALLRQ)|(1<<EPEN);  //stall
					return;
				}
				pgm_read_word_postinc(desc_val, list);
				if (desc_val != wValue) {
					list += sizeof(struct descriptor_list_struct)-2;
					continue;
				}
				pgm_read_word_postinc(desc_val, list);
				if (desc_val != wIndex) {
					list += sizeof(struct descriptor_list_struct)-4;
					continue;
				}
				pgm_read_word_postinc(desc_addr, list);
				desc_length = pgm_read_byte(list);
				break;
			}
			len = (wLength < 256) ? wLength : 255;
			if (len > desc_length) len = desc_length;
			list = desc_addr;
			do {
				// wait for host ready for IN packet
				do {
					i = UEINTX;
				} while (!(i & ((1<<TXINI)|(1<<RXOUTI))));
				if (i & (1<<RXOUTI)) return;	// abort
				// send IN packet
				n = len < ENDPOINT0_SIZE ? len : ENDPOINT0_SIZE;
				for (i = n; i; i--) {
					pgm_read_byte_postinc(UEDATX, list);
				}
				len -= n;
				usb_send_in();
			} while (len || n == ENDPOINT0_SIZE);
			return;
                }
		if (bRequest == SET_ADDRESS) {
			usb_send_in();
			usb_wait_in_ready();
			UDADDR = wValue | (1<<ADDEN);
			return;
		}
		if (bRequest == SET_CONFIGURATION && bmRequestType == 0) {
			usb_configuration = wValue;
			cdc_line_rtsdtr = 0;
			transmit_flush_timer = 0;
			usb_send_in();
			cfg = endpoint_config_table;
			for (i=1; i<7; i++) {
				UENUM = i;
				//pgm_read_byte_postinc(en, cfg);
				//UECONX = en;
				UECONX = 1;
				//if (en) {
				pgm_read_byte_postinc(UECFG0X, cfg);
				pgm_read_byte_postinc(UECFG1X, cfg);
				//}
			}
        		UERST = 0x1E;
        		UERST = 0;
			return;
		}
		if (bRequest == GET_CONFIGURATION && bmRequestType == 0x80) {
			usb_wait_in_ready();
			UEDATX = usb_configuration;
			usb_send_in();
			return;
		}
		if (bRequest == CDC_GET_LINE_CODING /* 0x21 */ && bmRequestType == 0xA1) {
			usb_wait_in_ready();
			p = cdc_line_coding;
			for (i=0; i<7; i++) {
				UEDATX = *p++;
			}
			usb_send_in();
			return;
		}
		if (bRequest == CDC_SET_LINE_CODING /* 0x20 */ && bmRequestType == 0x21) {
			usb_wait_receive_out();
			p = cdc_line_coding;
			for (i=0; i<7; i++) {
				*p++ = UEDATX;
			}
			usb_ack_out();
			usb_send_in();
			if (*(long *)cdc_line_coding == 134L) reboot_timer = 15;
			if (*(long *)cdc_line_coding == 150L) {
				UENUM = CDC_TX_ENDPOINT;
				while (UESTA0X & 0x03) {
					UEINTX = 0xFF;
					while (UEINTX & 0x04) /* TODO: timeout? */ ;
				}
				_restart_Teensyduino_();
			}
			return;
		}
		if (bRequest == CDC_SET_CONTROL_LINE_STATE /* 0x22 */ && bmRequestType == 0x21) {
			cdc_line_rtsdtr = wValue;
			usb_wait_in_ready();
			usb_send_in();
			return;
		}
		if (bRequest == CDC_SEND_BREAK /* 0x23 */ && bmRequestType == 0x21) {
			usb_wait_in_ready();
			usb_send_in();
			return;
		}
		if (bRequest == GET_STATUS) {
			usb_wait_in_ready();
			i = 0;
			if (bmRequestType == 0x82) {
				UENUM = wIndex;
				if (UECONX & (1<<STALLRQ)) i = 1;
				UENUM = 0;
			}
			UEDATX = i;
			UEDATX = 0;
			usb_send_in();
			return;
		}
		if ((bRequest == CLEAR_FEATURE || bRequest == SET_FEATURE)
		  && bmRequestType == 0x02 && wValue == 0) {
			i = wIndex & 0x7F;
			if (i >= 1 && i <= MAX_ENDPOINT) {
				usb_send_in();
				UENUM = i;
				if (bRequest == SET_FEATURE) {
					UECONX = (1<<STALLRQ)|(1<<EPEN);
				} else {
					UECONX = (1<<STALLRQC)|(1<<RSTDT)|(1<<EPEN);
					UERST = (1 << i);
					UERST = 0;
				}
				return;
			}
		}
                if (wIndex == KEYBOARD_INTERFACE) {
                        if (bmRequestType == 0xA1) {
                                if (bRequest == HID_GET_REPORT) {
                                        usb_wait_in_ready();
                                        //len = keyboard_protocol ? sizeof(keyboard_keys) : 8;
                                        for (i=0; i < 8; i++) {
                                                UEDATX = keyboard_report_data[i];
                                        }
                                        usb_send_in();
                                        return;
                                }
                                if (bRequest == HID_GET_IDLE) {
                                        usb_wait_in_ready();
                                        UEDATX = keyboard_idle_config;
                                        usb_send_in();
                                        return;
                                }
                                if (bRequest == HID_GET_PROTOCOL) {
                                        usb_wait_in_ready();
                                        UEDATX = keyboard_protocol;
                                        usb_send_in();
                                        return;
                                }
                        }
                        if (bmRequestType == 0x21) {
                                if (bRequest == HID_SET_REPORT) {
                                        usb_wait_receive_out();
                                        keyboard_leds = UEDATX;
                                        usb_ack_out();
                                        usb_send_in();
                                        return;
                                }
                                if (bRequest == HID_SET_IDLE) {
                                        keyboard_idle_config = (wValue >> 8);
                                        keyboard_idle_count = 0;
                                        //usb_wait_in_ready();
                                        usb_send_in();
                                        return;
                                }
                                if (bRequest == HID_SET_PROTOCOL) {
                                        keyboard_protocol = wValue;
                                        //usb_wait_in_ready();
                                        usb_send_in();
                                        return;
                                }
                        }
                }
                if (wIndex == MOUSE_INTERFACE) {
                        if (bmRequestType == 0xA1) {
                                if (bRequest == HID_GET_REPORT) {
                                        usb_wait_in_ready();
                                        UEDATX = mouse_buttons;
                                        UEDATX = 0;
                                        UEDATX = 0;
                                        UEDATX = 0;
                                        usb_send_in();
                                        return;
                                }
                                if (bRequest == HID_GET_PROTOCOL) {
                                        usb_wait_in_ready();
                                        UEDATX = mouse_protocol;
                                        usb_send_in();
                                        return;
                                }
                        }
                        if (bmRequestType == 0x21) {
                                if (bRequest == HID_SET_PROTOCOL) {
                                        mouse_protocol = wValue;
                                        usb_send_in();
                                        return;
                                }
                        }
                }
                if (wIndex == JOYSTICK_INTERFACE) {
                        if (bmRequestType == 0xA1) {
                                if (bRequest == HID_GET_REPORT) {
                                        usb_wait_in_ready();
                                        for (i=0; i<12; i++) {
                                                UEDATX = joystick_report_data[i];
                                        }
                                        usb_send_in();
                                        return;
                                }
                        }
                }
        }
	UECONX = (1<<STALLRQ) | (1<<EPEN);	// stall
}


