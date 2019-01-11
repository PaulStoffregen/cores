#ifndef USBserial_h_
#define USBserial_h_

#include <inttypes.h>

#include "Print.h"
#include "Stream.h"
#include "elapsedMillis.h"

class FlightSimClass;
class FlightSimCommand;
class FlightSimInteger;

class _XpRefStr_;
#define XPlaneRef(str) ((const _XpRefStr_ *)(PSTR(str)))

class FlightSimClass
{
public:
	FlightSimClass();
	static void update(void);
	static bool isEnabled(void);
	static unsigned long getFrameCount(void) { return frameCount; }
private:
	static uint8_t request_id_messages;
	static uint8_t enabled;
	static elapsedMillis enableTimeout;
	static unsigned long frameCount;
	static void enable(void) { enabled = 1; enableTimeout = 0; }
	static void disable(void) { enabled = 0; }
	static uint8_t recv(uint8_t *buffer);
	static void xmit(const uint8_t *p1, uint8_t n1);
	static void xmit(const uint8_t *p1, uint8_t n1, const uint8_t *p2, uint8_t n2);
	static void xmit(const uint8_t *p1, uint8_t n1, const _XpRefStr_ *p2, uint16_t n2);
	static void xmit_big_packet(const uint8_t *p1, uint8_t n1, const _XpRefStr_ *p2, uint16_t n2);
	friend class FlightSimCommand;
	friend class FlightSimInteger;
	friend class FlightSimFloat;
};


class FlightSimCommand
{
public:
	FlightSimCommand();
	void assign(const _XpRefStr_ *s) { name = s; if (FlightSimClass::enabled) identify(); }
	FlightSimCommand & operator = (const _XpRefStr_ *s) { assign(s); return *this; }
	void begin(void) { sendcmd(4); }
	void end(void) { sendcmd(5); }
	FlightSimCommand & operator = (int n) { sendcmd((n) ? 4 : 5); return *this; }
	void once(void) { sendcmd(6); }
	void identify(void);
private:
	unsigned int id;
	const _XpRefStr_ *name;
	void sendcmd(uint8_t n);
	FlightSimCommand *next;
	static FlightSimCommand *first;
	static FlightSimCommand *last;
	friend class FlightSimClass;
};


class FlightSimInteger
{
public:
	FlightSimInteger();
	void assign(const _XpRefStr_ *s) { name = s; if (FlightSimClass::enabled) identify(); }
	FlightSimInteger & operator = (const _XpRefStr_ *s) { assign(s); return *this; }
	void write(long val);
	FlightSimInteger & operator = (char n) { write((long)n); return *this; }
	FlightSimInteger & operator = (int n) { write((long)n); return *this; }
	FlightSimInteger & operator = (long n) { write(n); return *this; }
	FlightSimInteger & operator = (unsigned char n) { write((long)n); return *this; }
	FlightSimInteger & operator = (unsigned int n) { write((long)n); return *this; }
	FlightSimInteger & operator = (unsigned long n) { write((long)n); return *this; }
	FlightSimInteger & operator = (float n) { write((long)n); return *this; }
	FlightSimInteger & operator = (double n) { write((long)n); return *this; }
	long read(void) const { return value; }
	operator long () const { return value; }
	void identify(void);
	void update(long val);
	static FlightSimInteger * find(unsigned int n);
	void onChange(void (*fptr)(long)) { 
		hasCallbackInfo=false;
		change_callback = fptr; 
	}
	void onChange(void (*fptr)(long,void*), void* info) {
		hasCallbackInfo=true;
		change_callback = (void (*)(long))fptr;
		callbackInfo = info;
	}
	// TODO: math operators....  + - * / % ++ --
private:
	unsigned int id;
	const _XpRefStr_ *name;
	long value;
	void (*change_callback)(long);
	void* callbackInfo;
	bool  hasCallbackInfo;
	FlightSimInteger *next;
	static FlightSimInteger *first;
	static FlightSimInteger *last;
	friend class FlightSimClass;
};


