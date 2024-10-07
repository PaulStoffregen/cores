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
#include "usb_joystick.h"
#include "core_pins.h" // for yield()
#include <string.h> // for memcpy()
#include "avr/pgmspace.h" // for PROGMEM, DMAMEM, FASTRUN
#include "debug/printf.h"
#include "core_pins.h"


#ifdef JOYSTICK_INTERFACE // defined by usb_dev.h -> usb_desc.h


uint32_t usb_joystick_data[(JOYSTICK_SIZE+3)/4];

static uint8_t transmit_previous_timeout=0;

// When the PC isn't listening, how long do we wait before discarding data?
#define TX_TIMEOUT_MSEC 30

#define TX_NUM     4
#if JOYSTICK_SIZE <= 32
  #define TX_BUFSIZE 32
#else
  #define TX_BUFSIZE 64
#endif
static transfer_t tx_transfer[TX_NUM] __attribute__ ((used, aligned(32)));
DMAMEM static uint8_t txbuffer[TX_NUM * TX_BUFSIZE] __attribute__ ((aligned(32)));
static uint8_t tx_head=0;
#if JOYSTICK_SIZE > TX_BUFSIZE
#error "Internal error, transmit buffer size is too small for joystick endpoint"
#endif


void usb_joystick_configure(void)
{
	memset(tx_transfer, 0, sizeof(tx_transfer));
	tx_head = 0;
	usb_config_tx(JOYSTICK_ENDPOINT, JOYSTICK_SIZE, 0, NULL);
}


int usb_joystick_send()
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
	delayNanoseconds(30); // TODO: why is status ready too soon?
        uint8_t *buffer = txbuffer + head * TX_BUFSIZE;
	memcpy(buffer, usb_joystick_data, JOYSTICK_SIZE);
        usb_prepare_transfer(xfer, buffer, JOYSTICK_SIZE, 0);
        arm_dcache_flush_delete(buffer, TX_BUFSIZE);
        usb_transmit(JOYSTICK_ENDPOINT, xfer);
        if (++head >= TX_NUM) head = 0;
        tx_head = head;
        return 0;
}


#endif // JOYSTICK_INTERFACE
