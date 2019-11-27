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

#include "HardwareSerial.h"
#include "core_pins.h"
#include "Arduino.h"
//#include "debug/printf.h"

/*typedef struct {
        const uint32_t VERID;
        const uint32_t PARAM;
        volatile uint32_t GLOBAL;
        volatile uint32_t PINCFG;
        volatile uint32_t BAUD;
        volatile uint32_t STAT;
        volatile uint32_t CTRL;
        volatile uint32_t DATA;
        volatile uint32_t MATCH;
        volatile uint32_t MODIR;
        volatile uint32_t FIFO;
        volatile uint32_t WATER;
} IMXRT_LPUART_t; */

//. From Onewire utility files
#define PIN_TO_BASEREG(pin)             (portOutputRegister(pin))
#define PIN_TO_BITMASK(pin)             (digitalPinToBitMask(pin))
#define IO_REG_TYPE uint32_t
#define IO_REG_BASE_ATTR
#define IO_REG_MASK_ATTR
#define DIRECT_READ(base, mask)         ((*((base)+2) & (mask)) ? 1 : 0)
#define DIRECT_MODE_INPUT(base, mask)   (*((base)+1) &= ~(mask))
#define DIRECT_MODE_OUTPUT(base, mask)  (*((base)+1) |= (mask))
#define DIRECT_WRITE_LOW(base, mask)    (*((base)+34) = (mask))
#define DIRECT_WRITE_HIGH(base, mask)   (*((base)+33) = (mask))

#define UART_CLOCK 24000000

#if defined(__IMXRT1052__)   
SerialEventCheckingFunctionPointer HardwareSerial::serial_event_handler_checks[8] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
#else
SerialEventCheckingFunctionPointer HardwareSerial::serial_event_handler_checks[7] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
#endif
uint8_t HardwareSerial::serial_event_handlers_active = 0;


#define CTRL_ENABLE 		(LPUART_CTRL_TE | LPUART_CTRL_RE | LPUART_CTRL_RIE | LPUART_CTRL_ILIE)
#define CTRL_TX_ACTIVE		(CTRL_ENABLE | LPUART_CTRL_TIE)
#define CTRL_TX_COMPLETING	(CTRL_ENABLE | LPUART_CTRL_TCIE)
#define CTRL_TX_INACTIVE	CTRL_ENABLE 

// Copied from T3.x - probably should move to other location.
int nvic_execution_priority(void)
{
	uint32_t priority=256;
	uint32_t primask, faultmask, basepri, ipsr;

	// full algorithm in ARM DDI0403D, page B1-639
	// this isn't quite complete, but hopefully good enough
	__asm__ volatile("mrs %0, faultmask\n" : "=r" (faultmask)::);
	if (faultmask) return -1;
	__asm__ volatile("mrs %0, primask\n" : "=r" (primask)::);
	if (primask) return 0;
	__asm__ volatile("mrs %0, ipsr\n" : "=r" (ipsr)::);
	if (ipsr) {
		if (ipsr < 16) priority = 0; // could be non-zero
		else priority = NVIC_GET_PRIORITY(ipsr - 16);
	}
	__asm__ volatile("mrs %0, basepri\n" : "=r" (basepri)::);
	if (basepri > 0 && basepri < priority) priority = basepri;
	return priority;
}


