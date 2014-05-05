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

#include "usb_seremu.h"

#ifdef NUM_ENDPOINTS

#ifdef SEREMU_INTERFACE // defined by usb_dev.h -> usb_desc.h
#include "core_pins.h" // for yield()
//#include "HardwareSerial.h"


#if !defined(SEREMU_RX_ENDPOINT)
#error "SEREMU_RX_ENDPOINT not defined"
#endif
#if !defined(SEREMU_TX_ENDPOINT)
#error "SEREMU_TX_ENDPOINT not defined"
#endif




volatile uint8_t usb_seremu_transmit_flush_timer = 0;

static usb_packet_t *rx_packet = NULL;
static usb_packet_t *tx_packet = NULL;
static volatile uint8_t tx_noautoflush = 0;

#ifndef SEREMU_TRANSMIT_FLUSH_TIMEOUT
#define SEREMU_TRANSMIT_FLUSH_TIMEOUT	5   /* in milliseconds */
#endif

// read the remainder of the waiting packet, or size whichever is less.

int usb_seremu_read(void *buffer, uint32_t size) {
        unsigned int i;
        int c = 0;
        uint8_t *p = buffer;

        if(!usb_configuration) return -1; // Possibly Okay to return -1 for an error.
        if(!rx_packet) rx_packet = usb_rx(SEREMU_RX_ENDPOINT);
        if(!rx_packet) return 0; // This is not an error.
        for(i = rx_packet->index; c < size && i < rx_packet->len;) {
                *p++ = rx_packet->buf[i++];
                c++;
        }
        if(i < rx_packet->len) return c;
        usb_free(rx_packet);
        rx_packet = NULL;
        return c;
}

// get the next character, or -1 if nothing received
// Original has what I would call a 'bug' since it aborts on a zero.
// what if I *want* to rx a zero? Was this intentional? TX does this too?

int usb_seremu_getchar(void) {
#if 1
        unsigned int i;
        int c;

        if(!rx_packet) {
                if(!usb_configuration) return -1;
                rx_packet = usb_rx(SEREMU_RX_ENDPOINT);
                if(!rx_packet) return -1;
        }
        i = rx_packet->index;
        c = rx_packet->buf[i++];
        if(i >= rx_packet->len) {
                usb_free(rx_packet);
                rx_packet = NULL;
        } else {
                rx_packet->index = i;
        }
        return c;
#else
        unsigned int i;
        int c;

        while(1) {
                if(!usb_configuration) return -1;
                if(!rx_packet) rx_packet = usb_rx(SEREMU_RX_ENDPOINT);
                if(!rx_packet) return -1;
                i = rx_packet->index;
                c = rx_packet->buf[i++];
                if(c) {
                        if(i >= rx_packet->len) {
                                usb_free(rx_packet);
                                rx_packet = NULL;
                        } else {
                                rx_packet->index = i;
                        }
                        return c;
                }
                usb_free(rx_packet);
                rx_packet = NULL;
        }
#endif
}

// peek at the next character, or -1 if nothing received

int usb_seremu_peekchar(void) {
        int c;

        while(1) {
                if(!usb_configuration) return -1;
                if(!rx_packet) rx_packet = usb_rx(SEREMU_RX_ENDPOINT);
                if(!rx_packet) return -1;
                c = rx_packet->buf[rx_packet->index];
                return c;
                //usb_free(rx_packet);
                //rx_packet = NULL;
        }
}

// number of bytes available in the receive buffer

int usb_seremu_available(void) {
        int i, len, count;

        if(!rx_packet) {
                if(usb_configuration) rx_packet = usb_rx(SEREMU_RX_ENDPOINT);
                if(!rx_packet) return 0;
        }
        len = rx_packet->len;
        i = rx_packet->index;
        count = 0;
        for(i = rx_packet->index; i < len; i++) {
                if(rx_packet->buf[i] == 0) break;
                count++;
        }
        if(count == 0) {
                usb_free(rx_packet);
                rx_packet = NULL;
        }
        return count;
}


// discard any buffered input

void usb_seremu_flush_input(void) {
        usb_packet_t *rx;

        if(!usb_configuration) return;
        if(rx_packet) {
                usb_free(rx_packet);
                rx_packet = NULL;
        }
        while(1) {
                rx = usb_rx(SEREMU_RX_ENDPOINT);
                if(!rx) break;
                usb_free(rx);
        }
}
#if (SEREMU_TX_TIMEOUT_MSEC > -1)
#if F_CPU == 96000000
#define TX_TIMEOUT (SEREMU_TX_TIMEOUT_MSEC * 596)
#elif F_CPU == 48000000
#define TX_TIMEOUT (SEREMU_TX_TIMEOUT_MSEC * 428)
#elif F_CPU == 24000000
#define TX_TIMEOUT (SEREMU_TX_TIMEOUT_MSEC * 262)
#endif
#endif

