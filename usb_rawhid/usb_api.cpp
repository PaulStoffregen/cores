/* USB API for Teensy USB Development Board
 * http://www.pjrc.com/teensy/teensyduino.html
 * Copyright (c) 2011 PJRC.COM, LLC
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


int usb_rawhid_class::available(void)
{
	uint8_t n=0, i, intr_state;

	intr_state = SREG;
	cli();
	if (usb_configuration) {
		UENUM = RAWHID_RX_ENDPOINT;
		n = UEBCLX;
	}
	SREG = intr_state;
	return n;
}

// receive a packet, with timeout
int usb_rawhid_class::recv(void *ptr, uint16_t timeout)
{
	uint8_t *buffer = (uint8_t *)ptr;
        uint8_t intr_state;

        // if we're not online (enumerated and configured), error
        if (!usb_configuration) return -1;
        intr_state = SREG;
        cli();
        rawhid_rx_timeout_count = timeout;
        UENUM = RAWHID_RX_ENDPOINT;
        // wait for data to be available in the FIFO
        while (1) {
                if (UEINTX & (1<<RWAL)) break;
                SREG = intr_state;
                if (rawhid_rx_timeout_count == 0) return 0;
                if (!usb_configuration) return -1;
                intr_state = SREG;
                cli();
                UENUM = RAWHID_RX_ENDPOINT;
        }
        // read bytes from the FIFO
        #if (RAWHID_RX_SIZE >= 64)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 63)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 62)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 61)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 60)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 59)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 58)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 57)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 56)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 55)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 54)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 53)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 52)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 51)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 50)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 49)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 48)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 47)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 46)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 45)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 44)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 43)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 42)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 41)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 40)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 39)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 38)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 37)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 36)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 35)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 34)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 33)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 32)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 31)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 30)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 29)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 28)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 27)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 26)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 25)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 24)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 23)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 22)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 21)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 20)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 19)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 18)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 17)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 16)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 15)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 14)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 13)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 12)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 11)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 10)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 9)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 8)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 7)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 6)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 5)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 4)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 3)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 2)
        *buffer++ = UEDATX;
        #endif
        #if (RAWHID_RX_SIZE >= 1)
        *buffer++ = UEDATX;
        #endif
        // release the buffer
        UEINTX = 0x6B;
        SREG = intr_state;
        return RAWHID_RX_SIZE;
}


// send a packet, with timeout
int usb_rawhid_class::send(const void *ptr, uint16_t timeout)
{
	const uint8_t *buffer = (const uint8_t *)ptr;
        uint8_t intr_state;

        // if we're not online (enumerated and configured), error
        if (!usb_configuration) return -1;
        intr_state = SREG;
        cli();
        rawhid_tx_timeout_count = timeout;
        UENUM = RAWHID_TX_ENDPOINT;
        // wait for the FIFO to be ready to accept data
        while (1) {
                if (UEINTX & (1<<RWAL)) break;
                SREG = intr_state;
                if (rawhid_tx_timeout_count == 0) return 0;
                if (!usb_configuration) return -1;
                intr_state = SREG;
                cli();
                UENUM = RAWHID_TX_ENDPOINT;
        }
        // write bytes from the FIFO
        #if (RAWHID_TX_SIZE >= 64)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 63)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 62)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 61)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 60)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 59)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 58)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 57)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 56)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 55)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 54)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 53)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 52)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 51)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 50)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 49)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 48)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 47)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 46)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 45)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 44)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 43)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 42)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 41)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 40)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 39)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 38)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 37)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 36)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 35)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 34)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 33)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 32)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 31)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 30)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 29)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 28)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 27)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 26)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 25)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 24)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 23)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 22)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 21)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 20)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 19)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 18)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 17)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 16)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 15)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 14)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 13)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 12)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 11)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 10)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 9)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 8)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 7)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 6)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 5)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 4)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 3)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 2)
        UEDATX = *buffer++;
        #endif
        #if (RAWHID_TX_SIZE >= 1)
        UEDATX = *buffer++;
        #endif
        // transmit it now
        UEINTX = 0x3A;
        SREG = intr_state;
        return RAWHID_TX_SIZE;
}






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
usb_rawhid_class	RawHID = usb_rawhid_class();

