/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2017 PJRC.COM, LLC.
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

#include "usb_dev.h"
#include "usb_keyboard.h"
#include "core_pins.h" // for yield()
#include "keylayouts.h"
#include <string.h> // for memcpy()
#include "avr/pgmspace.h" // for PROGMEM, DMAMEM, FASTRUN
#include "debug/printf.h"
#include "core_pins.h"

#ifdef KEYBOARD_INTERFACE // defined by usb_dev.h -> usb_desc.h

// which modifier keys are currently pressed
// 1=left ctrl,	   2=left shift,   4=left alt,	  8=left gui
// 16=right ctrl, 32=right shift, 64=right alt, 128=right gui
uint8_t keyboard_modifier_keys=0;

// which keys are currently pressed, up to 6 keys may be down at once
uint8_t keyboard_keys[6]={0,0,0,0,0,0};

#ifdef KEYMEDIA_INTERFACE
uint16_t keymedia_consumer_keys[4];
uint8_t keymedia_system_keys[3];
#endif

// protocol setting from the host.  We use exactly the same report
// either way, so this variable only stores the setting since we
// are required to be able to report which setting is in use.
uint8_t keyboard_protocol=1;

// the idle configuration, how often we send the report to the
// host (ms * 4) even when it hasn't changed
uint8_t keyboard_idle_config=125;

// count until idle timeout
uint8_t keyboard_idle_count=0;

// 1=num lock, 2=caps lock, 4=scroll lock, 8=compose, 16=kana
volatile uint8_t keyboard_leds=0;



static KEYCODE_TYPE unicode_to_keycode(uint16_t cpoint);
static void write_key(KEYCODE_TYPE keycode);
static uint8_t keycode_to_modifier(KEYCODE_TYPE keycode);
static uint8_t keycode_to_key(KEYCODE_TYPE keycode);
static void usb_keyboard_press_key(uint8_t key, uint8_t modifier);
static void usb_keyboard_release_key(uint8_t key, uint8_t modifier);
#ifdef DEADKEYS_MASK
static KEYCODE_TYPE deadkey_to_keycode(KEYCODE_TYPE keycode);
#endif
#ifdef KEYMEDIA_INTERFACE
static void usb_keymedia_press_consumer_key(uint16_t key);
static void usb_keymedia_release_consumer_key(uint16_t key);
static void usb_keymedia_press_system_key(uint8_t key);
static void usb_keymedia_release_system_key(uint8_t key);
static int usb_keymedia_send(void);
#endif


#define TX_NUM     12
#define TX_BUFSIZE 32
static transfer_t tx_transfer[TX_NUM] __attribute__ ((used, aligned(32)));
DMAMEM static uint8_t txbuffer[TX_NUM * TX_BUFSIZE] __attribute__ ((aligned(32)));
static uint8_t tx_head=0;
#if KEYBOARD_SIZE > TX_BUFSIZE
#error "Internal error, transmit buffer size is too small for keyboard endpoint"
#endif
#if defined(KEYMEDIA_INTERFACE) && KEYMEDIA_SIZE > TX_BUFSIZE
#error "Internal error, transmit buffer size is too small for media keys endpoint"
#endif


void usb_keyboard_configure(void)
{
	memset(tx_transfer, 0, sizeof(tx_transfer));
	tx_head = 0;
	usb_config_tx(KEYBOARD_ENDPOINT, KEYBOARD_SIZE, 0, NULL);  // normal keys use 8 byte packet
#ifdef KEYMEDIA_INTERFACE
	usb_config_tx(KEYMEDIA_ENDPOINT, KEYMEDIA_SIZE, 0, NULL);  // media keys use 8 byte packet
#endif
}


