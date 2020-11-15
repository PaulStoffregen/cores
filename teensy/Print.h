/*
  Print.h - Base class that provides print() and println()
  Copyright (c) 2008 David A. Mellis.  All right reserved.

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

#ifndef Print_h
#define Print_h

#include <inttypes.h>
#include <stdio.h> // for size_t
#include <stdarg.h>
#include "core_id.h"
#include "WString.h"
#include "Printable.h"

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2

// BYTE was defined in very old versions of Arduino
// maybe this now causes more trouble than it's worth?
//#ifndef BYTE
//#define BYTE 0
//#endif

class __FlashStringHelper;

class Print
{
  public:
	constexpr Print() : write_error(0) {}
	virtual size_t write(uint8_t b) = 0;
	size_t write(const char *str)			{ return write((const uint8_t *)str, strlen(str)); }
	virtual size_t write(const uint8_t *buffer, size_t size);
	virtual int availableForWrite(void)		{ return 0; }
	virtual void flush()				{ }
	size_t write(const char *buffer, size_t size)   { return write((const uint8_t *)buffer, size); }
	size_t print(const String &s);
	size_t print(char c)				{ return write((uint8_t)c); }
	size_t print(const char s[])			{ return write(s); }
	size_t print(const __FlashStringHelper *f);

	size_t print(uint8_t b)				{ return printNumber(b, 0, 10); }
	size_t print(int n)				{ return print((long)n); }
	size_t print(unsigned int n)			{ return printNumber(n, 0, 10); }
	size_t print(long n);
	size_t print(unsigned long n)			{ return printNumber(n, 0, 10); }
	size_t print(int64_t n);
	size_t print(uint64_t n)			{ return printNumber64(n, 10, 0); }

	size_t print(unsigned char n, int base)		{ return printNumber(n, 0, base); }
	size_t print(int n, int base)			{ return (base == 10) ? print(n) : printNumber(n, 0, base); }
	size_t print(unsigned int n, int base)		{ return printNumber(n, 0, base); }
	size_t print(long n, int base)			{ return (base == 10) ? print(n) : printNumber(n, 0, base); }
	size_t print(unsigned long n, int base)		{ return printNumber(n, 0, base); }
	size_t print(int64_t n, int base)		{ return (base == 10) ? print(n) : printNumber64(n, base, 0); }
	size_t print(uint64_t n, int base)		{ return printNumber64(n, base, 0); }

	size_t print(double n, int digits = 2)		{ return printFloat(n, digits); }
	size_t print(const Printable &obj)		{ return obj.printTo(*this); }
	size_t println(void);
	size_t println(const String &s)			{ return print(s) + println(); }
	size_t println(char c)				{ return print(c) + println(); }
	size_t println(const char s[])			{ return print(s) + println(); }
	size_t println(const __FlashStringHelper *f)	{ return print(f) + println(); }

	size_t println(uint8_t b)			{ return print(b) + println(); }
	size_t println(int n)				{ return print(n) + println(); }
	size_t println(unsigned int n)			{ return print(n) + println(); }
	size_t println(long n)				{ return print(n) + println(); }
	size_t println(unsigned long n)			{ return print(n) + println(); }
	size_t println(int64_t n)			{ return print(n) + println(); }
	size_t println(uint64_t n)			{ return print(n) + println(); }

	size_t println(unsigned char n, int base)	{ return print(n, base) + println(); }
	size_t println(int n, int base)			{ return print(n, base) + println(); }
	size_t println(unsigned int n, int base)	{ return print(n, base) + println(); }
	size_t println(long n, int base)		{ return print(n, base) + println(); }
	size_t println(unsigned long n, int base)	{ return print(n, base) + println(); }
	size_t println(int64_t n, int base)		{ return print(n, base) + println(); }
	size_t println(uint64_t n, int base)		{ return print(n, base) + println(); }

	size_t println(double n, int digits = 2)	{ return print(n, digits) + println(); }
	size_t println(const Printable &obj)		{ return obj.printTo(*this) + println(); }
	int getWriteError() { return write_error; }
	void clearWriteError() { setWriteError(0); }
	int printf(const char *format, ...);
	int printf(const __FlashStringHelper *format, ...);
  protected:
	void setWriteError(int err = 1) { write_error = err; }
  private:
	char write_error;
	size_t printNumberDec(unsigned long n, uint8_t sign);
	size_t printNumberHex(unsigned long n);
	size_t printNumberBin(unsigned long n);
	size_t printNumberAny(unsigned long n, uint8_t base);
	inline size_t printNumber(unsigned long n, uint8_t sign, uint8_t base) __attribute__((always_inline)) {
		// when "base" is a constant (pretty much always), the
		// compiler optimizes this to a single function call.
		if (base == 0) return write((uint8_t)n);
		if (base == 10 || base < 2) return printNumberDec(n, sign);
		//if (base == 10 || base < 2) return printNumberAny(n, 10); // testing only
		if (base == 16) return printNumberHex(n);
		if (base == 2) return printNumberBin(n);
		return printNumberAny(n, base);
	}
	size_t printNumber64(uint64_t n, uint8_t base, uint8_t sign);
	size_t printFloat(double n, uint8_t digits);
};


#endif
