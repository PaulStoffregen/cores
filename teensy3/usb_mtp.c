/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2015 PJRC.COM, LLC.
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
#include "usb_mtp.h"
#include "core_pins.h" // for yield()
#include "HardwareSerial.h"

#ifdef MTP_INTERFACE // defined by usb_dev.h -> usb_desc.h
#if F_CPU >= 20000000

#define DMABUFATTR __attribute__ ((section(".dmabuffers"), aligned (4)))
uint8_t usb_mtp_receive_buffer[MTP_RX_SIZE] DMABUFATTR;
uint8_t usb_mtp_event_buffer[MTP_EVENT_SIZE] DMABUFATTR;
uint8_t usb_mtp_transmit_buffer[MTP_TX_SIZE] DMABUFATTR;
uint8_t usb_audio_transmit_setting=0;
uint8_t usb_mtp_receive_setting=0;

//bdp_t* usb_mtp_write_buffers[2];
//bdp_t* usb_mtp_read_buffer[2];

// Called from the USB interrupt when ready to transmit another
// packet.  If we place data into the transmit buffer,
// the return is the number of bytes.  Otherwise, return 0 means
// no data to transmit
unsigned int usb_mtp_transmit_callback(void) {
  serial_print("<transmit>\n");
  return 0;
}

void usb_mtp_receive_callback(unsigned int len) {
  serial_print(">receive ");
  serial_phex32(len);
  serial_print(":");
  serial_phex(usb_mtp_receive_buffer[0]);
  serial_phex(usb_mtp_receive_buffer[1]);
  serial_phex(usb_mtp_receive_buffer[2]);
  serial_phex(usb_mtp_receive_buffer[3]);
  serial_print(" ");
  serial_phex(usb_mtp_receive_buffer[4]);
  serial_phex(usb_mtp_receive_buffer[5]);
  serial_phex(usb_mtp_receive_buffer[6]);
  serial_phex(usb_mtp_receive_buffer[7]);
  serial_print("\n");
}

void usb_mtp_update(void)
{
	serial_print("test\n");

	// TODO: a lot of work here....
}

#if 0
// {rx, tx}
// Use tx_state[]
uint16_t usb_banks[2];
#define USB_BANK(EP, TX) ((usb_banks[TX] >> EP) & 1)
#define FLIP_USB_BANK(EP, TX) usb_banks[TX] ^= (1 << EP)
bdt_t* usb_next_buffer(int endpoint, int tx) {
  bdt_t* ret = table + index(endpoint, tx, USB_BANK(endpoint, tx));
  if (bdt_owned(ret)) return ret;
  return NULL;
}

void usb_release_buffer(bdt_t* b, int len) {
  int entry = b - table;
  int endpoint = entry >> 2;
  int tx = (entry >> 1) & 1;
#if 0
  assert(usb_next_buffer(entry, tx) == b);
  assert(len <= 
#endif
  b->desc |= (len << 16) | BDT_OWN;
  FLIP_USB_BANK(endpoint, tx);
}


int usb_mtp_write_available() {
  return btp_space_available(usb_mtp_tx_bdp(false)) + btp_space_available(usb_mtp_tx_bdp(false));
}

void usb_mtp_send() {
  bdp_t* b = usb_mtp_tx_bdp(false);
  btp_release(b);
  usb_mtp_current_endpoint = !usb_mtp_current_endpoint;
}

int usb_mtp_write(uint8_t* data, int size) {
  int copied = 0;
  while (size) {
    bdp_t* b = usb_mtp_tx_bdp(false);
    int avail = bdp_space_available(b);
    if (!avail) return copied;
    int to_copy = min(avail, size);
    memcpy(b->addr + b->len, to_copy, data);
    b->len += to_copy;
    size -= to_copy;
    copied += to_copy;
    if (!bdp_space_available(b)) usb_mt_send();
  }
}



bool usb_mtp_rx_odd;
bdp_t* usb_mtp_rx_bdp(bool other) {
  return table + index(MTP_TX_ENDPOINT, true, usb_mtp_rx_odd ^ other);
}

int bdp_space_used(btp_t* b) {
  return btp_owned(b) ? b->len : 0;
}

int usb_mtp_read_pos;

int usb_mtp_read_available() {
  return btp_space_used(usb_mtp_rx_bdp(false)) +
    btp_space_used(usb_mtp_rx_bdp(false)) -
    usb_mtp_read_pos;
}

int usb_mtp_read(uint8_t* data, uint32_t size) {
  int copied = 0;
  while (size) {
    bdp_t* b = usb_mtp_rx_bdp(false);
    int avail = bdp_space_used(b) - usb_read_pos;
    if (!avail) return copied;
    int to_copy = min(avail, size);
    memcpy(b->addr + usb_mtp_read_pos, to_copy, data);
    usb_mtp_read_pos += to_copy;
    size -= to_copy;
    copied += to_copy;
    if (bdp_space_used(b)) usb_mt_send();
  }
}

#endif

#endif // F_CPU
#endif // MTP_INTERFACE
