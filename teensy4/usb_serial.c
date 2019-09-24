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
#include "usb_serial.h"
#include "core_pins.h"// for delay()
//#include "HardwareSerial.h"
#include <string.h> // for memcpy()

#include "debug/printf.h"
#include "core_pins.h"

// defined by usb_dev.h -> usb_desc.h
#if defined(CDC_STATUS_INTERFACE) && defined(CDC_DATA_INTERFACE)
//#if F_CPU >= 20000000

uint32_t usb_cdc_line_coding[2];
volatile uint32_t usb_cdc_line_rtsdtr_millis;
volatile uint8_t usb_cdc_line_rtsdtr=0;
volatile uint8_t usb_cdc_transmit_flush_timer=0;

//static usb_packet_t *rx_packet=NULL;
//static usb_packet_t *tx_packet=NULL;
static volatile uint8_t tx_noautoflush=0;

// TODO: should be 2 different timeouts, high speed (480) vs full speed (12)
#define TRANSMIT_FLUSH_TIMEOUT	75   /* in microseconds */

static void timer_config(void (*callback)(void), uint32_t microseconds);
static void timer_start_oneshot();
static void timer_stop();
static void usb_serial_flush_callback(void);

#define TX_NUM   7
#define TX_SIZE  256  /* should be a multiple of CDC_TX_SIZE */
static transfer_t tx_transfer[TX_NUM] __attribute__ ((used, aligned(32)));
static uint8_t txbuffer[TX_SIZE * TX_NUM];
static uint8_t tx_head=0;
static uint16_t tx_available=0;

#define RX_NUM  3
static transfer_t rx_transfer[RX_NUM] __attribute__ ((used, aligned(32)));
static uint8_t rx_buffer[RX_NUM * CDC_RX_SIZE];
static uint16_t rx_count[RX_NUM];
static uint16_t rx_index[RX_NUM];

static void rx_event(transfer_t *t)
{
	int len = CDC_RX_SIZE - ((t->status >> 16) & 0x7FFF);
	int index = t->callback_param;
	//printf("rx event, len=%d, i=%d\n", len, index);
	rx_count[index] = len;
	rx_index[index] = 0;
}

void usb_serial_reset(void)
{
	printf("usb_serial_reset\n");
	// deallocate all transfer descriptors
}

void usb_serial_configure(void)
{
	printf("usb_serial_configure\n");
	memset(tx_transfer, 0, sizeof(tx_transfer));
	tx_head = 0;
	tx_available = 0;
	memset(rx_transfer, 0, sizeof(rx_transfer));
	memset(rx_count, 0, sizeof(rx_count));
	memset(rx_index, 0, sizeof(rx_index));
	usb_config_tx(CDC_ACM_ENDPOINT, CDC_ACM_SIZE, 0, NULL);
	usb_config_rx(CDC_RX_ENDPOINT, CDC_RX_SIZE, 0, rx_event);
	usb_config_tx(CDC_TX_ENDPOINT, CDC_TX_SIZE, 0, NULL);
	usb_prepare_transfer(rx_transfer + 0, rx_buffer + 0, CDC_RX_SIZE, 0);
	usb_receive(CDC_RX_ENDPOINT, rx_transfer + 0);
	timer_config(usb_serial_flush_callback, TRANSMIT_FLUSH_TIMEOUT);
}


// get the next character, or -1 if nothing received
int usb_serial_getchar(void)
{
	if (rx_index[0] < rx_count[0]) {
		int c = rx_buffer[rx_index[0]++];
		if (rx_index[0] >= rx_count[0]) {
			// reschedule transfer
			usb_prepare_transfer(rx_transfer + 0, rx_buffer + 0, CDC_RX_SIZE, 0);
			usb_receive(CDC_RX_ENDPOINT, rx_transfer + 0);
		}
		return c;
	}
	return -1;
}

// peek at the next character, or -1 if nothing received
int usb_serial_peekchar(void)
{
	if (rx_index[0] < rx_count[0]) {
		return rx_buffer[rx_index[0]];
	}

	return -1;
}

// number of bytes available in the receive buffer
int usb_serial_available(void)
{
	return rx_count[0] - rx_index[0];
}

// read a block of bytes to a buffer
int usb_serial_read(void *buffer, uint32_t size)
{
	// Quick and dirty to make it at least limp...
	uint8_t *p = (uint8_t *)buffer;
	uint32_t count=0;

	while (size) {
		int ch = usb_serial_getchar();
		if (ch == -1) break;
		*p++ = (uint8_t)ch;
		size--;
		count++;
	}
	return count;
}