// Step #1, decode UTF8 to Unicode code points
//
void usb_keyboard_write(uint8_t c)
{
	static int utf8_state=0;
	static uint16_t unicode_wchar=0;

	if (c < 0x80) {
		// single byte encoded, 0x00 to 0x7F
		utf8_state = 0;
		usb_keyboard_write_unicode(c);
	} else if (c < 0xC0) {
		// 2nd, 3rd or 4th byte, 0x80 to 0xBF
		c &= 0x3F;
		if (utf8_state == 1) {
			utf8_state = 0;
			usb_keyboard_write_unicode(unicode_wchar | c);
		} else if (utf8_state == 2) {
			unicode_wchar |= ((uint16_t)c << 6);
			utf8_state = 1;
		}
	} else if (c < 0xE0) {
		// begin 2 byte sequence, 0xC2 to 0xDF
		// or illegal 2 byte sequence, 0xC0 to 0xC1
		unicode_wchar = (uint16_t)(c & 0x1F) << 6;
		utf8_state = 1;
	} else if (c < 0xF0) {
		// begin 3 byte sequence, 0xE0 to 0xEF
		unicode_wchar = (uint16_t)(c & 0x0F) << 12;
		utf8_state = 2;
	} else {
		// begin 4 byte sequence (not supported), 0xF0 to 0xF4
		// or illegal, 0xF5 to 0xFF
		utf8_state = 255;
	}
}


// Step #2: translate Unicode code point to keystroke sequence
//
static KEYCODE_TYPE unicode_to_keycode(uint16_t cpoint)
{
	// Unicode code points beyond U+FFFF are not supported
	// technically this input should probably be called UCS-2
	if (cpoint < 32) {
		if (cpoint == 10) return KEY_ENTER & KEYCODE_MASK;
		if (cpoint == 11) return KEY_TAB & KEYCODE_MASK;
		return 0;
	}
	if (cpoint < 128) {
		return keycodes_ascii[cpoint - 0x20];
	}
	#ifdef ISO_8859_1_A0
	if (cpoint >= 0xA0 && cpoint < 0x100) {
		return keycodes_iso_8859_1[cpoint - 0xA0];
	}
	#endif
	//#ifdef UNICODE_20AC
	//if (cpoint == 0x20AC) return UNICODE_20AC & 0x3FFF;
	//#endif
	#ifdef KEYCODE_EXTRA00
	if (cpoint == UNICODE_EXTRA00) return (KEYCODE_EXTRA00) & 0x3FFF;
	#endif
	#ifdef KEYCODE_EXTRA01
	if (cpoint == UNICODE_EXTRA01) return (KEYCODE_EXTRA01) & 0x3FFF;
	#endif
	#ifdef KEYCODE_EXTRA02
	if (cpoint == UNICODE_EXTRA02) return (KEYCODE_EXTRA02) & 0x3FFF;
	#endif
	#ifdef KEYCODE_EXTRA03
	if (cpoint == UNICODE_EXTRA03) return (KEYCODE_EXTRA03) & 0x3FFF;
	#endif
	#ifdef KEYCODE_EXTRA04
	if (cpoint == UNICODE_EXTRA04) return (KEYCODE_EXTRA04) & 0x3FFF;
	#endif
	#ifdef KEYCODE_EXTRA05
	if (cpoint == UNICODE_EXTRA05) return (KEYCODE_EXTRA05) & 0x3FFF;
	#endif
	#ifdef KEYCODE_EXTRA06
	if (cpoint == UNICODE_EXTRA06) return (KEYCODE_EXTRA06) & 0x3FFF;
	#endif
	#ifdef KEYCODE_EXTRA07
	if (cpoint == UNICODE_EXTRA07) return (KEYCODE_EXTRA07) & 0x3FFF;
	#endif
	#ifdef KEYCODE_EXTRA08
	if (cpoint == UNICODE_EXTRA08) return (KEYCODE_EXTRA08) & 0x3FFF;
	#endif
	#ifdef KEYCODE_EXTRA09
	if (cpoint == UNICODE_EXTRA09) return (KEYCODE_EXTRA09) & 0x3FFF;
	#endif
	#ifdef KEYCODE_EXTRA0A
	if (cpoint == UNICODE_EXTRA0A) return (KEYCODE_EXTRA0A) & 0x3FFF;
	#endif
	return 0;
}

