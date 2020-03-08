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

extern "C" {
#include "usb_dev.h"
}
#include "usb_flightsim.h"
#include "debug/printf.h"
#include "avr/pgmspace.h"
#include "core_pins.h" // for yield(), millis()
#include <string.h>    // for memcpy()

#ifdef FLIGHTSIM_INTERFACE // defined by usb_dev.h -> usb_desc.h
#if F_CPU >= 20000000

FlightSimCommand * FlightSimCommand::first = NULL;
FlightSimCommand * FlightSimCommand::last = NULL;
FlightSimInteger * FlightSimInteger::first = NULL;
FlightSimInteger * FlightSimInteger::last = NULL;
FlightSimFloat * FlightSimFloat::first = NULL;
FlightSimFloat * FlightSimFloat::last = NULL;
/// JB
FlightSimEvent * FlightSimEvent::first = NULL;
FlightSimEvent * FlightSimEvent::last = NULL;
FlightSimData * FlightSimData::first = NULL;
FlightSimData * FlightSimData::last = NULL;
/// JB End

uint8_t FlightSimClass::enabled = 0;
uint8_t FlightSimClass::request_id_messages = 0;
unsigned long FlightSimClass::frameCount = 0;
elapsedMillis FlightSimClass::enableTimeout;

static unsigned int unassigned_id = 1;  // TODO: move into FlightSimClass

static uint8_t tx_noautoflush=0;
static uint8_t transmit_previous_timeout=0;

#define TX_NUM   8
static transfer_t tx_transfer[TX_NUM] __attribute__ ((used, aligned(32)));
DMAMEM static uint8_t txbuffer[FLIGHTSIM_TX_SIZE * TX_NUM] __attribute__ ((aligned(32)));
static uint8_t tx_head=0;
static uint16_t tx_available=0;

#define RX_NUM  6
static transfer_t rx_transfer[RX_NUM] __attribute__ ((used, aligned(32)));
DMAMEM static uint8_t rx_buffer[RX_NUM * FLIGHTSIM_RX_SIZE] __attribute__ ((aligned(32)));
static volatile uint8_t rx_head;
static volatile uint8_t rx_tail;
static uint8_t rx_list[RX_NUM + 1];
static volatile uint32_t rx_available;

extern "C" {
static void rx_queue_transfer(int i);
static void rx_event(transfer_t *t);
static void* usb_flightsim_get_packet();
static void usb_flightsim_free_packet();
static bool wait_for_tx_buf(transfer_t *xfer);
static void send_packet(transfer_t *xfer);
}

// When the PC isn't listening, how long do we wait before discarding data?
#define TX_TIMEOUT_MSEC 40

extern volatile uint8_t usb_configuration;

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

/// JB
FlightSimEvent::FlightSimEvent()
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
	occur_callback = NULL;
	occurredFlag = 0;
	callbackInfo = NULL;
	hasCallbackInfo = 0;
	value = 0;
	FlightSimClass::request_id_messages = 1;
}

void FlightSimEvent::identify(void)
{
	uint8_t len, buf[6];

	if (!FlightSim.enabled || !name) return;
	len = strlen((const char *)name);
	buf[0] = len + 6;
	buf[1] = 1;
	buf[2] = id;
	buf[3] = id >> 8;
	buf[4] = 3;
	buf[5] = 0;
	FlightSimClass::xmit(buf, 6, name, len);
}

void FlightSimEvent::send(unsigned int data, unsigned int flags)
{
	uint8_t buf[4];
	uint32_t txData[2];

	if (!FlightSim.enabled || !name) return;
	buf[0] = 12;
	buf[1] = 7;
	buf[2] = id;
	buf[3] = id >> 8;
	value = data;
	txData[0] = data;
	txData[1] = flags;
	FlightSimClass::xmit(buf, 4, (uint8_t *)&txData, 8);
}

void FlightSimEvent::update(long val)
{
	value = (unsigned int) val;
	occurredFlag = true;
	if (occur_callback) {
		if (!hasCallbackInfo) {
			(*occur_callback)(val);
		} else {
			(*(void(*)(long,void*))occur_callback)(val,callbackInfo);
		}
	}
}

