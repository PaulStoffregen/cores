/* Experimental File & Dir base classes.  VERY experimental!

   These are intended to someday allow libraries using files,
   such as a JPEG decoder, to accept a File object from SD,
   Bridge, USB Host, ESP SPIFFS, and others.  Perhaps only a
   distant dream at this point, but maybe someday....
*/


#ifndef FS_H
#define FS_H
#ifdef __cplusplus

#include "Stream.h"
#include "WString.h"

class File : public Stream {
public:
	constexpr File() {}
	enum SeekMode {
		SeekSet = 0,
		SeekCur = 1,
		SeekEnd = 2
	};
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
	//virtual const char* name() const; // why does ESP have this in File?

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

	// needed for compatiblity with Arduino's SD & Bridge libs
	virtual const char* name();
	virtual bool isDirectory();
	virtual File openNextFile(uint8_t mode=0);
	virtual void rewindDirectory(void);
};

class Dir {
public:
	constexpr Dir() {}
	virtual const char *name(); // from SD's File (and ESP's File)
	virtual uint32_t fileSize();
	virtual bool isDirectory(); // from SD, not in ESP
	virtual File openFile(const char *mode);
	virtual bool next();
	String fileName() {
		return String(name());
	}
};

#endif // __cplusplus
#endif // FS_H