class FlightSimFloat
{
public:
	FlightSimFloat();
	void assign(const _XpRefStr_ *s) { name = s; if (FlightSimClass::enabled) identify(); }
	FlightSimFloat & operator = (const _XpRefStr_ *s) { assign(s); return *this; }
	void write(float val);
	FlightSimFloat & operator = (char n) { write((float)n); return *this; }
	FlightSimFloat & operator = (int n) { write((float)n); return *this; }
	FlightSimFloat & operator = (long n) { write((float)n); return *this; }
	FlightSimFloat & operator = (unsigned char n) { write((float)n); return *this; }
	FlightSimFloat & operator = (unsigned int n) { write((float)n); return *this; }
	FlightSimFloat & operator = (unsigned long n) { write((float)n); return *this; }
	FlightSimFloat & operator = (float n) { write(n); return *this; }
	FlightSimFloat & operator = (double n) { write((float)n); return *this; }
	float read(void) const { return value; }
	operator float () const { return value; }
	void identify(void);
	void update(float val);
	static FlightSimFloat * find(unsigned int n);
	void onChange(void (*fptr)(float)) {
		hasCallbackInfo=false;
		change_callback = fptr; 
	}
	void onChange(void (*fptr)(float,void*), void* info) {
		hasCallbackInfo=true;
		change_callback = (void (*)(float))fptr;
		callbackInfo = info;
	}
	// TODO: math operators....  + - * / % ++ --
private:
	unsigned int id;
	const _XpRefStr_ *name;
	float value;
	void (*change_callback)(float);
	void* callbackInfo;
	bool  hasCallbackInfo;
	FlightSimFloat *next;
	static FlightSimFloat *first;
	static FlightSimFloat *last;
	friend class FlightSimClass;
};


class FlightSimElapsedFrames
{
private:
	unsigned long count;
public:
	FlightSimElapsedFrames(void) { count = FlightSimClass::getFrameCount(); }
	FlightSimElapsedFrames(unsigned long val) { count = FlightSimClass::getFrameCount() - val; }
	FlightSimElapsedFrames(const FlightSimElapsedFrames &orig) { count = orig.count; }
	operator unsigned long () const { return FlightSimClass::getFrameCount() - count; }
	FlightSimElapsedFrames & operator = (const FlightSimElapsedFrames &rhs) { count = rhs.count; return *this; }
	FlightSimElapsedFrames & operator = (unsigned long val) { count = FlightSimClass::getFrameCount() - val; return *this; }
	FlightSimElapsedFrames & operator -= (unsigned long val)    { count += val; return *this; }
	FlightSimElapsedFrames & operator += (unsigned long val)    { count -= val; return *this; }
	FlightSimElapsedFrames operator - (int val) const           { FlightSimElapsedFrames r(*this); r.count += val; return r; }
	FlightSimElapsedFrames operator - (unsigned int val) const  { FlightSimElapsedFrames r(*this); r.count += val; return r; }
	FlightSimElapsedFrames operator - (long val) const          { FlightSimElapsedFrames r(*this); r.count += val; return r; }
	FlightSimElapsedFrames operator - (unsigned long val) const { FlightSimElapsedFrames r(*this); r.count += val; return r; }
	FlightSimElapsedFrames operator + (int val) const           { FlightSimElapsedFrames r(*this); r.count -= val; return r; }
	FlightSimElapsedFrames operator + (unsigned int val) const  { FlightSimElapsedFrames r(*this); r.count -= val; return r; }
	FlightSimElapsedFrames operator + (long val) const          { FlightSimElapsedFrames r(*this); r.count -= val; return r; }
	FlightSimElapsedFrames operator + (unsigned long val) const { FlightSimElapsedFrames r(*this); r.count -= val; return r; }
};


extern FlightSimClass FlightSim;



#if 0
class usb_rawhid_class
{
	public:
	int available(void);
	int recv(void *buffer, uint16_t timeout);
	int send(const void *buffer, uint16_t timeout);
};

extern usb_rawhid_class RawHID;
#endif

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
