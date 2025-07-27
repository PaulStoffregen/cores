// MTP.h - Teensy MTP Responder library
// Copyright (C) 2017 Fredrik Hubinette <hubbe@hubbe.net>
//
// With updates from MichaelMC and Yoong Hor Meng <yoonghm@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// modified for SDFS by WMXZ
// Modified by KurtE and mjs513 for Teensy Integration. 

#pragma once

#if defined(USB_MTPDISK) || defined(USB_MTPDISK_SERIAL)

#include "IntervalTimer.h"
#include "core_pins.h"
#include "usb_dev.h"
extern "C" int usb_mtp_sendEvent(const void *buffer, uint32_t len,
                                 uint32_t timeout);
extern "C" int usb_init_events(void);

#include "MTP_Storage.h"
// modify strings if needed (see MTP.cpp how they are used)
#define MTP_MANUF "PJRC"
#define MTP_MODEL "Teensy"
#define MTP_VERS "1.0"
#define MTP_SERNR "1234"
#define MTP_NAME "Teensy"

#define USE_EVENTS 1

// probably ok to default larger verbose output on these for now
#if defined(__IMXRT1062__) || defined(__MK64FX512__) || defined(__MK66FX1M0__)
#define MTP_VERBOSE_PRINT_CONTAINER 1
#endif

extern "C" {
extern volatile uint8_t usb_configuration;
}


// MTP Responder.
class MTP_class {
public:
  explicit constexpr MTP_class() {}
  int begin();
  void loop(void);

  void reset() {
    // TODO check if session open
    // TODO clear storage info
    // TODO other state to zero or initialize?
    send_DeviceResetEvent();
  }

  // Add a file system to the list of storages that will be seen by
  // the host computer.  Returns the index of the item within the list
  bool addFilesystem(FS &disk, const char *diskname) {
    return storage_.addFilesystem(disk, diskname);
  }


  operator bool() { return usb_configuration && (sessionID_ != 0); }

#if 1
  // returns the count of file systems that have been added to the storage list
  //inline uint32_t getFilesystemCount(void) { return storage_.get_FSCount(); }

  FS* getFilesystemByIndex(uint32_t store) {
    if (store >= storage_.get_FSCount()) return nullptr;
    return storage_.getStoreFS(store);
  }

  // Return the storage name that with the given store index
  const char *getNameByIndex(uint32_t store) {
    if (store >= storage_.get_FSCount()) return nullptr;
    return storage_.getStoreName(store);
  }
#endif

  // Set which of the file systems should be used to store our storage index.  This index is used 
  // to remember the mappings of object IDs to underlying file system object.  By default the system
  // uses the first storage tht was added.
  bool useFilesystemForIndexList(FS &disk) {
    unsigned int count = storage_.get_FSCount();
    for (unsigned int store=0; store < count; store++) {
      if (storage_.getStoreFS(store) == &disk) {
        return storage_.setIndexStore(store);
      }
    }
    return false;
  }

  //inline bool useFileSystemIndexFileStore(uint32_t store = 0) { return storage_.setIndexStore(store); }

  // maps a file system name (The diskname parameter in addFilesystem)
  // and returns the file system index.
  //inline uint32_t getFilesystemIndexFromName(const char *fsname) { return storage_.getStoreID(fsname); }

  // Reurns a pointer to stream object that is being used within MTP_Teensy
  // code to output debug and informational messages.  By default it
  // is a pointer to the Serial object.
  static inline Stream *PrintStream(void) { return printStream_; }

  // Set what stream object should be used to output debug and information 
  // messages.  By default the system uses the Serial object.
  static void PrintStream(Stream *stream) { printStream_ = stream; }

  // Print info about internal data
  void printFilesystemsInfo(Stream &stream = Serial);
  void printIndexList(Stream &stream = Serial) { storage_.dumpIndexList(stream); }

