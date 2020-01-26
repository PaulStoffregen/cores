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

#include <inttypes.h>

#include "usb_serial_port.h"

#if F_CPU >= 20000000 && !defined(USB_DISABLED)

#include "core_pins.h" // for millis()

// C language implementation
#ifdef __cplusplus
extern "C" {
#endif
extern struct usb_serial_port usb_serial_instance;

static inline int usb_serial_getchar(void)
{
	return __usb_serial_getchar(&usb_serial_instance);
}

static inline int usb_serial_peekchar(void)
{
	return __usb_serial_peekchar(&usb_serial_instance);
}

static inline int usb_serial_available(void)
{
	return __usb_serial_available(&usb_serial_instance);
}

static inline int usb_serial_read(void *buffer, uint32_t size)
{
	return __usb_serial_read(&usb_serial_instance, buffer, size);
}

static inline void usb_serial_flush_input(void)
{
	__usb_serial_flush_input(&usb_serial_instance);
}

static inline int usb_serial_putchar(uint8_t c)
{
	return __usb_serial_putchar(&usb_serial_instance, c);
}

static inline int usb_serial_write(const void *buffer, uint32_t size)
{
	return __usb_serial_write(&usb_serial_instance, buffer, size);
}

static inline int usb_serial_write_buffer_free(void)
{
	return __usb_serial_write_buffer_free(&usb_serial_instance);
}

static inline void usb_serial_flush_output(void)
{
	__usb_serial_flush_output(&usb_serial_instance);
}

static inline void usb_serial_flush_callback(void)
{
	__usb_serial_flush_callback(&usb_serial_instance);
}

#define usb_cdc_line_coding		usb_serial_instance.cdc_line_coding
#define usb_cdc_line_rtsdtr_millis	usb_serial_instance.cdc_line_rtsdtr_millis
#define usb_cdc_line_rtsdtr		usb_serial_instance.cdc_line_rtsdtr
#define usb_cdc_transmit_flush_timer	usb_serial_instance.cdc_transmit_flush_timer

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
        virtual int available() { return usb_serial_available(); }
        virtual int read() { return usb_serial_getchar(); }
        virtual int peek() { return usb_serial_peekchar(); }
        virtual void flush() { usb_serial_flush_output(); }  // TODO: actually wait for data to leave USB...
        virtual void clear(void) { usb_serial_flush_input(); }
        virtual size_t write(uint8_t c) { return usb_serial_putchar(c); }
        virtual size_t write(const uint8_t *buffer, size_t size) { return usb_serial_write(buffer, size); }
	size_t write(unsigned long n) { return write((uint8_t)n); }
	size_t write(long n) { return write((uint8_t)n); }
	size_t write(unsigned int n) { return write((uint8_t)n); }
	size_t write(int n) { return write((uint8_t)n); }
	virtual int availableForWrite() { return usb_serial_write_buffer_free(); }
	using Print::write;
        void send_now(void) { usb_serial_flush_output(); }
        uint32_t baud(void) { return usb_serial_instance.cdc_line_coding[0]; }
        uint8_t stopbits(void) {
		uint8_t b = usb_serial_instance.cdc_line_coding[1];
		if (!b) b = 1;
		return b;
	}
        uint8_t paritytype(void) {
		// 0=none, 1=odd, 2=even
		return usb_serial_instance.cdc_line_coding[1] >> 8;
	}
        uint8_t numbits(void) {
		return usb_serial_instance.cdc_line_coding[1] >> 16;
	}
        uint8_t dtr(void) {
		return (usb_serial_instance.cdc_line_rtsdtr & USB_SERIAL_DTR) ?
		       1 : 0;
	}
        uint8_t rts(void) {
		return (usb_serial_instance.cdc_line_rtsdtr & USB_SERIAL_RTS) ?
		       1 : 0;
	}
        operator bool() {
		return usb_configuration &&
		       (usb_serial_instance.cdc_line_rtsdtr & USB_SERIAL_DTR) &&
		       ((uint32_t)(systick_millis_count - usb_serial_instance.cdc_line_rtsdtr_millis) >= 15);
	}
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
extern usb_serial_class Serial;
extern void serialEvent(void);
#endif // __cplusplus


#else  // F_CPU < 20000000

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
extern void serialEvent(void);
#endif // __cplusplus


#endif // F_CPU
