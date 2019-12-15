/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2019 PJRC.COM, LLC.
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
#include "usb_seremu.h"
#include "core_pins.h" // for yield()
#include <string.h> // for memcpy()
#include "avr/pgmspace.h" // for PROGMEM, DMAMEM, FASTRUN
#include "debug/printf.h"
#include "core_pins.h"

#if defined(SEREMU_INTERFACE) && !defined(CDC_STATUS_INTERFACE) && !defined(CDC_DATA_INTERFACE)

static volatile uint8_t tx_noautoflush=0;
extern volatile uint8_t usb_high_speed;

// TODO: should be 2 different timeouts, high speed (480) vs full speed (12)
#define TRANSMIT_FLUSH_TIMEOUT  75   /* in microseconds */
static void timer_config(void (*callback)(void), uint32_t microseconds);
static void timer_start_oneshot();
static void timer_stop();
static void usb_seremu_flush_callback(void);

#define TX_NUM   12
static transfer_t tx_transfer[TX_NUM] __attribute__ ((used, aligned(32)));
DMAMEM static uint8_t txbuffer[SEREMU_TX_SIZE * TX_NUM] __attribute__ ((aligned(32)));
static uint8_t tx_head=0;
static uint16_t tx_available=0;

#define RX_NUM  8
static transfer_t rx_transfer[RX_NUM] __attribute__ ((used, aligned(32)));
DMAMEM static uint8_t rx_buffer[SEREMU_RX_SIZE * RX_NUM] __attribute__ ((aligned(32)));
static uint16_t rx_index[RX_NUM];
static volatile uint8_t rx_head;
static volatile uint8_t rx_tail;
static uint8_t rx_list[RX_NUM + 1];
static volatile uint32_t rx_available;
static void rx_queue_transfer(int i);
static void rx_event(transfer_t *t);


void usb_seremu_configure(void)
{
	printf("usb_seremu_configure\n");
	memset(tx_transfer, 0, sizeof(tx_transfer));
	tx_head = 0;
	tx_available = 0;
	memset(rx_transfer, 0, sizeof(rx_transfer));
	memset(rx_index, 0, sizeof(rx_index));
	rx_head = 0;
	rx_tail = 0;
	rx_available = 0;
	usb_config_rx(SEREMU_RX_ENDPOINT, SEREMU_RX_SIZE, 0, rx_event); // SEREMU_RX_SIZE = 32
	usb_config_tx(SEREMU_TX_ENDPOINT, SEREMU_TX_SIZE, 0, NULL);     // SEREMU_TX_SIZE = 64
	int i;
	for (i=0; i < RX_NUM; i++) rx_queue_transfer(i);
	timer_config(usb_seremu_flush_callback, TRANSMIT_FLUSH_TIMEOUT);
}


/*************************************************************************/
/**                               Receive                               **/
/*************************************************************************/

static void rx_queue_transfer(int i)
{
	NVIC_DISABLE_IRQ(IRQ_USB1);
	void *buffer = rx_buffer + i * SEREMU_RX_SIZE;
	usb_prepare_transfer(rx_transfer + i, buffer, SEREMU_RX_SIZE, i);
	arm_dcache_delete(buffer, SEREMU_RX_SIZE);
	usb_receive(SEREMU_RX_ENDPOINT, rx_transfer + i);
	NVIC_ENABLE_IRQ(IRQ_USB1);
}

// called by USB interrupt when any packet is received
static void rx_event(transfer_t *t)
{
	int len = SEREMU_RX_SIZE - ((t->status >> 16) & 0x7FFF);
	int i = t->callback_param;
	printf("rx event, len=%d, i=%d\n", len, i);
	if (len == SEREMU_RX_SIZE && rx_buffer[i * SEREMU_RX_SIZE] != 0) {
		// received a packet with data
		uint32_t head = rx_head;
		rx_index[i] = 0;
		if (++head > RX_NUM) head = 0;
		rx_list[head] = i;
		rx_head = head;
		rx_available += len;
		// TODO: trigger serialEvent
	} else {
		// received a short packet - should never happen with HID
		rx_queue_transfer(i);
	}
}

// get the next character, or -1 if nothing received
int usb_seremu_getchar(void)
{
	uint32_t tail = rx_tail;

	if (tail == rx_head) return -1;
	if (++tail > RX_NUM) tail = 0;
	uint32_t i = rx_list[tail];
	uint32_t index = rx_index[i];
	uint8_t *p = rx_buffer + i * SEREMU_RX_SIZE + index;
	int c = *p;
	if (++index >= SEREMU_RX_SIZE || *(p+1) == 0) {
		rx_tail = tail;
		rx_queue_transfer(i);
	} else {
		rx_index[i] = index;
	}
	return c;
}

// peek at the next character, or -1 if nothing received
int usb_seremu_peekchar(void)
{
	uint32_t tail = rx_tail;
	if (tail == rx_head) return -1;
	if (++tail > RX_NUM) tail = 0;
	uint32_t i = rx_list[tail];
	return rx_buffer[i * SEREMU_RX_SIZE + rx_index[i]];
}

