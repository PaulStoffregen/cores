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
#include "avr/pgmspace.h" // for PROGMEM, DMAMEM, FASTRUN

#include "debug/printf.h"
#include "core_pins.h"

// defined by usb_dev.h -> usb_desc.h
#if defined(CDC3_STATUS_INTERFACE) && defined(CDC3_DATA_INTERFACE)

uint32_t usb_cdc3_line_coding[2];
volatile uint32_t usb_cdc3_line_rtsdtr_millis;
volatile uint8_t usb_cdc3_line_rtsdtr=0;
volatile uint8_t usb_cdc3_transmit_flush_timer=0;

static volatile uint8_t tx_noautoflush=0;
extern volatile uint8_t usb_high_speed;

// TODO: should be 2 different timeouts, high speed (480) vs full speed (12)
#define TRANSMIT_FLUSH_TIMEOUT	75   /* in microseconds */

static void timer_config(void (*callback)(void), uint32_t microseconds);
static void timer_start_oneshot();
static void timer_stop();
static void usb_serial3_flush_callback(void);

#define TX_NUM   4
#define TX_SIZE  2048 /* should be a multiple of CDC_TX_SIZE */
static transfer_t tx_transfer[TX_NUM] __attribute__ ((used, aligned(32)));
DMAMEM static uint8_t txbuffer[TX_SIZE * TX_NUM] __attribute__ ((aligned(32)));
static uint8_t tx_head=0;
static uint16_t tx_available=0;
static uint16_t tx_packet_size=0;

#define RX_NUM  8
static transfer_t rx_transfer[RX_NUM] __attribute__ ((used, aligned(32)));
DMAMEM static uint8_t rx_buffer[RX_NUM * CDC_RX_SIZE_480] __attribute__ ((aligned(32)));
static uint16_t rx_count[RX_NUM];
static uint16_t rx_index[RX_NUM];
static uint16_t rx_packet_size=0;
static volatile uint8_t rx_head;
static volatile uint8_t rx_tail;
static uint8_t rx_list[RX_NUM + 1];
static volatile uint32_t rx_available;
static void rx_queue_transfer(int i);
static void rx_event(transfer_t *t);


void usb_serial3_configure(void)
{
	int i;

	printf("usb_serial3_configure\n");
	if (usb_high_speed) {
		tx_packet_size = CDC_TX_SIZE_480;
		rx_packet_size = CDC_RX_SIZE_480;
	} else {
		tx_packet_size = CDC_TX_SIZE_12;
		rx_packet_size = CDC_RX_SIZE_12;
	}
	memset(tx_transfer, 0, sizeof(tx_transfer));
	tx_head = 0;
	tx_available = 0;
	memset(rx_transfer, 0, sizeof(rx_transfer));
	memset(rx_count, 0, sizeof(rx_count));
	memset(rx_index, 0, sizeof(rx_index));
	rx_head = 0;
	rx_tail = 0;
	rx_available = 0;
	usb_config_tx(CDC3_ACM_ENDPOINT, CDC_ACM_SIZE, 0, NULL); // size same 12 & 480
	usb_config_rx(CDC3_RX_ENDPOINT, rx_packet_size, 0, rx_event);
	usb_config_tx(CDC3_TX_ENDPOINT, tx_packet_size, 1, NULL);
	for (i=0; i < RX_NUM; i++) rx_queue_transfer(i);
	timer_config(usb_serial3_flush_callback, TRANSMIT_FLUSH_TIMEOUT);
}


/*************************************************************************/
/**                               Receive                               **/
/*************************************************************************/

static void rx_queue_transfer(int i)
{
	NVIC_DISABLE_IRQ(IRQ_USB1);
	printf("rx queue i=%d\n", i);
	void *buffer = rx_buffer + i * CDC_RX_SIZE_480;
	usb_prepare_transfer(rx_transfer + i, buffer, rx_packet_size, i);
	arm_dcache_delete(buffer, rx_packet_size);
	usb_receive(CDC3_RX_ENDPOINT, rx_transfer + i);
	NVIC_ENABLE_IRQ(IRQ_USB1);
}

