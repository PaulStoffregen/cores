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


// HardwareSerial is now an abstract class, intended to allow FlexIO and USB Host
// serial devices to be compatible with libraries like MIDI, OSC, Adafruit_GPS
// which expect a pointer or reference to a HardwareSerial port.
class HardwareSerial : public Stream
{
public:
	virtual void begin(uint32_t baud, uint16_t format=0) = 0;
	virtual void end() = 0;
	virtual int available(void) = 0;
	virtual int peek(void) = 0;
	virtual int read(void) = 0;
	virtual void flush(void) = 0;
	virtual int availableForWrite(void) = 0;
	virtual size_t write(uint8_t) = 0;
	using Print::write;
	virtual operator bool() = 0;
};

class HardwareSerialIMXRT : public HardwareSerial
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
		// General settings for this Serial object.
		uint8_t serial_index;	// which object are we? 0 based
		void (*irq_handler)(void);
		void (* _serialEvent)(void);
		const uint16_t irq_priority;
		const uint16_t rts_low_watermark;
		const uint16_t rts_high_watermark;

		// Settings that apply to underlying LPUART object.
		IRQ_NUMBER_t irq;
		volatile uint32_t &ccm_register;
		const uint32_t ccm_value;
		const uint8_t xbar_out_lpuartX_trig_input;

		// Pin lists
		pin_info_t rx_pins[cnt_rx_pins];
		pin_info_t tx_pins[cnt_tx_pins];
		const uint8_t cts_pin;
		const uint8_t cts_mux_val;
	} hardware_t;