void HardwareSerial::begin(uint32_t baud, uint16_t format)
{
	//printf("HardwareSerial begin\n");
	float base = (float)UART_CLOCK / (float)baud;
	float besterr = 1e20;
	int bestdiv = 1;
	int bestosr = 4;
	for (int osr=4; osr <= 32; osr++) {
		float div = base / (float)osr;
		int divint = (int)(div + 0.5f);
		if (divint < 1) divint = 1;
		else if (divint > 8191) divint = 8191;
		float err = ((float)divint - div) / div;
		if (err < 0.0f) err = -err;
		if (err <= besterr) {
			besterr = err;
			bestdiv = divint;
			bestosr = osr;
		}
	}
	//printf(" baud %d: osr=%d, div=%d\n", baud, bestosr, bestdiv);
	rx_buffer_head_ = 0;
	rx_buffer_tail_ = 0;
	tx_buffer_head_ = 0;
	tx_buffer_tail_ = 0;
	rts_low_watermark_ = rx_buffer_total_size_ - hardware->rts_low_watermark;
	rts_high_watermark_ = rx_buffer_total_size_ - hardware->rts_high_watermark;

	transmitting_ = 0;

	hardware->ccm_register |= hardware->ccm_value;

//	uint32_t fastio = IOMUXC_PAD_SRE | IOMUXC_PAD_DSE(3) | IOMUXC_PAD_SPEED(3);

	*(portControlRegister(hardware->rx_pins[rx_pin_index_].pin)) = IOMUXC_PAD_DSE(7) | IOMUXC_PAD_PKE | IOMUXC_PAD_PUE | IOMUXC_PAD_PUS(3) | IOMUXC_PAD_HYS;
	*(portConfigRegister(hardware->rx_pins[rx_pin_index_].pin)) = hardware->rx_pins[rx_pin_index_].mux_val;
	if (hardware->rx_pins[rx_pin_index_].select_input_register) {
	 	*(hardware->rx_pins[rx_pin_index_].select_input_register) =  hardware->rx_pins[rx_pin_index_].select_val;		
	}	

	*(portControlRegister(hardware->tx_pins[tx_pin_index_].pin)) =  IOMUXC_PAD_SRE | IOMUXC_PAD_DSE(3) | IOMUXC_PAD_SPEED(3);
	*(portConfigRegister(hardware->tx_pins[tx_pin_index_].pin)) = hardware->tx_pins[tx_pin_index_].mux_val;

	//hardware->rx_mux_register = hardware->rx_mux_val;
	//hardware->tx_mux_register = hardware->tx_mux_val;

	port->BAUD = LPUART_BAUD_OSR(bestosr - 1) | LPUART_BAUD_SBR(bestdiv);
	port->PINCFG = 0;

	// Enable the transmitter, receiver and enable receiver interrupt
	attachInterruptVector(hardware->irq, hardware->irq_handler);
	NVIC_SET_PRIORITY(hardware->irq, hardware->irq_priority);	// maybe should put into hardware...
	NVIC_ENABLE_IRQ(hardware->irq);
	uint16_t tx_fifo_size = (((port->FIFO >> 4) & 0x7) << 2);
	uint8_t tx_water = (tx_fifo_size < 16) ? tx_fifo_size >> 1 : 7;
	uint16_t rx_fifo_size = (((port->FIFO >> 0) & 0x7) << 2);
	uint8_t rx_water = (rx_fifo_size < 16) ? rx_fifo_size >> 1 : 7;
	/*
	Serial.printf("SerialX::begin stat:%x ctrl:%x fifo:%x water:%x\n", port->STAT, port->CTRL, port->FIFO, port->WATER );
	Serial.printf("  FIFO sizes: tx:%d rx:%d\n",tx_fifo_size, rx_fifo_size);	
	Serial.printf("  Watermark tx:%d, rx: %d\n", tx_water, rx_water);
	*/
	port->WATER = LPUART_WATER_RXWATER(rx_water) | LPUART_WATER_TXWATER(tx_water);
	port->FIFO |= LPUART_FIFO_TXFE | LPUART_FIFO_RXFE;


	// lets configure up our CTRL register value
	uint32_t ctrl = CTRL_TX_INACTIVE;

	// Now process the bits in the Format value passed in
	// Bits 0-2 - Parity plus 9  bit. 
	ctrl |= (format & (LPUART_CTRL_PT | LPUART_CTRL_PE) );	// configure parity - turn off PT, PE, M and configure PT, PE
	if (format & 0x04) ctrl |= LPUART_CTRL_M;		// 9 bits (might include parity)
	if ((format & 0x0F) == 0x04) ctrl |=  LPUART_CTRL_R9T8; // 8N2 is 9 bit with 9th bit always 1

	// Bit 5 TXINVERT
	if (format & 0x20) ctrl |= LPUART_CTRL_TXINV;		// tx invert

	// write out computed CTRL
	port->CTRL = ctrl;

	// Bit 3 10 bit - Will assume that begin already cleared it.
	// process some other bits which change other registers.
	if (format & 0x08) 	port->BAUD |= LPUART_BAUD_M10;

	// Bit 4 RXINVERT 
	uint32_t c = port->STAT & ~LPUART_STAT_RXINV;
	if (format & 0x10) c |= LPUART_STAT_RXINV;		// rx invert
	port->STAT = c;

	// bit 8 can turn on 2 stop bit mote
	if ( format & 0x100) port->BAUD |= LPUART_BAUD_SBNS;	

	//Serial.printf("    stat:%x ctrl:%x fifo:%x water:%x\n", port->STAT, port->CTRL, port->FIFO, port->WATER );
	enableSerialEvents(); 		// Enable the processing of serialEvent for this object
};