FlightSimEvent * FlightSimEvent::find(unsigned int n)
{
	for (FlightSimEvent *p = first; p; p = p->next) {
		if (p->id == n) return p;
	}
	return NULL;
}


FlightSimData::FlightSimData()
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
	valueLen = 0;
	hasCallbackInfo = 0;
	callbackWithObject = 0;
	callbackInfo = NULL;
	change_callback = NULL;
	FlightSimClass::request_id_messages = 1;
}

void FlightSimData::identify(void)
{
	uint8_t len, buf[6];

	if (!FlightSim.enabled || !name) return;
	len = strlen((const char *)name);
	buf[0] = len + 6;
	buf[1] = 1;
	buf[2] = id;
	buf[3] = id >> 8;
	buf[4] = 4;
	buf[5] = 0;
	FlightSimClass::xmit(buf, 6, name, len);
}

void FlightSimData::update(char *val, size_t len)
{
	valueLen = len;
	memcpy(value, val, len);
	if (len<FLIGHTSIM_DATA_MAXLEN) {
		memset(value+len,0,FLIGHTSIM_DATA_MAXLEN-len);
	}
	if (change_callback) {
		if (!callbackWithObject) {
			if (!hasCallbackInfo) {
				(*change_callback)(value);
			} else {
				(*(void(*)(char*,void*))change_callback)(value,callbackInfo);
			}
		} else {
			if (!hasCallbackInfo) {
				(*(void(*)(FlightSimData*))change_callback)(this);
			} else {
				(*(void(*)(FlightSimData*,void*))change_callback)(this,callbackInfo);
			}
		}
	}
}

