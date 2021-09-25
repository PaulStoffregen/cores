/* Teensyduino Core Library - File base class
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2021 PJRC.COM, LLC.
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

class File;


// FileImpl is the actual implementation of access to files stored on media.
// Libraries providing access to files must inherit FileImpl.  Instances of
// FileImpl are always created with "new".  When a FileImpl instance is
// created, it is usually wrapped in a File instance: File(new myFileImpl(...));
// FileImpl instances are automatically deleted when the last referencing
// File is closed or goes out of scope.  The refcount variable is meant to
// be maintained by File class instances, never access by FileImpl functions.
// The FileImpl functions are meant to be called only by use of File instances.
//
class FileImpl {
protected:
	virtual ~FileImpl() { }
	virtual size_t read(void *buf, size_t nbyte) = 0;
	virtual size_t write(const void *buf, size_t size) = 0;
	virtual int available() = 0;
	virtual int peek() = 0;
	virtual void flush() = 0;
	virtual bool truncate(uint64_t size=0) = 0;
	virtual bool seek(uint64_t pos, int mode) = 0;
	virtual uint64_t position() = 0;
	virtual uint64_t size() = 0;
	virtual void close() = 0;
	virtual bool isOpen() = 0;
	virtual const char* name() = 0;
	virtual bool isDirectory() = 0;
	virtual File openNextFile(uint8_t mode=0) = 0;
	virtual void rewindDirectory(void) = 0;
	virtual bool getCreateTime(DateTimeFields &tm) { return false; }
	virtual bool getModifyTime(DateTimeFields &tm) { return false; }
	virtual bool setCreateTime(const DateTimeFields &tm) { return false; }
	virtual bool setModifyTime(const DateTimeFields &tm) { return false; }
private:
	friend class File;
	unsigned int refcount = 0; // number of File instances referencing this FileImpl
};


// Libraries known to inherit from FileImpl (will need testing if FileImpl changes)
//   https://github.com/PaulStoffregen/SD
//   https://github.com/PaulStoffregen/LittleFS
//   https://github.com/PaulStoffregen/USBHost_t36
//   https://github.com/FrankBoesing/MemFile



// TODO: does this help in any way, or just extra useless code?
#define FILE_USE_MOVE


// Programs and libraries using files do so with instances of File.
// File is merely a pointer to a FileImpl instance.  More than one
// instance of File may reference the same FileImpl.  File may also
// reference nothing (the pointer is NULL), as a result of having
// closed the file or the File instance created without referencing
// anything.
//
class File final : public Stream {
public:
	// Empty constructor, used when a program creates a File variable
	// but does not immediately assign or initialize it.
	constexpr File() : f(nullptr) { }

	// Explicit FileImpl constructor.  Used by libraries which provide
	// access to files stored on media.  Normally this is used within
	// functions derived from FS::open() and FileImpl::openNextFile().
	// Not normally called used from ordinary programs or libraries
	// which only access files.
	File(FileImpl *file) {
		f = file;
		if (f) f->refcount++;
		//Serial.printf("File ctor %x, refcount=%d\n", (int)f, get_refcount());
	}

	// Copy constructor.  Typically used when a File is passed by value
	// into a function.  The File instance within the called function is
	// a copy of the original.  Also used when a File instance is created
	// and assigned a value (eg, "File f =
	File(const File& file) {
		f = file.f;
		if (f) f->refcount++;
		//Serial.printf("File copy ctor %x, refcount=%d\n", (int)f, get_refcount());
	}
#ifdef FILE_USE_MOVE
	// Move constructor.
	File(const File&& file) {
		f = file.f;
		if (f) f->refcount++;
		//Serial.printf("File copy ctor %x, refcount=%d\n", (int)f, get_refcount());
	}
#endif
	// Copy assignment.
	File& operator = (const File& file) {
		//Serial.println("File copy assignment");
		if (file.f) file.f->refcount++;
		if (f) { dec_refcount(); /*Serial.println("File copy assignment autoclose");*/ }
		f = file.f;
		return *this;
	}
#ifdef FILE_USE_MOVE
	// Move assignment.
	File& operator = (const File&& file) {
		//Serial.println("File move assignment");
		if (file.f) file.f->refcount++;
		if (f) { dec_refcount(); /*Serial.println("File move assignment autoclose");*/ }
		f = file.f;
		return *this;
	}
#endif
	virtual ~File() {
		//Serial.printf("File dtor %x, refcount=%d\n", (int)f, get_refcount());
		if (f) dec_refcount();
	}
	size_t read(void *buf, size_t nbyte) {
		return (f) ? f->read(buf, nbyte) : 0;
	}
	size_t write(const void *buf, size_t size) {
		return (f) ? f->write(buf, size) : 0;
	}
	int available() {
		return (f) ? f->available() : 0;
	}
	int peek() {
		return (f) ? f->peek() : -1;
	}
	void flush() {
		if (f) f->flush();
	}
	bool truncate(uint64_t size=0) {
		return (f) ? f->truncate(size) : false;
	}
	bool seek(uint64_t pos, int mode) {
		return (f) ? f->seek(pos, mode) : false;
	}
	uint64_t position() {
		return (f) ? f->position() : 0;
	}
	uint64_t size() {
		return (f) ? f->size() : 0;
	}
	void close() {
		if (f) {
			f->close();
			dec_refcount();
		}
	}
	operator bool() {
		return (f) ? f->isOpen() : false;
	}
	const char* name() {
		return (f) ? f->name() : "";
	}
	bool isDirectory() {
		return (f) ? f->isDirectory() : false;
	}
	File openNextFile(uint8_t mode=0) {
		return (f) ? f->openNextFile(mode) : *this;
	}
	void rewindDirectory(void) {
		if (f) f->rewindDirectory();
	}
	bool getCreateTime(DateTimeFields &tm) {
		return (f) ? f->getCreateTime(tm) : false;
	}
	bool getModifyTime(DateTimeFields &tm) {
		return (f) ? f->getModifyTime(tm) : false;
	}
	bool setCreateTime(const DateTimeFields &tm) {
		return (f) ? f->setCreateTime(tm) : false;
	}
	bool setModifyTime(const DateTimeFields &tm) {
		return (f) ? f->setModifyTime(tm) : false;
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
		return (f) ? f->write(&b, 1) : 0;
	}
	size_t write(const char *str) {
		return (f) ? f->write(str, strlen(str)) : 0;
	}
	size_t readBytes(char *buffer, size_t length) {
		return read(buffer, length);
	}
	size_t write(unsigned long n) { return write((uint8_t)n); }
	size_t write(long n) { return write((uint8_t)n); }
	size_t write(unsigned int n) { return write((uint8_t)n); }
	size_t write(int n) { return write((uint8_t)n); }
	using Print::write;
private:
	void dec_refcount() {
		if (--(f->refcount) == 0) {
			f->close();
			delete f;
		}
		f = nullptr;
	}
	int get_refcount() {
		if (f == nullptr) return -1;
		return f->refcount;
	}
	FileImpl *f;
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