inline void HardwareSerial::rts_assert() 
{
	DIRECT_WRITE_LOW(rts_pin_baseReg_, rts_pin_bitmask_);
}

inline void HardwareSerial::rts_deassert()
{
	DIRECT_WRITE_HIGH(rts_pin_baseReg_, rts_pin_bitmask_);
}


void HardwareSerial::end(void)
{
	if (!(hardware->ccm_register & hardware->ccm_value)) return;
	while (transmitting_) yield();  // wait for buffered data to send
	port->CTRL = 0;	// disable the TX and RX ...

	// Not sure if this is best, but I think most IO pins default to Mode 5? which appears to be digital IO? 
	*(portConfigRegister(hardware->rx_pins[rx_pin_index_].pin)) = 5;
	*(portConfigRegister(hardware->tx_pins[tx_pin_index_].pin)) = 5;


	// Might need to clear out other areas as well? 
	rx_buffer_head_ = 0;
	rx_buffer_tail_ = 0;
	if (rts_pin_baseReg_) rts_deassert();
	// 
	disableSerialEvents(); 		// disable the processing of serialEvent for this object
}

void HardwareSerial::transmitterEnable(uint8_t pin)
{
	while (transmitting_) ;
	pinMode(pin, OUTPUT);
	transmit_pin_baseReg_ = PIN_TO_BASEREG(pin);
	transmit_pin_bitmask_ = PIN_TO_BITMASK(pin);
	DIRECT_WRITE_LOW(transmit_pin_baseReg_, transmit_pin_bitmask_);
}

void HardwareSerial::setRX(uint8_t pin)
{
	if (pin != hardware->rx_pins[rx_pin_index_].pin) {
		for (uint8_t rx_pin_new_index = 0; rx_pin_new_index < cnt_rx_pins; rx_pin_new_index++) {
			if (pin == hardware->rx_pins[rx_pin_index_].pin) {
				// new pin - so lets maybe reset the old pin to INPUT? and then set new pin parameters
				*(portConfigRegister(hardware->rx_pins[rx_pin_index_].pin)) = 5;

				// now set new pin info.
				rx_pin_index_ = rx_pin_new_index;
				*(portControlRegister(hardware->rx_pins[rx_pin_index_].pin)) =  IOMUXC_PAD_DSE(7) | IOMUXC_PAD_PKE | IOMUXC_PAD_PUE | IOMUXC_PAD_PUS(3) | IOMUXC_PAD_HYS;;
				*(portConfigRegister(hardware->rx_pins[rx_pin_index_].pin)) = hardware->rx_pins[rx_pin_index_].mux_val;
				if (hardware->rx_pins[rx_pin_index_].select_input_register) {
				 	*(hardware->rx_pins[rx_pin_index_].select_input_register) =  hardware->rx_pins[rx_pin_index_].select_val;		
				}	
				break;
			}
		}
	}
}