// Step #3: execute keystroke sequence
//
#ifdef DEADKEYS_MASK
static KEYCODE_TYPE deadkey_to_keycode(KEYCODE_TYPE keycode)
{
	keycode &= DEADKEYS_MASK;
	if (keycode == 0) return 0;
	#ifdef ACUTE_ACCENT_BITS
	if (keycode == ACUTE_ACCENT_BITS) return DEADKEY_ACUTE_ACCENT;
	#endif
	#ifdef CEDILLA_BITS
	if (keycode == CEDILLA_BITS) return DEADKEY_CEDILLA;
	#endif
	#ifdef CIRCUMFLEX_BITS
	if (keycode == CIRCUMFLEX_BITS) return DEADKEY_CIRCUMFLEX;
	#endif
	#ifdef DIAERESIS_BITS
	if (keycode == DIAERESIS_BITS) return DEADKEY_DIAERESIS;
	#endif
	#ifdef GRAVE_ACCENT_BITS
	if (keycode == GRAVE_ACCENT_BITS) return DEADKEY_GRAVE_ACCENT;
	#endif
	#ifdef TILDE_BITS
	if (keycode == TILDE_BITS) return DEADKEY_TILDE;
	#endif
	#ifdef RING_ABOVE_BITS
	if (keycode == RING_ABOVE_BITS) return DEADKEY_RING_ABOVE;
	#endif
	#ifdef DEGREE_SIGN_BITS
	if (keycode == DEGREE_SIGN_BITS) return DEADKEY_DEGREE_SIGN;
	#endif
	#ifdef CARON_BITS
	if (keycode == CARON_BITS) return DEADKEY_CARON;
	#endif
	#ifdef BREVE_BITS
	if (keycode == BREVE_BITS) return DEADKEY_BREVE;
	#endif
	#ifdef OGONEK_BITS
	if (keycode == OGONEK_BITS) return DEADKEY_OGONEK;
	#endif
	#ifdef DOT_ABOVE_BITS
	if (keycode == DOT_ABOVE_BITS) return DEADKEY_DOT_ABOVE;
	#endif
	#ifdef DOUBLE_ACUTE_BITS
	if (keycode == DOUBLE_ACUTE_BITS) return DEADKEY_DOUBLE_ACUTE;
	#endif
	return 0;
}
#endif

void usb_keyboard_write_unicode(uint16_t cpoint)
{
	KEYCODE_TYPE keycode;

	keycode = unicode_to_keycode(cpoint);
	if (keycode) {
		#ifdef DEADKEYS_MASK
		KEYCODE_TYPE deadkeycode = deadkey_to_keycode(keycode);
		if (deadkeycode) write_key(deadkeycode);
		#endif
		write_key(keycode);
	}
}


// Step #4: do each keystroke
//
static void write_key(KEYCODE_TYPE keycode)
{
/*
	uint8_t key, modifier=0;

	#ifdef SHIFT_MASK
	if (keycode & SHIFT_MASK) modifier |= MODIFIERKEY_SHIFT;
	#endif
	#ifdef ALTGR_MASK
	if (keycode & ALTGR_MASK) modifier |= MODIFIERKEY_RIGHT_ALT;
	#endif
	#ifdef RCTRL_MASK
	if (keycode & RCTRL_MASK) modifier |= MODIFIERKEY_RIGHT_CTRL;
	#endif
	key = keycode & 0x3F;
	#ifdef KEY_NON_US_100
	if (key == KEY_NON_US_100) key = 100;
	#endif
	usb_keyboard_press(key, modifier);
*/
	usb_keyboard_press(keycode_to_key(keycode), keycode_to_modifier(keycode));
}

static uint8_t keycode_to_modifier(KEYCODE_TYPE keycode)
{
	uint8_t modifier=0;

	#ifdef SHIFT_MASK
	if (keycode & SHIFT_MASK) modifier |= MODIFIERKEY_SHIFT;
	#endif
	#ifdef ALTGR_MASK
	if (keycode & ALTGR_MASK) modifier |= MODIFIERKEY_RIGHT_ALT;
	#endif
	#ifdef RCTRL_MASK
	if (keycode & RCTRL_MASK) modifier |= MODIFIERKEY_RIGHT_CTRL;
	#endif
	return modifier;
}

