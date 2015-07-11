/* USB API for Teensy USB Development Board
 * http://www.pjrc.com/teensy/teensyduino.html
 * Copyright (c) 2012 PJRC.COM, LLC
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

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include "usb_common.h"
#include "usb_private.h"
#include "usb_api.h"
#include "wiring.h"


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
	uint16_t len;
	uint8_t buf[6];

	if (!FlightSim.enabled || !name) return;
	len = strlen_P((const char *)name);
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
	FlightSimClass::xmit(buf, 4);
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
	uint16_t len;
	uint8_t buf[6];

	if (!FlightSim.enabled || !name) return;
	len = strlen_P((const char *)name);
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
	if (change_callback) {
		if (!hasCallbackInfo) {
			(*change_callback)(val);
		} else {
			(*(void(*)(long,void*))change_callback)(val,callbackInfo);
		}
	}
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
	uint16_t len;
	uint8_t buf[6];

	if (!FlightSim.enabled || !name) return;
	len = strlen_P((const char *)name);
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
	if (change_callback) {
		if (!hasCallbackInfo) {
			(*change_callback)(val);
		} else {
			(*(void(*)(long,void*))change_callback)(val,callbackInfo);
		}
	}
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
	uint8_t len, maxlen, type, buf[64], *p;
	uint16_t id;

	while (recv(buf)) {
		p = buf;
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
		} while (p < buf + 64);
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


// receive a packet
uint8_t FlightSimClass::recv(uint8_t *buffer)
{
        uint8_t intr_state;

        // if we're not online (enumerated and configured), error
        if (!usb_configuration) return 0;
        intr_state = SREG;
        cli();
        UENUM = FLIGHTSIM_RX_ENDPOINT;
	if (!(UEINTX & (1<<RWAL))) {
        	SREG = intr_state;
		return 0;
	}
        *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX;
        *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX;
        *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX;
        *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX;

        *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX;
        *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX;
        *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX;
        *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX;

        *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX;
        *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX;
        *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX;
        *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX;

        *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX;
        *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX;
        *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX;
        *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX; *buffer++ = UEDATX;

        UEINTX = 0x6B;
        SREG = intr_state;
        return 1;
}




void FlightSimClass::xmit(const uint8_t *p1, uint8_t n1)
{
	uint8_t intr_state, avail;

	if (!enabled || !usb_configuration) return;
	intr_state = SREG;
	cli();
	UENUM = FLIGHTSIM_TX_ENDPOINT;
	avail = FLIGHTSIM_TX_SIZE - UEBCLX;
	if ((UEINTX & (1<<RWAL)) && (avail >= n1)) {
		goto send;
	} else {
		while (avail) {
			UEDATX = 0;
			avail--;
		}
		UEINTX = 0x3A;
		while (1) {
			if (UEINTX & (1<<RWAL)) break;
			SREG = intr_state;
			if (!enabled || !usb_configuration) return;
			intr_state = SREG;
			cli();
			UENUM = FLIGHTSIM_TX_ENDPOINT;
		}
	}
send:
	do {
		UEDATX = *p1++;
	} while (--n1 > 0);
	if (UEBCLX == FLIGHTSIM_TX_SIZE) UEINTX = 0x3A;
	SREG = intr_state;
}


void FlightSimClass::xmit(const uint8_t *p1, uint8_t n1, const uint8_t *p2, uint8_t n2)
{
	uint8_t intr_state, total, avail;

	total = n1 + n2;
	if (!enabled || !usb_configuration) return;
	intr_state = SREG;
	cli();
	UENUM = FLIGHTSIM_TX_ENDPOINT;
	avail = FLIGHTSIM_TX_SIZE - UEBCLX;
	if ((UEINTX & (1<<RWAL)) && (avail >= total)) {
		goto send;
	} else {
		while (avail) {
			UEDATX = 0;
			avail--;
		}
		UEINTX = 0x3A;
		while (1) {
			if (UEINTX & (1<<RWAL)) break;
			SREG = intr_state;
			if (!enabled || !usb_configuration) return;
			intr_state = SREG;
			cli();
			UENUM = FLIGHTSIM_TX_ENDPOINT;
		}
	}
send:
	do {
		UEDATX = *p1++;
	} while (--n1 > 0);
	do {
		UEDATX = *p2++;
	} while (--n2 > 0);
	if (UEBCLX == FLIGHTSIM_TX_SIZE) UEINTX = 0x3A;
	SREG = intr_state;
}


void FlightSimClass::xmit(const uint8_t *p1, uint8_t n1, const _XpRefStr_ *p2, uint16_t n2) {
	uint8_t intr_state, total, avail;
	const char * PROGMEM s2 = (const char *)p2;

	total = n1 + n2;
	if (total > FLIGHTSIM_TX_SIZE) {
		xmit_big_packet(p1, n1, p2,  n2);
		return;
	}
	if (!enabled || !usb_configuration) return;
	intr_state = SREG;
	cli();
	UENUM = FLIGHTSIM_TX_ENDPOINT;
	avail = FLIGHTSIM_TX_SIZE - UEBCLX;
	if ((UEINTX & (1<<RWAL)) && (avail >= total)) {
		goto send;
	} else {
		while (avail) {
			UEDATX = 0;
			avail--;
		}
		UEINTX = 0x3A;
		while (1) {
			if (UEINTX & (1<<RWAL)) break;
			SREG = intr_state;
			if (!enabled || !usb_configuration) return;
			intr_state = SREG;
			cli();
			UENUM = FLIGHTSIM_TX_ENDPOINT;
		}
	}
send:
	do {
		UEDATX = *p1++;
	} while (--n1 > 0);
	do {
		pgm_read_byte_postinc(UEDATX, s2);
	} while (--n2 > 0);
	if (UEBCLX == FLIGHTSIM_TX_SIZE) UEINTX = 0x3A;
	SREG = intr_state;
}

void FlightSimClass::xmit_big_packet(const uint8_t *p1, uint8_t n1, const _XpRefStr_ *p2, uint16_t n2) {
	uint8_t intr_state, avail;
	uint16_t total;

	bool part1 = true;
	const char * PROGMEM s2 = (const char *)p2;
	uint8_t packet_id = 1;

	total = n1 + n2;

	if (!enabled || !usb_configuration) return;
	intr_state = SREG;
	cli();
	UENUM = FLIGHTSIM_TX_ENDPOINT;
	avail = FLIGHTSIM_TX_SIZE - UEBCLX;

	while (total>0) {
		if (part1) {
			UEDATX = *p1++;
			part1 = (--n1 != 0);
		} else {
			pgm_read_byte_postinc(UEDATX, s2);
			n2--;
 		}
		total--;

		if (!--avail) {
			// transmit packet
			UEINTX = 0x3A;
			while (1) {
				if (UEINTX & (1<<RWAL)) break;
				SREG = intr_state;
				if (!enabled || !usb_configuration) return;
				intr_state = SREG;
				cli();
				UENUM = FLIGHTSIM_TX_ENDPOINT;
			}

			// start new fragment with length and fragment ID
			UEDATX = (total<(FLIGHTSIM_TX_SIZE-3) ? total+3 : FLIGHTSIM_TX_SIZE); // length byte
			UEDATX = 0xff;
			UEDATX = packet_id++;
			avail = FLIGHTSIM_TX_SIZE - 3;
		}
	}
	if (UEBCLX == FLIGHTSIM_TX_SIZE) UEINTX = 0x3A;
	SREG = intr_state;
}


FlightSimClass FlightSim;









static volatile uint8_t prev_byte=0;

void usb_serial_class::begin(long speed)
{
	// make sure USB is initialized
	usb_init();
	uint16_t begin_wait = (uint16_t)millis();
	while (1) {
		if (usb_configuration) {
			delay(200);  // a little time for host to load a driver
			return;
		}
		if (usb_suspended) {
			uint16_t begin_suspend = (uint16_t)millis();
			while (usb_suspended) {
				// must remain suspended for a while, because
				// normal USB enumeration causes brief suspend
				// states, typically under 0.1 second
				if ((uint16_t)millis() - begin_suspend > 250) {
					return;
				}
			}
		}
		// ... or a timout (powered by a USB power adaptor that
		// wiggles the data lines to keep a USB device charging)
		if ((uint16_t)millis() - begin_wait > 2500) return;
	}
	prev_byte = 0;
}

void usb_serial_class::end()
{
	usb_shutdown();
	delay(25);
}



// number of bytes available in the receive buffer
int usb_serial_class::available()
{
        uint8_t c;

	c = prev_byte;  // assume 1 byte static volatile access is atomic
	if (c) return 1;
	c = readnext();
	if (c) {
		prev_byte = c;
		return 1;
	}
	return 0;
}

// get the next character, or -1 if nothing received
int usb_serial_class::read()
{
	uint8_t c;

	c = prev_byte;
	if (c) {
		prev_byte = 0;
		return c;
	}
	c = readnext();
	if (c) return c;
	return -1;
}

int usb_serial_class::peek()
{
	uint8_t c;
	
	c = prev_byte;
	if (c) return c;
	c = readnext();
	if (c) {
		prev_byte = c;
		return c;
	}
	return -1;
}

// get the next character, or 0 if nothing
uint8_t usb_serial_class::readnext(void)
{
        uint8_t c, intr_state;

        // interrupts are disabled so these functions can be
        // used from the main program or interrupt context,
        // even both in the same program!
        intr_state = SREG;
        cli();
        if (!usb_configuration) {
                SREG = intr_state;
                return 0;
        }
        UENUM = DEBUG_RX_ENDPOINT;
try_again:
        if (!(UEINTX & (1<<RWAL))) {
                // no packet in buffer
                SREG = intr_state;
                return 0;
        }
        // take one byte out of the buffer
        c = UEDATX;
	if (c == 0) {
		// if we see a zero, discard it and
		// discard the rest of this packet
		UEINTX = 0x6B;
		goto try_again;
	}
        // if this drained the buffer, release it
        if (!(UEINTX & (1<<RWAL))) UEINTX = 0x6B;
        SREG = intr_state;
        return c;
}

// discard any buffered input
void usb_serial_class::flush()
{
        uint8_t intr_state;

        if (usb_configuration) {
                intr_state = SREG;
                cli();
		UENUM = DEBUG_RX_ENDPOINT;
                while ((UEINTX & (1<<RWAL))) {
                        UEINTX = 0x6B;
                }
                SREG = intr_state;
        }
	prev_byte = 0;
}

// transmit a character.
#if ARDUINO >= 100
size_t usb_serial_class::write(uint8_t c)
#else
void usb_serial_class::write(uint8_t c)
#endif
{
        //static uint8_t previous_timeout=0;
        uint8_t timeout, intr_state;

        // if we're not online (enumerated and configured), error
        if (!usb_configuration) goto error;
        // interrupts are disabled so these functions can be
        // used from the main program or interrupt context,
        // even both in the same program!
        intr_state = SREG;
        cli();
        UENUM = DEBUG_TX_ENDPOINT;
        // if we gave up due to timeout before, don't wait again
#if 0
	// this seems to be causig a lockup... why????
        if (previous_timeout) {
                if (!(UEINTX & (1<<RWAL))) {
                        SREG = intr_state;
                        return;
                }
                previous_timeout = 0;
        }
#endif
        // wait for the FIFO to be ready to accept data
        timeout = UDFNUML + TRANSMIT_TIMEOUT;
        while (1) {
                // are we ready to transmit?
                if (UEINTX & (1<<RWAL)) break;
                SREG = intr_state;
                // have we waited too long?  This happens if the user
                // is not running an application that is listening
                if (UDFNUML == timeout) {
                        //previous_timeout = 1;
			goto error;
		}
                // has the USB gone offline?
                if (!usb_configuration) goto error;
                // get ready to try checking again
                intr_state = SREG;
                cli();
                UENUM = DEBUG_TX_ENDPOINT;
        }
        // actually write the byte into the FIFO
        UEDATX = c;
        // if this completed a packet, transmit it now!
        if (!(UEINTX & (1<<RWAL))) {
		UEINTX = 0x3A;
        	debug_flush_timer = 0;
	} else {
        	debug_flush_timer = TRANSMIT_FLUSH_TIMEOUT;
	}
        SREG = intr_state;
#if ARDUINO >= 100
	return 1;
#endif
error:
#if ARDUINO >= 100
	setWriteError();
	return 0;
#else
	return;
#endif
}


// These are Teensy-specific extensions to the Serial object

// immediately transmit any buffered output.
// This doesn't actually transmit the data - that is impossible!
// USB devices only transmit when the host allows, so the best
// we can do is release the FIFO buffer for when the host wants it
void usb_serial_class::send_now(void)
{
        uint8_t intr_state;

        intr_state = SREG;
        cli();
        if (debug_flush_timer) {
                UENUM = DEBUG_TX_ENDPOINT;
		while ((UEINTX & (1<<RWAL))) {
			UEDATX = 0;
		}
                UEINTX = 0x3A;
                debug_flush_timer = 0;
        }
        SREG = intr_state;
}

uint32_t usb_serial_class::baud(void)
{
	return ((uint32_t)DEBUG_TX_SIZE * 10000 / DEBUG_TX_INTERVAL);
}

uint8_t usb_serial_class::stopbits(void)
{
	return 1;
}

uint8_t usb_serial_class::paritytype(void)
{
	return 0;
}

uint8_t usb_serial_class::numbits(void)
{
	return 8;
}

uint8_t usb_serial_class::dtr(void)
{
	return 1;
}

uint8_t usb_serial_class::rts(void)
{
	return 1;
}

usb_serial_class::operator bool()
{
	if (usb_configuration) return true;
	return false;
}



// Preinstantiate Objects //////////////////////////////////////////////////////

usb_serial_class	Serial = usb_serial_class();

