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
//WMXZ: cloned from rawhid and modified for mtp

#include "usb_dev.h"
#include "usb_mtp.h"
#include "core_pins.h" // for yield(), millis()
#include <string.h>    // for memcpy()
//#include "HardwareSerial.h"

#include "debug/printf.h"

#ifdef MTP_INTERFACE // defined by usb_dev.h -> usb_desc.h

#define TX_NUM   8
static transfer_t tx_transfer[TX_NUM] __attribute__ ((used, aligned(32)));
static uint8_t txbuffer[MTP_TX_SIZE * TX_NUM] __attribute__ ((used, aligned(32)));
static uint8_t tx_head=0;

#define RX_NUM   1
static transfer_t rx_transfer[RX_NUM] __attribute__ ((used, aligned(32)));
static uint8_t rx_buffer[MTP_RX_SIZE*RX_NUM] __attribute__ ((used, aligned(32)));
static uint8_t rx_head=0;
//static uint8_t rx_tail=0;

static transfer_t tx_event_transfer[1] __attribute__ ((used, aligned(32)));
static uint8_t tx_event_buffer[MTP_EVENT_SIZE] __attribute__ ((used, aligned(32)));

static transfer_t rx_event_transfer[1] __attribute__ ((used, aligned(32)));
static uint8_t rx_event_buffer[MTP_EVENT_SIZE] __attribute__ ((used, aligned(32)));

extern volatile uint8_t usb_configuration;

uint32_t mtp_rx_counter=0;
static void rx_event(transfer_t *t)
{	mtp_rx_counter++;
//	printf("rx %d %d %d\n",mtp_rx_counter, MTP_RX_SIZE - (t->status>>16), t->callback_param);
//  uint16_t ii=t->callback_param;
//	uint16_t *data = (uint16_t*) (rx_buffer+ii*MTP_RX_SIZE);
//	for(int ii=0; ii<8;ii++) printf("%x ",data[ii]); printf("\n");
}

uint32_t mtp_tx_counter=0;
static void tx_event(transfer_t *t)
{
	mtp_tx_counter++;
//	printf("tx %d %d %d\n",mtp_tx_counter, t->status>>16, t->callback_param);
}

uint32_t mtp_rx_event_counter=0;
static void rx_event_event(transfer_t *t)
{
	mtp_rx_event_counter++;
	printf("rx_event %d %x %d\n",mtp_rx_event_counter, t->status, t->callback_param);
	usb_prepare_transfer(rx_event_transfer + 0, rx_event_buffer, MTP_EVENT_SIZE, MTP_EVENT_ENDPOINT);
	usb_receive(MTP_EVENT_ENDPOINT, rx_event_transfer + 0);

}

uint32_t mtp_tx_event_counter=0;
static void tx_event_event(transfer_t *t)
{
	mtp_tx_event_counter++;
//	printf("tx_event %d %d\n",mtp_tx_event_counter, t->callback_param);
}


void usb_mtp_configure(void)
{
	printf("usb_mtp_configure\n");
	memset(tx_transfer, 0, sizeof(tx_transfer));
	memset(rx_transfer, 0, sizeof(rx_transfer));
	tx_head = 0;
	memset(rx_event_transfer, 0, sizeof(rx_event_transfer));
	memset(tx_event_transfer, 0, sizeof(tx_event_transfer));

	usb_config_tx(MTP_TX_ENDPOINT, MTP_TX_SIZE, 0, tx_event);
	usb_config_rx(MTP_RX_ENDPOINT, MTP_RX_SIZE, 0, rx_event);
	//usb_config_rx(MTP_RX_ENDPOINT, MTP_RX_SIZE, 0, NULL); // why does this not work?

	usb_config_rx(MTP_EVENT_ENDPOINT, MTP_EVENT_SIZE, 0, rx_event_event);
	usb_config_tx(MTP_EVENT_ENDPOINT, MTP_EVENT_SIZE, 0, tx_event_event);

    for(int ii=0; ii<RX_NUM;ii++)
	{
		usb_prepare_transfer(rx_transfer + ii, rx_buffer+ii*MTP_RX_SIZE, MTP_RX_SIZE, ii);
		usb_receive(MTP_RX_ENDPOINT, rx_transfer + ii);
	}

	usb_prepare_transfer(rx_event_transfer + 0, rx_event_buffer, MTP_EVENT_SIZE, MTP_EVENT_ENDPOINT);
	usb_receive(MTP_EVENT_ENDPOINT, rx_event_transfer + 0);
}

