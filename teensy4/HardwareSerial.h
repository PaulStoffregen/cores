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

#ifndef HardwareSerial_h
#define HardwareSerial_h

#include "imxrt.h"

// Uncomment to enable 9 bit formats.  These are default disabled to save memory.
//#define SERIAL_9BIT_SUPPORT
//
// On Windows & Linux, this file is in Arduino's hardware/teensy/avr/cores/teensy3
//   folder.  The Windows installer puts Arduino in C:\Program Files (x86)\Arduino
// On Macintosh, you must control-click Arduino and select "Show Package Contents", then
//   look in Contents/Java/hardware/teensy/avr/cores/teensy3 to find this file.
//
// Teensy 4.x boards support 9 bit mode on all their serial ports


#define SERIAL_7E1 0x02
#define SERIAL_7O1 0x03
#define SERIAL_8N1 0x00
#define SERIAL_8E1 0x06
#define SERIAL_8O1 0x07
#define SERIAL_7E1_RXINV 0x12
#define SERIAL_7O1_RXINV 0x13
#define SERIAL_8N1_RXINV 0x10
#define SERIAL_8E1_RXINV 0x16
#define SERIAL_8O1_RXINV 0x17
#define SERIAL_7E1_TXINV 0x22
#define SERIAL_7O1_TXINV 0x23
#define SERIAL_8N1_TXINV 0x20
#define SERIAL_8E1_TXINV 0x26
#define SERIAL_8O1_TXINV 0x27
#define SERIAL_7E1_RXINV_TXINV 0x32
#define SERIAL_7O1_RXINV_TXINV 0x33
#define SERIAL_8N1_RXINV_TXINV 0x30
#define SERIAL_8E1_RXINV_TXINV 0x36
#define SERIAL_8O1_RXINV_TXINV 0x37
#ifdef SERIAL_9BIT_SUPPORT
#define SERIAL_9N1 0x84
#define SERIAL_9E1 0x8E
#define SERIAL_9O1 0x8F
#define SERIAL_9N1_RXINV 0x94
#define SERIAL_9E1_RXINV 0x9E
#define SERIAL_9O1_RXINV 0x9F
#define SERIAL_9N1_TXINV 0xA4
#define SERIAL_9E1_TXINV 0xAE
#define SERIAL_9O1_TXINV 0xAF
#define SERIAL_9N1_RXINV_TXINV 0xB4
#define SERIAL_9E1_RXINV_TXINV 0xBE
#define SERIAL_9O1_RXINV_TXINV 0xBF
#endif
// We have 1/2 bit stop setting
#define SERIAL_2STOP_BITS 0x100
#define SERIAL_8E2 (SERIAL_8E1 | SERIAL_2STOP_BITS)
#define SERIAL_8O2 (SERIAL_8O1 | SERIAL_2STOP_BITS)
#define SERIAL_8E2_RXINV (SERIAL_8E1_RXINV | SERIAL_2STOP_BITS)
#define SERIAL_8O2_RXINV (SERIAL_8O1_RXINV | SERIAL_2STOP_BITS)
#define SERIAL_8E2_TXINV (SERIAL_8E1_TXINV | SERIAL_2STOP_BITS)
#define SERIAL_8O2_TXINV (SERIAL_8O1_TXINV | SERIAL_2STOP_BITS)
#define SERIAL_8E2_RXINV_TXINV (SERIAL_8E1_RXINV_TXINV | SERIAL_2STOP_BITS)
#define SERIAL_8O2_RXINV_TXINV (SERIAL_8O1_RXINV_TXINV | SERIAL_2STOP_BITS)
#define SERIAL_8N2 (SERIAL_8N1 | SERIAL_2STOP_BITS)
#define SERIAL_8N2_RXINV (SERIAL_8N1_RXINV | SERIAL_2STOP_BITS)
#define SERIAL_8N2_TXINV (SERIAL_8N1_TXINV | SERIAL_2STOP_BITS)
#define SERIAL_8N2_RXINV_TXINV (SERIAL_8N1_RXINV_TXINV | SERIAL_2STOP_BITS)

// Half duplex support
#define SERIAL_HALF_DUPLEX 0x200
#define SERIAL_7E1_HALF_DUPLEX (SERIAL_7E1 | SERIAL_HALF_DUPLEX)
#define SERIAL_7O1_HALF_DUPLEX (SERIAL_7O1 | SERIAL_HALF_DUPLEX)
#define SERIAL_8N1_HALF_DUPLEX (SERIAL_8N1 | SERIAL_HALF_DUPLEX)

// bit0: parity, 0=even, 1=odd
// bit1: parity, 0=disable, 1=enable
// bit2: mode, 1=9bit, 0=8bit
// bit3: mode10: 1=10bit, 0=8bit
// bit4: rxinv, 0=normal, 1=inverted
// bit5: txinv, 0=normal, 1=inverted
// bit6: unused
// bit7: actual data goes into 9th bit