static uint8_t keycode_to_key(KEYCODE_TYPE keycode)
{
	uint8_t key = keycode & 0x3F;
	#ifdef KEY_NON_US_100
	if (key == KEY_NON_US_100) key = 100;
	#endif
	return key;
}


// Input can be:
//     32 - 127     ASCII direct (U+0020 to U+007F) <-- uses layout
//    128 - 0xC1FF  Unicode direct (U+0080 to U+C1FF) <-- uses layout
// 0xC200 - 0xDFFF  Unicode UTF8 packed (U+0080 to U+07FF) <-- uses layout
// 0xE000 - 0xE0FF  Modifier key (bitmap, 8 keys, shift/ctrl/alt/gui)
// 0xE200 - 0xE2FF  System key (HID usage code, within usage page 1)
// 0xE400 - 0xE7FF  Media/Consumer key (HID usage code, within usage page 12)
// 0xF000 - 0xFFFF  Normal key (HID usage code, within usage page 7)

void usb_keyboard_press_keycode(uint16_t n)
{
	uint8_t key, mod, msb, modrestore=0;
	KEYCODE_TYPE keycode;
	#ifdef DEADKEYS_MASK
	KEYCODE_TYPE deadkeycode;
	#endif

	msb = n >> 8;

	if (msb >= 0xC2) {
		if (msb <= 0xDF) {
			n = (n & 0x3F) | ((uint16_t)(msb & 0x1F) << 6);
		} else if (msb == 0xF0) {
			usb_keyboard_press_key(n, 0);
			return;
		} else if (msb == 0xE0) {
			usb_keyboard_press_key(0, n);
			return;
#ifdef KEYMEDIA_INTERFACE
		} else if (msb == 0xE2) {
			usb_keymedia_press_system_key(n);
			return;
		} else if (msb >= 0xE4 && msb <= 0xE7) {
			usb_keymedia_press_consumer_key(n & 0x3FF);
			return;
#endif
		} else {
			return;
		}
	}
	keycode = unicode_to_keycode(n);
	if (!keycode) return;
#ifdef DEADKEYS_MASK
	deadkeycode = deadkey_to_keycode(keycode);
	if (deadkeycode) {
		modrestore = keyboard_modifier_keys;
		if (modrestore) {
			keyboard_modifier_keys = 0;
			usb_keyboard_send();
		}
		// TODO: test if operating systems recognize
		// deadkey sequences when other keys are held
		mod = keycode_to_modifier(deadkeycode);
		key = keycode_to_key(deadkeycode);
		usb_keyboard_press_key(key, mod);
		usb_keyboard_release_key(key, mod);
	}
#endif
	mod = keycode_to_modifier(keycode);
	key = keycode_to_key(keycode);
	usb_keyboard_press_key(key, mod | modrestore);
}


void usb_keyboard_release_keycode(uint16_t n)
{
	uint8_t key, mod, msb;

	msb = n >> 8;
	if (msb >= 0xC2) {
		if (msb <= 0xDF) {
			n = (n & 0x3F) | ((uint16_t)(msb & 0x1F) << 6);
		} else if (msb == 0xF0) {
			usb_keyboard_release_key(n, 0);
			return;
		} else if (msb == 0xE0) {
			usb_keyboard_release_key(0, n);
			return;
#ifdef KEYMEDIA_INTERFACE
		} else if (msb == 0xE2) {
			usb_keymedia_release_system_key(n);
			return;
		} else if (msb >= 0xE4 && msb <= 0xE7) {
			usb_keymedia_release_consumer_key(n & 0x3FF);
			return;
#endif
		} else {
			return;
		}
	}
	KEYCODE_TYPE keycode = unicode_to_keycode(n);
	if (!keycode) return;
	mod = keycode_to_modifier(keycode);
	key = keycode_to_key(keycode);
	usb_keyboard_release_key(key, mod);
}