// When we've suffered the transmit timeout, don't wait again until the computer
// begins accepting data.  If no software is running to receive, we'll just discard
// data as rapidly as Serial.print() can generate it, until there's something to
// actually receive it.
static uint8_t transmit_previous_timeout = 0;


// transmit a character.  0 returned on success, -1 on error

int usb_seremu_putchar(uint8_t c) {
        return usb_seremu_write(&c, 1);
}

int usb_seremu_write(const void *buffer, uint32_t size) {
        uint32_t len;
        uint32_t wait_count;
        const uint8_t *src = (const uint8_t *) buffer;
        uint8_t *dest;

        tx_noautoflush = 1;
        while(size > 0) {
                if(!tx_packet) {
                        wait_count = 0;
                        while(1) {
                                if(!usb_configuration) {
                                        tx_noautoflush = 0;
                                        return -1;
                                }
                                if(usb_tx_packet_count(SEREMU_TX_ENDPOINT) < SEREMU_TX_PACKET_LIMIT) {
                                        tx_noautoflush = 1;
                                        tx_packet = usb_malloc();
                                        if(tx_packet) break;
                                        tx_noautoflush = 0;
                                }
#if (SEREMU_TX_TIMEOUT_MSEC > -1)
                                if(++wait_count > TX_TIMEOUT || transmit_previous_timeout) {
                                        transmit_previous_timeout = 1;
                                        tx_noautoflush = 0;
                                        return -1;
                                }
#endif
                                tx_noautoflush = 0;
                                yield();
                                tx_noautoflush = 1;
                        }
                }
                transmit_previous_timeout = 0;
                len = SEREMU_TX_SIZE - tx_packet->index;
                if(len > size) len = size;
                dest = tx_packet->buf + tx_packet->index;
                tx_packet->index += len;
                size -= len;
                while(len-- > 0) *dest++ = *src++;
#if (SEREMU_TX_TIMEOUT_MSEC > -1)
                if(tx_packet->index < SEREMU_TX_SIZE) {
                        usb_seremu_transmit_flush_timer = SEREMU_TRANSMIT_FLUSH_TIMEOUT;
                } else {
#endif
                        tx_packet->len = SEREMU_TX_SIZE;
                        usb_seremu_transmit_flush_timer = 0;
                        usb_tx(SEREMU_TX_ENDPOINT, tx_packet);
                        tx_packet = NULL;
#if (SEREMU_TX_TIMEOUT_MSEC > -1)
                }
#endif
        }
        tx_noautoflush = 0;
        return 0;
}

void usb_seremu_flush_output(void) {
#if 1
        if(tx_noautoflush) return;
        if(tx_packet) {
                tx_packet->len = tx_packet->index;
                usb_tx(SEREMU_TX_ENDPOINT, tx_packet);
                tx_packet = NULL;
        } else {
                usb_packet_t *tx = usb_malloc();
                if(tx) {
                        usb_tx(SEREMU_TX_ENDPOINT, tx);
                }
        }

#else
        int i;

        if(!usb_configuration) return;
        //serial_print("usb_serial_flush_output\n");
        if(tx_packet && tx_packet->index > 0) {
                usb_seremu_transmit_flush_timer = 0;
                for(i = tx_packet->index; i < SEREMU_TX_SIZE; i++) {
                        tx_packet->buf[i] = 0;
                }
                tx_packet->len = tx_packet->index;
                usb_tx(SEREMU_TX_ENDPOINT, tx_packet);
                tx_packet = NULL;
        }
        // while (usb_tx_byte_count(SEREMU_TX_ENDPOINT) > 0) ; // wait
#endif
}

void usb_seremu_flush_callback(void) {
        int i;
        //serial_print("C");
        if(tx_noautoflush) return;
        //serial_print("usb_flush_callback \n");
        for(i = tx_packet->index; i < SEREMU_TX_SIZE; i++) {
                tx_packet->buf[i] = 0;
        }
        tx_packet->len = SEREMU_TX_SIZE;
        usb_tx(SEREMU_TX_ENDPOINT, tx_packet);
        tx_packet = NULL;
        //serial_print("usb_flush_callback end\n");
}

#endif // SEREMU_INTERFACE
#endif
