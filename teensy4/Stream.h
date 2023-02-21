/*
  Stream.h - base class for character-based streams.
  Copyright (c) 2010 David A. Mellis.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef Stream_h
#define Stream_h

#include <inttypes.h>
#include "Print.h"

class Stream : public Print
{
  public:
	constexpr Stream() : _timeout(1000), read_error(0) {}
	virtual int available() = 0;
	virtual int read() = 0;
	virtual int peek() = 0;

	void setTimeout(unsigned long timeout);
	bool find(const char *target);
	bool find(const uint8_t *target) { return find ((const char *)target); }
	bool find(const String &target) { return find(target.c_str()); }
	bool find(const char *target, size_t length);
	bool find(const uint8_t *target, size_t length) { return find ((const char *)target, length); }
	bool find(const String &target, size_t length) { return find(target.c_str(), length); }
	bool findUntil(const char *target, const char *terminator);
	bool findUntil(const uint8_t *target, const char *terminator) { return findUntil((const char *)target, terminator); }
	bool findUntil(const String &target, const char *terminator) { return findUntil(target.c_str(), terminator); }
	bool findUntil(const char *target, const String &terminator) { return findUntil(target, terminator.c_str()); }
	bool findUntil(const String &target, const String &terminator) { return findUntil(target.c_str(), terminator.c_str()); }
	bool findUntil(const char *target, size_t targetLen, const char *terminate, size_t termLen);
	bool findUntil(const uint8_t *target, size_t targetLen, const char *terminate, size_t termLen) {return findUntil((const char *)target, targetLen, terminate, termLen); }
	bool findUntil(const String &target, size_t targetLen, const char *terminate, size_t termLen);
	bool findUntil(const char *target, size_t targetLen, const String &terminate, size_t termLen);
	bool findUntil(const String &target, size_t targetLen, const String &terminate, size_t termLen);
	long parseInt();
	long parseInt(char skipChar);
	float parseFloat();
	float parseFloat(char skipChar);
	size_t readBytes(char *buffer, size_t length);
	size_t readBytes(uint8_t *buffer, size_t length) { return readBytes((char *)buffer, length); }
	size_t readBytesUntil(char terminator, char *buffer, size_t length);
	size_t readBytesUntil(char terminator, uint8_t *buffer, size_t length) { return readBytesUntil(terminator, (char *)buffer, length); }
	String readString(size_t max = 0 /* 0 means unlimited length */);
	String readStringUntil(char terminator, size_t max = 0 /* 0 means unlimited length */);
	int getReadError() { return read_error; }
	void clearReadError() { setReadError(0); }
  protected:
	void setReadError(int err = 1) { read_error = err; }
	int timedRead();
	int timedPeek();
	int peekNextDigit();

	unsigned long _timeout;
  private:
	char read_error;
};

#endif