void HardwareSerial::setTX(uint8_t pin, bool opendrain)
{
	uint8_t tx_pin_new_index = tx_pin_index_;

	if (pin != hardware->tx_pins[tx_pin_index_].pin) {
		for (tx_pin_new_index = 0; tx_pin_new_index < cnt_tx_pins; tx_pin_new_index++) {
			if (pin == hardware->tx_pins[tx_pin_index_].pin) {
				break;
			}
		}
		if (tx_pin_new_index == cnt_tx_pins) return;	// not a new valid pid... 
	}

	// turn on or off opendrain mode.
	// new pin - so lets maybe reset the old pin to INPUT? and then set new pin parameters
	if (tx_pin_new_index != tx_pin_index_) {
		*(portConfigRegister(hardware->tx_pins[tx_pin_index_].pin)) = 5;
	
		*(portConfigRegister(hardware->tx_pins[tx_pin_new_index].pin)) = hardware->tx_pins[tx_pin_new_index].mux_val;
	}

	// now set new pin info.
	tx_pin_index_ = tx_pin_new_index;
	if (opendrain) 
		*(portControlRegister(pin)) = IOMUXC_PAD_ODE | IOMUXC_PAD_DSE(3) | IOMUXC_PAD_SPEED(3);
	else 	
		*(portControlRegister(pin)) = IOMUXC_PAD_SRE | IOMUXC_PAD_DSE(3) | IOMUXC_PAD_SPEED(3);
}


bool HardwareSerial::attachRts(uint8_t pin)
{
	if (!(hardware->ccm_register & hardware->ccm_value)) return 0;
	if (pin < CORE_NUM_DIGITAL) {
		rts_pin_baseReg_ = PIN_TO_BASEREG(pin);
		rts_pin_bitmask_ = PIN_TO_BITMASK(pin);
		pinMode(pin, OUTPUT);
		rts_assert();
	} else {
		rts_pin_baseReg_ = NULL;
		return 0;
	}
	return 1;
}

bool HardwareSerial::attachCts(uint8_t pin)
{
	if (!(hardware->ccm_register & hardware->ccm_value)) return false;
	if ((pin != 0xff) && (pin == hardware->cts_pin)) {
		// Setup the IO pin as weak PULL down. 
		*(portControlRegister(pin)) = IOMUXC_PAD_DSE(7) | IOMUXC_PAD_PKE | IOMUXC_PAD_PUE | IOMUXC_PAD_PUS(0) | IOMUXC_PAD_HYS;
		*(portConfigRegister(hardware->cts_pin)) = hardware->cts_mux_val;
		port->MODIR |= LPUART_MODIR_TXCTSE;
		return true;
	} else {
		port->MODIR &= ~LPUART_MODIR_TXCTSE;
		return false;
	}
}

void HardwareSerial::clear(void)
{
	// BUGBUG:: deal with FIFO
	rx_buffer_head_ = rx_buffer_tail_;
	if (rts_pin_baseReg_) rts_assert();
}

int HardwareSerial::availableForWrite(void)
{
	uint32_t head, tail;

	head = tx_buffer_head_;
	tail = tx_buffer_tail_;
	if (head >= tail) return tx_buffer_total_size_ - 1 - head + tail;
	return tail - head - 1;
}




int HardwareSerial::available(void)
{
	uint32_t head, tail;

	head = rx_buffer_head_;
	tail = rx_buffer_tail_;
	if (head >= tail) return head - tail;
	return rx_buffer_total_size_ + head - tail;
}

void HardwareSerial::addStorageForRead(void *buffer, size_t length) 
{
	rx_buffer_storage_ = (BUFTYPE*)buffer;
	if (buffer) {
		rx_buffer_total_size_ = rx_buffer_total_size_ + length;
	} else {
		rx_buffer_total_size_ = rx_buffer_total_size_;
	} 

	rts_low_watermark_ = rx_buffer_total_size_ - hardware->rts_low_watermark;
	rts_high_watermark_ = rx_buffer_total_size_ - hardware->rts_high_watermark;
}