// number of bytes available in the receive buffer
int usb_seremu_available(void)
{
	uint32_t tail = rx_tail;
	if (tail == rx_head) return 0;
	// TODO: how much is actually available?
	return 1;
}

// discard any buffered input
void usb_seremu_flush_input(void)
{
	uint32_t tail = rx_tail;
	while (tail != rx_head) {
		if (++tail > RX_NUM) tail = 0;
		uint32_t i = rx_list[tail];
		rx_queue_transfer(i);
		rx_tail = tail;
	}
}


/*************************************************************************/
/**                               Transmit                              **/
/*************************************************************************/


// When the PC isn't listening, how long do we wait before discarding data?  If this is
// too short, we risk losing data during the stalls that are common with ordinary desktop
// software.  If it's too long, we stall the user's program when no software is running.
#define TX_TIMEOUT_MSEC 50

// When we've suffered the transmit timeout, don't wait again until the computer
// begins accepting data.  If no software is running to receive, we'll just discard
// data as rapidly as Serial.print() can generate it, until there's something to
// actually receive it.
static uint8_t transmit_previous_timeout=0;


// transmit a character.  0 returned on success, -1 on error
int usb_seremu_putchar(uint8_t c)
{
	return usb_seremu_write(&c, 1);
}

extern volatile uint32_t systick_millis_count;
static void timer_config(void (*callback)(void), uint32_t microseconds);
static void timer_start_oneshot();
static void timer_stop();

static void timer_config(void (*callback)(void), uint32_t microseconds)
{
	usb_timer0_callback = callback;
	USB1_GPTIMER0CTRL = 0;
	USB1_GPTIMER0LD = microseconds - 1;
	USB1_USBINTR |= USB_USBINTR_TIE0;
}

static void timer_start_oneshot(void)
{
	// restarts timer if already running (retriggerable one-shot)
	USB1_GPTIMER0CTRL = USB_GPTIMERCTRL_GPTRUN | USB_GPTIMERCTRL_GPTRST;
}

static void timer_stop(void)
{
	USB1_GPTIMER0CTRL = 0;
}


void tx_zero_pad(void)
{
	if (!tx_available) return;
	uint8_t *txdata = txbuffer + (tx_head * SEREMU_TX_SIZE) + (SEREMU_TX_SIZE - tx_available);
	memset(txdata, 0, tx_available);
	tx_available = 0;
}

void tx_queue_transfer(void)
{
	transfer_t *xfer = tx_transfer + tx_head;
	uint8_t *txbuf = txbuffer + (tx_head * SEREMU_TX_SIZE);
	usb_prepare_transfer(xfer, txbuf, SEREMU_TX_SIZE, 0);
	arm_dcache_flush_delete(txbuf, SEREMU_TX_SIZE);
	usb_transmit(SEREMU_TX_ENDPOINT, xfer);
	if (++tx_head >= TX_NUM) tx_head = 0;
}

int usb_seremu_write(const void *buffer, uint32_t size)
{
	uint32_t sent=0;
	const uint8_t *data = (const uint8_t *)buffer;

	if (!usb_configuration) return 0;
	while (size > 0) {
		transfer_t *xfer = tx_transfer + tx_head;
		int waiting=0;
		uint32_t wait_begin_at=0;
		while (!tx_available) {
			uint32_t status = usb_transfer_status(xfer);
			if (!(status & 0x80)) {
				if (status & 0x68) {
					// TODO: what if status has errors???
					printf("ERROR status = %x, i=%d, ms=%u\n",
						status, tx_head, systick_millis_count);
				}
				tx_available = SEREMU_TX_SIZE;
				transmit_previous_timeout = 0;
				break;
			}
			if (!waiting) {
				wait_begin_at = systick_millis_count;
				waiting = 1;
			}
			if (transmit_previous_timeout) return sent;
			if (systick_millis_count - wait_begin_at > TX_TIMEOUT_MSEC) {
				// waited too long, assume the USB host isn't listening
				transmit_previous_timeout = 1;
				return sent;
			}
			if (!usb_configuration) return sent;
			yield();
		}
		uint8_t *txdata = txbuffer + (tx_head * SEREMU_TX_SIZE) + (SEREMU_TX_SIZE - tx_available);
		if (size >= tx_available) {
			memcpy(txdata, data, tx_available);
			size -= tx_available;
			sent += tx_available;
			data += tx_available;
			tx_available = 0;
			tx_queue_transfer();
			timer_stop();
		} else {
			memcpy(txdata, data, size);
			tx_available -= size;
			sent += size;
			size = 0;
			timer_start_oneshot();
		}
	}
	return sent;
}

int usb_seremu_write_buffer_free(void)
{
	return 1;
}

void usb_seremu_flush_output(void)
{
	if (!usb_configuration) return;
	if (tx_available == 0) return;
	tx_noautoflush = 1;
	tx_zero_pad();
	tx_queue_transfer();
	tx_noautoflush = 0;
}

static void usb_seremu_flush_callback(void)
{
	if (tx_noautoflush) return;
	tx_zero_pad();
	tx_queue_transfer();
}

#endif // SEREMU_INTERFACE
