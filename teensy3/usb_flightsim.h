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

#ifndef USBflightsim_h_
#define USBflightsim_h_

#include "usb_desc.h"

#if defined(FLIGHTSIM_INTERFACE)

#ifdef __cplusplus

#include <inttypes.h>
#include "elapsedMillis.h"

// workaround for elapsedMillis.h bringing in WProgram.h which brings usb_undef.h
#undef USB_DESC_LIST_DEFINE
#include "usb_desc.h"

class FlightSimClass;
class FlightSimCommand;
class FlightSimInteger;

class _XpRefStr_;
#define XPlaneRef(str) ((const _XpRefStr_ *)(str))

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
	static void xmit(const void *p1, uint8_t n1, const void *p2, uint8_t n2);
	static void xmit_big_packet(const void *p1, uint8_t n1, const void *p2, uint8_t n2);
	friend class FlightSimCommand;
	friend class FlightSimInteger;
	friend class FlightSimFloat;
/// JB
	friend class FlightSimEvent;
	friend class FlightSimData;
/// JB End
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

/// JB
class FlightSimEvent
{
public:
	FlightSimEvent();
	void assign(const _XpRefStr_ *s) { name = s; if (FlightSimClass::enabled) identify(); }
	FlightSimEvent & operator = (const _XpRefStr_ *s) { assign(s); return *this; }
	void send() { send(0,0); }
	void send(int data) { send(data,0); }
	void sendOnce() { send(0,0); }
	void sendOnce(int data) { send(data,0); }
	void sendRepeat(int data, uint16_t initialDelay, uint16_t repeatDelay) { send(data, initialDelay<<16 | repeatDelay); }
	void sendRepeat(uint16_t initialDelay, uint16_t repeatDelay) { send(0, initialDelay<<16 | repeatDelay); }
	void stopRepeat() { send(0,-1); }
	FlightSimEvent & operator = (int n) { send(n,0); return *this; }	
	bool occurred() { bool hasOccurred = occurredFlag; occurredFlag = 0; return hasOccurred; }
	void identify();
	static FlightSimEvent * find(unsigned int n);
	void update(long val);
	void onOccur(void (*fptr)(long)) { 
		hasCallbackInfo=false;
		occur_callback = fptr; 
	}
	void onOccur(void (*fptr)(long,void*), void* info) {
		hasCallbackInfo=true;
		occur_callback = (void (*)(long))fptr;
		callbackInfo = info;
	}
private:
	void send(unsigned int data, unsigned int flags);
	unsigned int id;
	const _XpRefStr_ *name;
	bool occurredFlag;
	unsigned int value;
	FlightSimEvent *next;
	
	void (*occur_callback)(long);
	void* callbackInfo;
	bool  hasCallbackInfo;
	
	static FlightSimEvent *first;
	static FlightSimEvent *last;
	friend class FlightSimClass;
};

#define FLIGHTSIM_DATA_MAXLEN 58

class FlightSimData
{
public:
	FlightSimData();
	void assign(const _XpRefStr_ *s) { name = s; if (FlightSimClass::enabled) identify(); }
	FlightSimData & operator = (const _XpRefStr_ *s) { assign(s); return *this; }
	char *read()  { return value; }
	operator char* () { return value; }
	void identify();
	void update(char *val, size_t len);
	size_t len() { return valueLen; }
	static FlightSimData * find(unsigned int n);
	void onChange(void (*fptr)(char *)) {
		hasCallbackInfo = false;
		change_callback = fptr;
	}
	void onChange(void (*fptr)(char *,void *), void *info) {
		hasCallbackInfo = true;
		change_callback = (void (*)(char*)) fptr;
		callbackInfo = info;
	}
	void onChange(void (*fptr)(FlightSimData *)) {
		callbackWithObject = true;
		hasCallbackInfo = false;
		change_callback = (void (*)(char*)) fptr;
	}
	void onChange(void (*fptr)(FlightSimData *, void*), void* info) {
		callbackWithObject = true;
		hasCallbackInfo = true;
		change_callback = (void (*)(char*)) fptr;
		callbackInfo = info;
	}
private:
	unsigned int id;
	const _XpRefStr_ *name;
	char value[FLIGHTSIM_DATA_MAXLEN];
	size_t valueLen;
	void (*change_callback)(char *);
	void* callbackInfo;
	bool  hasCallbackInfo;
	bool  callbackWithObject;
	FlightSimData *next;
	static FlightSimData *first;
	static FlightSimData *last;
	friend class FlightSimClass;
};
/// JB End


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

#endif // __cplusplus

#endif // FLIGHTSIM_INTERFACE

#endif // USBflightsim_h_
