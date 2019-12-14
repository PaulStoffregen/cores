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

#if defined(SEREMU_INTERFACE) && !defined(CDC_STATUS_INTERFACE) && !defined(CDC_DATA_INTERFACE)

#include <stdint.h>

// C language implementation
#ifdef __cplusplus
extern "C" {
#endif
void usb_seremu_reset(void);
void usb_seremu_configure(void);
int usb_seremu_getchar(void);
int usb_seremu_peekchar(void);
int usb_seremu_available(void);
void usb_seremu_flush_input(void);
int usb_seremu_putchar(uint8_t c);
int usb_seremu_write(const void *buffer, uint32_t size);
int usb_seremu_write_buffer_free(void);
void usb_seremu_flush_output(void);
extern volatile uint8_t usb_configuration;
#ifdef __cplusplus
}
#endif

// C++ interface
#ifdef __cplusplus
#include "Stream.h"
class usb_seremu_class : public Stream
{
public:
	constexpr usb_seremu_class() {}
        void begin(long) { /* TODO: call a function that tries to wait for enumeration */ };
        void end() { /* TODO: flush output and shut down USB port */ };
        virtual int available() { return usb_seremu_available(); }
        virtual int read() { return usb_seremu_getchar(); }
        virtual int peek() { return usb_seremu_peekchar(); }
        virtual void flush() { usb_seremu_flush_output(); }
        virtual size_t write(uint8_t c) { return usb_seremu_putchar(c); }
        virtual size_t write(const uint8_t *buffer, size_t size) { return usb_seremu_write(buffer, size); }
        size_t write(unsigned long n) { return write((uint8_t)n); }
        size_t write(long n) { return write((uint8_t)n); }
        size_t write(unsigned int n) { return write((uint8_t)n); }
        size_t write(int n) { return write((uint8_t)n); }
	virtual int availableForWrite() { return usb_seremu_write_buffer_free(); }
	using Print::write;
        void send_now(void) { usb_seremu_flush_output(); };
        uint32_t baud(void) { return 9600; }
        uint8_t stopbits(void) { return 1; }
        uint8_t paritytype(void) { return 0; }
        uint8_t numbits(void) { return 8; }
        uint8_t dtr(void) { return 1; }
        uint8_t rts(void) { return 1; }
        operator bool() { return usb_configuration; }
};
extern usb_seremu_class Serial;
extern void serialEvent(void);
#endif // __cplusplus


#if 0
// Allow Arduino programs using Serial to compile, but Serial will do nothing.
#ifdef __cplusplus
#include "Stream.h"
class usb_seremu_class : public Stream
{
public:
	constexpr usb_seremu_class() {}
	void begin(long) { };
	void end() { };
	virtual int available() { return 0; }
	virtual int read() { return -1; }
	virtual int peek() { return -1; }
	virtual void flush() { }
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

extern usb_seremu_class Serial;
extern void serialEvent(void);
#endif // __cplusplus
#endif


#endif // SEREMU_INTERFACE
