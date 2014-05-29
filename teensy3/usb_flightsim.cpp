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

#include "usb_dev.h"
#include "usb_flightsim.h"
#include "core_pins.h" // for yield(), millis()
#include <string.h>    // for memcpy()

#ifdef FLIGHTSIM_INTERFACE // defined by usb_dev.h -> usb_desc.h

FlightSimCommand * FlightSimCommand::first = NULL;
FlightSimCommand * FlightSimCommand::last = NULL;
FlightSimInteger * FlightSimInteger::first = NULL;
FlightSimInteger * FlightSimInteger::last = NULL;
FlightSimFloat * FlightSimFloat::first = NULL;
FlightSimFloat * FlightSimFloat::last = NULL;

uint8_t FlightSimClass::enabled = 0;
uint8_t FlightSimClass::request_id_messages = 0;
unsigned long FlightSimClass::frameCount = 0;
elapsedMillis FlightSimClass::enableTimeout;

static unsigned int unassigned_id = 1;  // TODO: move into FlightSimClass


FlightSimCommand::FlightSimCommand()
{
	id = unassigned_id++;
	if (!first) {
		first = this;
	} else {
		last->next = this;
	}
	last = this;
	name = NULL;
	next = NULL;
	FlightSimClass::request_id_messages = 1;
}

void FlightSimCommand::identify(void)
{
	uint8_t len, buf[6];

	if (!FlightSim.enabled || !name) return;
	len = strlen((const char *)name);
	buf[0] = len + 6;
	buf[1] = 1;
	buf[2] = id;
	buf[3] = id >> 8;
	buf[4] = 0;
	buf[5] = 0;
	FlightSimClass::xmit(buf, 6, name, len);
}

void FlightSimCommand::sendcmd(uint8_t n)
{
	uint8_t buf[4];

	if (!FlightSim.enabled || !name) return;
	buf[0] = 4;
	buf[1] = n;
	buf[2] = id;
	buf[3] = id >> 8;
	FlightSimClass::xmit(buf, 4, NULL, 0);
}


FlightSimInteger::FlightSimInteger()
{
	id = unassigned_id++;
	if (!first) {
		first = this;
	} else {
		last->next = this;
	}
	last = this;
	name = NULL;
	next = NULL;
	value = 0;
	change_callback = NULL;
	FlightSimClass::request_id_messages = 1;
}

void FlightSimInteger::identify(void)
{
	uint8_t len, buf[6];

	if (!FlightSim.enabled || !name) return;
	len = strlen((const char *)name);
	buf[0] = len + 6;
	buf[1] = 1;
	buf[2] = id;
	buf[3] = id >> 8;
	buf[4] = 1;
	buf[5] = 0;
	FlightSimClass::xmit(buf, 6, name, len);
}

void FlightSimInteger::write(long val)
{
	uint8_t buf[6];

	value = val;
	if (!FlightSim.enabled || !name) return; // TODO: mark as dirty
	buf[0] = 10;
	buf[1] = 2;
	buf[2] = id;
	buf[3] = id >> 8;
	buf[4] = 1;
	buf[5] = 0;
	FlightSimClass::xmit(buf, 6, (uint8_t *)&value, 4);
}

void FlightSimInteger::update(long val)
{
	value = val;
	if (change_callback) (*change_callback)(val);
}

FlightSimInteger * FlightSimInteger::find(unsigned int n)
{
	for (FlightSimInteger *p = first; p; p = p->next) {
		if (p->id == n) return p;
	}
	return NULL;
}




FlightSimFloat::FlightSimFloat()
{
	id = unassigned_id++;
	if (!first) {
		first = this;
	} else {
		last->next = this;
	}
	last = this;
	name = NULL;
	next = NULL;
	value = 0;
	change_callback = NULL;
	FlightSimClass::request_id_messages = 1;
}

void FlightSimFloat::identify(void)
{
	uint8_t len, buf[6];

	if (!FlightSim.enabled || !name) return;
	len = strlen((const char *)name);
	buf[0] = len + 6;
	buf[1] = 1;
	buf[2] = id;
	buf[3] = id >> 8;
	buf[4] = 2;
	buf[5] = 0;
	FlightSimClass::xmit(buf, 6, name, len);
}

void FlightSimFloat::write(float val)
{
	uint8_t buf[6];

	value = val;
	if (!FlightSim.enabled || !name) return; // TODO: mark as dirty
	buf[0] = 10;
	buf[1] = 2;
	buf[2] = id;
	buf[3] = id >> 8;
	buf[4] = 2;
	buf[5] = 0;
	FlightSimClass::xmit(buf, 6, (uint8_t *)&value, 4);
}

void FlightSimFloat::update(float val)
{
	value = val;
	if (change_callback) (*change_callback)(val);
}

