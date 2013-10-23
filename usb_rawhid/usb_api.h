#ifndef USBserial_h_
#define USBserial_h_

#include <inttypes.h>

#include "Print.h"
#include "Stream.h"

class usb_rawhid_class
{
	public:
	int available(void);
	int recv(void *buffer, uint16_t timeout);
	int send(const void *buffer, uint16_t timeout);
};

extern usb_rawhid_class RawHID;


class usb_serial_class : public Stream
{
	public:
	// standard Arduino functions
	void begin(long);
	void end();
	virtual int available();
	virtual int read();
	virtual int peek();
	virtual void flush();
#if ARDUINO >= 100
	virtual size_t write(uint8_t);
#else
	virtual void write(uint8_t);
#endif
	using Print::write;
	operator bool();
	// Teensy extensions
	void send_now(void);
	uint32_t baud(void);
	uint8_t stopbits(void);
	uint8_t paritytype(void);
	uint8_t numbits(void);
	uint8_t dtr(void);
	uint8_t rts(void);
	private:
	uint8_t readnext(void);
};

extern usb_serial_class Serial;


#endif
