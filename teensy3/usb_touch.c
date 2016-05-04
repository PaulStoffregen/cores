/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2016 PJRC.COM, LLC.
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
#include "core_pins.h" // for yield()
#include "HardwareSerial.h"
#include <string.h> // for memcpy()

#ifdef MULTITOUCH_INTERFACE // defined by usb_dev.h -> usb_desc.h
#if F_CPU >= 20000000

static uint8_t  prev_id=0;
static uint8_t  pressure[MULTITOUCH_FINGERS];
static uint8_t  contactid[MULTITOUCH_FINGERS];
static uint16_t xpos[MULTITOUCH_FINGERS];
static uint16_t ypos[MULTITOUCH_FINGERS];

static uint8_t  scan_state=0;
static uint8_t  scan_remain=0; // number of finger to left to transmit on this scan
static uint8_t  scan_index=0;  // index of next (possible) finger to transmit
static uint8_t  scan_pressure[MULTITOUCH_FINGERS];
static uint16_t scan_timestamp;


void usb_touchscreen_press(uint8_t finger, uint32_t x, uint32_t y, uint32_t press)
{
	uint8_t id;

	if (finger >= MULTITOUCH_FINGERS) return;
	press >>= 1;
	if (press > 127) press = 127;
	if (x > 32767) x = 32767;
	if (y > 32767) y = 32767;
	if (pressure[finger] == 0) {
		id = prev_id + 1;
		if (id == 0) id = 1;
		prev_id = id;
		contactid[finger] = id;
	}
	xpos[finger] = x;
	ypos[finger] = y;
	pressure[finger] = (press << 1) | 1;
}

void usb_touchscreen_release(uint8_t finger)
{
	if (finger >= MULTITOUCH_FINGERS) return;
	pressure[finger] = 0;
}

// touch report
//  0: on/off + pressure
//  1: contact id
//  2: X lsb
//  3: X msb
//  4: Y lsb
//  5: Y msb
//  6: scan time lsb
//  7: scan time msb
//  8: contact count

static int usb_touchscreen_transmit(int index, int count)
{
	usb_packet_t *tx_packet;
	tx_packet = usb_malloc();
	if (tx_packet == NULL) return 0;
	*(tx_packet->buf + 0) = pressure[index];
	*(tx_packet->buf + 1) = contactid[index];
	*(tx_packet->buf + 2) = xpos[index];
	*(tx_packet->buf + 3) = xpos[index] >> 8;
	*(tx_packet->buf + 4) = ypos[index];
	*(tx_packet->buf + 5) = ypos[index] >> 8;
	*(tx_packet->buf + 6) = scan_timestamp;
	*(tx_packet->buf + 7) = scan_timestamp >> 8;
	*(tx_packet->buf + 8) = count;
	tx_packet->len = 9;
	usb_tx(MULTITOUCH_ENDPOINT, tx_packet);
	return 1;
}


// Called by the start-of-frame interrupt.
//
void usb_touchscreen_update_callback(void)
{
	int i, r, count=0;

	if (scan_state == 0) {
		if (usb_tx_packet_count(MULTITOUCH_ENDPOINT) > 1) {
			// wait to begin another scan if if more than
			// one prior packet remains to transmit
			return;
		}
		// copy the pressure data - whether each finger is
		// in contact at the moment of this "scan"
		memcpy(scan_pressure, pressure, MULTITOUCH_FINGERS);
		for (i=0; i < MULTITOUCH_FINGERS; i++) {
			if (scan_pressure[i] > 0) count++;
		}
		if (count > 0) {
			scan_remain = count;
			scan_index = 0;
			scan_timestamp = millis() * 10;
		} else {
			scan_remain = 0;
		}
	}
	if (scan_remain > 0) {
		for (i = scan_index; i < MULTITOUCH_FINGERS; i++) {
			if (scan_pressure[i] > 0) break;
		}
		r = usb_touchscreen_transmit(i, (scan_state == 0) ? scan_remain : 0);
		if (!r) return;
		scan_index = i + 1;
		scan_remain--;
	}
	if (++scan_state >= MULTITOUCH_ENDPOINT) {
		scan_state = 0;
	}
}


#endif // F_CPU
#endif // MULTITOUCH_INTERFACE