// called by USB interrupt when any packet is received
static void rx_event(transfer_t *t)
{
	int len = rx_packet_size - ((t->status >> 16) & 0x7FFF);
	int i = t->callback_param;
	printf("rx event, len=%d, i=%d\n", len, i);
	if (len > 0) {
		// received a packet with data
		uint32_t head = rx_head;
		if (head != rx_tail) {
			// a previous packet is still buffered
			uint32_t ii = rx_list[head];
			uint32_t count = rx_count[ii];
			if (len <= CDC_RX_SIZE_480 - count) {
				// previous buffer has enough free space for this packet's data
				memcpy(rx_buffer + ii * CDC_RX_SIZE_480 + count,
					rx_buffer + i * CDC_RX_SIZE_480, len);
				rx_count[ii] = count + len;
				rx_available += len;
				rx_queue_transfer(i);
				// TODO: trigger serialEvent
				return;
			}
		}
		// add this packet to rx_list
		rx_count[i] = len;
		rx_index[i] = 0;
		if (++head > RX_NUM) head = 0;
		rx_list[head] = i;
		rx_head = head;
		rx_available += len;
		// TODO: trigger serialEvent
	} else {
		// received a zero length packet
		rx_queue_transfer(i);
	}
}

//static int maxtimes=0;

// read a block of bytes to a buffer
int usb_serial3_read(void *buffer, uint32_t size)
{
	uint8_t *p = (uint8_t *)buffer;
	uint32_t count=0;

	NVIC_DISABLE_IRQ(IRQ_USB1);
	//if (++maxtimes > 15) while (1) ;
	uint32_t tail = rx_tail;
	//printf("usb_serial3_read, size=%d, tail=%d, head=%d\n", size, tail, rx_head);
	while (count < size && tail != rx_head) {
		if (++tail > RX_NUM) tail = 0;
		uint32_t i = rx_list[tail];
		uint32_t len = size - count;
		uint32_t avail = rx_count[i] - rx_index[i];
		 //printf("usb_serial3_read, count=%d, size=%d, i=%d, index=%d, len=%d, avail=%d, c=%c\n",
		  //count, size, i, rx_index[i], len, avail, rx_buffer[i * CDC_RX_SIZE_480]);
		if (avail > len) {
			// partially consume this packet
			memcpy(p, rx_buffer + i * CDC_RX_SIZE_480 + rx_index[i], len);
			rx_available -= len;
			rx_index[i] += len;
			count += len;
		} else {
			// fully consume this packet
			memcpy(p, rx_buffer + i * CDC_RX_SIZE_480 + rx_index[i], avail);
			p += avail;
			rx_available -= avail;
			count += avail;
			rx_tail = tail;
			rx_queue_transfer(i);
		}
	}
	NVIC_ENABLE_IRQ(IRQ_USB1);
	return count;
}

// peek at the next character, or -1 if nothing received
int usb_serial3_peekchar(void)
{
	uint32_t tail = rx_tail;
	if (tail == rx_head) return -1;
	if (++tail > RX_NUM) tail = 0;
	uint32_t i = rx_list[tail];
	return rx_buffer[i * CDC_RX_SIZE_480 + rx_index[i]];
}

// number of bytes available in the receive buffer
int usb_serial3_available(void)
{
	return rx_available;
}

// discard any buffered input
void usb_serial3_flush_input(void)
{
	uint32_t tail = rx_tail;
	while (tail != rx_head) {
		if (++tail > RX_NUM) tail = 0;
		uint32_t i = rx_list[tail];
		rx_available -= rx_count[i] - rx_index[i];
		rx_queue_transfer(i);
		rx_tail = tail;
	}
}


// get the next character, or -1 if nothing received
int usb_serial3_getchar(void)
{
	uint8_t c;
	if (usb_serial3_read(&c, 1)) return c;
	return -1;
}













