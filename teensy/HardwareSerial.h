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
	int available(void) override;
	int peek(void) override;
	int read(void) override;
	void flush(void) override;
	int availableForWrite(void) override;
	void clear(void);
#if ARDUINO >= 100
	size_t write(uint8_t) override;
#else
	virtual void write(uint8_t);
#endif
	using Print::write;
	friend uintptr_t Teensyduino_Test_constinit_HardwareSerial(int instance, int index);
};

extern HardwareSerial Serial1;

#endif
