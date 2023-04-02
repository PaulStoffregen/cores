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

#pragma once

#include "usb_desc.h"
#include <stdint.h>

#if (defined(CDC_STATUS_INTERFACE) && defined(CDC_DATA_INTERFACE)) || defined(USB_DISABLED)

#if !defined(USB_DISABLED)

// C language implementation
#ifdef __cplusplus
extern "C" {
#endif
void usb_serial_reset(void);
void usb_serial_configure(void);
int usb_serial_getchar(void);
int usb_serial_peekchar(void);
int usb_serial_available(void);
int usb_serial_read(void *buffer, uint32_t size);
void usb_serial_flush_input(void);
int usb_serial_putchar(uint8_t c);
int usb_serial_write(const void *buffer, uint32_t size);
int usb_serial_write_buffer_free(void);
void usb_serial_flush_output(void);
extern uint32_t usb_cdc_line_coding[2];
extern volatile uint32_t usb_cdc_line_rtsdtr_millis;
extern volatile uint32_t systick_millis_count;
extern volatile uint8_t usb_cdc_line_rtsdtr;
extern volatile uint8_t usb_cdc_transmit_flush_timer;
extern volatile uint8_t usb_configuration;
extern void serialEvent(void) __attribute__((weak));
#ifdef __cplusplus
}
#endif

#define USB_SERIAL_DTR  0x01
#define USB_SERIAL_RTS  0x02