/*************************************************************************/
/**                               Transmit                              **/
/*************************************************************************/


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
int usb_serial3_putchar(uint8_t c)
{
	return usb_serial3_write(&c, 1);
}

extern volatile uint32_t systick_millis_count;

static void timer_config(void (*callback)(void), uint32_t microseconds);
static void timer_start_oneshot();
static void timer_stop();

static void quadtimer_isr(void)
{
	TMR1_SCTRL3 = 0;
	usb_serial3_flush_callback();
}

static void timer_config(void (*callback)(void), uint32_t microseconds)
{
	// Both USB timers are already used with USB_TRIPLE_SERIAL
	// Ideally we should have a software layer to extend the timers
	// to any many USB interfaces as required.  But until that
	// glorious future, as a quick hack we will commandeer Quad
	// Timer #1 channel 3 (which isn't used by any PWM pin) and
	// hope no other software needs it or it's interrupt.  The
	// other 3 channels of Quad Timer #1 are normally used for PWM
	// which doesn't use interrupts, so this is (probably) the
	// safest Quad Timer channel to commandeer for an interrupt
	// that the other 3 channels (hopefully) won't use.
	TMR1_CTRL3 = 0;
	TMR1_SCTRL3 = 0;
	attachInterruptVector(IRQ_QTIMER1, quadtimer_isr);
	NVIC_ENABLE_IRQ(IRQ_QTIMER1);
	// kludge - both inputs ignored and hard-coded into other functions
}

static void timer_start_oneshot(void)
{
	TMR1_CTRL3 = 0;
	TMR1_CNTR3 = 0;
	TMR1_COMP13 = TRANSMIT_FLUSH_TIMEOUT * (F_BUS_ACTUAL >> 10) / (16000000 >> 10);
	TMR1_SCTRL3 = TMR_SCTRL_TCFIE;
	TMR1_CTRL3 = TMR_CTRL_CM(1) | TMR_CTRL_PCS(12) | TMR_CTRL_ONCE;
}

static void timer_stop(void)
{
	TMR1_CTRL3 = 0;
}


int usb_serial3_write(const void *buffer, uint32_t size)
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
			uint8_t *txbuf = txbuffer + (tx_head * TX_SIZE);
			usb_prepare_transfer(xfer, txbuf, TX_SIZE, 0);
			arm_dcache_flush_delete(txbuf, TX_SIZE);
			usb_transmit(CDC3_TX_ENDPOINT, xfer);
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

int usb_serial3_write_buffer_free(void)
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

void usb_serial3_flush_output(void)
{

	if (!usb_configuration) return;
	if (tx_available == 0) return;
	tx_noautoflush = 1;
	transfer_t *xfer = tx_transfer + tx_head;
	uint8_t *txbuf = txbuffer + (tx_head * TX_SIZE);
	uint32_t txnum = TX_SIZE - tx_available;
	usb_prepare_transfer(xfer, txbuf, txnum, 0);
	arm_dcache_flush_delete(txbuf, txnum);
	usb_transmit(CDC3_TX_ENDPOINT, xfer);
	if (++tx_head >= TX_NUM) tx_head = 0;
	tx_available = 0;
	tx_noautoflush = 0;
}

static void usb_serial3_flush_callback(void)
{
	if (tx_noautoflush) return;
	if (!usb_configuration) return;
	if (tx_available == 0) return;
	//printf("flush callback, %d bytes\n", TX_SIZE - tx_available);
	transfer_t *xfer = tx_transfer + tx_head;
	uint8_t *txbuf = txbuffer + (tx_head * TX_SIZE);
	uint32_t txnum = TX_SIZE - tx_available;
	usb_prepare_transfer(xfer, txbuf, txnum, 0);
	arm_dcache_flush_delete(txbuf, txnum);
	usb_transmit(CDC3_TX_ENDPOINT, xfer);
	if (++tx_head >= TX_NUM) tx_head = 0;
	tx_available = 0;
}



#endif // CDC3_STATUS_INTERFACE && CDC3_DATA_INTERFACE
