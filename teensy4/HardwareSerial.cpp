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

extern "C" {
    extern void xbar_connect(unsigned int input, unsigned int output);
}

#if defined(ARDUINO_TEENSY41)   
HardwareSerial 	*HardwareSerial::s_serials_with_serial_events[8];
#else
HardwareSerial 	*HardwareSerial::s_serials_with_serial_events[7];
#endif

// define our static objects
uint8_t 		HardwareSerial::s_count_serials_with_serial_events = 0;



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

	// Maybe different pin configs if half duplex
	half_duplex_mode_ = (format & SERIAL_HALF_DUPLEX) != 0;
	if (!half_duplex_mode_)  {
		*(portControlRegister(hardware->rx_pins[rx_pin_index_].pin)) = IOMUXC_PAD_DSE(7) | IOMUXC_PAD_PKE | IOMUXC_PAD_PUE | IOMUXC_PAD_PUS(3) | IOMUXC_PAD_HYS;
		*(portConfigRegister(hardware->rx_pins[rx_pin_index_].pin)) = hardware->rx_pins[rx_pin_index_].mux_val;
		if (hardware->rx_pins[rx_pin_index_].select_input_register) {
		 	*(hardware->rx_pins[rx_pin_index_].select_input_register) =  hardware->rx_pins[rx_pin_index_].select_val;		
		}	

		*(portControlRegister(hardware->tx_pins[tx_pin_index_].pin)) =  IOMUXC_PAD_SRE | IOMUXC_PAD_DSE(3) | IOMUXC_PAD_SPEED(3);
		*(portConfigRegister(hardware->tx_pins[tx_pin_index_].pin)) = hardware->tx_pins[tx_pin_index_].mux_val;
	} else {
		// Half duplex maybe different pin pad config like PU...		
		*(portControlRegister(hardware->tx_pins[tx_pin_index_].pin)) =  IOMUXC_PAD_SRE | IOMUXC_PAD_DSE(3) | IOMUXC_PAD_SPEED(3) 
				| IOMUXC_PAD_PKE | IOMUXC_PAD_PUE | IOMUXC_PAD_PUS(3);
		*(portConfigRegister(hardware->tx_pins[tx_pin_index_].pin)) = hardware->tx_pins[tx_pin_index_].mux_val;
	}
	if (hardware->tx_pins[tx_pin_index_].select_input_register) {
	 	*(hardware->tx_pins[tx_pin_index_].select_input_register) =  hardware->tx_pins[tx_pin_index_].select_val;		
	}	
	//hardware->rx_mux_register = hardware->rx_mux_val;
	//hardware->tx_mux_register = hardware->tx_mux_val;

	port->BAUD = LPUART_BAUD_OSR(bestosr - 1) | LPUART_BAUD_SBR(bestdiv)
		| (bestosr <= 8 ? LPUART_BAUD_BOTHEDGE : 0);
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

	// Now see if the user asked for Half duplex:
	if (half_duplex_mode_) ctrl |= (LPUART_CTRL_LOOPS | LPUART_CTRL_RSRC);

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
	// Only if the user implemented their own...
	if (!(*hardware->serial_event_handler_default)) addToSerialEventsList(); 		// Enable the processing of serialEvent for this object
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
			if (pin == hardware->rx_pins[rx_pin_new_index].pin) {
				// new pin - so lets maybe reset the old pin to INPUT? and then set new pin parameters
				// only change IO pins if done after begin has been called. 
				if ((hardware->ccm_register & hardware->ccm_value)) {
					*(portConfigRegister(hardware->rx_pins[rx_pin_index_].pin)) = 5;

					// now set new pin info.
					*(portControlRegister(hardware->rx_pins[rx_pin_new_index].pin)) =  IOMUXC_PAD_DSE(7) | IOMUXC_PAD_PKE | IOMUXC_PAD_PUE | IOMUXC_PAD_PUS(3) | IOMUXC_PAD_HYS;;
					*(portConfigRegister(hardware->rx_pins[rx_pin_new_index].pin)) = hardware->rx_pins[rx_pin_new_index].mux_val;
					if (hardware->rx_pins[rx_pin_new_index].select_input_register) {
					 	*(hardware->rx_pins[rx_pin_new_index].select_input_register) =  hardware->rx_pins[rx_pin_new_index].select_val;		
					}
				}		
				rx_pin_index_ = rx_pin_new_index;
				return;  // done. 
			}
		}
		// If we got to here and did not find a valid pin there.  Maybe see if it is an XBar pin... 
		for (uint8_t i = 0; i < count_pin_to_xbar_info; i++) {
			if (pin_to_xbar_info[i].pin == pin) {
				// So it is an XBAR pin set the XBAR..
				//Serial.printf("ACTS XB(%d), X(%u %u), MUX:%x\n", i, pin_to_xbar_info[i].xbar_in_index, 
				//			hardware->xbar_out_lpuartX_trig_input,  pin_to_xbar_info[i].mux_val);
				CCM_CCGR2 |= CCM_CCGR2_XBAR1(CCM_CCGR_ON);
				xbar_connect(pin_to_xbar_info[i].xbar_in_index, hardware->xbar_out_lpuartX_trig_input);

				// We need to update port register to use this as the trigger
				port->PINCFG = LPUART_PINCFG_TRGSEL(1);  // Trigger select as alternate RX

				//  configure the pin. 
				*(portControlRegister(pin)) = IOMUXC_PAD_DSE(7) | IOMUXC_PAD_PKE | IOMUXC_PAD_PUE | IOMUXC_PAD_PUS(3) | IOMUXC_PAD_HYS;;
				*(portConfigRegister(pin)) = pin_to_xbar_info[i].mux_val;
				port->MODIR |= LPUART_MODIR_TXCTSE;
				if (pin_to_xbar_info[i].select_input_register) *(pin_to_xbar_info[i].select_input_register) = pin_to_xbar_info[i].select_val;
				//Serial.printf("SerialX::begin stat:%x ctrl:%x fifo:%x water:%x\n", port->STAT, port->CTRL, port->FIFO, port->WATER );
				//Serial.printf("  PINCFG: %x MODIR: %x\n", port->PINCFG, port->MODIR);	
				return;
			}
		}
	}
}