static void usb_keyboard_press_key(uint8_t key, uint8_t modifier)
{
	int i, send_required = 0;

	if (modifier) {
		if ((keyboard_modifier_keys & modifier) != modifier) {
			keyboard_modifier_keys |= modifier;
			send_required = 1;
		}
	}
	if (key) {
		for (i=0; i < 6; i++) {
			if (keyboard_keys[i] == key) goto end;
		}
		for (i=0; i < 6; i++) {
			if (keyboard_keys[i] == 0) {
				keyboard_keys[i] = key;
				send_required = 1;
				goto end;
			}
		}
	}
	end:
	if (send_required) usb_keyboard_send();
}


static void usb_keyboard_release_key(uint8_t key, uint8_t modifier)
{
	int i, send_required = 0;

	if (modifier) {
		if ((keyboard_modifier_keys & modifier) != 0) {
			keyboard_modifier_keys &= ~modifier;
			send_required = 1;
		}
	}
	if (key) {
		for (i=0; i < 6; i++) {
			if (keyboard_keys[i] == key) {
				keyboard_keys[i] = 0;
				send_required = 1;
			}
		}
	}
	if (send_required) usb_keyboard_send();
}

void usb_keyboard_release_all(void)
{
	uint8_t i, anybits;

	anybits = keyboard_modifier_keys;
	keyboard_modifier_keys = 0;
	for (i=0; i < 6; i++) {
		anybits |= keyboard_keys[i];
		keyboard_keys[i] = 0;
	}
	if (anybits) usb_keyboard_send();
#ifdef KEYMEDIA_INTERFACE
	anybits = 0;
	for (i=0; i < 4; i++) {
		if (keymedia_consumer_keys[i] != 0) anybits = 1;
		keymedia_consumer_keys[i] = 0;
	}
	for (i=0; i < 3; i++) {
		if (keymedia_system_keys[i] != 0) anybits = 1;
		keymedia_system_keys[i] = 0;
	}
	if (anybits) usb_keymedia_send();
#endif
}


int usb_keyboard_press(uint8_t key, uint8_t modifier)
{
	int r;
	keyboard_modifier_keys = modifier;
	keyboard_keys[0] = key;
	keyboard_keys[1] = 0;
	keyboard_keys[2] = 0;
	keyboard_keys[3] = 0;
	keyboard_keys[4] = 0;
	keyboard_keys[5] = 0;
	r = usb_keyboard_send();
	if (r) return r;
	keyboard_modifier_keys = 0;
	keyboard_keys[0] = 0;
	return usb_keyboard_send();
}


static uint8_t transmit_previous_timeout=0;

// When the PC isn't listening, how long do we wait before discarding data?
#define TX_TIMEOUT_MSEC 50

static int usb_keyboard_transmit(int endpoint, const uint8_t *data, uint32_t len)
{
	if (!usb_configuration) return -1;
	uint32_t head = tx_head;
	transfer_t *xfer = tx_transfer + head;
	uint32_t wait_begin_at = systick_millis_count;
	while (1) {
		uint32_t status = usb_transfer_status(xfer);
		if (!(status & 0x80)) {
			if (status & 0x68) {
				// TODO: what if status has errors???
				printf("ERROR status = %x, i=%d, ms=%u\n",
					status, tx_head, systick_millis_count);
			}
			transmit_previous_timeout = 0;
			break;
		}
		if (transmit_previous_timeout) return -1;
		if (systick_millis_count - wait_begin_at > TX_TIMEOUT_MSEC) {
			// waited too long, assume the USB host isn't listening
			transmit_previous_timeout = 1;
			return -1;
		}
		if (!usb_configuration) return -1;
		yield();
	}
	uint8_t *buffer = txbuffer + head * TX_BUFSIZE;
	memcpy(buffer, data, len);
	usb_prepare_transfer(xfer, buffer, len, 0);
	arm_dcache_flush_delete(buffer, TX_BUFSIZE);
	usb_transmit(endpoint, xfer);
	if (++head >= TX_NUM) head = 0;
	tx_head = head;
	return 0;
}