  // Returns a pointer to the underlying MTPStorage object.  Most sketches
  // do not need this, but it does allow access to things such as
  // debug functions.
  //MTPStorage *storage() {return &storage_ ;}

  // Test to set file name to 232 as overhead of 24 in storage...
  enum {MAX_FILENAME_LEN=232, MAX_PATH_LEN=256};

private:
  friend class MTPStorage;
  static Stream *printStream_;

  struct MTPHeader {
    uint32_t len;            // 0
    uint16_t type;           // 4
    uint16_t op;             // 6
    uint32_t transaction_id; // 8
  };

  struct MTPContainer {
    uint32_t len;            // 0
    uint16_t type;           // 4
    uint16_t op;             // 6
    uint32_t transaction_id; // 8
    uint32_t params[5];      // 12
  };

  typedef struct {
    uint16_t len;   // number of data bytes
    uint16_t index; // position in processing data
    uint16_t size;  // total size of buffer
    uint8_t *data;  // pointer to the data
    void *usb;      // packet info (needed on Teensy 3)
  } packet_buffer_t;

  packet_buffer_t receive_buffer = {0, 0, 0, NULL, NULL};
  packet_buffer_t transmit_buffer = {0, 0, 0, NULL, NULL};
  packet_buffer_t event_buffer = {0, 0, 0, NULL, NULL};
  bool receive_bulk(uint32_t timeout);
  void free_received_bulk();
  void allocate_transmit_bulk();
  int transmit_bulk();
  void allocate_transmit_event();
  int transmit_event();

#if defined(__MK20DX128__) || defined(__MK20DX256__) || \
    defined(__MK64FX512__) || defined(__MK66FX1M0__)

  static uint8_t usb_mtp_status;

#elif defined(__IMXRT1062__)
#define MTP_RX_SIZE MTP_RX_SIZE_480
#define MTP_TX_SIZE MTP_TX_SIZE_480

  uint8_t tx_data_buffer[MTP_TX_SIZE] __attribute__((aligned(32))) = {0};
  static const uint32_t DISK_BUFFER_SIZE = 4 * 1024; // used by MTP_Storage
  uint8_t rx_data_buffer[MTP_RX_SIZE] __attribute__((aligned(32))) = {0};
  static uint8_t disk_buffer_[DISK_BUFFER_SIZE] __attribute__((aligned(32)));
  uint16_t transmit_packet_size_mask = 0x01FF;

#endif

  static uint32_t sessionID_;

  bool write_transfer_open = false;
  size_t write(const void *ptr, size_t len);
  void write_finish();

  void write8(uint8_t x)   { write(&x, sizeof(x)); }
  void write16(uint16_t x) { write(&x, sizeof(x)); }
  void write32(uint32_t x) { write(&x, sizeof(x)); }
  void write64(uint64_t x) { write(&x, sizeof(x)); }

  void writestring(const char *str);
  uint32_t writestringlen(const char *str);
  void writeDataPhaseHeader(struct MTPContainer &container, uint32_t data_size);

  uint32_t GetDeviceInfo(struct MTPContainer &cmd);
  void WriteDescriptor();
  uint32_t GetStorageIDs(struct MTPContainer &cmd);
  uint32_t GetStorageInfo(struct MTPContainer &cmd, bool mediaAccessAllowed=true);

  uint32_t GetNumObjects(struct MTPContainer &cmd);

  uint32_t GetObjectHandles(struct MTPContainer &cmd);
  void GetObjectHandles(uint32_t storage, uint32_t parent);

  uint32_t GetObjectInfo(struct MTPContainer &cmd);
  uint32_t GetObject(struct MTPContainer &cmd);
  uint32_t GetPartialObject(struct MTPContainer &cmd);

  bool read(void *ptr, uint32_t size);
  bool read8(uint8_t *n) { return read(n, 1); }
  bool read16(uint16_t *n) { return read(n, 2); }
  bool read32(uint32_t *n) { return read(n, 4); }
  bool readDataPhaseHeader(struct MTPHeader *header=nullptr);
  bool readstring(char *buffer, uint32_t buffer_size);
  bool readDateTimeString(uint32_t *pdt);