void HardwareSerial::addStorageForWrite(void *buffer, size_t length) 
{
	tx_buffer_storage_ = (BUFTYPE*)buffer;
	if (buffer) {
		tx_buffer_total_size_ = tx_buffer_total_size_ + length;
	} else {
		tx_buffer_total_size_ = tx_buffer_total_size_;
	} 
}

int HardwareSerial::peek(void)
{
	uint32_t head, tail;

	head = rx_buffer_head_;
	tail = rx_buffer_tail_;
	if (head == tail) return -1;
	if (++tail >= rx_buffer_total_size_) tail = 0;
	if (tail < rx_buffer_size_) {
		return rx_buffer_[tail];
	} else {
		return rx_buffer_storage_[tail-rx_buffer_size_];
	}
}

int HardwareSerial::read(void)
{
	uint32_t head, tail;
	int c;

	head = rx_buffer_head_;
	tail = rx_buffer_tail_;
	if (head == tail) return -1;
	if (++tail >= rx_buffer_total_size_) tail = 0;
	if (tail < rx_buffer_size_) {
		c = rx_buffer_[tail];
	} else {
		c = rx_buffer_storage_[tail-rx_buffer_size_];
	}
	rx_buffer_tail_ = tail;
	if (rts_pin_baseReg_) {
		uint32_t avail;
		if (head >= tail) avail = head - tail;
		else avail = rx_buffer_total_size_ + head - tail;

		if (avail <= rts_low_watermark_) rts_assert();
	}
	return c;
}	

void HardwareSerial::flush(void)
{
	while (transmitting_) yield(); // wait
}

size_t HardwareSerial::write(uint8_t c)
{
	// use the 9 bit version (maybe 10 bit) do do the work. 
	return write9bit(c);
}

size_t HardwareSerial::write9bit(uint32_t c)
{
	uint32_t head, n;
	//digitalWrite(3, HIGH);
	//digitalWrite(5, HIGH);
	if (transmit_pin_baseReg_) DIRECT_WRITE_HIGH(transmit_pin_baseReg_, transmit_pin_bitmask_);
	head = tx_buffer_head_;
	if (++head >= tx_buffer_total_size_) head = 0;
	while (tx_buffer_tail_ == head) {
		int priority = nvic_execution_priority();
		if (priority <= hardware->irq_priority) {
			if ((port->STAT & LPUART_STAT_TDRE)) {
				uint32_t tail = tx_buffer_tail_;
				if (++tail >= tx_buffer_total_size_) tail = 0;
				if (tail < tx_buffer_size_) {
					n = tx_buffer_[tail];
				} else {
					n = tx_buffer_storage_[tail-tx_buffer_size_];
				}
				port->DATA  = n;
				tx_buffer_tail_ = tail;
			}
		} else if (priority >= 256) 
		{
			yield(); // wait
		} 
	}
	//digitalWrite(5, LOW);
	//Serial.printf("WR %x %d %d %d %x %x\n", c, head, tx_buffer_size_,  tx_buffer_total_size_, (uint32_t)tx_buffer_, (uint32_t)tx_buffer_storage_);
	if (head < tx_buffer_size_) {
		tx_buffer_[head] = c;
	} else {
		tx_buffer_storage_[head - tx_buffer_size_] = c;
	}
	__disable_irq();
	transmitting_ = 1;
	tx_buffer_head_ = head;
	port->CTRL |= LPUART_CTRL_TIE; // (may need to handle this issue)BITBAND_SET_BIT(LPUART0_CTRL, TIE_BIT);
	__enable_irq();
	//digitalWrite(3, LOW);
	return 1;
}

