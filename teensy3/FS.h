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

class File;

class File : public Stream {
public:
	constexpr File() : f(nullptr) { }
	constexpr File(const File &file) : f(file.f) { }
	virtual ~File();
	virtual size_t read(void *buf, size_t nbyte);
	virtual size_t write(const void *buf, size_t size);
	virtual int available();
	virtual int read();
	virtual int peek();
	virtual void flush();
	virtual bool seek(uint32_t pos, int mode);
	virtual uint32_t position() const;
	virtual uint32_t size() const;
	virtual void close();
	virtual operator bool() const;
	virtual const char* name();
	virtual bool isDirectory();
	virtual File openNextFile(uint8_t mode=0);
	virtual void rewindDirectory(void);

	virtual bool seek(uint32_t pos) {
		return seek(pos, SeekSet);
	}
	virtual size_t write(uint8_t b) {
		return write(&b, 1);
	}
	virtual size_t write(const char *str) {
		return write(str, strlen(str));
	}
	virtual size_t readBytes(char *buffer, size_t length) {
		return read(buffer, length);
	}
	virtual void whoami(); // testing only
//protected:
	File *f; // points to actual implementing class, or nullptr
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