// bit8: 2 stop bits 
// bit9: Half Duplex Mode

#ifdef __cplusplus
#include "Stream.h"
#include "core_pins.h"

#ifdef SERIAL_9BIT_SUPPORT
#define BUFTYPE uint16_t
#else
#define BUFTYPE uint8_t
#endif

extern "C" {
	extern void IRQHandler_Serial1();
	extern void IRQHandler_Serial2();
	extern void IRQHandler_Serial3();
	extern void IRQHandler_Serial4();
	extern void IRQHandler_Serial5();
	extern void IRQHandler_Serial6();
	extern void IRQHandler_Serial7();
	#if defined(ARDUINO_TEENSY41)   
	extern void IRQHandler_Serial8();
	#endif
}

//===================================================================
// Should find a good home for this
// Map IO pin to XBar pin... 
//===================================================================
// BUGBUG - find a good home
typedef struct _pin_to_xbar_info{
	const uint8_t 		pin;		// The pin number
	const uint8_t		xbar_in_index; // What XBar input index. 
	const uint32_t 		mux_val;	// Value to set for mux;
	volatile uint32_t	*select_input_register; // Which register controls the selection
	const uint32_t		select_val;	// Value for that selection
} pin_to_xbar_info_t;

extern const pin_to_xbar_info_t pin_to_xbar_info[];
extern const uint8_t count_pin_to_xbar_info;


class HardwareSerial : public Stream
{
public:
	static const uint8_t cnt_tx_pins = 2;
	static const uint8_t cnt_rx_pins = 2;
	typedef struct {
		const uint8_t 		pin;		// The pin number
		const uint32_t 		mux_val;	// Value to set for mux;
		volatile uint32_t	*select_input_register; // Which register controls the selection
		const uint32_t		select_val;	// Value for that selection
	} pin_info_t;

	typedef struct {
		uint8_t serial_index;	// which object are we? 0 based
		IRQ_NUMBER_t irq;
		void (*irq_handler)(void);
		void (* _serialEvent)(void);
		const uint8_t *serial_event_handler_default;
		volatile uint32_t &ccm_register;
		const uint32_t ccm_value;
		pin_info_t rx_pins[cnt_rx_pins];
		pin_info_t tx_pins[cnt_tx_pins];
		const uint8_t cts_pin;
		const uint8_t cts_mux_val;
		const uint16_t irq_priority;
		const uint16_t rts_low_watermark;
		const uint16_t rts_high_watermark;
		const uint8_t xbar_out_lpuartX_trig_input;
	} hardware_t;
public:
	constexpr HardwareSerial(IMXRT_LPUART_t *myport, const hardware_t *myhardware, 
		volatile BUFTYPE *_tx_buffer, size_t _tx_buffer_size, 
		volatile BUFTYPE *_rx_buffer, size_t _rx_buffer_size) :
		port(myport), hardware(myhardware),
		tx_buffer_(_tx_buffer), rx_buffer_(_rx_buffer), tx_buffer_size_(_tx_buffer_size),  rx_buffer_size_(_rx_buffer_size),
		tx_buffer_total_size_(_tx_buffer_size), rx_buffer_total_size_(_rx_buffer_size) {
	}
	void begin(uint32_t baud, uint16_t format=0);
	void end(void);

	virtual int available(void);
	virtual int peek(void);
	virtual void flush(void);
	virtual size_t write(uint8_t c);
	virtual int read(void);

	void transmitterEnable(uint8_t pin);
	void setRX(uint8_t pin);
	void setTX(uint8_t pin, bool opendrain=false);
	bool attachRts(uint8_t pin);
	bool attachCts(uint8_t pin);
	void clear(void);
	int availableForWrite(void);
	void addMemoryForRead(void *buffer, size_t length);
	void addMemoryForWrite(void *buffer, size_t length);
	void addStorageForRead(void *buffer, size_t length) __attribute__((deprecated("addStorageForRead was renamed to addMemoryForRead"))){
		addMemoryForRead(buffer, length);
	}
	void addStorageForWrite(void *buffer, size_t length) __attribute__((deprecated("addStorageForWrite was renamed to addMemoryForWrite"))){
		addMemoryForWrite(buffer, length);
	}
	size_t write9bit(uint32_t c);
	
	// Event Handler functions and data
	static uint8_t serial_event_handlers_active;

	using Print::write; 
	size_t write(unsigned long n) { return write((uint8_t)n); }
	size_t write(long n) { return write((uint8_t)n); }
	size_t write(unsigned int n) { return write((uint8_t)n); }
	size_t write(int n) { return write((uint8_t)n); }

	// Only overwrite some of the virtualWrite functions if we are going to optimize them over Print version

	/*
	virtual void begin(uint32_t baud) { serial_begin(BAUD2DIV(baud)); }
	virtual void begin(uint32_t baud, uint32_t format) {
					  serial_begin(BAUD2DIV(baud));
					  serial_format(format); }
	*/