// C++ interface
#ifdef __cplusplus
#include "Stream.h"
class usb_serial_class : public Stream
{
public:
	constexpr usb_serial_class() {}
	// Serial.begin(baud) is optional on Teensy.  The main USB device port
	// is always initialized early during startup.  The baud rate setting
	// is not used.  Communication occurs at USB native speed.  For
	// compatibility with Arduino code, Serial.begin waits up to 2 seconds
	// for your PC to open the virtual serial port.
        void begin(long baud_unused __attribute__((unused))) {
		uint32_t millis_begin = systick_millis_count;
		while (!(*this)) {
			uint32_t elapsed = systick_millis_count - millis_begin;
			if (usb_configuration) {
				// Wait up to 2 seconds for Arduino Serial Monitor
				if (elapsed > 2000) break;
			} else {
				// But wait only 3/4 second if there is no sign the
				// USB host has begun the USB enumeration process.
				if (elapsed > 750) break;
			}
			yield();
		}
	}
        void end() { /* TODO: flush output and shut down USB port */ };
	// Returns the number of bytes which have been received from your PC and
	// can be fetched using Serial.read() or Serial.readBytes().
        virtual int available() { return usb_serial_available(); }
	// Reads the next received byte, or returns -1 if nothing has been received
	// from your PC.
        virtual int read() { return usb_serial_getchar(); }
	// Returns the next received byte, but does not remove it from the receive
	// buffer.  Returns -1 if nothing has been received from your PC.
        virtual int peek() { return usb_serial_peekchar(); }
	// Wait for all data written by print() or write() to actually transmit to
	// your PC.  On Teensy 4, this function has a known limitation where it
	// returns early, when buffered data has been given to Teensy's USB device
	// controller, but before your PC's USB host controller actually transfers
	// the data across your USB cable.
        virtual void flush() { usb_serial_flush_output(); }  // TODO: actually wait for data to leave USB...
	// Discard all received data which has not been read.
        virtual void clear(void) { usb_serial_flush_input(); }
	// Transmit a single byte to your PC
        virtual size_t write(uint8_t c) { return usb_serial_putchar(c); }
	// Transmit a buffer containing any number of bytes to your PC
        virtual size_t write(const uint8_t *buffer, size_t size) { return usb_serial_write(buffer, size); }
	// Transmit a single byte to your PC
	size_t write(unsigned long n) { return write((uint8_t)n); }
	// Transmit a single byte to your PC
	size_t write(long n) { return write((uint8_t)n); }
	// Transmit a single byte to your PC
	size_t write(unsigned int n) { return write((uint8_t)n); }
	// Transmit a single byte to your PC
	size_t write(int n) { return write((uint8_t)n); }
	// Returns the number of bytes which may be transmitted by write() or print()
	// without waiting.  Typically programs which must maintain rapid checking
	// and response to sensors use availableForWrite() to decide whether to
	// transmit.
	virtual int availableForWrite() { return usb_serial_write_buffer_free(); }
	using Print::write;
	// Cause any previously transmitted data written to buffers to be actually
	// sent over the USB cable to your PC as soon as possible.  Normally writes
	// are combined to efficiently use maximum size USB packets.  Use of send_now()
	// minimizes latency, but excessive use can lead to inefficient utilization
	// of USB bandwidth.
        void send_now(void) { usb_serial_flush_output(); }
	// Returns the baud rate configuration set by PC software.  This setting is
	// not used for USB communication.  You would typically call this function
	// when making a USB to Serial converter, where you wish to know the baud
	// rate software on the PC intends for you to configure on the serial port.
        uint32_t baud(void) { return usb_cdc_line_coding[0]; }
	// Returns the baud rate configuration set by PC software.  This setting is
	// not used for USB communication.  You would typically call this function
	// when making a USB to Serial converter, where you wish to know the baud
	// rate software on the PC intends for you to configure on the serial port.
        uint8_t stopbits(void) { uint8_t b = usb_cdc_line_coding[1]; if (!b) b = 1; return b; }
	// Returns the number of stop bits configuration set by PC software.  This
	// setting is not used for USB communication.  You would typically call this
	// function when making a USB to Serial converter, where you wish to know how
	// the PC software intends for you to configure the serial port.
        uint8_t paritytype(void) { return usb_cdc_line_coding[1] >> 8; } // 0=none, 1=odd, 2=even
	// Returns the number of data bits configuration set by PC software.
	// 0=none, 1=odd, 2=even.  This setting is not used for USB communication,
	// which always checks for errors at the USB packet level.  You would typically
	// call this function when making a USB to Serial converter, where you wish
	// to know how the PC software intends for you to configure the serial port.
        uint8_t numbits(void) { return usb_cdc_line_coding[1] >> 16; }
	// Returns the current state of the virtual serial DTR signal.
        uint8_t dtr(void) { return (usb_cdc_line_rtsdtr & USB_SERIAL_DTR) ? 1 : 0; }
	// Returns the current state of the virtual serial RTS signal.
        uint8_t rts(void) { return (usb_cdc_line_rtsdtr & USB_SERIAL_RTS) ? 1 : 0; }
	// Testing Serial as a boolean indicates whether USB is active and a program
	// running on your PC has raised the DTR signal, which typically means it has
	// opened the port and is ready to communicate.
        operator bool() {
		yield();
		return usb_configuration && (usb_cdc_line_rtsdtr & USB_SERIAL_DTR) &&
		((uint32_t)(systick_millis_count - usb_cdc_line_rtsdtr_millis) >= 15);
	}
	// Read up to length bytes into a buffer.  readBytes() will wait up to
	// the number of milliseconds configured by setTimeout().  The return value
	// is the number of bytes actually read, which may be zero if your PC
	// does not send anything.  To read without waiting, configure setTimeout(0).
	size_t readBytes(char *buffer, size_t length) {
		size_t count=0;
		unsigned long startMillis = millis();
		do {
			count += usb_serial_read(buffer + count, length - count);
			if (count >= length) return count;
		} while(millis() - startMillis < _timeout);
		setReadError();
		return count;
	}

};
// Serial provides USB Virtual Serial communication with your computer.
extern usb_serial_class Serial;
#endif // __cplusplus

#else  // !defined(USB_DISABLED)

// Allow Arduino programs using Serial to compile, but Serial will do nothing.
#ifdef __cplusplus
#include "Stream.h"
class usb_serial_class : public Stream
{
public:
    constexpr usb_serial_class() {}
        void begin(long) { };
        void end() { };
        virtual int available() { return 0; }
        virtual int read() { return -1; }
        virtual int peek() { return -1; }
        virtual void flush() { }
        virtual void clear() { }
        virtual size_t write(uint8_t c) { return 1; }
        virtual size_t write(const uint8_t *buffer, size_t size) { return size; }
    size_t write(unsigned long n) { return 1; }
    size_t write(long n) { return 1; }
    size_t write(unsigned int n) { return 1; }
    size_t write(int n) { return 1; }
    int availableForWrite() { return 0; }
    using Print::write;
        void send_now(void) { }
        uint32_t baud(void) { return 0; }
        uint8_t stopbits(void) { return 1; }
        uint8_t paritytype(void) { return 0; }
        uint8_t numbits(void) { return 8; }
        uint8_t dtr(void) { return 1; }
        uint8_t rts(void) { return 1; }
        operator bool() { return true; }
};