// discard any buffered input
void usb_serial_flush_input(void)
{
	if (rx_index[0] < rx_count[0]) {
		rx_index[0] = rx_count[0];
		usb_prepare_transfer(rx_transfer + 0, rx_buffer + 0, CDC_RX_SIZE, 0);
		usb_receive(CDC_RX_ENDPOINT, rx_transfer + 0);
	}
}

// When the PC isn't listening, how long do we wait before discarding data?  If this is
// too short, we risk losing data during the stalls that are common with ordinary desktop
// software.  If it's too long, we stall the user's program when no software is running.
#define TX_TIMEOUT_MSEC 120


// When we've suffered the transmit timeout, don't wait again until the computer
// begins accepting data.  If no software is running to receive, we'll just discard
// data as rapidly as Serial.print() can generate it, until there's something to
// actually receive it.
static uint8_t transmit_previous_timeout=0;


// transmit a character.  0 returned on success, -1 on error
int usb_serial_putchar(uint8_t c)
{
	return usb_serial_write(&c, 1);
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


int usb_serial_write(const void *buffer, uint32_t size)
{
	uint32_t sent=0;
	const uint8_t *data = (const uint8_t *)buffer;

	if (!usb_configuration) return 0;
	while (size > 0) {
		transfer_t *xfer = tx_transfer + tx_head;
		int waiting=0;
		uint32_t wait_begin_at=0;
		while (!tx_available) {
			//digitalWriteFast(3, HIGH);
			uint32_t status = usb_transfer_status(xfer);
			if (!(status & 0x80)) {
				if (status & 0x68) {
					// TODO: what if status has errors???
					printf("ERROR status = %x, i=%d, ms=%u\n",
						status, tx_head, systick_millis_count);
				}
				tx_available = TX_SIZE;
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
				//printf("\nstop, waited too long\n");
				//printf("status = %x\n", status);
				//printf("tx head=%d\n", tx_head);
				//printf("TXFILLTUNING=%08lX\n", USB1_TXFILLTUNING);
				//usb_print_transfer_log();
				//while (1) ;
			}
			if (!usb_configuration) return sent;
			yield();
		}
		//digitalWriteFast(3, LOW);
		uint8_t *txdata = txbuffer + (tx_head * TX_SIZE) + (TX_SIZE - tx_available);
		if (size >= tx_available) {
			memcpy(txdata, data, tx_available);
			//*(txbuffer + (tx_head * TX_SIZE)) = 'A' + tx_head; // to see which buffer
			//*(txbuffer + (tx_head * TX_SIZE) + 1) = ' '; // really see it
			usb_prepare_transfer(xfer, txbuffer + (tx_head * TX_SIZE), TX_SIZE, 0);
			usb_transmit(CDC_TX_ENDPOINT, xfer);
			if (++tx_head >= TX_NUM) tx_head = 0;
			size -= tx_available;
			sent += tx_available;
			data += tx_available;
			tx_available = 0;
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

int usb_serial_write_buffer_free(void)
{
	uint32_t sum = 0;
	tx_noautoflush = 1;
	for (uint32_t i=0; i < TX_NUM; i++) {
		if (i == tx_head) continue;
		if (!(usb_transfer_status(tx_transfer + i) & 0x80)) sum += TX_SIZE;
	}
	tx_noautoflush = 0;
	return sum;
}

void usb_serial_flush_output(void)
{
	if (!usb_configuration) return;
	if (tx_available == 0) return;
	tx_noautoflush = 1;
	transfer_t *xfer = tx_transfer + tx_head;
	usb_prepare_transfer(xfer, txbuffer + (tx_head * TX_SIZE), TX_SIZE - tx_available, 0);
	usb_transmit(CDC_TX_ENDPOINT, xfer);
	if (++tx_head >= TX_NUM) tx_head = 0;
	tx_available = 0;
	tx_noautoflush = 0;
}

static void usb_serial_flush_callback(void)
{
	if (tx_noautoflush) return;
	if (!usb_configuration) return;
	if (tx_available == 0) return;
	//printf("flush callback, %d bytes\n", TX_SIZE - tx_available);
	transfer_t *xfer = tx_transfer + tx_head;
	usb_prepare_transfer(xfer, txbuffer + (tx_head * TX_SIZE), TX_SIZE - tx_available, 0);
	usb_transmit(CDC_TX_ENDPOINT, xfer);
	if (++tx_head >= TX_NUM) tx_head = 0;
	tx_available = 0;
}



//#endif // F_CPU
#endif // CDC_STATUS_INTERFACE && CDC_DATA_INTERFACE
