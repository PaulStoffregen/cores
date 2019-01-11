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

#define VENDOR_ID		0x16C0
#define PRODUCT_ID		0x0484
#ifndef STR_PRODUCT
#define STR_PRODUCT		L"Teensy Disk/Keyboard"
#endif
#ifndef STR_SERIAL_NUMBER
#define STR_SERIAL_NUMBER	L"123456789ABCDEF0"
#endif

// Some operating systems, especially Windows, may cache USB device
// info.  Changes to the device name may not update on the same
// computer unless the vendor or product ID numbers change, or the
// "bcdDevice" revision code is increased.

#define TRANSMIT_FLUSH_TIMEOUT	4   /* in milliseconds */
#define TRANSMIT_TIMEOUT	25   /* in milliseconds */

/**************************************************************************
 *
 *  Endpoint Buffer Configuration
 *
 **************************************************************************/

#if defined(__AVR_ATmega32U4__) || defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__)

#define ENDPOINT0_SIZE		64

#define DISK_INTERFACE		0
#define DISK_RX_ENDPOINT	3
#define DISK_RX_SIZE		64
#define DISK_RX_BUFFER		EP_DOUBLE_BUFFER
#define DISK_TX_ENDPOINT	4
#define DISK_TX_SIZE		64
#define DISK_TX_BUFFER		EP_DOUBLE_BUFFER

#define KEYBOARD_INTERFACE	1
#define KEYBOARD_ENDPOINT	5
#define KEYBOARD_SIZE		8
#define KEYBOARD_BUFFER		EP_DOUBLE_BUFFER
#define KEYBOARD_INTERVAL	1

#define DEBUG_INTERFACE		2
#define DEBUG_TX_ENDPOINT	1
#define DEBUG_TX_SIZE		64
#define DEBUG_TX_BUFFER		EP_DOUBLE_BUFFER
#define DEBUG_TX_INTERVAL	1
#define DEBUG_RX_ENDPOINT	2
#define DEBUG_RX_SIZE		32
#define DEBUG_RX_BUFFER		EP_DOUBLE_BUFFER
#define DEBUG_RX_INTERVAL	2

#define NUM_ENDPOINTS		7
#define NUM_INTERFACE		3

#elif defined(__AVR_AT90USB162__)
#error "USB Disk is not supported on Teensy 1.0\n"
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

// disk media access functions
void media_claim(void);
uint8_t media_read_sector(uint32_t lba, uint8_t *buffer);
uint8_t media_write_sector(uint32_t lba, const uint8_t *buffer);
void media_release(uint8_t read_only_mode);


#define OK_UNUSED __attribute__ ((unused))
#if defined(__AVR_AT90USB1286__)
static void (*boot_flash_page_erase_and_write)(uint32_t addr) OK_UNUSED = (void (*)(uint32_t))0xFFE4;
static void (*boot_flash_fill_temp_buffer)(uint16_t data, uint16_t addr) OK_UNUSED = (void (*)(uint16_t, uint16_t))0xFFEA;
static void (*boot_flash_prg_page)(uint32_t addr) OK_UNUSED = (void (*)(uint32_t))0xFFEC;
static void (*boot_flash_page_erase)(uint32_t addr) OK_UNUSED = (void (*)(uint32_t))0xFFEE;
#elif defined(__AVR_AT90USB646__)
static void (*boot_flash_page_erase_and_write)(uint16_t addr) OK_UNUSED = (void (*)(uint16_t))0x7FE4;
static void (*boot_flash_fill_temp_buffer)(uint16_t data, uint16_t addr) OK_UNUSED = (void (*)(uint16_t, uint16_t))0x7FEA;
static void (*boot_flash_prg_page)(uint16_t addr) OK_UNUSED = (void (*)(uint16_t))0x7FEC;
static void (*boot_flash_page_erase)(uint16_t addr) OK_UNUSED = (void (*)(uint16_t))0x7FEE;
#endif

#if defined(__AVR_ATmega32U4__)
#define LPM "lpm "
#define EPZ 0x3F
#if defined(USB_DISK_SDFLASH)
#define READ_ONLY 0
#else
#define READ_ONLY 1
#endif
#elif defined(__AVR_AT90USB646__)
#define LPM "lpm "
#define EPZ 0x7E
#define READ_ONLY 0
#elif defined(__AVR_AT90USB1286__)
#define LPM "elpm "
#define EPZ 0xFE
#define READ_ONLY 0
#endif


#define MS_STATE_IDLE		0
#define MS_STATE_STALLED	1
#define MS_STATE_SEND_STATUS	2
#define MS_STATE_SEND_ZEROPAD	3
#define MS_STATE_SEND_DATA	4
#define MS_STATE_RECEIVE_DATA	5

#define SCSI_CMD_TEST_UNIT_READY	0x00
#define SCSI_CMD_REQUEST_SENSE		0x03
#define SCSI_CMD_INQUIRY		0x12
#define SCSI_CMD_MODE_SENSE_6		0x1A
#define SCSI_CMD_MODE_SENSE_10		0x5A
#define SCSI_CMD_READ_CAPACITY		0x25
#define SCSI_CMD_READ_10		0x28
#define SCSI_CMD_WRITE_10		0x2A
#define SCSI_CMD_FORMAT_UNIT		0x04
#define SCSI_CMD_SEND_DIAGNOSTIC	0x1D
#define SCSI_CMD_PREVENT_ALLOW_MEDIA_REMOVAL 0x1E
#define SCSI_CMD_READ_FORMAT_CAPACITIES 0x23

#define SCSI_SENSE_OK			0x00	// http://docs.hp.com/en/A5159-96003/apas01.html
#define SCSI_SENSE_NOT_READY		0x02
#define SCSI_SENSE_ILLEGAL_REQUEST	0x05
#define SCSI_SENSE_UNIT_ATTENTION	0x06

#define SCSI_ASENSE_NONE		0x00
#define SCSI_ASENSE_INVALID_COMMAND	0x20
#define SCSI_ASENSE_NOT_READY_TO_READY	0x28
#define SCSI_ASENSE_MEDIUM_NOT_PRESENT	0x3A


#ifdef __cplusplus
} // extern "C"
#endif

#endif
