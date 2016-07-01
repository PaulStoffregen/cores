#ifndef USBserial_HID_h_
#define USBserial_HID_h_

#include <inttypes.h>

#include "keylayouts.h"
#include "Print.h"
#include "Stream.h"

class usb_serial_class : public Stream
{
public:
	void begin(long);
	void end();
	virtual int available();
	virtual int read();
	virtual int peek();
	virtual void flush();
#if ARDUINO >= 100
	virtual size_t write(uint8_t c)		{ return write(&c, 1); }
	virtual size_t write(const uint8_t *buffer, uint16_t size);
	using Print::write;
#else
	virtual void write(uint8_t c)		{ write(&c, 1); }
	virtual void write(const uint8_t *buffer, uint16_t size);
	virtual void write(const char *s)	{ write((const uint8_t *)s, strlen(s)); }
#endif
	void send_now(void);
	uint32_t baud(void);
	uint8_t stopbits(void);
	uint8_t paritytype(void);
	uint8_t numbits(void);
	uint8_t dtr(void);
	uint8_t rts(void);
	operator bool();
private:
	int16_t peek_buf;
};

extern usb_serial_class Serial;




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
	void set_media(uint8_t) {
	}
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



#define MOUSE_LEFT 1
#define MOUSE_MIDDLE 4
#define MOUSE_RIGHT 2
#define MOUSE_BACK 8
#define MOUSE_FORWARD 16
#define MOUSE_ALL (MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE | MOUSE_BACK | MOUSE_FORWARD)

class usb_mouse_class
{
        public:
	void begin(void) { }
	void end(void) { }
        void move(int8_t x, int8_t y, int8_t wheel=0, int8_t horiz=0);
        void click(uint8_t b = MOUSE_LEFT);
        void scroll(int8_t wheel, int8_t horiz=0);
        void set_buttons(uint8_t left, uint8_t middle=0, uint8_t right=0, uint8_t back=0, uint8_t forward=0);
        void press(uint8_t b = MOUSE_LEFT);
        void release(uint8_t b = MOUSE_LEFT);
        bool isPressed(uint8_t b = MOUSE_ALL);
};

extern usb_mouse_class Mouse;


extern uint8_t joystick_report_data[12];

class usb_joystick_class
{
        public:
        usb_joystick_class() { manual_mode = 0; }
        inline void button(uint8_t button, bool val) {
                button--;
                uint8_t mask = (1 << (button & 7));
                if (val) {
                        if (button < 8) joystick_report_data[0] |= mask;
                        else if (button < 16) joystick_report_data[1] |= mask;
                        else if (button < 24) joystick_report_data[2] |= mask;
                        else if (button < 32) joystick_report_data[3] |= mask;
                } else {
                        mask = ~mask;
                        if (button < 8) joystick_report_data[0] &= mask;
                        else if (button < 16) joystick_report_data[1] &= mask;
                        else if (button < 24) joystick_report_data[2] &= mask;
                        else if (button < 32) joystick_report_data[3] &= mask;
                }
                if (!manual_mode) send_now();
        }
        inline void X(uint16_t val) {
                if (val > 1023) val = 1023;
                joystick_report_data[4] = (joystick_report_data[4] & 0x0F) | (val << 4);
                joystick_report_data[5] = (joystick_report_data[5] & 0xC0) | (val >> 4);
                if (!manual_mode) send_now();
        }
        inline void Y(uint16_t val) {
                if (val > 1023) val = 1023;
                joystick_report_data[5] = (joystick_report_data[5] & 0x3F) | (val << 6);
                joystick_report_data[6] = (val >> 2);
                if (!manual_mode) send_now();
        }
        inline void position(uint16_t x, uint16_t y) {
                if (x > 1023) x = 1023;
                if (y > 1023) y = 1023;
                joystick_report_data[4] = (joystick_report_data[4] & 0x0F) | (x << 4);
                joystick_report_data[5] = (x >> 4) | (y << 6);
                joystick_report_data[6] = (y >> 2);
                if (!manual_mode) send_now();
        }
        inline void Z(uint16_t val) {
                if (val > 1023) val = 1023;
                joystick_report_data[7] = val;
                joystick_report_data[8] = (joystick_report_data[8] & 0xFC) | (val >> 8);
                if (!manual_mode) send_now();
        }
        inline void Zrotate(uint16_t val) {
                if (val > 1023) val = 1023;
                joystick_report_data[8] = (joystick_report_data[8] & 0x03) | (val << 2);
                joystick_report_data[9] = (joystick_report_data[9] & 0xF0) | (val >> 6);
                if (!manual_mode) send_now();
        }
        inline void sliderLeft(uint16_t val) {
                if (val > 1023) val = 1023;
                joystick_report_data[9] = (joystick_report_data[9] & 0x0F) | (val << 4);
                joystick_report_data[10] = (joystick_report_data[10] & 0xC0) | (val >> 4);
                if (!manual_mode) send_now();
        }
        inline void sliderRight(uint16_t val) {
                if (val > 1023) val = 1023;
                joystick_report_data[10] = (joystick_report_data[10] & 0x3F) | (val << 6);
                joystick_report_data[11] = (val >> 2);
                if (!manual_mode) send_now();
        }
        inline void slider(uint16_t val) {
                if (val > 1023) val = 1023;
                joystick_report_data[9] = (joystick_report_data[9] & 0x0F) | (val << 4);
                joystick_report_data[10] = (val >> 4) | (val << 6);
                joystick_report_data[11] = (val >> 2);
                if (!manual_mode) send_now();
        }
        inline void hat(int16_t dir) {
                uint8_t val;
                if (dir < 0) val = 15;
                else if (dir < 23) val = 0;
                else if (dir < 68) val = 1;
                else if (dir < 113) val = 2;
                else if (dir < 158) val = 3;
                else if (dir < 203) val = 4;
                else if (dir < 245) val = 5;
                else if (dir < 293) val = 6;
                else if (dir < 338) val = 7;
                joystick_report_data[4] = (joystick_report_data[4] & 0xF0) | val;
                if (!manual_mode) send_now();
        }
        inline void useManualSend(bool mode) {
                manual_mode = mode;
        }
        void send_now(void);
        private:
        //static uint8_t manual_mode;
        uint8_t manual_mode;
};

extern usb_joystick_class Joystick;


#endif
