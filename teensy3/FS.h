/* Experimental File & FS base classes.
*/

#ifndef FS_H
#define FS_H
#ifdef __cplusplus

#include <Arduino.h>

#define FILE_READ  0
#define FILE_WRITE 1

enum SeekMode {
	SeekSet = 0,
	SeekCur = 1,
	SeekEnd = 2
};

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
#if 1
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
	virtual int read() {
		return (f) ? f->read() : -1;
	}
	virtual int peek() {
		return (f) ? f->peek() : -1;
	}
	virtual void flush() {
		if (f) f->flush();
	}
	virtual bool seek(uint32_t pos, int mode) {
		return (f) ? f->seek(pos, mode) : false;
	}
	virtual uint32_t position() const {
		return (f) ? f->position() : 0;
	}
	virtual uint32_t size() const {
		return (f) ? f->size() : 0;
	}
	virtual void close() {
		if (f) f->close();
	}
	virtual operator bool() const {
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
	bool seek(uint32_t pos) {
		return seek(pos, SeekSet);
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
	File open(const char *filename, uint8_t mode = FILE_READ);
	bool exists(const char *filepath);
	bool mkdir(const char *filepath);
	bool remove(const char *filepath);
	bool rmdir(const char *filepath);
};


#endif // __cplusplus
#endif // FS_H
