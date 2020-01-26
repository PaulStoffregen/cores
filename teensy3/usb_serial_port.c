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
#include "usb_serial_port.h"
#include "core_pins.h" // for yield()
//#include "HardwareSerial.h"
#include <string.h> // for memcpy()

// defined by usb_dev.h -> usb_desc.h
#if defined(CDC_STATUS_INTERFACE) && defined(CDC_DATA_INTERFACE)
#if F_CPU >= 20000000

#define TRANSMIT_FLUSH_TIMEOUT	5   /* in milliseconds */

// get the next character, or -1 if nothing received
int __usb_serial_getchar(struct usb_serial_port *port)
{
	unsigned int i;
	int c;

	if (!port->rx_packet) {
		if (!usb_configuration) return -1;
		port->rx_packet = usb_rx(port->cdc_rx_endpoint);
		if (!port->rx_packet) return -1;
	}
	i = port->rx_packet->index;
	c = port->rx_packet->buf[i++];
	if (i >= port->rx_packet->len) {
		usb_free(port->rx_packet);
		port->rx_packet = NULL;
	} else {
		port->rx_packet->index = i;
	}
	return c;
}

// peek at the next character, or -1 if nothing received
int __usb_serial_peekchar(struct usb_serial_port *port)
{
	if (!port->rx_packet) {
		if (!usb_configuration) return -1;
		port->rx_packet = usb_rx(port->cdc_rx_endpoint);
		if (!port->rx_packet) return -1;
	}
	if (!port->rx_packet) return -1;
	return port->rx_packet->buf[port->rx_packet->index];
}

// number of bytes available in the receive buffer
int __usb_serial_available(struct usb_serial_port *port)
{
	int count;
	count = usb_rx_byte_count(port->cdc_rx_endpoint);
	if (port->rx_packet)
		count += port->rx_packet->len - port->rx_packet->index;
	return count;
}

// read a block of bytes to a buffer
int __usb_serial_read(struct usb_serial_port *port, void *buffer,
		      uint32_t size)
{
	uint8_t *p = (uint8_t *)buffer;
	uint32_t qty, count=0;

	while (size) {
		if (!usb_configuration) break;
		if (!port->rx_packet) {
			rx:
			port->rx_packet = usb_rx(port->cdc_rx_endpoint);
			if (!port->rx_packet) break;
			if (port->rx_packet->len == 0) {
				usb_free(port->rx_packet);
				goto rx;
			}
		}
		qty = port->rx_packet->len - port->rx_packet->index;
		if (qty > size) qty = size;
		memcpy(p, port->rx_packet->buf + port->rx_packet->index, qty);
		p += qty;
		count += qty;
		size -= qty;
		port->rx_packet->index += qty;
		if (port->rx_packet->index >= port->rx_packet->len) {
			usb_free(port->rx_packet);
			port->rx_packet = NULL;
		}
	}
	return count;
}

// discard any buffered input
void __usb_serial_flush_input(struct usb_serial_port *port)
{
	usb_packet_t *rx;

	if (!usb_configuration) return;
	if (port->rx_packet) {
		usb_free(port->rx_packet);
		port->rx_packet = NULL;
	}
	while (1) {
		rx = usb_rx(port->cdc_rx_endpoint);
		if (!rx) break;
		usb_free(rx);
	}
}

// Maximum number of transmit packets to queue so we don't starve other endpoints for memory
#define TX_PACKET_LIMIT 8

// When the PC isn't listening, how long do we wait before discarding data?  If this is
// too short, we risk losing data during the stalls that are common with ordinary desktop
// software.  If it's too long, we stall the user's program when no software is running.
#define TX_TIMEOUT_MSEC 70
#if F_CPU == 256000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 1706)
#elif F_CPU == 240000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 1600)
#elif F_CPU == 216000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 1440)
#elif F_CPU == 192000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 1280)
#elif F_CPU == 180000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 1200)
#elif F_CPU == 168000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 1100)
#elif F_CPU == 144000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 932)
#elif F_CPU == 120000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 764)
#elif F_CPU == 96000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 596)
#elif F_CPU == 72000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 512)
#elif F_CPU == 48000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 428)
#elif F_CPU == 24000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 262)
#endif

// When we've suffered the transmit timeout, don't wait again until the computer
// begins accepting data.  If no software is running to receive, we'll just discard
// data as rapidly as Serial.print() can generate it, until there's something to
// actually receive it.
static uint8_t transmit_previous_timeout=0;