  uint32_t SendObjectInfo(struct MTPContainer &cmd);
  uint32_t SendObject(struct MTPContainer &cmd);

  uint32_t GetDevicePropValue(struct MTPContainer &cmd);
  uint32_t GetDevicePropDesc(struct MTPContainer &cmd);
  uint32_t GetObjectPropsSupported(struct MTPContainer &cmd);

  uint32_t GetObjectPropDesc(struct MTPContainer &cmd);
  uint32_t GetObjectPropValue(struct MTPContainer &cmd);

  uint32_t setObjectPropValue(struct MTPContainer &cmd);
  uint32_t formatStore(struct MTPContainer &cmd);
  
  static MTP_class *g_pmtpd_interval;
  static void _interval_timer_handler();
  static IntervalTimer g_intervaltimer;
  void processIntervalTimer();

  uint32_t deleteObject(uint32_t p1);
  uint32_t copyObject(uint32_t p1, uint32_t p2, uint32_t p3/*, int &object_id*/);
  uint32_t moveObject(uint32_t p1, uint32_t p2, uint32_t p3);
  uint32_t OpenSession(struct MTPContainer &cmd);

  uint32_t TID = 0;
#if USE_EVENTS == 1
  int send_Event(uint16_t eventCode, uint32_t p1);
  int send_Event(uint16_t eventCode, uint32_t p1, uint32_t p2);
  int send_Event(uint16_t eventCode, uint32_t p1, uint32_t p2, uint32_t p3);
#endif

private:
  void addSendObjectBuffer(
      char *pb,
      uint32_t cb); // you can extend the send object buffer by this buffer

  // page 45: "StorageID ... most-significant 16 bits identify a physical storage
  // location, such as a removable memory card or an internal memory bank. The
  // least-significant 16 bits identify a logical partition of that physical
  // storage."
  inline uint32_t Store2Storage(uint32_t store) {
    return ((store + 1) << 16) | 0x0001;
  }
  static inline uint32_t Storage2Store(uint32_t storage) {
    return (storage >> 16) - 1;
  }

#if USE_EVENTS == 1
  int send_Event(uint16_t eventCode);
  int send_addObjectEvent(uint32_t p1);
  int send_removeObjectEvent(uint32_t p1);
  int send_StorageInfoChangedEvent(uint32_t p1);

  // Send a device reset event, when processed by the host
  // they will start a new session, at which point we will
  // clear our file system store file as the object ids are
  // only valid during  a sesion. 

  int send_DeviceResetEvent(void);

  // Send an event telling the host, that we added another storeage
  // to our list.  Example:  USBHost detects a new USB device has
  // been inserted, and we wish to show the new filesystem(s)
  int send_StoreAddedEvent(uint32_t store);


  // Send an event telling the host, that a file system is no longer
  // available and for the host to remove it from their list. 
  int send_StoreRemovedEvent(uint32_t store);

  // higer level version of sending events
  // unclear if should pass in pfs or store?
  bool send_addObjectEvent(uint32_t store, const char *pathname);
  bool send_removeObjectEvent(uint32_t store, const char *pathname);
  void printContainer(const void *container, const char *msg = nullptr);
#endif
  // Support for SendObject, holding parameters from SendObjectInfo.
  uint32_t object_id_ = 0;
  uint32_t dtCreated_ = 0;
  uint32_t dtModified_ = 0;
  uint32_t dtFormatStart_ = 0;
  static const uint32_t MAX_FORMAT_TIME_ = 2750; // give a little time. 
  bool storage_ids_sent_ = false;
  MTPStorage storage_;

};

extern MTP_class MTP;

#endif // USB_MTPDISK or USB_MTPDISK_SERIAL