extern usb_serial_class Serial;
#endif // __cplusplus

#endif // !defined(USB_DISABLED)

#endif // CDC_STATUS_INTERFACE && CDC_DATA_INTERFACE




#if defined(CDC2_STATUS_INTERFACE) && defined(CDC2_DATA_INTERFACE)

// C language implementation
#ifdef __cplusplus
extern "C" {
#endif
void usb_serial2_configure(void);
int usb_serial2_getchar(void);
int usb_serial2_peekchar(void);
int usb_serial2_available(void);
int usb_serial2_read(void *buffer, uint32_t size);
void usb_serial2_flush_input(void);
int usb_serial2_putchar(uint8_t c);
int usb_serial2_write(const void *buffer, uint32_t size);
int usb_serial2_write_buffer_free(void);
void usb_serial2_flush_output(void);
extern uint32_t usb_cdc2_line_coding[2];
extern volatile uint32_t usb_cdc2_line_rtsdtr_millis;
extern volatile uint8_t usb_cdc2_line_rtsdtr;
extern volatile uint8_t usb_cdc2_transmit_flush_timer;
extern void serialEventUSB1(void) __attribute__((weak));
#ifdef __cplusplus
}
#endif

// C++ interface
#ifdef __cplusplus
#include "Stream.h"
class usb_serial2_class : public Stream
{
public:
        constexpr usb_serial2_class() {}
        void begin(long) {
                //uint32_t millis_begin = systick_millis_count;
                //disabled for now - causes more trouble than it solves?
                //while (!(*this)) {
                        // wait up to 2.5 seconds for Arduino Serial Monitor
                        // Yes, this is a long time, but some Windows systems open
                        // the port very slowly.  This wait allows programs for
                        // Arduino Uno to "just work" (without forcing a reboot when
                        // the port is opened), and when no PC is connected the user's
                        // sketch still gets to run normally after this wait time.
                        //if ((uint32_t)(systick_millis_count - millis_begin) > 2500) break;
                //}
        }
        void end() { /* TODO: flush output and shut down USB port */ };
        virtual int available() { return usb_serial2_available(); }
        virtual int read() { return usb_serial2_getchar(); }
        virtual int peek() { return usb_serial2_peekchar(); }
        virtual void flush() { usb_serial2_flush_output(); }  // TODO: actually wait for data to leave USB...
        virtual void clear(void) { usb_serial2_flush_input(); }
        virtual size_t write(uint8_t c) { return usb_serial2_putchar(c); }
        virtual size_t write(const uint8_t *buffer, size_t size) { return usb_serial2_write(buffer, size); }
        size_t write(unsigned long n) { return write((uint8_t)n); }
        size_t write(long n) { return write((uint8_t)n); }
        size_t write(unsigned int n) { return write((uint8_t)n); }
        size_t write(int n) { return write((uint8_t)n); }
        virtual int availableForWrite() { return usb_serial2_write_buffer_free(); }
        using Print::write;
        void send_now(void) { usb_serial2_flush_output(); }
        uint32_t baud(void) { return usb_cdc2_line_coding[0]; }
        uint8_t stopbits(void) { uint8_t b = usb_cdc2_line_coding[1]; if (!b) b = 1; return b; }
        uint8_t paritytype(void) { return usb_cdc2_line_coding[1] >> 8; } // 0=none, 1=odd, 2=even
        uint8_t numbits(void) { return usb_cdc2_line_coding[1] >> 16; }
        uint8_t dtr(void) { return (usb_cdc2_line_rtsdtr & USB_SERIAL_DTR) ? 1 : 0; }
        uint8_t rts(void) { return (usb_cdc2_line_rtsdtr & USB_SERIAL_RTS) ? 1 : 0; }
        operator bool() {
		yield();
		return usb_configuration && (usb_cdc2_line_rtsdtr & USB_SERIAL_DTR) &&
                ((uint32_t)(systick_millis_count - usb_cdc2_line_rtsdtr_millis) >= 15);
        }
        size_t readBytes(char *buffer, size_t length) {
                size_t count=0;
                unsigned long startMillis = millis();
                do {
                        count += usb_serial2_read(buffer + count, length - count);
                        if (count >= length) return count;
                } while(millis() - startMillis < _timeout);
                setReadError();
                return count;
        }

};
extern usb_serial2_class SerialUSB1;
#endif // __cplusplus