// transmit a character.  0 returned on success, -1 on error
int __usb_serial_putchar(struct usb_serial_port *port, uint8_t c)
{
	return __usb_serial_write(port, &c, 1);
}


int __usb_serial_write(struct usb_serial_port *port, const void *buffer,
		       uint32_t size)
{
	uint32_t ret = size;
	uint32_t len;
	uint32_t wait_count;
	const uint8_t *src = (const uint8_t *)buffer;
	uint8_t *dest;

	port->tx_noautoflush = 1;
	while (size > 0) {
		if (!port->tx_packet) {
			wait_count = 0;
			while (1) {
				if (!usb_configuration) {
					port->tx_noautoflush = 0;
					return -1;
				}
				if (usb_tx_packet_count(port->cdc_tx_endpoint) < TX_PACKET_LIMIT) {
					port->tx_noautoflush = 1;
					port->tx_packet = usb_malloc();
					if (port->tx_packet) break;
					port->tx_noautoflush = 0;
				}
				if (++wait_count > TX_TIMEOUT || transmit_previous_timeout) {
					transmit_previous_timeout = 1;
					return -1;
				}
				yield();
			}
		}
		transmit_previous_timeout = 0;
		len = port->cdc_tx_size - port->tx_packet->index;
		if (len > size) len = size;
		dest = port->tx_packet->buf + port->tx_packet->index;
		port->tx_packet->index += len;
		size -= len;
		while (len-- > 0) *dest++ = *src++;
		if (port->tx_packet->index >= port->cdc_tx_size) {
			port->tx_packet->len = port->cdc_tx_size;
			usb_tx(port->cdc_tx_endpoint, port->tx_packet);
			port->tx_packet = NULL;
		}
		port->cdc_transmit_flush_timer = TRANSMIT_FLUSH_TIMEOUT;
	}
	port->tx_noautoflush = 0;
	return ret;
}

int __usb_serial_write_buffer_free(struct usb_serial_port *port)
{
	uint32_t len;

	port->tx_noautoflush = 1;
	if (!port->tx_packet) {
		if (!usb_configuration ||
		  usb_tx_packet_count(port->cdc_tx_endpoint) >= TX_PACKET_LIMIT ||
		  (port->tx_packet = usb_malloc()) == NULL) {
			port->tx_noautoflush = 0;
			return 0;
		}
	}
	len = port->cdc_tx_size - port->tx_packet->index;
	// TODO: Perhaps we need "port->cdc_transmit_flush_timer = TRANSMIT_FLUSH_TIMEOUT"
	// added here, so the SOF interrupt can't take away the available buffer
	// space we just promised the user could write without blocking?
	// But does this come with other performance downsides?  Could it lead to
	// buffer data never actually transmitting in some usage cases?  More
	// investigation is needed.
	// https://github.com/PaulStoffregen/cores/issues/10#issuecomment-61514955
	port->tx_noautoflush = 0;
	return len;
}

void __usb_serial_flush_output(struct usb_serial_port *port)
{
	if (!usb_configuration) return;
	port->tx_noautoflush = 1;
	if (port->tx_packet) {
		port->cdc_transmit_flush_timer = 0;
		port->tx_packet->len = port->tx_packet->index;
		usb_tx(port->cdc_tx_endpoint, port->tx_packet);
		port->tx_packet = NULL;
	} else {
		usb_packet_t *tx = usb_malloc();
		if (tx) {
			port->cdc_transmit_flush_timer = 0;
			usb_tx(port->cdc_tx_endpoint, tx);
		} else {
			port->cdc_transmit_flush_timer = 1;
		}
	}
	port->tx_noautoflush = 0;
}

void __usb_serial_flush_callback(struct usb_serial_port *port)
{
	if (port->tx_noautoflush) return;
	if (port->tx_packet) {
		port->tx_packet->len = port->tx_packet->index;
		usb_tx(port->cdc_tx_endpoint, port->tx_packet);
		port->tx_packet = NULL;
	} else {
		usb_packet_t *tx = usb_malloc();
		if (tx) {
			usb_tx(port->cdc_tx_endpoint, tx);
		} else {
			port->cdc_transmit_flush_timer = 1;
		}
	}
}




#endif // F_CPU
#endif // CDC_STATUS_INTERFACE && CDC_DATA_INTERFACE