	operator bool()			{ return true; }

	static inline void processSerialEventsList() {
		for (uint8_t i = 0; i < s_count_serials_with_serial_events; i++) {
			s_serials_with_serial_events[i]->doYieldCode();
		}
	}
private:
	IMXRT_LPUART_t * const port;
	const hardware_t * const hardware;
	uint8_t				rx_pin_index_ = 0x0;	// default is always first item
	uint8_t				tx_pin_index_ = 0x0;
	uint8_t				half_duplex_mode_ = 0; // are we in half duplex mode?

	volatile BUFTYPE 	*tx_buffer_;
	volatile BUFTYPE 	*rx_buffer_;
	volatile BUFTYPE	*rx_buffer_storage_ = nullptr;
	volatile BUFTYPE	*tx_buffer_storage_ = nullptr;
	size_t				tx_buffer_size_;
	size_t				rx_buffer_size_;
	size_t				tx_buffer_total_size_;
	size_t				rx_buffer_total_size_;
	size_t  			rts_low_watermark_ = 0;
	size_t  			rts_high_watermark_ = 0;
	volatile uint8_t 	transmitting_ = 0;
	volatile uint16_t 	tx_buffer_head_ = 0;
	volatile uint16_t 	tx_buffer_tail_ = 0;
	volatile uint16_t 	rx_buffer_head_ = 0;
	volatile uint16_t 	rx_buffer_tail_ = 0;

	volatile uint32_t 	*transmit_pin_baseReg_ = 0;
	uint32_t 			transmit_pin_bitmask_ = 0;

	volatile uint32_t 	*rts_pin_baseReg_ = 0;
	uint32_t 			rts_pin_bitmask_ = 0;

  	inline void rts_assert();
  	inline void rts_deassert();

	void IRQHandler();
	friend void IRQHandler_Serial1();
	friend void IRQHandler_Serial2();
	friend void IRQHandler_Serial3();
	friend void IRQHandler_Serial4();
	friend void IRQHandler_Serial5();
	friend void IRQHandler_Serial6();
	friend void IRQHandler_Serial7();
	#if defined(ARDUINO_TEENSY41)   
	friend void IRQHandler_Serial8();
	static HardwareSerial 	*s_serials_with_serial_events[8];
	#else	
	static HardwareSerial 	*s_serials_with_serial_events[7];
	#endif
	static uint8_t 			s_count_serials_with_serial_events;
	void addToSerialEventsList(); 
	inline void doYieldCode()  {
		if (available()) (*hardware->_serialEvent)();
	}



};
extern HardwareSerial Serial1;
extern HardwareSerial Serial2;
extern HardwareSerial Serial3;
extern HardwareSerial Serial4;
extern HardwareSerial Serial5;
extern HardwareSerial Serial6;
extern HardwareSerial Serial7;
extern void serialEvent1(void);
extern void serialEvent2(void);
extern void serialEvent3(void);
extern void serialEvent4(void);
extern void serialEvent5(void);
extern void serialEvent6(void);
extern void serialEvent7(void);

	#if defined(ARDUINO_TEENSY41)   
extern HardwareSerial Serial8;
extern void serialEvent8(void);
#endif


#endif // __cplusplus


// c functions to call c++ code in case some programs call the old functions
// Defined under extern "C" {}

#ifdef __cplusplus
extern "C" {
#endif
extern void serial_print(const char *p);
extern void serial_phex(uint32_t n);
extern void serial_phex16(uint32_t n);
extern void serial_phex32(uint32_t n);

#ifdef __cplusplus
}
#endif


// TODO: replace with proper divisor+oversample calculation
#define BAUD2DIV(baud) (24000000/16/(baud))

/*
#if defined(KINETISK)
#define BAUD2DIV(baud)  (((F_CPU * 2) + ((baud) >> 1)) / (baud))
#define BAUD2DIV2(baud) (((F_CPU * 2) + ((baud) >> 1)) / (baud))
#define BAUD2DIV3(baud) (((F_BUS * 2) + ((baud) >> 1)) / (baud))
#elif defined(KINETISL)

#if F_CPU <= 2000000
#define BAUD2DIV(baud)  (((F_PLL / 16 ) + ((baud) >> 1)) / (baud))
#elif F_CPU <= 16000000
#define BAUD2DIV(baud)  (((F_PLL / (F_PLL / 1000000)) + ((baud) >> 1)) / (baud))
#else
#define BAUD2DIV(baud)  (((F_PLL / 2 / 16) + ((baud) >> 1)) / (baud))
#endif

#define BAUD2DIV2(baud) (((F_BUS / 16) + ((baud) >> 1)) / (baud))
#define BAUD2DIV3(baud) (((F_BUS / 16) + ((baud) >> 1)) / (baud))
#endif
*/

#endif