void HardwareSerial::IRQHandler() 
{
	//digitalWrite(4, HIGH);
	uint32_t head, tail, n;
	uint32_t ctrl;

	// See if we have stuff to read in.
	// Todo - Check idle. 
	if (port->STAT & (LPUART_STAT_RDRF | LPUART_STAT_IDLE)) {
		// See how many bytes or pending. 
		//digitalWrite(5, HIGH);
		uint8_t avail = (port->WATER >> 24) & 0x7;
		if (avail) {
			uint32_t newhead;
			head = rx_buffer_head_;
			tail = rx_buffer_tail_;
			do {
				n = port->DATA & 0x3ff;		// Use only up to 10 bits of data
				newhead = head + 1;

				if (newhead >= rx_buffer_total_size_) newhead = 0;
				if (newhead != rx_buffer_tail_) {
					head = newhead;
					if (newhead < rx_buffer_size_) {
						rx_buffer_[head] = n;
					} else {
						rx_buffer_storage_[head-rx_buffer_size_] = n;
					}
				}
			} while (--avail > 0) ;
			rx_buffer_head_ = head;
			if (rts_pin_baseReg_) {
				uint32_t avail;
				if (head >= tail) avail = head - tail;
				else avail = rx_buffer_total_size_ + head - tail;
				if (avail >= rts_high_watermark_) rts_deassert();
			}
		}

		// If it was an idle status clear the idle
		if (port->STAT & LPUART_STAT_IDLE) {
			port->STAT |= LPUART_STAT_IDLE;	// writing a 1 to idle should clear it. 
		}
		//digitalWrite(5, LOW);

	}

	// See if we are transmitting and room in buffer. 
	ctrl = port->CTRL;
	if ((ctrl & LPUART_CTRL_TIE) && (port->STAT & LPUART_STAT_TDRE))
	{
		//digitalWrite(3, HIGH);

		head = tx_buffer_head_;
		tail = tx_buffer_tail_;
		do {
			if (head == tail) break;
			if (++tail >= tx_buffer_total_size_) tail = 0;
			if (tail < tx_buffer_size_) {
				n = tx_buffer_[tail];
			} else {
				n = tx_buffer_storage_[tail-tx_buffer_size_];
			}
			port->DATA = n;
		} while (((port->WATER >> 8) & 0x7) < 4); 	// need to computer properly
		tx_buffer_tail_ = tail;
		if (head == tail) {
			port->CTRL &= ~LPUART_CTRL_TIE; 
  			port->CTRL |= LPUART_CTRL_TCIE; // Actually wondering if we can just leave this one on...
		}
		//digitalWrite(3, LOW);
	}

	if ((ctrl & LPUART_CTRL_TCIE) && (port->STAT & LPUART_STAT_TC))
	{
		transmitting_ = 0;
		if (transmit_pin_baseReg_) DIRECT_WRITE_LOW(transmit_pin_baseReg_, transmit_pin_bitmask_);

		port->CTRL &= ~LPUART_CTRL_TCIE;
	}
	//digitalWrite(4, LOW);
}


void HardwareSerial::processSerialEvents()
{
	if (!serial_event_handlers_active) return;	// bail quick if no one processing SerialEvents.
	uint8_t handlers_still_to_process = serial_event_handlers_active;
	for (uint8_t i = 0; i < 8; i++) {
		if (serial_event_handler_checks[i]) {
			(*serial_event_handler_checks[i])();
			if (--handlers_still_to_process == 0) return;
		}
	}
}

void HardwareSerial::enableSerialEvents() 
{
	if (!serial_event_handler_checks[hardware->serial_index]) {
		serial_event_handler_checks[hardware->serial_index] = hardware->serial_event_handler_check;	// clear it out
		serial_event_handlers_active++;
	}
}

void HardwareSerial::disableSerialEvents() 
{
	if (serial_event_handler_checks[hardware->serial_index]) {
		serial_event_handler_checks[hardware->serial_index] = nullptr;	// clear it out
		serial_event_handlers_active--;
	}
}