public:
	constexpr HardwareSerialIMXRT(uintptr_t myport, const hardware_t *myhardware,
		volatile BUFTYPE *_tx_buffer, size_t _tx_buffer_size, 
		volatile BUFTYPE *_rx_buffer, size_t _rx_buffer_size) :
		port_addr(myport), hardware(myhardware),
		tx_buffer_(_tx_buffer), rx_buffer_(_rx_buffer), tx_buffer_size_(_tx_buffer_size),  rx_buffer_size_(_rx_buffer_size),
		tx_buffer_total_size_(_tx_buffer_size), rx_buffer_total_size_(_rx_buffer_size) {
	}
	friend uintptr_t Teensyduino_Test_constinit_HardwareSerial(int instance, int index);
	// Initialize hardware serial port with baud rate and data format.  For a list
	// of all supported formats, see https://www.pjrc.com/teensy/td_uart.html
	void begin(uint32_t baud, uint16_t format=0);
	void end(void);
	// Returns the number of bytes which have been received and
	// can be fetched with read() or readBytes().
	virtual int available(void);
	// Returns the next received byte, but does not remove it from the receive
	// buffer.  Returns -1 if nothing has been received.
	virtual int peek(void);
	// Wait for all data written by print() or write() to actually transmit.
	virtual void flush(void);
	// Transmit a single byte
	virtual size_t write(uint8_t c);
	// Reads the next received byte, or returns -1 if nothing has been received.
	virtual int read(void);
	// Configures a digital pin to be HIGH while transmitting.  Typically this
	// pin is used to control the DE and RE' pins of an 8 pin RS485 transceiver
	// chip, which transmits when DE is high and receives when RE' is low.
	void transmitterEnable(uint8_t pin);
	// Configure the serial hardware to receive with an alternate pin.  This
	// function may be called before begin(baud) so the default receive pin
	// is never used, or may be called while the serial hardware is running.  Only
	// specific pins are supported.  https://www.pjrc.com/teensy/td_uart.html
	void setRX(uint8_t pin);
	// Configure the serial hardware to transmit with an alternate pin.  This
	// function may be called before begin(baud) so the default transmit pin
	// is never used, or may be called while the serial hardware is running.  Only
	// specific pins are supported.  https://www.pjrc.com/teensy/td_uart.html
	void setTX(uint8_t pin, bool opendrain=false);
	// Configure RTS flow control.  The pin will be LOW when Teensy is able to
	// receive more data, or HIGH when the serial device should pause transmission.
	// All digital pins are supported.
	bool attachRts(uint8_t pin);
	// Same as attachRts except the signal levels are reversed.
	// Configure RTS flow control.  The pin will be HIGH when Teensy is able to
	// receive more data, or LOW when the serial device should pause transmission.
	// All digital pins are supported.
	bool attachRtsInverted(uint8_t pin);
	// Configure CTS flow control.  Teensy will transmit when this pin is LOW
	// and will pause transmission when the pin is HIGH.  Only specific pins are
	// supported.  See https://www.pjrc.com/teensy/td_uart.html
	bool attachCts(uint8_t pin);
	// // Discard all received data which has not been read.
	void clear(void);
	// Returns the number of bytes which may be transmitted by write() or print()
	// without waiting.  Typically programs which must maintain rapid checking
	// and response to sensors use availableForWrite() to decide whether to
	// transmit.
	virtual int availableForWrite(void);
	// Increase the amount of buffer memory between reception of bytes by the
	// serial hardware and the available() and read() functions. This is useful
	// when your program must spend lengthy times performing other work, like
	// writing to a SD card, before it can return to reading the incoming serial
	// data.  The buffer array must be a global or static variable.
	void addMemoryForRead(void *buffer, size_t length);
	// Increase the amount of buffer memory between print(), write() and actual
	// hardware serial transmission. This can be useful when your program needs
	// to print or write a large amount of data, without waiting.  The buffer
	// array must be a global or static variable.
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
	// Transmit a single byte
	size_t write(unsigned long n) { return write((uint8_t)n); }
	// Transmit a single byte
	size_t write(long n) { return write((uint8_t)n); }
	// Transmit a single byte
	size_t write(unsigned int n) { return write((uint8_t)n); }
	// Transmit a single byte
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
	const uintptr_t port_addr;
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
	bool				rts_pin_invert_ = false;

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
	static HardwareSerialIMXRT 	*s_serials_with_serial_events[8];
	#else	
	static HardwareSerialIMXRT 	*s_serials_with_serial_events[7];
	#endif
	static uint8_t 			s_count_serials_with_serial_events;
	void addToSerialEventsList(); 
	inline void doYieldCode()  {
		if (available()) (*hardware->_serialEvent)();
	}



};
// Serial1 hardware serial port for pins RX1 and TX1.  More detail at
// https://www.pjrc.com/teensy/td_uart.html
extern HardwareSerialIMXRT Serial1;
// Serial2 hardware serial port for pins RX2 and TX2.  More detail at
// https://www.pjrc.com/teensy/td_uart.html
extern HardwareSerialIMXRT Serial2;
// Serial3 hardware serial port for pins RX3 and TX3.  More detail at
// https://www.pjrc.com/teensy/td_uart.html
extern HardwareSerialIMXRT Serial3;
// Serial4 hardware serial port for pins RX4 and TX4.  More detail at
// https://www.pjrc.com/teensy/td_uart.html
extern HardwareSerialIMXRT Serial4;
// Serial5 hardware serial port for pins RX5 and TX5.  More detail at
// https://www.pjrc.com/teensy/td_uart.html
extern HardwareSerialIMXRT Serial5;
// Serial6 hardware serial port for pins RX6 and TX6.  More detail at
// https://www.pjrc.com/teensy/td_uart.html
extern HardwareSerialIMXRT Serial6;
// Serial7 hardware serial port for pins RX7 and TX7.  More detail at
// https://www.pjrc.com/teensy/td_uart.html
extern HardwareSerialIMXRT Serial7;
extern void serialEvent1(void) __attribute__((weak));
extern void serialEvent2(void) __attribute__((weak));
extern void serialEvent3(void) __attribute__((weak));
extern void serialEvent4(void) __attribute__((weak));
extern void serialEvent5(void) __attribute__((weak));
extern void serialEvent6(void) __attribute__((weak));
extern void serialEvent7(void) __attribute__((weak));

#if defined(ARDUINO_TEENSY41)
// Serial8 hardware serial port for pins RX8 and TX8.  More detail at
// https://www.pjrc.com/teensy/td_uart.html
extern HardwareSerialIMXRT Serial8;
extern void serialEvent8(void) __attribute__((weak));
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