#endif // CDC2_STATUS_INTERFACE && CDC2_DATA_INTERFACE



#if defined(CDC3_STATUS_INTERFACE) && defined(CDC3_DATA_INTERFACE)

// C language implementation
#ifdef __cplusplus
extern "C" {
#endif
void usb_serial3_configure(void);
int usb_serial3_getchar(void);
int usb_serial3_peekchar(void);
int usb_serial3_available(void);
int usb_serial3_read(void *buffer, uint32_t size);
void usb_serial3_flush_input(void);
int usb_serial3_putchar(uint8_t c);
int usb_serial3_write(const void *buffer, uint32_t size);
int usb_serial3_write_buffer_free(void);
void usb_serial3_flush_output(void);
extern uint32_t usb_cdc3_line_coding[2];
extern volatile uint32_t usb_cdc3_line_rtsdtr_millis;
extern volatile uint8_t usb_cdc3_line_rtsdtr;
extern volatile uint8_t usb_cdc3_transmit_flush_timer;
extern void serialEventUSB2(void) __attribute__((weak));
#ifdef __cplusplus
}
#endif

// C++ interface
#ifdef __cplusplus
#include "Stream.h"
class usb_serial3_class : public Stream
{
public:
        constexpr usb_serial3_class() {}
        void begin(long) {
                //uint32_t millis_begin = systick_millis_count;
                //disabled for now - causes more trouble than it solves?
                //while (!(*this)) {
                        // wait up to 2.5 seconds for Arduino Serial Monitor
                        // Yes, this is a long time, but some Windows systems open
                        // the port very slowly.  This wait allows programs for
                        // Arduino Uno to "just work" (without forcing a reboot when
                        // the port is opened), and when no PC is connected the user's
                        // sketch still gets to run normally after this wait time.
                        //if ((uint32_t)(systick_millis_count - millis_begin) > 2500) break;
                //}
        }
        void end() { /* TODO: flush output and shut down USB port */ };
        virtual int available() { return usb_serial3_available(); }
        virtual int read() { return usb_serial3_getchar(); }
        virtual int peek() { return usb_serial3_peekchar(); }
        virtual void flush() { usb_serial3_flush_output(); }  // TODO: actually wait for data to leave USB...
        virtual void clear(void) { usb_serial3_flush_input(); }
        virtual size_t write(uint8_t c) { return usb_serial3_putchar(c); }
        virtual size_t write(const uint8_t *buffer, size_t size) { return usb_serial3_write(buffer, size); }
        size_t write(unsigned long n) { return write((uint8_t)n); }
        size_t write(long n) { return write((uint8_t)n); }
        size_t write(unsigned int n) { return write((uint8_t)n); }
        size_t write(int n) { return write((uint8_t)n); }
        virtual int availableForWrite() { return usb_serial3_write_buffer_free(); }
        using Print::write;
        void send_now(void) { usb_serial3_flush_output(); }
        uint32_t baud(void) { return usb_cdc3_line_coding[0]; }
        uint8_t stopbits(void) { uint8_t b = usb_cdc3_line_coding[1]; if (!b) b = 1; return b; }
        uint8_t paritytype(void) { return usb_cdc3_line_coding[1] >> 8; } // 0=none, 1=odd, 2=even
        uint8_t numbits(void) { return usb_cdc3_line_coding[1] >> 16; }
        uint8_t dtr(void) { return (usb_cdc3_line_rtsdtr & USB_SERIAL_DTR) ? 1 : 0; }
        uint8_t rts(void) { return (usb_cdc3_line_rtsdtr & USB_SERIAL_RTS) ? 1 : 0; }
        operator bool() {
		yield();
		return usb_configuration && (usb_cdc3_line_rtsdtr & USB_SERIAL_DTR) &&
                ((uint32_t)(systick_millis_count - usb_cdc3_line_rtsdtr_millis) >= 15);
        }
        size_t readBytes(char *buffer, size_t length) {
                size_t count=0;
                unsigned long startMillis = millis();
                do {
                        count += usb_serial3_read(buffer + count, length - count);
                        if (count >= length) return count;
                } while(millis() - startMillis < _timeout);
                setReadError();
                return count;
        }

};
extern usb_serial3_class SerialUSB2;
#endif // __cplusplus

#endif // CDC3_STATUS_INTERFACE && CDC3_DATA_INTERFACE