// send the contents of keyboard_keys and keyboard_modifier_keys
int usb_keyboard_send(void)
{
	uint8_t buffer[KEYBOARD_SIZE];
	buffer[0] = keyboard_modifier_keys;
	buffer[1] = 0;
	buffer[2] = keyboard_keys[0];
	buffer[3] = keyboard_keys[1];
	buffer[4] = keyboard_keys[2];
	buffer[5] = keyboard_keys[3];
	buffer[6] = keyboard_keys[4];
	buffer[7] = keyboard_keys[5];
	return usb_keyboard_transmit(KEYBOARD_ENDPOINT, buffer, KEYBOARD_SIZE);
}


#ifdef KEYMEDIA_INTERFACE

static void usb_keymedia_press_consumer_key(uint16_t key)
{
	int i;

	if (key == 0) return;
	for (i=0; i < 4; i++) {
		if (keymedia_consumer_keys[i] == key) return;
	}
	for (i=0; i < 4; i++) {
		if (keymedia_consumer_keys[i] == 0) {
			keymedia_consumer_keys[i] = key;
			usb_keymedia_send();
			return;
		}
	}
}

static void usb_keymedia_release_consumer_key(uint16_t key)
{
	int i;

	if (key == 0) return;
	for (i=0; i < 4; i++) {
		if (keymedia_consumer_keys[i] == key) {
			keymedia_consumer_keys[i] = 0;
			usb_keymedia_send();
			return;
		}
	}
}

static void usb_keymedia_press_system_key(uint8_t key)
{
	int i;

	if (key == 0) return;
	for (i=0; i < 3; i++) {
		if (keymedia_system_keys[i] == key) return;
	}
	for (i=0; i < 3; i++) {
		if (keymedia_system_keys[i] == 0) {
			keymedia_system_keys[i] = key;
			usb_keymedia_send();
			return;
		}
	}
}

static void usb_keymedia_release_system_key(uint8_t key)
{
	int i;

	if (key == 0) return;
	for (i=0; i < 3; i++) {
		if (keymedia_system_keys[i] == key) {
			keymedia_system_keys[i] = 0;
			usb_keymedia_send();
			return;
		}
	}
}

void usb_keymedia_release_all(void)
{
	uint8_t i, anybits;

	anybits = 0;
	for (i=0; i < 4; i++) {
		if (keymedia_consumer_keys[i] != 0) anybits = 1;
		keymedia_consumer_keys[i] = 0;
	}
	for (i=0; i < 3; i++) {
		if (keymedia_system_keys[i] != 0) anybits = 1;
		keymedia_system_keys[i] = 0;
	}
	if (anybits) usb_keymedia_send();
}

// send the contents of keyboard_keys and keyboard_modifier_keys
static int usb_keymedia_send(void)
{
	uint8_t buffer[8];
	const uint16_t *consumer = keymedia_consumer_keys;
	// 44444444 44333333 33332222 22222211 11111111
	// 98765432 10987654 32109876 54321098 76543210
	buffer[0] = consumer[0];
	buffer[1] = (consumer[1] << 2) | ((consumer[0] >> 8) & 0x03);
	buffer[2] = (consumer[2] << 4) | ((consumer[1] >> 6) & 0x0F);
	buffer[3] = (consumer[3] << 6) | ((consumer[2] >> 4) & 0x3F);
	buffer[4] = consumer[3] >> 2;
	buffer[5] = keymedia_system_keys[0];
	buffer[6] = keymedia_system_keys[1];
	buffer[7] = keymedia_system_keys[2];
	return usb_keyboard_transmit(KEYMEDIA_ENDPOINT, buffer, KEYMEDIA_SIZE);
}

#endif // KEYMEDIA_INTERFACE

#endif // KEYBOARD_INTERFACE