void HardwareSerial::setTX(uint8_t pin, bool opendrain)
{
	uint8_t tx_pin_new_index = tx_pin_index_;

	if (pin != hardware->tx_pins[tx_pin_index_].pin) {
		for (tx_pin_new_index = 0; tx_pin_new_index < cnt_tx_pins; tx_pin_new_index++) {
			if (pin == hardware->tx_pins[tx_pin_new_index].pin) {
				break;
			}
		}
		if (tx_pin_new_index == cnt_tx_pins) return;	// not a new valid pid... 
	}

	// turn on or off opendrain mode.
	// new pin - so lets maybe reset the old pin to INPUT? and then set new pin parameters
	if ((hardware->ccm_register & hardware->ccm_value)) {  // only do if we are already active. 
	if (tx_pin_new_index != tx_pin_index_) {
		*(portConfigRegister(hardware->tx_pins[tx_pin_index_].pin)) = 5;
	
		*(portConfigRegister(hardware->tx_pins[tx_pin_new_index].pin)) = hardware->tx_pins[tx_pin_new_index].mux_val;
	}
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
		// See maybe this a pin we can use XBAR for.
		for (uint8_t i = 0; i < count_pin_to_xbar_info; i++) {
			if (pin_to_xbar_info[i].pin == pin) {
				// So it is an XBAR pin set the XBAR..
				//Serial.printf("ACTS XB(%d), X(%u %u), MUX:%x\n", i, pin_to_xbar_info[i].xbar_in_index, 
				//			hardware->xbar_out_lpuartX_trig_input,  pin_to_xbar_info[i].mux_val);
				CCM_CCGR2 |= CCM_CCGR2_XBAR1(CCM_CCGR_ON);
				xbar_connect(pin_to_xbar_info[i].xbar_in_index, hardware->xbar_out_lpuartX_trig_input);

				// We need to update port register to use this as the trigger
				port->PINCFG = LPUART_PINCFG_TRGSEL(2);  // Trigger select as alternate CTS pin

				//  configure the pin. 
				*(portControlRegister(pin)) = IOMUXC_PAD_DSE(7) | IOMUXC_PAD_PKE | IOMUXC_PAD_PUE | IOMUXC_PAD_PUS(0) | IOMUXC_PAD_HYS;
				*(portConfigRegister(pin)) = pin_to_xbar_info[i].mux_val;
				if (pin_to_xbar_info[i].select_input_register) *(pin_to_xbar_info[i].select_input_register) = pin_to_xbar_info[i].select_val;
				port->MODIR |= LPUART_MODIR_TXCTSE;

				//Serial.printf("SerialX::begin stat:%x ctrl:%x fifo:%x water:%x\n", port->STAT, port->CTRL, port->FIFO, port->WATER );
				//Serial.printf("  PINCFG: %x MODIR: %x\n", port->PINCFG, port->MODIR);	
				return true;
			}
		}
		// Fell through so not valid pin for this. 
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

	// WATER> 0 so IDLE involved may want to check if port has already has RX data to retrieve
	__disable_irq();
	head = rx_buffer_head_;
	tail = rx_buffer_tail_;
	int avail;
	if (head >= tail) avail = head - tail;
	else avail = rx_buffer_total_size_ + head - tail;	
	avail += (port->WATER >> 24) & 0x7;
	__enable_irq();
	return avail;
}

void HardwareSerial::addMemoryForRead(void *buffer, size_t length)
{
	rx_buffer_storage_ = (BUFTYPE*)buffer;
	if (buffer) {
		rx_buffer_total_size_ = rx_buffer_size_ + length;
	} else {
		rx_buffer_total_size_ = rx_buffer_size_;
	} 

	// Make sure we don't end up indexing into no mans land. 
	rx_buffer_head_ = 0;
	rx_buffer_tail_ = 0;
	rts_low_watermark_ = rx_buffer_total_size_ - hardware->rts_low_watermark;
	rts_high_watermark_ = rx_buffer_total_size_ - hardware->rts_high_watermark;
}

void HardwareSerial::addMemoryForWrite(void *buffer, size_t length)
{
	tx_buffer_storage_ = (BUFTYPE*)buffer;
	if (buffer) {
		tx_buffer_total_size_ = tx_buffer_size_ + length;
	} else {
		tx_buffer_total_size_ = tx_buffer_size_;
	} 
	// Make sure we don't end up indexing into no mans land. 
	tx_buffer_head_ = 0;
	tx_buffer_tail_ = 0;
}

int HardwareSerial::peek(void)
{
	uint32_t head, tail;

	head = rx_buffer_head_;
	tail = rx_buffer_tail_;
	if (head == tail) {
		__disable_irq();
		head = rx_buffer_head_;  // reread head to make sure no ISR happened
		if (head == tail) {
			// Still empty Now check for stuff in FIFO Queue.
			int c = -1;	// assume nothing to return
			if (port->WATER & 0x7000000) {
				c = port->DATA & 0x3ff;		// Use only up to 10 bits of data
				// But we don't want to throw it away...
				// since queue is empty, just going to reset to front of queue...
				rx_buffer_head_ = 1;
				rx_buffer_tail_ = 0; 
				rx_buffer_[1] = c;
			}
			__enable_irq();
			return c;
		}
		__enable_irq();

	} 
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
	if (head == tail) {
		__disable_irq();
		head = rx_buffer_head_;  // reread head to make sure no ISR happened
		if (head == tail) {
			// Still empty Now check for stuff in FIFO Queue.
			c = -1;	// assume nothing to return
			if (port->WATER & 0x7000000) {
				c = port->DATA & 0x3ff;		// Use only up to 10 bits of data
			}
			__enable_irq();
			return c;
		}
		__enable_irq();

	}
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
	if(half_duplex_mode_) {		
		__disable_irq();
	    port->CTRL |= LPUART_CTRL_TXDIR;
		__enable_irq();
		//digitalWriteFast(2, HIGH);
	}

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
		if(half_duplex_mode_) {		
			__disable_irq();
		    port->CTRL &= ~LPUART_CTRL_TXDIR;
			__enable_irq();
			//digitalWriteFast(2, LOW);
		}

		port->CTRL &= ~LPUART_CTRL_TCIE;
	}
	//digitalWrite(4, LOW);
}