static int mtp_xfer_wait(transfer_t *xfer,uint32_t timeout)
{
	uint32_t wait_begin_at = systick_millis_count;
	while (1) {
		if (!usb_configuration) return -1; // usb not enumerated by host
		uint32_t status = usb_transfer_status(xfer);
		if (!(status & 0x80)) break; // transfer descriptor ready
		if (systick_millis_count - wait_begin_at > timeout) return 0;
		yield();
	}
	return 1;
}
int usb_mtp_read(void *buffer, uint32_t timeout)
{
	uint8_t *rxdata = rx_buffer + (rx_head * MTP_RX_SIZE);
	memcpy(buffer, rxdata, MTP_RX_SIZE);

	return MTP_RX_SIZE;
}

int usb_mtp_recv(void *buffer, uint32_t timeout)
{
	if (++rx_head >= RX_NUM) rx_head = 0;
	transfer_t *xfer = rx_transfer + rx_head;

    int ret;
	if((ret=mtp_xfer_wait(xfer,timeout)) <= 0) return ret;

	uint8_t *rxdata = rx_buffer + (rx_head * MTP_RX_SIZE);

	memset(xfer, 0, sizeof(transfer_t));
	usb_prepare_transfer(xfer, rxdata, MTP_RX_SIZE, rx_head);
	usb_receive(MTP_RX_ENDPOINT, xfer);

	return MTP_RX_SIZE;
}

int usb_mtp_send(const void *buffer, int len, uint32_t timeout)
{
	transfer_t *xfer = tx_transfer + tx_head;

    int ret;
	if((ret=mtp_xfer_wait(xfer,timeout)) <= 0) return ret;

	uint8_t *txdata = txbuffer + (tx_head * MTP_TX_SIZE);
	memcpy(txdata, buffer, len);
	usb_prepare_transfer(xfer, txdata, len,  tx_head);
	usb_transmit(MTP_TX_ENDPOINT, xfer);
	if (++tx_head >= TX_NUM) tx_head = 0;
	return MTP_TX_SIZE;
}

int usb_mtp_available(void)
{
	if (!usb_configuration) return 0;
	if (!(usb_transfer_status(rx_transfer) & 0x80)) return MTP_RX_SIZE;
	return 0;
}

int usb_mtp_eventSend(const void *buffer, uint32_t timeout)
{
	transfer_t *xfer = tx_event_transfer;

    int ret;
	if((ret=mtp_xfer_wait(xfer,timeout)) <= 0) return ret;

	uint8_t *txdata = tx_event_buffer;
	memcpy(txdata, buffer, MTP_EVENT_SIZE);
	usb_prepare_transfer(xfer, txdata, MTP_EVENT_SIZE,  MTP_EVENT_ENDPOINT);
	usb_transmit(MTP_EVENT_ENDPOINT, xfer);
	return MTP_EVENT_SIZE;
}

int usb_mtp_eventRecv(void *buffer, uint32_t timeout)
{
	transfer_t *xfer = rx_event_transfer;

    int ret;
	if((ret=mtp_xfer_wait(xfer,timeout)) <= 0) return ret;

	memcpy(buffer, rx_event_buffer, MTP_EVENT_SIZE);
	memset(xfer, 0, sizeof(rx_event_transfer));
	usb_prepare_transfer(xfer, rx_event_buffer, MTP_EVENT_SIZE, MTP_EVENT_ENDPOINT);
	usb_receive(MTP_EVENT_ENDPOINT, xfer);

	return MTP_EVENT_SIZE;
}
#endif // MTP_INTERFACE
