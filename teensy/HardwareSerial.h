#ifndef HardwareSerial_h
#define HardwareSerial_h

#include <inttypes.h>
#include "Stream.h"

class HardwareSerial : public Stream
{
public:
	inline void begin(uint32_t baud, uint8_t txen_pin=255) {
		_begin(((F_CPU / 8) + (baud / 2)) / baud, txen_pin);
	}
	void _begin(uint16_t baud_count, uint8_t pin);
	void end(void);
	void transmitterEnable(uint8_t pin);
	virtual int available(void);
	virtual int peek(void);
	virtual int read(void);
	virtual void flush(void);
	int availableForWrite(void);
	void clear(void);
#if ARDUINO >= 100
	virtual size_t write(uint8_t);
#else
	virtual void write(uint8_t);
#endif
	using Print::write;
	friend uintptr_t Teensyduino_Test_constinit_HardwareSerial(int instance, int index);
};

extern HardwareSerial Serial1;

#endif