void HardwareSerial::addToSerialEventsList() {
	for (uint8_t i = 0; i < s_count_serials_with_serial_events; i++) {
		if (s_serials_with_serial_events[i] == this) return; // already in the list.
	}
	s_serials_with_serial_events[s_count_serials_with_serial_events++] = this;
	yield_active_check_flags |= YIELD_CHECK_HARDWARE_SERIAL;
}


const pin_to_xbar_info_t PROGMEM pin_to_xbar_info[] = {
	{0,  17, 1, &IOMUXC_XBAR1_IN17_SELECT_INPUT, 0x1},
	{1,  16, 1, nullptr, 0},
	{2,   6, 3, &IOMUXC_XBAR1_IN06_SELECT_INPUT, 0x0},
	{3,   7, 3, &IOMUXC_XBAR1_IN07_SELECT_INPUT, 0x0},
	{4,   8, 3, &IOMUXC_XBAR1_IN08_SELECT_INPUT, 0x0},
	{5,  17, 3, &IOMUXC_XBAR1_IN17_SELECT_INPUT, 0x0},
	{7,  15, 1, nullptr, 0 },
	{8,  14, 1, nullptr, 0},
	{30, 23, 1, &IOMUXC_XBAR1_IN23_SELECT_INPUT, 0x0},
	{31, 22, 1, &IOMUXC_XBAR1_IN22_SELECT_INPUT, 0x0},
	{32, 10, 1, nullptr, 0},
	{33,  9, 3, &IOMUXC_XBAR1_IN09_SELECT_INPUT, 0x0},

#ifdef ARDUINO_TEENSY41
	{36, 16, 1, nullptr, 0},
	{37, 17, 1, &IOMUXC_XBAR1_IN17_SELECT_INPUT, 0x3},
	{42,  7, 3, &IOMUXC_XBAR1_IN07_SELECT_INPUT, 0x1},
	{43,  6, 3, &IOMUXC_XBAR1_IN06_SELECT_INPUT, 0x1},
	{44,  5, 3, &IOMUXC_XBAR1_IN05_SELECT_INPUT, 0x1},
	{45,  4, 3, &IOMUXC_XBAR1_IN04_SELECT_INPUT, 0x1},
	{46,  9, 3, &IOMUXC_XBAR1_IN09_SELECT_INPUT, 0x1},
	{47,  8, 3, &IOMUXC_XBAR1_IN08_SELECT_INPUT, 0x1}
#else	
	{34,  7, 3, &IOMUXC_XBAR1_IN07_SELECT_INPUT, 0x1},
	{35,  6, 3, &IOMUXC_XBAR1_IN06_SELECT_INPUT, 0x1},
	{36,  5, 3, &IOMUXC_XBAR1_IN05_SELECT_INPUT, 0x1},
	{37,  4, 3, &IOMUXC_XBAR1_IN04_SELECT_INPUT, 0x1},
	{38,  9, 3, &IOMUXC_XBAR1_IN09_SELECT_INPUT, 0x1},
	{39,  8, 3, &IOMUXC_XBAR1_IN08_SELECT_INPUT, 0x1}
#endif
};

const uint8_t PROGMEM count_pin_to_xbar_info = sizeof(pin_to_xbar_info)/sizeof(pin_to_xbar_info[0]);

