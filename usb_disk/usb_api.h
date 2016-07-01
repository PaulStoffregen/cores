#ifndef USBserial_h_
#define USBserial_h_

#include <inttypes.h>

#include "keylayouts.h"
#include "Print.h"
#include "Stream.h"


class usb_keyboard_class : public Print
{
	public:
	void begin(void) { }
	void end(void) { }
#if ARDUINO >= 100
	virtual size_t write(uint8_t);
#else
	virtual void write(uint8_t);
#endif
	using Print::write;
	void write_unicode(uint16_t unicode) { write_keycode(unicode_to_keycode(unicode)); }
	void set_modifier(uint16_t);
	void set_key1(uint8_t);
	void set_key2(uint8_t);
	void set_key3(uint8_t);
	void set_key4(uint8_t);
	void set_key5(uint8_t);
	void set_key6(uint8_t);
	void set_media(uint8_t);
	void send_now(void);
	void press(uint16_t n);
	void release(uint16_t n);
	void releaseAll(void);
	private:
	KEYCODE_TYPE unicode_to_keycode(uint16_t unicode);
	KEYCODE_TYPE deadkey_to_keycode(KEYCODE_TYPE keycode);
	uint8_t keycode_to_modifier(KEYCODE_TYPE keycode);
	uint8_t keycode_to_key(KEYCODE_TYPE keycode);
	void presskey(uint8_t key, uint8_t modifier);
	void releasekey(uint8_t key, uint8_t modifier);
	void write_keycode(KEYCODE_TYPE key);
	void write_key(KEYCODE_TYPE code);
	uint8_t utf8_state;
	uint16_t unicode_wchar;
};

extern usb_keyboard_class Keyboard;


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

extern "C" {
extern void media_claim(void);
extern uint8_t media_read_sector(uint32_t lba, uint8_t *buffer);
extern uint8_t media_write_sector(uint32_t lba, const uint8_t *buffer);
extern void media_release(uint8_t read_only_mode);
uint8_t media_lock(void);
void media_unlock(void);
}

class usb_disk_class
{
	public:
	inline void pause(void) {
		while (!media_lock()) /* wait */ ;
	}
	inline void resume(void) {
		media_unlock();
	}
	inline void claim(void) {
		media_claim();
	}
	inline uint8_t readSector(uint32_t addr, uint8_t *buffer) {
		return media_read_sector(addr, buffer);
	}
	inline uint8_t writeSector(uint32_t addr, const uint8_t *buffer) {
		return media_write_sector(addr, buffer);
	}
	inline void release(void) {
		media_release(0);
	}
	inline void releaseReadOnly(void) {
		media_release(1);
	}
};

extern usb_disk_class Disk;

#endif