FlightSimData * FlightSimData::find(unsigned int n)
{
	for (FlightSimData *p = first; p; p = p->next) {
		if (p->id == n) return p;
	}
	return NULL;
}
/// JB End


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
	callbackInfo = NULL;
	hasCallbackInfo = false;
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
	hasCallbackInfo = false;
	callbackInfo = NULL;
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
	if (change_callback) { // add: JB
		if (!hasCallbackInfo) {
			(*change_callback)(val);
		} else {
			(*(void(*)(float,void*))change_callback)(val,callbackInfo);
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
	uint8_t len, maxlen, type, *p, *end;
	union {
		uint8_t b[4];
		long l;
		float f;
	} data;
	void *rx_packet;
	uint16_t id;

	while (1) {
		if (!usb_configuration) break;
		rx_packet = usb_flightsim_get_packet();
		if (!rx_packet) break;
		p = (uint8_t*) rx_packet;
		end = p + FLIGHTSIM_RX_SIZE;
		maxlen = FLIGHTSIM_RX_SIZE;
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
					data.b[0] = p[6];
					data.b[1] = p[7];
					data.b[2] = p[8];
					data.b[3] = p[9];
					item->update(data.l);
				} else if (type == 2) {
					FlightSimFloat *item = FlightSimFloat::find(id);
					if (!item) break;
					data.b[0] = p[6];
					data.b[1] = p[7];
					data.b[2] = p[8];
					data.b[3] = p[9];
					item->update(data.f);
/// JB
				} else if (type == 3) {
					FlightSimEvent *item = FlightSimEvent::find(id);
					if (!item) break;
					data.b[0] = p[6];
					data.b[1] = p[7];
					data.b[2] = p[8];
					data.b[3] = p[9];
					item->update(data.f);
				} else if (type == 4) {
					FlightSimData *item = FlightSimData::find(id);
					if (!item) break;
					item->update(((char*)p)+6,len-6);
/// JB End
				}
				break;
			  case 0x03: // enable/disable
				if (len < 4) break;
				switch (p[2]) {
				  case 1:
					request_id_messages = 1;
					/* no break */
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
		usb_flightsim_free_packet();
	}
	if (enabled && request_id_messages) {
		request_id_messages = 0;
		for (FlightSimCommand *p = FlightSimCommand::first; p; p = p->next) {
			p->identify();
		}
/// JB
		for (FlightSimEvent *p = FlightSimEvent::first; p; p = p->next) {
			p->identify();
		}
		for (FlightSimData *p = FlightSimData::first; p; p=p->next) {
			p->identify();
		}
/// JB End
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



void FlightSimClass::xmit(const void *p1, uint8_t n1, const void *p2, uint8_t n2)
{
	if (!enabled || !usb_configuration) return;

	uint16_t total = n1 + n2;
	if (total > FLIGHTSIM_TX_SIZE) {
		xmit_big_packet(p1, n1, p2,  n2);
		return;
	}

	// handle small packets
	tx_noautoflush = 1;
	transfer_t *xfer = tx_transfer + tx_head;
	if (!wait_for_tx_buf(xfer)) return;

	if (total > tx_available) {
		// send previous packet
		uint8_t *txdata = (uint8_t *)(txbuffer + (tx_head * FLIGHTSIM_TX_SIZE) + (FLIGHTSIM_TX_SIZE - tx_available));
		while (tx_available > 0) {
			// fill packet
			*txdata++ = 0;
			tx_available--;
		}
		send_packet(xfer);
		xfer = tx_transfer + tx_head;
		if (!wait_for_tx_buf(xfer)) return;
	}

	uint8_t *txdata = (uint8_t *)(txbuffer + (tx_head * FLIGHTSIM_TX_SIZE) + (FLIGHTSIM_TX_SIZE - tx_available));
	memcpy(txdata, p1, n1);
	tx_available -= n1;
	txdata += n1;
	if (n2 > 0) {
		memcpy(txdata, p2, n2);
		tx_available -= n2;
	}
	if (tx_available == 0) {
		// packet filled, send it
		send_packet(xfer);
	} else {
		// wait for send until next SOF
		usb_start_sof_interrupts(FLIGHTSIM_INTERFACE);
	}
	tx_noautoflush = 0;
}

void FlightSimClass::xmit_big_packet(const void *p1, uint8_t n1, const void *p2, uint8_t n2)
{

	uint16_t remaining = n1 + n2;
	if (remaining > 255) {
		printf("Invalid flight sim packet length (>255)");
		return;
	}
	
	tx_noautoflush =1; // don't mess with my data, I'm working on it!

	transfer_t *xfer = tx_transfer + tx_head;
	if (!wait_for_tx_buf(xfer)) return; // after this, tx_available is guaranteed to be > 0

	bool part2 = false;
	uint8_t remainingPart1 = n1;
	const uint8_t *dataPtr = (const uint8_t*)p1;
	bool writeFragmentHeader = false;
	uint8_t fragmentCounter = 1;

	uint8_t *txdata = (uint8_t *)(txbuffer + (tx_head * FLIGHTSIM_TX_SIZE) + (FLIGHTSIM_TX_SIZE - tx_available));

	// fill first packet with whatever fits
	uint8_t partLen = tx_available > n1 ? n1 : tx_available;
	// copy first part, containing total packet length
	printf("%d bytes free, adding first %d bytes from p1, writing to %x\n", tx_available, partLen, txdata);

	memcpy(txdata, dataPtr, partLen);
	remainingPart1 -= partLen;
	txdata += partLen;
	tx_available -= partLen;
	if (remainingPart1) {
		// there still is data from the first part that
		// will go to the next packet. The boolean variable
		// part2 remains false
		remaining = remainingPart1+n2;
		dataPtr += partLen;
	} else {
		// maybe we have space for some data from the second part
		part2=true;
		// there is no need here to check whether tx_available is
		// bigger than n2. It's not. If it were, all the data
		// would have fit in a single packet and xmit_big_packet
		// would never have been called...
		printf("adding first %d bytes from p2, writing to %x\n", tx_available, txdata);
		remaining = n2;
		if (tx_available) {
			memcpy(txdata, p2, tx_available);
			remaining -= tx_available;
		}
		dataPtr = (const uint8_t*)p2 + tx_available;
	}
	
	// first packet filled, send it
	tx_available = 0;
	send_packet(xfer);
	xfer = tx_transfer + tx_head;

	writeFragmentHeader = true;
	printf("remaining bytes to send: %d\n", remaining);

	while (remaining >0) {
		if (!wait_for_tx_buf(xfer)) return;

		uint8_t *txdata = (uint8_t *)(txbuffer + (tx_head * FLIGHTSIM_TX_SIZE) + (FLIGHTSIM_TX_SIZE - tx_available));

		if (writeFragmentHeader) {
			printf("writing header of fragment %d to %x\n", fragmentCounter, txdata);
			*txdata++=(remaining+3 <= FLIGHTSIM_TX_SIZE) ? (uint8_t) remaining+3 : FLIGHTSIM_TX_SIZE;
			*txdata++=0xff;
			*txdata++=fragmentCounter++;
			tx_available -= 3;
		}
		if (!part2) {
			// we still need to send the first part
			uint8_t partLen = tx_available > remainingPart1 ? remainingPart1 : tx_available;
			printf("copying remaining %d bytes from first part to %x\n", partLen, txdata);
			memcpy(txdata, dataPtr, partLen);
			dataPtr += partLen;
			txdata += partLen;
			tx_available -= partLen;
			remaining -= partLen;
			remainingPart1 -= partLen;
			if (!remainingPart1) {
				part2=true;
				dataPtr = (const uint8_t*)p2;
			}
		}

		if (part2) {
			uint8_t partLen = tx_available > remaining ? remaining : tx_available;
			printf("copying %d bytes from second part to %x\n", partLen, txdata);
			if (partLen) {
				memcpy(txdata, dataPtr, partLen);
				remaining -= partLen;
				tx_available -= partLen;
				txdata += partLen;
				dataPtr += partLen;
			}
		} 
		writeFragmentHeader = true;
		
		if (!tx_available) {
			// packet filled, send it
			send_packet(xfer);
			xfer = tx_transfer + tx_head;
		} else {
			// send on next SOF
			printf("tx_available: %d\n", tx_available);
			usb_start_sof_interrupts(FLIGHTSIM_INTERFACE);
		}
	}
	tx_noautoflush = 0;  // data is ready to be transmitted on start of USB token
}

extern "C" {
void usb_flightsim_configure() {
	printf("Flightsim_configure\n");
	memset(tx_transfer, 0, sizeof(tx_transfer));
	tx_head = 0;
	tx_available = 0;
	memset(rx_transfer, 0, sizeof(rx_transfer));
	printf("tx_transfer: %x\n", tx_transfer);
	printf("txbuffer:    %x\n", txbuffer);
	printf("rx_transfer: %x\n", rx_transfer);
	printf("rxbuffer:    %x\n", rx_buffer);
	rx_head = 0;
	rx_tail = 0;
	rx_available = 0;
	usb_config_rx(FLIGHTSIM_RX_ENDPOINT, FLIGHTSIM_RX_SIZE, 0, rx_event);
	usb_config_tx(FLIGHTSIM_TX_ENDPOINT, FLIGHTSIM_TX_SIZE, 0, NULL); // TODO: is ZLP needed?
	int i;
	for (i=0; i < RX_NUM; i++) rx_queue_transfer(i);
	tx_noautoflush = 0;
	transmit_previous_timeout = 0;

}

// This gets called from usb_isr when a USB start token arrives.
// If we have a packet to transmit AND transmission isn't disabled 
// by tx_noautoflush, we fill it up with zeros and send it out 
// to USB
void usb_flightsim_flush_output(void)
{
	if (tx_noautoflush == 0 && tx_available > 0) {
		printf(" flush, %d %d\n", FLIGHTSIM_TX_SIZE, tx_available);
		uint32_t head = tx_head;
		transfer_t *xfer = tx_transfer + head;
		uint8_t *txbuf = txbuffer + (head * FLIGHTSIM_TX_SIZE);
		uint8_t *txPtr = txbuf + (FLIGHTSIM_TX_SIZE - tx_available);
		while (tx_available>0) {
			*txPtr++ = 0;
			tx_available--;
		}
		usb_prepare_transfer(xfer, txbuf, FLIGHTSIM_TX_SIZE, 0);
		arm_dcache_flush_delete(txbuf, FLIGHTSIM_TX_SIZE);
		usb_transmit(FLIGHTSIM_TX_ENDPOINT, xfer);
		if (++head >= TX_NUM) head = 0;
		tx_head = head;
		usb_stop_sof_interrupts(FLIGHTSIM_INTERFACE);
	}
}

static bool wait_for_tx_buf(transfer_t *xfer) {
	uint32_t wait_begin_at = systick_millis_count;
	while (!tx_available) {
		uint32_t status = usb_transfer_status(xfer);
		if (!(status & 0x80)) {
			if (status & 0x68) {
				// TODO: what if status has errors???
			}
			tx_available = FLIGHTSIM_TX_SIZE;
			transmit_previous_timeout = 0;
			break;
		}
		if (systick_millis_count - wait_begin_at > TX_TIMEOUT_MSEC) {
			transmit_previous_timeout = 1;
		}
		if (transmit_previous_timeout) {
			printf("Flight sim tx timeout");
			return false;
		}
		if (!usb_configuration) return false;
		yield();
	}
	return true;
}

static void send_packet(transfer_t *xfer) {
	uint32_t head = tx_head;
	uint8_t *txbuf = txbuffer + (tx_head * FLIGHTSIM_TX_SIZE);
	usb_prepare_transfer(xfer, txbuf, FLIGHTSIM_TX_SIZE, 0);
	arm_dcache_flush_delete(txbuf, FLIGHTSIM_TX_SIZE);
	usb_transmit(FLIGHTSIM_TX_ENDPOINT, xfer);
	if (++head >= TX_NUM) head = 0;
	tx_head = head;
	usb_stop_sof_interrupts(FLIGHTSIM_INTERFACE);
}

static void rx_queue_transfer(int i)
{
	NVIC_DISABLE_IRQ(IRQ_USB1);
	void *buffer = rx_buffer + i * FLIGHTSIM_RX_SIZE;
	usb_prepare_transfer(rx_transfer + i, buffer, FLIGHTSIM_RX_SIZE, i);
	arm_dcache_delete(buffer, FLIGHTSIM_RX_SIZE);
	usb_receive(FLIGHTSIM_RX_ENDPOINT, rx_transfer + i);
	NVIC_ENABLE_IRQ(IRQ_USB1);
}

static void rx_event(transfer_t *t)
{
	int len = FLIGHTSIM_RX_SIZE - ((t->status >> 16) & 0x7FFF);
	len &= 0xFFFC; // MIDI packets must be multiple of 4 bytes
	int i = t->callback_param;
//	printf("Flight sim rx event, len=%d, i=%d", len, i);
	if (len == FLIGHTSIM_RX_SIZE) {
		uint32_t head = rx_head;
		if (++head > RX_NUM) head = 0;
		rx_list[head] = i;
		rx_head = head;
		rx_available += len;
	} else {
		// received packet with invalid length
		rx_queue_transfer(i);
	}
//	printf(" ...done\n");
}

static void* usb_flightsim_get_packet(void)
{
	void *result = NULL;
	NVIC_DISABLE_IRQ(IRQ_USB1);
	uint32_t tail = rx_tail;
	if (tail != rx_head) {
		if (++tail > RX_NUM) tail = 0;
		uint32_t i = rx_list[tail];
		result = rx_buffer + i * FLIGHTSIM_RX_SIZE;
		rx_available -= FLIGHTSIM_RX_SIZE;
	}
	NVIC_ENABLE_IRQ(IRQ_USB1);
	return result;
}

static void usb_flightsim_free_packet() {
	NVIC_DISABLE_IRQ(IRQ_USB1);
	uint32_t tail = rx_tail;
	if (tail != rx_head) {
		if (++tail > RX_NUM) tail = 0;
		uint32_t i = rx_list[tail];
		rx_tail = tail;
		rx_queue_transfer(i);
	}
	NVIC_ENABLE_IRQ(IRQ_USB1);
}

}  // extern "C"

#endif // F_CPU
#endif // FLIGHTSIM_INTERFACE
