/* Teensyduino Core Library - File base class
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2020 PJRC.COM, LLC.
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

#ifndef FS_H
#define FS_H
#ifdef __cplusplus

#include <Arduino.h>

#define FILE_READ  0
#define FILE_WRITE 1
#define FILE_WRITE_BEGIN 2

enum SeekMode {
	SeekSet = 0,
	SeekCur = 1,
	SeekEnd = 2
};

#define FILE_WHOAMI

class File : public Stream {
public:
	constexpr File() : f(nullptr) { }
	File(File *file) {
		// "file" must only be a class derived from File
		// can we use is_same or is_polymorphic with static_assert?
		// or is_base_of
		//static_assert(std::is_same<decltype(*file),File>::value,
			//"File(File *file) constructor only accepts pointers "
			//"to derived classes, not File itself");
		f = file;
		if (f) f->refcount++;
	}
	File(const File &file) {
		//Serial.println("File copy constructor");
		//static int copycount=0;
		//if (++copycount > 20) while (1) ;
		f = file.f;
		if (f) f->refcount++;
	}
	File& operator = (const File &file) {
		//Serial.println("File assignment");
		//static int assigncount=0;
		//if (++assigncount > 20) while (1) ;
		invalidate();
		f = file.f;
		if (f) f->refcount++;
		return *this;
	}
	virtual ~File() {
		invalidate();
	}
#ifdef FILE_WHOAMI
	virtual void whoami() { // testing only
		Serial.printf("  File    this=%x, f=%x\n", (int)this, (int)f);
		if (f) f->whoami();
	}
	unsigned int getRefcount() { // testing only
		return refcount;
	}
#endif
	virtual size_t read(void *buf, size_t nbyte) {
		return (f) ? f->read(buf, nbyte) : 0;
	}
	virtual size_t write(const void *buf, size_t size) {
		return (f) ? f->write(buf, size) : 0;
	}
	virtual int available() {
		return (f) ? f->available() : 0;
	}
	virtual int peek() {
		return (f) ? f->peek() : -1;
	}
	virtual void flush() {
		if (f) f->flush();
	}
	virtual bool truncate(uint64_t size=0) {
		return (f) ? f->truncate(size) : false;
	}
	virtual bool seek(uint64_t pos, int mode) {
		return (f) ? f->seek(pos, mode) : false;
	}
	virtual uint64_t position() {
		return (f) ? f->position() : 0;
	}
	virtual uint64_t size() {
		return (f) ? f->size() : 0;
	}
	virtual void close() {
		if (f) f->close();
	}
	virtual operator bool() {
		return (f) ? (bool)*f : false;
	}
	virtual const char* name() {
		return (f) ? f->name() : "";
	}
	virtual bool isDirectory() {
		return (f) ? f->isDirectory() : false;
	}
	virtual File openNextFile(uint8_t mode=0) {
		return (f) ? f->openNextFile(mode) : *this;
	}
	virtual void rewindDirectory(void) {
		if (f) f->rewindDirectory();
	}
	bool seek(uint64_t pos) {
		return seek(pos, SeekSet);
	}
	int read() {
		if (!f) return -1;
		unsigned char b;
		if (f->read(&b, 1) < 1) return -1;
		return b;
	}
	size_t write(uint8_t b) {
		return write(&b, 1);
	}
	size_t write(const char *str) {
		return write(str, strlen(str));
	}
	size_t readBytes(char *buffer, size_t length) {
		return read(buffer, length);
	}
private:
	void invalidate() {
		if (f && --(f->refcount) == 0) delete f;
	}
	union {
		// instances of base File class use this pointer
		File *f;
		// instances of derived classes (which actually access media)
		// use this reference count which is managed by the base class
		unsigned int refcount;
	};
};


class FS
{
public:
	FS() {}
	virtual File open(const char *filename, uint8_t mode = FILE_READ) = 0;
	virtual bool exists(const char *filepath) = 0;
	virtual bool mkdir(const char *filepath) = 0;
	virtual bool rename(const char *oldfilepath, const char *newfilepath) = 0;
	virtual bool remove(const char *filepath) = 0;
	virtual bool rmdir(const char *filepath) = 0;
	virtual uint64_t usedSize() = 0;
	virtual uint64_t totalSize() = 0;
};


#endif // __cplusplus
#endif // FS_H
