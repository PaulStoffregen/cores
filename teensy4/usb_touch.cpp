/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2019 PJRC.COM, LLC.
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
#include "usb_touch.h"
#include "core_pins.h" // for millis()
#include <string.h> // for memcpy()
#include "avr/pgmspace.h" // for PROGMEM, DMAMEM, FASTRUN
#include "debug/printf.h"
#include "core_pins.h"


#ifdef MULTITOUCH_INTERFACE // defined by usb_dev.h -> usb_desc.h

static uint8_t  prev_id=0;
static uint8_t  scan_index=0;
static uint8_t  scan_count=0;
static uint8_t  contactid[MULTITOUCH_FINGERS];
static uint8_t  pressure[MULTITOUCH_FINGERS];
static uint16_t xpos[MULTITOUCH_FINGERS];
static uint16_t ypos[MULTITOUCH_FINGERS];
static uint16_t scan_timestamp;

#define TX_BUFSIZE 32
static transfer_t tx_transfer __attribute__ ((used, aligned(32)));
DMAMEM static uint8_t txbuffer[TX_BUFSIZE] __attribute__ ((aligned(32)));
extern volatile uint8_t usb_high_speed;
#if MULTITOUCH_SIZE > TX_BUFSIZE
#error "Internal error, transmit buffer size is too small for touchscreen endpoint"
#endif


void usb_touchscreen_configure(void)
{
	memset(&tx_transfer, 0, sizeof(tx_transfer));
	usb_config_tx(MULTITOUCH_ENDPOINT, MULTITOUCH_SIZE, 0, NULL);
	usb_start_sof_interrupts(MULTITOUCH_INTERFACE);
}


void usb_touchscreen_press(uint8_t finger, uint32_t x, uint32_t y, uint32_t press)
{
	if (finger >= MULTITOUCH_FINGERS) return;
	if (press > 255) press = 255;
	if (x > 32767) x = 32767;
	if (y > 32767) y = 32767;
	__disable_irq();
	if (pressure[finger] == 0 && press > 0) {
		// Begin a new finger touch, assign a
		// new Contact Identifier (usage 0x51)
		uint8_t id = prev_id + 1;
		if (id == 0 || id > 127) id = 1;
		prev_id = id;
		contactid[finger] = (id << 1) | 1;
	}
	xpos[finger] = x;
	ypos[finger] = y;
	pressure[finger] = press;
	__enable_irq();
}

// User should allow at least 12 ms after release before starting a
// new touch with press, in case the host's driver does not properly
// parse a change in contact identifier to mean a new touch.

void usb_touchscreen_release(uint8_t finger)
{
	if (finger >= MULTITOUCH_FINGERS) return;
	pressure[finger] = 0;
}

// touch report
//  0: contact id + on/off
//  1: pressure
//  2: X lsb
//  3: X msb
//  4: Y lsb
//  5: Y msb
//  6: scan time lsb
//  7: scan time msb
//  8: contact count

// Called by the start-of-frame interrupt.
//
void usb_touchscreen_update_callback(void)
{
	static uint8_t microframe_count=0;
	uint8_t contact_count = 0;

	if (usb_high_speed) {
		// if 480 speed, run only every 8th micro-frame
		if (++microframe_count < 8) return;
		microframe_count = 0;
	}

	// do nothing if previous packet not yet sent
	uint32_t status = usb_transfer_status(&tx_transfer);
	if ((status & 0x80)) {
		return;
	}
	if (status & 0x68) {
		// TODO: what if status has errors???
	}

	if (scan_index == 0) {
		scan_timestamp = millis() * 10;
		scan_count = 0;
		// Get the contact count (usage 0x54)
		// Only set this value on first contact
		// Subsequent concurrent contacts should report 0
		for (uint8_t i = 0; i < MULTITOUCH_FINGERS; i++) {
			if (contactid[i]) contact_count++;
		}
	}
	while (scan_index < MULTITOUCH_FINGERS) {
		uint32_t press = pressure[scan_index];
		uint32_t id = contactid[scan_index];
		if (id) {
			if (press == 0) {
				// End a finger touch.  One final packet sent
				// with same Contact Identifier (usage 0x51)
				// and Tip Switch (usage 0x42) = zero
				id &= 0xFE;
				contactid[scan_index] = 0;
			}
			//uint8_t buffer[MULTITOUCH_SIZE]; // MULTITOUCH_SIZE = 8
			txbuffer[0] = id;
			txbuffer[1] = press;
			txbuffer[2] = xpos[scan_index];
			txbuffer[3] = xpos[scan_index] >> 8;
			txbuffer[4] = ypos[scan_index];
			txbuffer[5] = ypos[scan_index] >> 8;
			txbuffer[6] = scan_timestamp;
			txbuffer[7] = scan_timestamp >> 8;
			txbuffer[8] = contact_count;
			//delayNanoseconds(30);
			usb_prepare_transfer(&tx_transfer, txbuffer, MULTITOUCH_SIZE, 0);
			arm_dcache_flush_delete(txbuffer, TX_BUFSIZE);
			usb_transmit(MULTITOUCH_ENDPOINT, &tx_transfer);
			scan_index++;
			return;
		}
		scan_index++;
	}
	if (++scan_count >= MULTITOUCH_FINGERS) {
		// when done early, wait to restart another scan
		scan_index = 0;
	}
}


#endif // MULTITOUCH_INTERFACE