FlightSimFloat * FlightSimFloat::find(unsigned int n)
{
	for (FlightSimFloat *p = first; p; p = p->next) {
		if (p->id == n) return p;
	}
	return NULL;
}






FlightSimClass::FlightSimClass()
{
}

void FlightSimClass::update(void)
{
	uint8_t len, maxlen, type, *p, *end;
	usb_packet_t *rx_packet;
	uint16_t id;

	while (1) {
		if (!usb_configuration) break;
		rx_packet = usb_rx(FLIGHTSIM_RX_ENDPOINT);
		if (!rx_packet) break;
		p = rx_packet->buf;
		end = p + 64;
		maxlen = 64;
		do {
			len = p[0];
			if (len < 2 || len > maxlen) break;
			switch (p[1]) {
			  case 0x02: // write data
				if (len < 10) break;
				id = p[2] | (p[3] << 8);
				type = p[4];
				if (type == 1) {
					FlightSimInteger *item = FlightSimInteger::find(id);
					if (!item) break;
					item->update(*(long *)(p + 6));
				} else if (type == 2) {
					FlightSimFloat *item = FlightSimFloat::find(id);
					if (!item) break;
					item->update(*(float *)(p + 6));
				}
				break;
			  case 0x03: // enable/disable
				if (len < 4) break;
				switch (p[2]) {
				  case 1:
					request_id_messages = 1;
				  case 2:
					enable();
					frameCount++;
					break;
				  case 3:
					disable();
				}
			}
			p += len;
			maxlen -= len;
		} while (p < end);
		usb_free(rx_packet);
	}
	if (enabled && request_id_messages) {
		request_id_messages = 0;
		for (FlightSimCommand *p = FlightSimCommand::first; p; p = p->next) {
			p->identify();
		}
		for (FlightSimInteger *p = FlightSimInteger::first; p; p = p->next) {
			p->identify();
			// TODO: send any dirty data
		}
		for (FlightSimFloat *p = FlightSimFloat::first; p; p = p->next) {
			p->identify();
			// TODO: send any dirty data
		}
	}
}


bool FlightSimClass::isEnabled(void)
{
        if (!usb_configuration) return false;
        if (!enabled) return false;
	if (enableTimeout > 1500) return false;
        return true;
}


// Maximum number of transmit packets to queue so we don't starve other endpoints for memory
#define TX_PACKET_LIMIT 8

static usb_packet_t *tx_packet=NULL;
static volatile uint8_t tx_noautoflush=0;

void FlightSimClass::xmit(const void *p1, uint8_t n1, const void *p2, uint8_t n2)
{
	uint8_t total;

	total = n1 + n2;
	if (total > FLIGHTSIM_TX_SIZE) return;
	if (!enabled || !usb_configuration) return;
	tx_noautoflush = 1;
	if (tx_packet) {
		if (total <= FLIGHTSIM_TX_SIZE - tx_packet->index) goto send;
		for (int i = tx_packet->index; i < FLIGHTSIM_TX_SIZE; i++) {
			tx_packet->buf[i] = 0;
		}
		tx_packet->len = FLIGHTSIM_TX_SIZE;
		usb_tx(FLIGHTSIM_TX_ENDPOINT, tx_packet);
		tx_packet = NULL;
	}
	while (1) {
		if (usb_tx_packet_count(FLIGHTSIM_TX_ENDPOINT) < TX_PACKET_LIMIT) {
			tx_packet = usb_malloc();
			if (tx_packet) break;
		}
		if (!enabled || !usb_configuration) {
			tx_noautoflush = 0;
			return;
		}
		tx_noautoflush = 0;
		yield();
		tx_noautoflush = 1;
	}
send:
	memcpy(tx_packet->buf + tx_packet->index, p1, n1);
	tx_packet->index += n1;
	if (n2 > 0) {
		memcpy(tx_packet->buf + tx_packet->index, p2, n2);
		tx_packet->index += n2;
	}
	if (tx_packet->index >= FLIGHTSIM_TX_SIZE) {
		tx_packet->len = FLIGHTSIM_TX_SIZE;
		usb_tx(FLIGHTSIM_TX_ENDPOINT, tx_packet);
		tx_packet = NULL;
	}
	tx_noautoflush = 0;
}


extern "C" {
void usb_flightsim_flush_callback(void)
{
	if (tx_noautoflush || !tx_packet || tx_packet->index == 0) return;
	for (int i=tx_packet->index; i < FLIGHTSIM_TX_ENDPOINT; i++) {
		tx_packet->buf[i] = 0;
	}
	tx_packet->len = FLIGHTSIM_TX_SIZE;
	usb_tx(FLIGHTSIM_TX_ENDPOINT, tx_packet);
	tx_packet = NULL;
}
}

#endif // FLIGHTSIM_INTERFACE
