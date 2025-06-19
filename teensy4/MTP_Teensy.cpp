// MTP.cpp - Teensy MTP Responder library
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

#if defined(USB_MTPDISK) || defined(USB_MTPDISK_SERIAL)

#define USE_DISK_BUFFER // only currently on T4.x

#include "MTP_Teensy.h"
#include "MTP_Const.h"
#undef USB_DESC_LIST_DEFINE
#include "usb_desc.h"

#if defined(__IMXRT1062__)
// following only while usb_mtp is not included in cores
#include "usb_mtp.h"
#endif

#include "usb_names.h"
extern struct usb_string_descriptor_struct usb_string_serial_number;

// define global mtpd object;
MTP_class MTP;


// Define some of the static members
Stream *MTP_class::printStream_ = &Serial;

#if defined(__IMXRT1062__)
DMAMEM uint8_t MTP_class::disk_buffer_[DISK_BUFFER_SIZE] __attribute__((aligned(32)));
#endif

#define DEBUG 0
#if DEBUG > 0
#define printf(...) printStream_->printf(__VA_ARGS__)
#else
#define printf(...)
#endif
#if DEBUG > 2
#define DBGPRINTF(...) printf_debug(__VA_ARGS__)
extern "C" {
void printf_debug(const char *format, ...);
}
#else
#define DBGPRINTF(...)
#endif


// Define global(static) members
uint32_t MTP_class::sessionID_ = 0;


//***************************************************************************
//  Top level - public functions called by user program
//***************************************************************************
// test/hack have usb_mtp.c call us on first usb message..
void usb_mtp_first_rx_cb() {
  MTP.begin(); // 
}


int MTP_class::begin() {
  // maybe don't do anything if already running interval timer
  if (g_pmtpd_interval) {
    printf("MTP.begin previously called");
    return 0;
  }
  // lets set up to check for MTP messages and tell
  // other side we are busy...  Maybe should be function:
#if defined(__IMXRT1062__)
  transmit_packet_size_mask = usb_mtp_rxSize() - 1;
#endif
  g_pmtpd_interval = this;
  printf("\n\n*** Start Interval Timer at ms:%u ***\n", millis());
  g_intervaltimer.begin(&_interval_timer_handler, 50000); // 20 Hz
  return usb_init_events();
}

void MTP_class::loop(void) {
  if (g_pmtpd_interval) {
    g_pmtpd_interval = nullptr; // clear out timer.
    g_intervaltimer.end();      // try maybe 20 times per second...
    printf("*** end Interval Timer ***\n");
  }
  if (receive_bulk(0)) {
    if (receive_buffer.len >= 12 && receive_buffer.len <= 32) {
      // This container holds the operation code received from host
      // Commands which transmit a 12 byte header as the first part
      // of their data phase will reuse this container, overwriting
      // the len & type fields, but keeping op and transaction_id.
      // Then this container is again reused to transmit the final
      // response code, keeping the original transaction_id, but
      // the other 3 header fields are based on "return_code".  If
      // the response requires parameters, they are written into
      // this container's parameter list.
      struct MTPContainer container;
      memset(&container, 0, sizeof(container));
      memcpy(&container, receive_buffer.data, receive_buffer.len);
      free_received_bulk();
      printContainer(&container, "loop:");

      int p1 = container.params[0];
      int p2 = container.params[1];
      int p3 = container.params[2];
      TID = container.transaction_id;

      // The low 16 bits of return_code have the response code
      // operation field.  The top 4 bits indicate the number
      // of parameters to transmit with the response code.
      int return_code = 0x2001; // OK use as default value
      bool send_reset_event = false;

      if (container.type == MTP_CONTAINER_TYPE_COMMAND) {
        switch (container.op) {
        case 0x1001: // GetDeviceInfo
          return_code = GetDeviceInfo(container);
          break;
        case 0x1002: // OpenSession
          return_code = OpenSession(container);
          break;
        case 0x1003: // CloseSession
          printf("MTP_class::CloseSession\n");
          sessionID_ = 0; //
          break;
        case 0x1004: // GetStorageIDs
          return_code = GetStorageIDs(container);
          break;
        case 0x1005: // GetStorageInfo
          return_code = GetStorageInfo(container);
          break;
        case 0x1006: // GetNumObjects
          return_code = GetNumObjects(container);
          break;
        case 0x1007: // GetObjectHandles
          return_code = GetObjectHandles(container);
          break;
        case 0x1008: // GetObjectInfo
          return_code = GetObjectInfo(container);
          break;
        case 0x1009: // GetObject
          return_code = GetObject(container);
          break;
        case 0x100B: // DeleteObject
          if (p2) {
            return_code = 0x2014; // spec by format unsupported
          } else {
            if (!storage_.DeleteObject(p1)) {
              return_code = 0x2012; // partial deletion
            }
          }
          break;
        case 0x100C: // SendObjectInfo
          return_code = SendObjectInfo(container);
          break;
        case 0x100D: // SendObject
          return_code = SendObject(container);
          break;
        case 0x100F: // FormatStore
          return_code = formatStore(container);
          if (return_code == MTP_RESPONSE_OK) send_reset_event = true;
          break;
        case 0x1014: // GetDevicePropDesc
          return_code = GetDevicePropDesc(container);
          break;
        case 0x1015: // GetDevicePropvalue
          return_code = GetDevicePropValue(container);
          break;
        case 0x1010: // Reset
          return_code = 0x2005;
          break;
        case 0x1019: // MoveObject
          return_code = moveObject(p1, p2, p3);
          break;
        case 0x101A: // CopyObject
          return_code = copyObject(p1, p2, p3);
          if (!return_code) {
            return_code = 0x2005;
          } else {
            container.params[0] = return_code;
            uint8_t error_code = storage_.getLastError();
            switch (error_code) {
              default:
                return_code = 0x2001;
                break;
              case MTPStorage::RMDIR_FAIL:
              case MTPStorage::WRITE_ERROR:
              case MTPStorage::DEST_OPEN_FAIL:
                return_code = MTP_RESPONSE_STORAGE_FULL;
                break;
            }
            return_code |= (1<<28);
          }
          break;
        case 0x101B: // GetPartialObject
          return_code = GetPartialObject(container);
          break;
        case 0x9801: // GetObjectPropsSupported
          return_code = GetObjectPropsSupported(container);
          break;
        case 0x9802: // GetObjectPropDesc
          return_code = GetObjectPropDesc(container);
          break;
        case 0x9803: // GetObjectPropertyValue
          return_code = GetObjectPropValue(container);
          break;
        case 0x9804: // setObjectPropertyValue
          return_code = setObjectPropValue(container);
          break;
        default:
          return_code = 0x2005; // operation not supported
          break;
        }
      } else {
        return_code = 0x2005; // we should only get cmds
        printContainer(&container, "!!! unexpected/unknown message:");
      }
      if (return_code && usb_mtp_status == 0x01) {
        container.len = 12 + (return_code >> 28) * 4; // top 4 bits is number of parameters
        container.type = MTP_CONTAINER_TYPE_RESPONSE;
        container.op = (return_code & 0xFFFF);        // low 16 bits is op response code
        // container.transaction_id reused from original received command
        #if DEBUG > 1
        printContainer(&container); // to switch on set debug to 2 at beginning of file
        #endif
        write(&container, container.len);
        write_finish();

        // Maybe some operations might need to tell host to do reset
        // right now try after a format store.
        if (send_reset_event) {
          send_DeviceResetEvent();
        }

      }
    } else {
      printf("ERROR: loop received command with %u bytes\n", receive_buffer.len);
      free_received_bulk();
      // TODO: what is the proper way to handle this error?
      // Still Image Class spec 1.0 says on page 20:
      //   "If the number of bytes transferred in the Command phase is less than
      //    that specified in the first four bytes of the Command Block then the
      //    device has received an invalid command and should STALL the Bulk-Pipe
      //    (refer to Clause 7.2)."
      // What are we supposed to do is too much data arrives?  Or other invalid cmds?
    }
  }

  // check here to mske sure the USB status is reset
  if (usb_mtp_status != 0x01) {
    printf("MTP_class::Loop usb_mtp_status %x != 0x1 reset\n", usb_mtp_status);
    usb_mtp_status = 0x01;
  }

  // Storage loop() handles removable media insert / remove
  storage_.loop();
}


// IntervalTimer runs a mini version of loop() at 20 Hz, to keep quick response to host
//
MTP_class *MTP_class::g_pmtpd_interval = nullptr;
IntervalTimer MTP_class::g_intervaltimer;

void MTP_class::_interval_timer_handler() {
  if (g_pmtpd_interval)
    g_pmtpd_interval->processIntervalTimer();
}

void MTP_class::processIntervalTimer() {
  if (receive_bulk(0)) {
    if (receive_buffer.len >= 12 && receive_buffer.len <= 32) {
      struct MTPContainer container;
      memset(&container, 0, sizeof(container));
      memcpy(&container, receive_buffer.data, receive_buffer.len);
      free_received_bulk();
      printContainer(&container, "timer:"); // to switch on set debug to 1 at beginning of file

      TID = container.transaction_id;
      uint32_t return_code = 0x2001; // 0x2001=OK
      if (container.type == 1) { // command
        switch (container.op) {
        case MTP_OPERATION_GET_DEVICE_INFO: // GetDescription 0x1001
          return_code = GetDeviceInfo(container);
          break;
        case MTP_OPERATION_OPEN_SESSION: // open session 0x1002
          return_code = OpenSession(container);
          break;
        case MTP_OPERATION_GET_DEVICE_PROP_DESC: // 1014
          return_code = GetDevicePropDesc(container);
          break;
        case 0x1004: // GetStorageIDs 1004, needed by MacOS Android File Transfer app
          return_code = GetStorageIDs(container);
          break;
        case 0x1005: // GetStorageInfo
          return_code = GetStorageInfo(container, false); // media access not allowed for ISR
          break;
        case 0x9801: // GetObjectPropsSupported
          return_code = GetObjectPropsSupported(container);
          break;
        default:
          return_code = MTP_RESPONSE_DEVICE_BUSY; // busy 0x2019
          break;
        }
      } else {
        // TODO: should this send 0x2005 MTP_RESPONSE_OPERATION_NOT_SUPPORTED ??
        return_code = MTP_RESPONSE_UNDEFINED; // undefined 0x2000
      }
      container.type = 3;
      container.len = 12;
      container.op = return_code;
#if DEBUG > 1
      printContainer(&container);
#endif
      allocate_transmit_bulk();
      memcpy(transmit_buffer.data, &container, container.len);
      transmit_buffer.len = container.len;
      transmit_bulk();
    } else {
      printf("ERROR: intervaltimer received command with %u bytes\n", receive_buffer.len);
      free_received_bulk();
    }
  }
}


//***************************************************************************
//  MTP Commands - File Transfer and File Operations
//***************************************************************************

/*
  struct MTPHeader {
    uint32_t len;  // 0
    uint16_t type; // 4
    uint16_t op;   // 6
    uint32_t transaction_id; // 8
  };

  struct MTPContainer {
    uint32_t len;  // 0
    uint16_t type; // 4
    uint16_t op;   // 6
    uint32_t transaction_id; // 8
    uint32_t params[5];    // 12
  };
*/

// When the host (your PC) wants to put a new file onto any of Teensy's drives
// first uses SendObjectInfo to tell us info about the file.  Then SendObject
// is used to actually transfer the file's data.
//
// SendObjectInfo, MTP 1.1 spec, page 223
//   Command: 2 parameters: Destination StorageID, Parent ObjectHandle
//   Data: PC->Teensy: ObjectInfo
//   Response: 3 parameters: Destination StorageID, Parent ObjectHandle, ObjectHandle
uint32_t MTP_class::SendObjectInfo(struct MTPContainer &cmd) { // MTP 1.1 spec, page 223
  uint32_t storage = cmd.params[0];
  uint32_t parent = cmd.params[1];
  printf("SendObjectInfo: %x %x ", storage, parent);
  uint32_t store = Storage2Store(storage);
  struct MTPHeader header;
  if (!readDataPhaseHeader(&header)) return MTP_RESPONSE_INVALID_DATASET;
  printf("Dataset len=%u\n", header.len);
  // receive ObjectInfo Dataset, MTP 1.1 spec, page 50
  char filename[MTP_MAX_FILENAME_LEN];
  uint16_t oformat;
  uint32_t file_size;
  if (read(NULL, 4)                          // StorageID (unused)
   && read16(&oformat)                       // ObjectFormatCode
   && read(NULL, 2)                          // Protection Status (unused)
   && read32(&file_size)                     // Object Compressed Size
   && read(NULL, 40)                         // Image info (unused)
   && readstring(filename, sizeof(filename)) // Filename
   && readDateTimeString(&dtCreated_)        // Date Created
   && readDateTimeString(&dtModified_)       // Date Modified
   && readstring(NULL, 0)                    // Keywords
   && (true)) {                              // TODO: read complete function (handle ZLP)
    printf("%s ", (oformat == 0x3001) ? "Dir" : "File");
    printf("\"%s\" ", filename);
    printf("size:%u ", file_size);
    printf("Created:%x ", dtCreated_);
    printf("Modified:%x\n", dtModified_);
    if (receive_buffer.data == NULL) {
      printf(" read consumed all data (TODO: how to check ZLP)\n");
      // TODO: need to check for ZLP here....
    } else {
      printf(" ERROR, receive buffer has %u bytes unused!\n",
        receive_buffer.len - receive_buffer.index);
    }
  } else {
    return MTP_RESPONSE_INVALID_DATASET;
  }
  // Lets see if we have enough room to store this file:
  uint64_t free_space = storage_.totalSize(store) - storage_.usedSize(store);
  if (file_size == 0xFFFFFFFFUL) {
    printf("Size of object == 0xffffffff - Indicates >= 4GB file!\n \t?TODO: query real size? FS supports this - FAT32 no?\n");
  }
  if (file_size > free_space) {
    printf("Size of object:%u is > free space: %llu\n", file_size, free_space);
    return MTP_RESPONSE_STORAGE_FULL;
  }
  const bool dir = (oformat == 0x3001);
  object_id_ = storage_.Create(store, parent, dir, filename);
  if (object_id_ == 0xFFFFFFFFUL) {
    return MTP_RESPONSE_SPECIFICATION_OF_DESTINATION_UNSUPPORTED;
  }
  if (dir) {
    // lets see if we should update the date and time stamps.
    // if it is dirctory, then sendObject will not be called, so do it now.
    if (!storage_.updateDateTimeStamps(object_id_, dtCreated_, dtModified_)) {
      // BUGBUG: failed to update, maybe FS needs little time to settle in
      // before trying this.
      for (uint8_t i = 0; i < 10; i++) {
        printf("!!!(%d) Try delay and call update time stamps again\n", i);
        delay(25);
        if (storage_.updateDateTimeStamps(object_id_, dtCreated_, dtModified_))
          break;
      }
    }
    storage_.close();
  }
  cmd.params[2] = object_id_;
  return MTP_RESPONSE_OK | (3<<28); // response with 3 params
}

// SendObject, MTP 1.1 spec, page 225
//   Command: no parameters
//   Data: PC->Teensy: Binary Data
//   Response: no parameters
#if defined(__IMXRT1062__) && defined(USE_DISK_BUFFER)
uint32_t MTP_class::SendObject(struct MTPContainer &cmd) {
  MTPHeader header;
  if (!readDataPhaseHeader(&header)) return MTP_RESPONSE_PARAMETER_NOT_SUPPORTED;
  uint64_t size = header.len - sizeof(header);
  printf("SendObject: %llu(0x%llx) bytes, id=%x\n", size, size, object_id_);
  // TODO: check size matches file_size from SendObjectInfo
  // TODO: check if object_id_
  // TODO: should we do storage_.Create() here?  Can we preallocate file size?
  uint32_t ret = MTP_RESPONSE_OK;
  uint64_t pos = 0;

  // index into our disk buffer.

  bool huge_file = (size == 0xfffffffful);
  if (huge_file) size = (uint64_t)-1;
  uint64_t cb_left = size;

  #if DEBUG
  elapsedMillis em_send;
  elapsedMillis emPrint;
  uint32_t count_reads = 0;
  uint32_t to_copy_prev = 0;
  #endif

  // lets go ahead and copy the rest of the first receive buffer into
  // our disk buffer, so we don't have to play with starting index and the like...
  uint16_t disk_buffer_index = receive_buffer.len - receive_buffer.index;
  memcpy((char*)disk_buffer_, (char *)&receive_buffer.data[receive_buffer.index], disk_buffer_index);
  pos = disk_buffer_index;
  free_received_bulk();


  while (huge_file || (pos < size)) {
    if (!receive_bulk(100)) {
      if (pos <= 0xfffffffful) {
        printf("SO: receive failed pos:%llu size:%llu\n", pos, size);
        ret = MTP_RESPONSE_OPERATION_NOT_SUPPORTED;
      } else {
        printf("SO: receive failed pos:%llu large file EOF\n", pos);
      }
      break;
    }


    uint32_t to_copy = receive_buffer.len;

    #if DEBUG
    count_reads++;
    if ((to_copy != to_copy_prev) || (emPrint > 15000)) {
      printf("SO RC:%u CB:%u pos:%llu\n", count_reads, to_copy, pos);
      to_copy_prev = to_copy;
      emPrint = 0;
    }
    #endif

    uint16_t cb_buffer_avail = sizeof(disk_buffer_) - disk_buffer_index;
    // See if this will fill the buffer;
    if (cb_buffer_avail <= to_copy) {
      memcpy(&disk_buffer_[disk_buffer_index], (char*)&receive_buffer.data[receive_buffer.index], cb_buffer_avail);
      disk_buffer_index = 0;
      if (storage_.write((char*)disk_buffer_, sizeof(disk_buffer_)) != sizeof(disk_buffer_)) {
        ret = MTP_RESPONSE_OPERATION_NOT_SUPPORTED; // TODO: best response for write error??
        // maybe send MTP_EVENT_CANCEL_TRANSACTION event??
        break;
      }
      if (cb_buffer_avail != to_copy) {
        // copy in the remaining.
        disk_buffer_index = to_copy - cb_buffer_avail;
        memcpy(disk_buffer_, (char*)&receive_buffer.data[cb_buffer_avail], disk_buffer_index);
      }
    } else {
      memcpy(&disk_buffer_[disk_buffer_index], (char*)receive_buffer.data, to_copy);
      disk_buffer_index += to_copy;  
    }

    pos += to_copy;
    cb_left -= to_copy; // 

    free_received_bulk();
    if ((to_copy < 512) && (size == (uint64_t)-1) && (pos > 0xfffffffful)){
      printf("SendObject large EOF Detected: %lluu\n", pos);
      break;
    }
  }


  // clear out any trailing. 


  while (pos < size) {
    // consume remaining incoming data, if we aborted for any reason
    if (receive_buffer.data == NULL && !receive_bulk(250)) break; 
    uint16_t cb_packet = receive_buffer.len - receive_buffer.index;   
    pos += cb_packet;
    free_received_bulk();
    if (cb_packet < 512) break;
  }
  // write out anything left in our disk buffer... 
  if (disk_buffer_index) {
    if (storage_.write((char*)disk_buffer_, disk_buffer_index) != disk_buffer_index) {
      ret = MTP_RESPONSE_OPERATION_NOT_SUPPORTED; // TODO: best response for write error??
      // maybe send MTP_EVENT_CANCEL_TRANSACTION event??
    }

  }

  // TODO: check no lingering buffered data, and ZLP is present if expected
  #if DEBUG
  printf("SendObject complete pos:%u dt:%u\n", pos, (uint32_t)em_send / 1000);
  #endif

  storage_.updateDateTimeStamps(object_id_, dtCreated_, dtModified_);
  storage_.close();

  if (ret == MTP_RESPONSE_OK) object_id_ = 0; // SendObjectInfo can not be reused after success
  return ret;
}

#else
uint32_t MTP_class::SendObject(struct MTPContainer &cmd) {
  MTPHeader header;
  if (!readDataPhaseHeader(&header)) return MTP_RESPONSE_PARAMETER_NOT_SUPPORTED;
  uint64_t size = header.len - sizeof(header);
  printf("SendObject: %llu(0x%llx) bytes, id=%x\n", size, size, object_id_);
  // TODO: check size matches file_size from SendObjectInfo
  // TODO: check if object_id_
  // TODO: should we do storage_.Create() here?  Can we preallocate file size?
  uint32_t ret = MTP_RESPONSE_OK;
  uint64_t pos = 0;
  uint32_t count_reads = 0;
  uint32_t to_copy_prev = 0;
  bool huge_file = (size == 0xfffffffful);
  if (huge_file) size = (uint64_t)-1;
  uint64_t cb_left = size;
  while (huge_file || (pos < size)) {
    if (receive_buffer.data == NULL) {
      if (!receive_bulk(100)) {
        printf("SO: receive failed pos:%llu size:%llu\n", pos, size);
        ret = MTP_RESPONSE_OPERATION_NOT_SUPPORTED;
        break;
      }
    }
    uint32_t to_copy = receive_buffer.len - receive_buffer.index;
    count_reads++;
    if (to_copy != to_copy_prev) {
      printf("SO RC:%u CB:%u pos:%llu\n", count_reads, to_copy, pos);
      to_copy_prev = to_copy;;
    }


    //if (to_copy > size) to_copy = size;  // did not make sense to me
    if (to_copy > cb_left) to_copy = cb_left;

    //printf("SendObject, pos=%u, write=%u, size=%u\n", pos, to_copy, size);
    bool ok = storage_.write((char *)(receive_buffer.data + receive_buffer.index), to_copy);
    if (!ok) {
      ret = MTP_RESPONSE_OPERATION_NOT_SUPPORTED; // TODO: best response for write error??
      // maybe send MTP_EVENT_CANCEL_TRANSACTION event??
      break;
    }
    pos += to_copy;
    cb_left -= to_copy; // 
    receive_buffer.index += to_copy;
    if (receive_buffer.index >= receive_buffer.len) {
      free_received_bulk();
    #if 1
      if ((to_copy < 512) && (pos > 0xfffffffful)) {
        printf(">4gb file EOF detected pos:%llu\n", pos);
        break;
      }
    #endif    
    }
  }
  while ((pos < size) && (pos <  0xfffffffful)) {
    // consume remaining incoming data, if we aborted for any reason
    if (receive_buffer.data == NULL && !receive_bulk(250)) break;
    pos += receive_buffer.len - receive_buffer.index;
    free_received_bulk();
  }
  // TODO: check no lingering buffered data, and ZLP is present if expected
  printf("SendObject complete\n");
  storage_.updateDateTimeStamps(object_id_, dtCreated_, dtModified_);
  storage_.close();

  if (ret == MTP_RESPONSE_OK) object_id_ = 0; // SendObjectInfo can not be reused after success
  return ret;
}
#endif


// When the host (your PC) wants to put a read a file from any of Teensy's drives
// first it uses GetObjectInfo to request all the file's metadata.  Then GetObject
// is used to read the actual file data.
//
// GetObjectInfo, MTP 1.1 spec, page 218
//   Command: 1 parameter: ObjectHandle
//   Data: Teensy->PC: ObjectInfo
//   Response: no parameters
uint32_t MTP_class::GetObjectInfo(struct MTPContainer &cmd) {
  uint32_t handle = cmd.params[0];
  uint32_t parent, dt;
  uint64_t size;
  char filename[MTP_MAX_FILENAME_LEN], ctimebuf[16], mtimebuf[16];
  DateTimeFields dtf;
  uint16_t store;
  storage_.GetObjectInfo(handle, filename, &size, &parent, &store);

  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wformat-truncation" /* Or "-Wformat-truncation" */
  if (storage_.getCreateTime(handle, dt)) {
    breakTime(dt, dtf);
    snprintf(ctimebuf, sizeof(ctimebuf), "%04u%02u%02uT%02u%02u%02u",
             dtf.year + 1900, dtf.mon + 1, dtf.mday, dtf.hour, dtf.min,
             dtf.sec);
  } else {
    ctimebuf[0] = 0;
  }
  if (storage_.getModifyTime(handle, dt)) {
    breakTime(dt, dtf);
    snprintf(mtimebuf, sizeof(mtimebuf), "%04u%02u%02uT%02u%02u%02u",
             dtf.year + 1900, dtf.mon + 1, dtf.mday, dtf.hour, dtf.min,
             dtf.sec);
  } else {
    mtimebuf[0] = 0;
  }
#pragma GCC diagnostic pop

  writeDataPhaseHeader(cmd,
    4 + 2 + 2 + 4 + 2 + 4 + 4 + 4 + 4 + 4 + 4 + 4 + 2 + 4 + 4
    + writestringlen(filename) + writestringlen(ctimebuf)
    + writestringlen(mtimebuf) + writestringlen(""));

  // if size is > 4gb we need to send the size 0xfffffffful and it may then ask us for real size.
  bool is_directory = (size == (uint64_t)-1);
  if (size > 0xfffffffful) size = 0xfffffffful;

  uint32_t storage = Store2Storage(store);
  write32(storage);                                // storage
  write16(is_directory ? 0x3001 : 0x0000);         // format
  write16(0);                                      // protection
  write32(size);                                   // size
  write16(0);                                      // thumb format
  write32(0);                                      // thumb size
  write32(0);                                      // thumb width
  write32(0);                                      // thumb height
  write32(0);                                      // pix width
  write32(0);                                      // pix height
  write32(0);                                      // bit depth
  write32(parent);                                 // parent
  write16(is_directory ? 1 : 0);                   // association type
  write32(0);                                      // association description
  write32(0);                                      // sequence number
  writestring(filename);                           // filename
  writestring(ctimebuf);                           // date created
  writestring(mtimebuf);                           // date modified
  writestring("");                                 // keywords
  write_finish();
  return MTP_RESPONSE_OK;
}


//  GetObject, MTP 1.1 spec, page 219
//   Command: 1 parameter: ObjectHandle
//   Data: Teensy->PC: Binary Data
//   Response: no parameters
#if defined(__IMXRT1062__) && defined(USE_DISK_BUFFER)
// experiment again on T4.x use 4k buffer disk_buffer_
uint32_t MTP_class::GetObject(struct MTPContainer &cmd) {
  uint16_t cb_read = 0;
  uint64_t disk_pos = 0;
  uint64_t pos = 0;

  const int object_id = cmd.params[0];
  uint64_t size = storage_.GetSize(object_id);
  uint64_t count_remaining = size;

  writeDataPhaseHeader(cmd, (size > 0xfffffffful)?  0xfffffffful : size);

  printf("GetObject, size=%llu\n", size);
  #if DEBUG
  elapsedMillis emTotal;
  elapsedMillis emPrint;
  #endif
  while (count_remaining) {
    if (usb_mtp_status != 0x01) {
      printf("GetObject, abort status:%x\n", usb_mtp_status);
      return 0;
    }

    // Lets make it real simple for now.
    cb_read = storage_.read(object_id, disk_pos, (char*)disk_buffer_, sizeof(disk_buffer_));
    if (cb_read == 0) {
      break;
    }
    size_t cb_written = write(disk_buffer_, cb_read);
    if (cb_written != cb_read) {
      printf("GetObject, write count error: %u != %u\n", cb_written, cb_read);
      break;
    }
    count_remaining -= cb_read;
    pos += cb_read;
    disk_pos += cb_read;

    #if DEBUG
    if (emPrint >= 15000) {
      uint32_t percent_done = (pos * 100ull) / size;
      printf("\tdt:%u, pos:%llu %u%%\n", (uint32_t)emTotal/1000, pos, percent_done);
      emPrint = 0;
    }
    #endif
  }
  write_finish();
  printf("GetObject, done pos:%llu size:%llu dt:%u\n", pos, size, (uint32_t)emTotal/1000);
  return MTP_RESPONSE_OK;
}

#else
uint32_t MTP_class::GetObject(struct MTPContainer &cmd) {
  const int object_id = cmd.params[0];
  uint64_t size = storage_.GetSize(object_id);
  printf("GetObject, size=%llu\n", size);
  writeDataPhaseHeader(cmd, (size > 0xfffffffful)?  0xfffffffful : size);
  uint64_t pos = 0;
  #if DEBUG
  elapsedMillis emPrint;
  #endif
  while (pos < size) {
    if (usb_mtp_status != 0x01) {
      printf("GetObject, abort status:%x\n", usb_mtp_status);
      return 0;
    }
    if (transmit_buffer.data == NULL) allocate_transmit_bulk();
    uint32_t avail = transmit_buffer.size - transmit_buffer.len;
    uint64_t to_copy = size - pos;
    if (to_copy > avail) to_copy = avail;
    // Read directly from storage into usb buffer.
    uint32_t cb_read = storage_.read(object_id, pos,
                   (char *)(transmit_buffer.data + transmit_buffer.len), to_copy);
    #if DEBUG
    if ((emPrint >= 15000) || (cb_read != 512)) {
      printf("\tGO: read=%u, pos=%llu, Read:%u\n", to_copy, pos, cb_read);
      emPrint = 0;
    }
    #endif
    if (cb_read == 0) break;
    pos += to_copy;
    transmit_buffer.len += to_copy;
    if (transmit_buffer.len >= transmit_buffer.size) {
      transmit_bulk();
    }
  }
  write_finish();
  printf("GetObject, done pos:%llu size:%llu\n", pos, size);
  return MTP_RESPONSE_OK;
}
#endif

//  GetPartialObject, MTP 1.1 spec, page 240
//   Command: 3 parameters: ObjectHandle, Offset in bytes, Maximum number of bytes
//   Data: Teensy->PC: binary data
//   Response: 1 parameter: Actual number of bytes sent
uint32_t MTP_class::GetPartialObject(struct MTPContainer &cmd) {
  uint32_t object_id = cmd.params[0];
  uint32_t offset = cmd.params[1];
  uint64_t NumBytes = cmd.params[2];
  if (NumBytes == 0xfffffffful) NumBytes = (uint64_t)-1;
  uint64_t size = storage_.GetSize(object_id);
  printf("GetPartialObject: %x Of:%u NB:%u CB:%llu, FS:%llu\n", object_id, offset, cmd.params[2], NumBytes, size);
  if (offset >= size) {
    // writeDataPhaseHeader(cmd, 0); ???
    return MTP_RESPONSE_INVALID_PARAMETER;
  }
  if (NumBytes > size - offset) {
    NumBytes = size - offset;
  }
  writeDataPhaseHeader(cmd, NumBytes);
  uint32_t pos = offset; // into data
  uint32_t end = offset + NumBytes;
  while (pos < end) {
    if (usb_mtp_status != 0x01) {
      printf("GetPartialObject, abort\n");
      return 0;
    }
    if (transmit_buffer.data == NULL) allocate_transmit_bulk();
    uint32_t avail = transmit_buffer.size - transmit_buffer.len;
    uint32_t to_copy = end - pos;
    if (to_copy > avail) to_copy = avail;
    storage_.read(object_id, pos,
                   (char *)(transmit_buffer.data + transmit_buffer.len), to_copy);
    pos += to_copy;
    transmit_buffer.len += to_copy;
    if (transmit_buffer.len >= transmit_buffer.size) {
      transmit_bulk();
    }
  }
  write_finish();
  cmd.params[0] = (NumBytes < 0xfffffffful)? NumBytes : 0xfffffffful;
  return MTP_RESPONSE_OK + (1<<28);
}


//  DeleteObject, MTP 1.1 spec, page 221
//   Command: 3 parameters: ObjectHandle, [ObjectFormatCode]
//   Data: none
//   Response: no parameters
uint32_t MTP_class::deleteObject(uint32_t handle) {
  if (!storage_.DeleteObject(handle)) {
    return 0x2012; // partial deletion
  }
  return 0x2001;
}

//  MoveObject, MTP 1.1 spec, page 238
//   Command: 3 parameters: ObjectHandle, StorageID target, ObjectHandle of the new ParentObject
//   Data: none
//   Response: no parameters
uint32_t MTP_class::moveObject(uint32_t handle, uint32_t newStorage,
                          uint32_t newHandle) {
  uint32_t store1 = Storage2Store(newStorage);
  if (newHandle == 0) newHandle = store1;

  if (storage_.move(handle, store1, newHandle))
    return 0x2001;
  else
    return 0x2005;
}

//  CopyObject, MTP 1.1 spec, page 239
//   Command: 3 parameters: ObjectHandle, StorageID target, ObjectHandle of the new ParentObject
//   Data: none
//   Response: no parameters
uint32_t MTP_class::copyObject(uint32_t handle, uint32_t newStorage,
                          uint32_t newHandle) {
  uint32_t store1 = Storage2Store(newStorage);
  if (newHandle == 0) newHandle = store1;

  return storage_.copy(handle, store1, newHandle);
}

//  FormatStore, MTP 1.1 spec, page 228
//   Command: 2 parameters: StorageID, [FileSystem Format]
//   Data: none
//   Response: no parameters
uint32_t MTP_class::formatStore(struct MTPContainer &cmd) {
  printf("formatStore begin\n");
  const uint32_t store = Storage2Store(cmd.params[0]);
  const uint32_t format = cmd.params[1];
  g_pmtpd_interval = this;
  dtFormatStart_ = millis();  // remember when format started
  g_intervaltimer.begin(&_interval_timer_handler, 50000); // 20 Hz
  #if DEBUG > 0
  elapsedMillis msec = 0;
  #endif
  uint8_t success = storage_.formatStore(store, format);
  if (g_pmtpd_interval) g_intervaltimer.end();
  printf("formatStore success=%u, format took %u ms\n", success, (uint32_t)msec);
  if (success) {
    // The caller of this funciton will call device reset.
    // which when new session is started should reset the index
    //storage_.ResetIndex(); // maybe should add a less of sledge hammer here.
    // send_DeviceResetEvent();
    return MTP_RESPONSE_OK;
  } else {
    return MTP_RESPONSE_OPERATION_NOT_SUPPORTED;
  }
}





//***************************************************************************
//  MTP Commands - Metadata, Capability Detection, and Boring Stuff
//***************************************************************************


// GetStorageIDs, MTP 1.1 spec, page 213
//   Command: no parameters
//   Data: Teensy->PC: StorageID array (page 45)
//   Response: no parameters
uint32_t MTP_class::GetStorageIDs(struct MTPContainer &cmd) {
  uint32_t num = storage_.get_FSCount();
  // first count the number of filesystems
  uint32_t num_valid = 0;
  for (uint32_t store = 0; store < num; store++) {
    FS *fs = storage_.getStoreFS(store);
    if (fs && storage_.isMediaPresent(store)) num_valid++;
  }
  writeDataPhaseHeader(cmd, 4 + num_valid * 4);
  write32(num_valid); // number of storages (disks)
  for (uint32_t store = 0; store < num; store++) {
    FS *fs = storage_.getStoreFS(store);
    if (fs && storage_.isMediaPresent(store)) {
      // page 213 says "Removable storages with no inserted media shall be returned
      // in the dataset returned by this operation as well, though they would contain
      // a value of 0x0000 in the lower 16 bits indicating that they are not present"
      // However, Linux seems to get confused by these StorageIDs.  Because Windows
      // just hides them anyway, we'll not send these StorageID for removed media.
      uint32_t StorageID = Store2Storage(store);
      printf("\t%u(%s %s) StorageID=%08X\n", store, // FIXME: printing maybe ISR unsafe? // FIXME: printing maybe ISR unsafe?
        storage_.get_FSName(store), fs->name(), StorageID);
      write32(StorageID); // storage id
    }
  }
  write_finish();
  storage_ids_sent_ = true;
  return MTP_RESPONSE_OK;
}

// GetStorageInfo, MTP 1.1 spec, page 214
//   Command: 1 parameter: StorageID
//   Data: Teensy->PC: StorageInfo (page 46)
//   Response: no parameters
uint32_t MTP_class::GetStorageInfo(struct MTPContainer &cmd, bool mediaAccessAllowed) {
  uint32_t storage = cmd.params[0];
  uint32_t store = Storage2Store(storage);
  FS *fs = storage_.getStoreFS(store);
  if (fs == nullptr) {
    printf("MTP_class::GetStorageInfo %u is not valid (FS nullptr)\n", store);
    return MTP_RESPONSE_STORE_NOT_AVAILABLE;
  }
  if (!storage_.isMediaPresent(store)) {
    printf("MTP_class::GetStorageInfo %u(%s) removable media not present\n", store, name);
    // TODO: is this correct response for removable media not present?
    return MTP_RESPONSE_STORE_NOT_AVAILABLE;
  }
  const char *name = storage_.get_FSName(store);
  const char *volname = fs->name(); // assume no media access if previously called
  if (volname) {
    name = volname;
  } else if (!name) {
    name = "Untitled";
  }
  uint32_t size = 2 + 2 + 2 + 8 + 8 + 4 + writestringlen(name) + writestringlen("");
  writeDataPhaseHeader(cmd, size);
  // StorageInfo, MTP 1.1 spec, page 46
  write16(storage_.readonly(store) ? 0x0001
                                    : 0x0004); // storage type (removable RAM)
  write16(storage_.has_directories(store)
              ? 0x0002
              : 0x0001); // filesystem type (generic hierarchical)
  write16(0x0000);       // access capability (read-write)

  //elapsedMillis em;
  uint64_t ntotal = storage_.totalSize(store, mediaAccessAllowed);
  write64(ntotal); // max capacity
  uint64_t nused = storage_.usedSize(store, mediaAccessAllowed);
  write64((ntotal - nused)); // free space (100M)
  //printf("GetStorageInfo dt:%u tot:%lu, used: %lu\n", (uint32_t)em, ntotal, nused);
  write32(0xFFFFFFFFUL); // free space (objects)
  writestring(name); // storage descriptor
  writestring(""); // volume identifier (neither Windows nor Linux seem to use this)
  write_finish();
  printf("\t%x name:%s\n", storage, name);
  return MTP_RESPONSE_OK;
}

// GetNumObjects, MTP 1.1 spec, page 215
//   Command: 3 parameters: StorageID, [ObjectFormatCode], [Parent folder]
//   Data: none
//   Response: 1 parameter: NumObjects
uint32_t MTP_class::GetNumObjects(struct MTPContainer &cmd) {
  uint32_t storage = cmd.params[0];
  uint32_t format = cmd.params[1];
  uint32_t parent = cmd.params[2];
  if (format) {
    return MTP_RESPONSE_SPECIFICATION_BY_FORMAT_UNSUPPORTED;
  }
  unsigned int num = 0;
  uint32_t store = Storage2Store(storage);
  if (storage_.isMediaPresent(store)) {
    storage_.StartGetObjectHandles(store, parent);
    while (storage_.GetNextObjectHandle(store)) {
      num++;
    }
  }
  cmd.params[0] = num;
  return MTP_RESPONSE_OK | (1<<28);
}

// GetObjectHandles, MTP 1.1 spec, page 217
//   Command: 3 parameters: StorageID, [ObjectFormatCode], [Parent folder]
//   Data: Teensy->PC: ObjectHandle array
//   Response: no parameters
uint32_t MTP_class::GetObjectHandles(struct MTPContainer &cmd) {
  uint32_t storage = cmd.params[0];
  uint32_t format = cmd.params[1];
  uint32_t parent = cmd.params[2];
  if (format) {
    writeDataPhaseHeader(cmd, 4);
    write32(0); // empty ObjectHandle array
    write_finish();
    return MTP_RESPONSE_SPECIFICATION_BY_FORMAT_UNSUPPORTED;
  }
  const uint32_t store = Storage2Store(storage);
  uint32_t num_handles = 0;
  if (storage_.isMediaPresent(store)) {
    storage_.StartGetObjectHandles(store, parent);
    while (storage_.GetNextObjectHandle(store)) {
      num_handles++;
    }
  }
  writeDataPhaseHeader(cmd, 4 + num_handles*4);
  if (storage_.isMediaPresent(store)) {
    // ObjectHandle array, page 23 (ObjectHandle), page 20 (array)
    write32(num_handles);
    uint32_t handle;
    storage_.StartGetObjectHandles(store, parent);
    while ((handle = storage_.GetNextObjectHandle(store)) != 0) {
        write32(handle);
    }
  }
  write_finish();
  return MTP_RESPONSE_OK;
}

// GetDevicePropValue, MTP 1.1 spec, page 234
//   Command: 1 parameter: DevicePropCode
//   Data: Teensy->PC: DeviceProp Value
//   Response: no parameters
uint32_t MTP_class::GetDevicePropValue(struct MTPContainer &cmd) {
  const uint32_t property = cmd.params[0];
  switch (property) {
  case 0xd402: // friendly name
    writeDataPhaseHeader(cmd, writestringlen(MTP_NAME));
    // This is the name we'll actually see in the windows explorer.
    // Should probably be configurable.
    writestring(MTP_NAME);
    write_finish();
    return MTP_RESPONSE_OK;
    break;
  }
  writeDataPhaseHeader(cmd, 0);
  return MTP_RESPONSE_DEVICE_PROP_NOT_SUPPORTED;
}

// GetObjectPropDesc, MTP 1.1 spec, page 244
//   Command: 2 parameter: ObjectPropCode, Object Format Code
//   Data: Teensy->PC: ObjectPropDesc
//   Response: no parameters
uint32_t MTP_class::GetObjectPropDesc(struct MTPContainer &cmd) {
  uint32_t property = cmd.params[0];
  //uint32_t format = cmd.params[1]; // TODO: does this matter?
  uint32_t size;
  switch (property) {
  case MTP_PROPERTY_STORAGE_ID: // 0xDC01:
    size = 2 + 2 + 1 + 4 + 4 + 1;
    break;
  case MTP_PROPERTY_OBJECT_FORMAT: // 0xDC02:
    size = 2 + 2 + 1 + 2 + 4 + 1;
    break;
  case MTP_PROPERTY_PROTECTION_STATUS: // 0xDC03:
    size = 2 + 2 + 1 + 2 + 4 + 1;
    break;
  case MTP_PROPERTY_OBJECT_SIZE: // 0xDC04:
    size = 2 + 2 + 1 + 8 + 4 + 1;
    break;
  case MTP_PROPERTY_OBJECT_FILE_NAME: // 0xDC07:
    size = 2 + 2 + 1 + 1 + 4 + 1;
    break;
  case MTP_PROPERTY_DATE_CREATED: // 0xDC08:
    size = 2 + 2 + 1 + 1 + 4 + 1;
    break;
  case MTP_PROPERTY_DATE_MODIFIED: // 0xDC09:
    size = 2 + 2 + 1 + 1 + 4 + 1;
    break;
  case MTP_PROPERTY_PARENT_OBJECT: // 0xDC0B:
    size = 2 + 2 + 1 + 4 + 4 + 1;
    break;
  case MTP_PROPERTY_PERSISTENT_UID: // 0xDC41:
    size = 2 + 2 + 1 + 8 + 8 + 4 + 1;
    break;
  case MTP_PROPERTY_NAME: // 0xDC44:
    size = 2 + 2 + 1 + 1 + 4 + 1;
    break;
  default:
    size = 0;
    break;
  }
  writeDataPhaseHeader(cmd, size);
  if (size == 0) {
    write_finish(); // TODO: remove this when change to split header/data
    return MTP_RESPONSE_INVALID_OBJECT_PROP_CODE;
  }
  // ObjectPropDesc, MTP 1.1 spec, Table 5-1, page 56
  switch (property) {
  case MTP_PROPERTY_STORAGE_ID: // 0xDC01:
    write16(0xDC01);
    write16(0x006); // 6=uint32_t
    write8(0); // get
    write32(0);
    write32(0);
    write8(0);
    break;
  case MTP_PROPERTY_OBJECT_FORMAT: // 0xDC02:
    write16(0xDC02);
    write16(0x004); // 4=uint16_t
    write8(0); // get
    write16(0);
    write32(0);
    write8(0);
    break;
  case MTP_PROPERTY_PROTECTION_STATUS: // 0xDC03:
    write16(0xDC03);
    write16(0x004); // 4=uint16_t
    write8(0); // get
    write16(0);
    write32(0);
    write8(0);
    break;
  case MTP_PROPERTY_OBJECT_SIZE: // 0xDC04:
    write16(0xDC04);
    write16(0x008); // 8=uint64_t
    write8(0); // get
    write64(0);
    write32(0);
    write8(0);
    break;
  case MTP_PROPERTY_OBJECT_FILE_NAME: // 0xDC07:
    write16(0xDC07);
    write16(0xFFFF); // FFFF=string
    write8(1); // get/set
    write8(0);
    write32(0);
    write8(0);
    break;
  case MTP_PROPERTY_DATE_CREATED: // 0xDC08:
    write16(0xDC08);
    write16(0xFFFF); // FFFF=string
    write8(1); // get
    write8(0);
    write32(0);
    write8(0); // TODO: should this be 3 (Form Flag on page 56)
    break;
  case MTP_PROPERTY_DATE_MODIFIED: // 0xDC09:
    write16(0xDC09);
    write16(0xFFFF); // FFFF=string
    write8(1); // may be both get set?
    write8(0);
    write32(0);
    write8(0); // TODO: should this be 3 (Form Flag on page 56)
    break;
  case MTP_PROPERTY_PARENT_OBJECT: // 0xDC0B:
    write16(0xDC0B);
    write16(6); // 6=uint32_t
    write8(0); // get
    write32(0);
    write32(0);
    write8(0);
    break;
  case MTP_PROPERTY_PERSISTENT_UID: // 0xDC41:
    write16(0xDC41);
    write16(0x0A); // A=uint128_t
    write8(0); // get
    write64(0);
    write64(0);
    write32(0);
    write8(0);
    break;
  case MTP_PROPERTY_NAME: // 0xDC44:
    write16(0xDC44);
    write16(0xFFFF);
    write8(0); // get
    write8(0);
    write32(0);
    write8(0);
    break;
  }
  write_finish();
  return MTP_RESPONSE_OK;
}

// GetObjectPropValue, MTP 1.1 spec, page 245
//   Command: 2 parameters: ObjectHandle, ObjectPropCode
//   Data: Teensy->PC: ObjectProp Value
//   Response: no parameters
uint32_t MTP_class::GetObjectPropValue(struct MTPContainer &cmd) {
  const uint32_t handle = cmd.params[0];
  const uint32_t property = cmd.params[1];
  uint32_t data_size = 0;
  char name[MTP_MAX_FILENAME_LEN];
  uint64_t file_size;
  uint32_t parent;
  uint16_t store;
  uint32_t dt;
  DateTimeFields dtf;
  uint32_t storage = 0;
  bool info_needed = true;

  // first check if storage info is needed, and if data size is known
  switch (property) {
  case MTP_PROPERTY_STORAGE_ID: // 0xDC01:
    data_size = 4;
    break;
  case MTP_PROPERTY_OBJECT_FORMAT: // 0xDC02:
    data_size = 2;
    break;
  case MTP_PROPERTY_PROTECTION_STATUS: // 0xDC03:
    data_size = 2;
    info_needed = false;
    break;
  case MTP_PROPERTY_OBJECT_SIZE: // 0xDC04:
    data_size = 8;
    break;
  case MTP_PROPERTY_NAME: // 0xDC44:
  case MTP_PROPERTY_OBJECT_FILE_NAME: // 0xDC07:
    break;
  case MTP_PROPERTY_DATE_CREATED: // 0xDC08:
    if (storage_.getCreateTime(handle, dt)) {
      breakTime(dt, dtf);
      snprintf(name, MTP_MAX_FILENAME_LEN, "%04u%02u%02uT%02u%02u%02u",
               dtf.year + 1900, dtf.mon + 1, dtf.mday, dtf.hour, dtf.min,
               dtf.sec);
    } else {
      name[0] = 0;
    }
    data_size = writestringlen(name);
    info_needed = false;
    break;
  case MTP_PROPERTY_DATE_MODIFIED: // 0xDC09:
    if (storage_.getModifyTime(handle, dt)) {
      breakTime(dt, dtf);
      snprintf(name, MTP_MAX_FILENAME_LEN, "%04u%02u%02uT%02u%02u%02u",
               dtf.year + 1900, dtf.mon + 1, dtf.mday, dtf.hour, dtf.min,
               dtf.sec);
    } else {
      name[0] = 0;
    }
    data_size = writestringlen(name);
    info_needed = false;
    break;
  case MTP_PROPERTY_PARENT_OBJECT: // 0xDC0B:
    data_size = 4;
    break;
  case MTP_PROPERTY_PERSISTENT_UID: // 0xDC41:
    data_size = 4 + 4 + 4 + 4;
    break;
  }

  // get actual storage info, if needed
  if (info_needed) {
    storage_.GetObjectInfo(handle, name, &file_size, &parent, &store);
    if (property == MTP_PROPERTY_OBJECT_FILE_NAME || property == MTP_PROPERTY_NAME) {
      data_size = writestringlen(name);
    }
    storage = Store2Storage(store);
  }

  // begin data phase
  writeDataPhaseHeader(cmd, data_size);
  if (data_size == 0) {
    write_finish(); // TODO: remove this when change to split header/data
    return MTP_RESPONSE_INVALID_OBJECT_PROP_CODE;
  }

  // transmit actual data
  switch (property) {
  case MTP_PROPERTY_STORAGE_ID: // 0xDC01:
    write32(storage);
    break;
  case MTP_PROPERTY_OBJECT_FORMAT: // 0xDC02:
    write16((file_size == (uint64_t)-1) ? 0x3001 /*directory*/ : 0x3000 /*file*/);
    break;
  case MTP_PROPERTY_PROTECTION_STATUS: // 0xDC03:
    write16(0);
    break;
  case MTP_PROPERTY_OBJECT_SIZE: // 0xDC04:
    write64(file_size);
    printf("\tMTP_PROPERTY_OBJECT_SIZE: %s %llx\n", name, file_size);
    //write32(file_size & 0xfffffffful);
    //write32(file_size >> 32);
    break;
  case MTP_PROPERTY_OBJECT_FILE_NAME: // 0xDC07:
  case MTP_PROPERTY_NAME: // 0xDC44:
  case MTP_PROPERTY_DATE_CREATED: // 0xDC08:
  case MTP_PROPERTY_DATE_MODIFIED: // 0xDC09:
    writestring(name);
    break;
  case MTP_PROPERTY_PARENT_OBJECT: // 0xDC0B:
    write32((store == parent) ? 0 : parent);
    break;
  case MTP_PROPERTY_PERSISTENT_UID: // 0xDC41:
    write32(handle);
    write32(parent);
    write32(storage);
    write32(0);
    break;
  }
  write_finish();
  return MTP_RESPONSE_OK;
}

// SetObjectPropValue, MTP 1.1 spec, page 246
//   Command: 2 parameters: ObjectHandle, ObjectPropCode
//   Data: PC->Teensy: ObjectProp Value
//   Response: no parameters
uint32_t MTP_class::setObjectPropValue(struct MTPContainer &cmd) {
  uint32_t object_id = cmd.params[0];
  uint32_t property_code = cmd.params[1];

  struct MTPHeader header;
  if (!readDataPhaseHeader(&header)) return MTP_RESPONSE_INVALID_DATASET;

  if (property_code == 0xDC07) {
    char filename[MTP_MAX_FILENAME_LEN];
    if (readstring(filename, sizeof(filename))
     && (true)) {   // TODO: read complete function (handle ZLP)
      printf("setObjectPropValue, rename id=%x to \"%s\"\n", object_id, filename);
      storage_.rename(object_id, filename);
      return MTP_RESPONSE_OK;
    } else {
      return MTP_RESPONSE_OPERATION_NOT_SUPPORTED;
    }
  }
  read(NULL, header.len - sizeof(header)); // discard ObjectProp Value
  return MTP_RESPONSE_OPERATION_NOT_SUPPORTED;
}

// GetDevicePropDesc, MTP 1.1 spec, page 233
//   Command: 1 parameter: DevicePropCode
//   Data: Teensy->PC: DevicePropDesc
//   Response: no parameters
uint32_t MTP_class::GetDevicePropDesc(struct MTPContainer &cmd) {
  const uint32_t property = cmd.params[0];
  switch (property) {
  case 0xd402: // friendly name
    writeDataPhaseHeader(cmd, 5 + writestringlen(MTP_NAME)*2 + 1);
    // DevicePropDesc Dataset, MTP 1.1 spec, page 42
    write16(property);     // Device Property Code
    write16(0xFFFF);       // Datatype, string type
    write8(0);             // read-only
    writestring(MTP_NAME); // Factory Default Value
    writestring(MTP_NAME); // Current Value
    write8(0);             // no form
    write_finish();
    return MTP_RESPONSE_OK;
  }
  writeDataPhaseHeader(cmd, 0);
  return MTP_RESPONSE_DEVICE_PROP_NOT_SUPPORTED;
}

// GetObjectPropsSupported, MTP 1.1 spec, page 243
//   Command: 1 parameter: ObjectFormatCode
//   Data: Teensy->PC: ObjectPropCode Array
//   Response: no parameters
uint32_t MTP_class::GetObjectPropsSupported(struct MTPContainer &cmd) {
  PROGMEM static const uint16_t propertyList[] = {
    MTP_PROPERTY_STORAGE_ID,        // 0xDC01
    MTP_PROPERTY_OBJECT_FORMAT,     // 0xDC02
    MTP_PROPERTY_PROTECTION_STATUS, // 0xDC03
    MTP_PROPERTY_OBJECT_SIZE,       // 0xDC04
    MTP_PROPERTY_OBJECT_FILE_NAME,  // 0xDC07
    MTP_PROPERTY_DATE_CREATED,      // 0xDC08
    MTP_PROPERTY_DATE_MODIFIED,     // 0xDC09
    MTP_PROPERTY_PARENT_OBJECT,     // 0xDC0B
    MTP_PROPERTY_PERSISTENT_UID,    // 0xDC41
    MTP_PROPERTY_NAME               // 0xDC44
  };
  const uint32_t propertyListNum = sizeof(propertyList) / sizeof(propertyList[0]);
  //uint32_t format = cmd.params[0]; // TODO: does this matter?
  writeDataPhaseHeader(cmd, 4 + sizeof(propertyList));
  write32(propertyListNum);
  write(propertyList, sizeof(propertyList));
  write_finish();
  return MTP_RESPONSE_OK;
}

// GetDeviceInfo, MTP 1.1 spec, page 210
//   Command: no parameters
//   Data: Teensy->PC: DeviceInfo
//   Response: no parameters
uint32_t MTP_class::GetDeviceInfo(struct MTPContainer &cmd) {
  PROGMEM static const unsigned short supported_op[] = {
    MTP_OPERATION_GET_DEVICE_INFO,  // 0x1001
    MTP_OPERATION_OPEN_SESSION,     // 0x1002
    MTP_OPERATION_CLOSE_SESSION,    // 0x1003
    MTP_OPERATION_GET_STORAGE_IDS,  // 0x1004
    MTP_OPERATION_GET_STORAGE_INFO, // 0x1005
    // MTP_OPERATION_GET_NUM_OBJECTS                        ,//0x1006
    MTP_OPERATION_GET_OBJECT_HANDLES, // 0x1007
    MTP_OPERATION_GET_OBJECT_INFO,    // 0x1008
    MTP_OPERATION_GET_OBJECT,         // 0x1009
    // MTP_OPERATION_GET_THUMB                              ,//0x100A
    MTP_OPERATION_DELETE_OBJECT,         // 0x100B
    MTP_OPERATION_SEND_OBJECT_INFO,      // 0x100C
    MTP_OPERATION_SEND_OBJECT,           // 0x100D
    MTP_OPERATION_FORMAT_STORE,          // 0x100F
    MTP_OPERATION_GET_DEVICE_PROP_DESC,  // 0x1014
    MTP_OPERATION_GET_DEVICE_PROP_VALUE, // 0x1015
    // MTP_OPERATION_SET_DEVICE_PROP_VALUE                  ,//0x1016
    // MTP_OPERATION_RESET_DEVICE_PROP_VALUE                ,//0x1017
    MTP_OPERATION_MOVE_OBJECT,        // 0x1019
    MTP_OPERATION_COPY_OBJECT,        // 0x101A
    MTP_OPERATION_GET_PARTIAL_OBJECT, // 0x101B
    MTP_OPERATION_GET_OBJECT_PROPS_SUPPORTED, // 0x9801
    MTP_OPERATION_GET_OBJECT_PROP_DESC,       // 0x9802
    MTP_OPERATION_GET_OBJECT_PROP_VALUE,      // 0x9803
    MTP_OPERATION_SET_OBJECT_PROP_VALUE       // 0x9804
    // MTP_OPERATION_GET_OBJECT_PROP_LIST                   ,//0x9805
    // MTP_OPERATION_GET_OBJECT_REFERENCES                  ,//0x9810
    // MTP_OPERATION_SET_OBJECT_REFERENCES                  ,//0x9811
    // MTP_OPERATION_GET_PARTIAL_OBJECT_64                  ,//0x95C1
    // MTP_OPERATION_SEND_PARTIAL_OBJECT                    ,//0x95C2
    // MTP_OPERATION_TRUNCATE_OBJECT                        ,//0x95C3
    // MTP_OPERATION_BEGIN_EDIT_OBJECT                      ,//0x95C4
    // MTP_OPERATION_END_EDIT_OBJECT                         //0x95C5
  };
  const int supported_op_num = sizeof(supported_op) / sizeof(supported_op[0]);
  PROGMEM static const uint16_t supported_events[] = {
    //    MTP_EVENT_UNDEFINED                         ,//0x4000
    MTP_EVENT_CANCEL_TRANSACTION, // 0x4001
    MTP_EVENT_OBJECT_ADDED,       // 0x4002
    MTP_EVENT_OBJECT_REMOVED,     // 0x4003
    MTP_EVENT_STORE_ADDED,        // 0x4004
    MTP_EVENT_STORE_REMOVED,      // 0x4005
    //    MTP_EVENT_DEVICE_PROP_CHANGED               ,//0x4006
    //    MTP_EVENT_OBJECT_INFO_CHANGED               ,//0x4007
    //    MTP_EVENT_DEVICE_INFO_CHANGED               ,//0x4008
    //    MTP_EVENT_REQUEST_OBJECT_TRANSFER           ,//0x4009
    //    MTP_EVENT_STORE_FULL                        ,//0x400A
    MTP_EVENT_DEVICE_RESET,         // 0x400B
    MTP_EVENT_STORAGE_INFO_CHANGED, // 0x400C
    //    MTP_EVENT_CAPTURE_COMPLETE                  ,//0x400D
    MTP_EVENT_UNREPORTED_STATUS,   // 0x400E
    MTP_EVENT_OBJECT_PROP_CHANGED, // 0xC801
    //    MTP_EVENT_OBJECT_PROP_DESC_CHANGED          ,//0xC802
    //    MTP_EVENT_OBJECT_REFERENCES_CHANGED          //0xC803
  };
  const int supported_event_num = sizeof(supported_events) / sizeof(supported_events[0]);
  char buf[20];
  dtostrf((float)(TEENSYDUINO / 100.0f), 3, 2, buf);
  strlcat(buf, " / MTP " MTP_VERS, sizeof(buf));
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
  char sernum[10];
  for (size_t i = 0; i < 10; i++)
    sernum[i] = usb_string_serial_number.wString[i];
#pragma GCC diagnostic pop
  // DeviceInfo Dataset, MTP 1.1 spec, page 40
  uint32_t size = 2 + 4 + 2 + writestringlen("microsoft.com: 1.0;") + 2
                  + 4 + sizeof(supported_op)
                  + 4 + sizeof(supported_events)
                  + 4 + 2 + 4 + 4 + 2*2
                  + writestringlen(MTP_MANUF)
                  + writestringlen(MTP_MODEL)
                  + writestringlen(buf)
                  + writestringlen(sernum);
  printf("GetDeviceInfo size=%u\n", size);
  writeDataPhaseHeader(cmd, size);
  write16(100);           // MTP version
  write32(6);             // MTP extension
  write16(100);           // MTP version
  writestring("microsoft.com: 1.0;");
  write16(1);             // functional mode
  write32(supported_op_num); // Supported operations (array of uint16)
  write(supported_op, sizeof(supported_op));
  write32(supported_event_num); // Events (array of uint16)
  write(supported_events, sizeof(supported_events));
  write32(1);             // Device properties (array of uint16)
  write16(0xd402);        // Device friendly name
  write32(0);             // Capture formats (array of uint16)
  write32(2);             // Playback formats (array of uint16)
  write16(0x3000);        // Undefined format
  write16(0x3001);        // Folders (associations)
  writestring(MTP_MANUF); // Manufacturer
  writestring(MTP_MODEL); // Model
  writestring(buf);       // version
  writestring(sernum);    // serial number
  write_finish();
  return MTP_RESPONSE_OK;
}

// OpenSession, MTP 1.1 spec, page 211
//   Command: 1 parameter: SessionID
//   Data: none
//   Response: no parameters
uint32_t MTP_class::OpenSession(struct MTPContainer &cmd) {
  sessionID_ = cmd.params[0];
  storage_.ResetIndex();
  return MTP_RESPONSE_OK;
}






//***************************************************************************
//  Generic data read / write
//***************************************************************************


bool MTP_class::readDataPhaseHeader(struct MTPHeader *header) {
  if (!read(header, sizeof(struct MTPHeader))) return false;
  if (header && header->type != MTP_CONTAINER_TYPE_DATA) return false;
  // TODO: when we later implement split header + data USB optimization
  //       described in MTP 1.1 spec pages 281-282, we should check that
  //       receive_buffer.data is NULL.  Return false if unexpected data.
  return true;
}

bool MTP_class::readstring(char *buffer, uint32_t buffer_size) {
  uint8_t len;
  if (!read8(&len)) return false;
  if (len == 0) {
    if (buffer) *buffer = 0; // empty string
    return true;
  }
  unsigned int buffer_index = 0;
  for (unsigned int string_index = 0; string_index < len; string_index++) {
    uint16_t c;
    if (!read16(&c)) return false;
    if (string_index == (unsigned)(len-1) && c != 0) return false; // last char16 must be zero
    if (buffer) {
      // encode Unicode16 -> UTF8
      if (c < 0x80 && buffer_index < buffer_size-2) {
        buffer[buffer_index++] = c & 0x7F;
      } else if (c < 0x800 && buffer_index < buffer_size-3) {
        buffer[buffer_index++] = 0xC0 | ((c >> 6) & 0x1F);
        buffer[buffer_index++] = 0x80 | (c & 0x3F);
      } else if (buffer_index < buffer_size-4) {
        buffer[buffer_index++] = 0xE0 | ((c >> 12) & 0x0F);
        buffer[buffer_index++] = 0x80 | ((c >> 6) & 0x3F);
        buffer[buffer_index++] = 0x80 | (c & 0x3F);
      } else {
        while (buffer_index < buffer_size) buffer[buffer_index++] = 0;
        buffer = nullptr;
      }
    }
  }
  if (buffer) buffer[buffer_index] = 0; // redundant?? (last char16 must be zero)
  return true;
}

bool MTP_class::readDateTimeString(uint32_t *pdt) {
  char dtb[20]; // let it take care of the conversions.
  if (!readstring(dtb, sizeof(dtb))) return false;
  if (dtb[0] == 0) {
    // host sent empty string, use time from Teensy's RTC
    *pdt = Teensy3Clock.get();
    return true;
  }
  //printf("  DateTime string: %s\n", dtb);
  //                            01234567890123456
  // format of expected String: YYYYMMDDThhmmss.s
  if (strlen(dtb) < 15) return false;
  for (int i=0; i < 15; i++) {
    if (i == 8) {
      if (dtb[i] != 'T') return false;
    } else {
      if (dtb[i] < '0' || dtb[i] > '9') return false;
    }
  }
  DateTimeFields dtf;
  // Quick and dirty!
  uint16_t year = ((dtb[0] - '0') * 1000) + ((dtb[1] - '0') * 100) +
                  ((dtb[2] - '0') * 10) + (dtb[3] - '0');
  dtf.year = year - 1900;                               // range 70-206
  dtf.mon = ((dtb[4] - '0') * 10) + (dtb[5] - '0') - 1; // zero based not 1
  dtf.mday = ((dtb[6] - '0') * 10) + (dtb[7] - '0');
  dtf.wday = 0; // hopefully not needed...
  dtf.hour = ((dtb[9] - '0') * 10) + (dtb[10] - '0');
  dtf.min = ((dtb[11] - '0') * 10) + (dtb[12] - '0');
  dtf.sec = ((dtb[13] - '0') * 10) + (dtb[14] - '0');
  *pdt = makeTime(dtf);
  //printf(">> date/Time: %x %u/%u/%u %u:%u:%u\n", *pdt, dtf.mon + 1, dtf.mday,
         //year, dtf.hour, dtf.min, dtf.sec);
  return true;
}


bool MTP_class::read(void *ptr, uint32_t size) {
  char *data = (char *)ptr;
  while (size > 0) {
    if (receive_buffer.data == NULL) {
      if (!receive_bulk(100)) {
        if (data) memset(data, 0, size);
        return false;
      }
    }
    // TODO: what happens if read spans multiple packets?  Do any cases exist?
    uint32_t to_copy = receive_buffer.len - receive_buffer.index;
    if (to_copy > size) to_copy = size;
    if (data) {
      memcpy(data, receive_buffer.data + receive_buffer.index, to_copy);
      data += to_copy;
    }
    size -= to_copy;
    receive_buffer.index += to_copy;
    if (receive_buffer.index >= receive_buffer.len) {
      free_received_bulk();
    }
  }
  return true;
}




void MTP_class::writeDataPhaseHeader(struct MTPContainer &container, uint32_t data_size)
{
  container.len = data_size + 12;
  container.type = MTP_CONTAINER_TYPE_DATA;
  // container.op reused from received command container
  // container.transaction_id reused from received command container
  write(&container, 12);
  // TODO: when we later implement split header + data USB optimization
  //       described in MTP 1.1 spec pages 281-282, we will need to
  //       call transmit_bulk() here to transmit a partial packet
}


static int utf8_strlen(const char *str) {
  if (!str) return 0;
  int len=0, count=0;
  while (1) {
    unsigned int c = *str++;
    if (c == 0) return len;
    if ((c & 0x80) == 0) {
      len++;
      count = 0;
    } else if ((c & 0xC0) == 0x80 && count > 0) {
      if (--count == 0) len++;
    } else if ((c & 0xE0) == 0xC0) {
      count = 1;
    } else if ((c & 0xF0) == 0xE0) {
      count = 2;
    } else {
      count = 0;
    }
  }
}

void MTP_class::writestring(const char *str) {
  int len = utf8_strlen(str);
  if (len > 0) {
    write8(len + 1);
    int count = 0;
    uint16_t char16 = 0;
    while (1) {
      unsigned int c = *str++;
      if (c == 0) break;
      if ((c & 0x80) == 0) { // chars 1-127
        write16(c);
        count = 0;
      } else if ((c & 0xC0) == 0x80 && count > 0) { // extra 6 bits
        char16 = (char16 << 6) | (c & 0x3F);
        if (--count == 0) write16(char16);
      } else if ((c & 0xE0) == 0xC0) { // begin char 128-2047
        char16 = c & 0x1F;
        count = 1;
      } else if ((c & 0xF0) == 0xE0) { // begin char 2048-65535
        char16 = c & 0x0F;
        count = 2;
      } else { // chars 65536+ not supported
        count = 0;
      }
    }
    write16(0);
  } else {
    write8(0);
  }
}

uint32_t MTP_class::writestringlen(const char *str) {
  int len = utf8_strlen(str);
  if (len == 0) return 1;
  return len*2 + 2 + 1;
}

size_t MTP_class::write(const void *ptr, size_t len) {
  size_t len_in = len;
  const char *data = (const char *)ptr;
  while (len > 0) {
    if (usb_mtp_status != 0x01) {
      printf("write, abort\n");
      return 0;
    }

    if (transmit_buffer.data == NULL) allocate_transmit_bulk();
    unsigned int avail = transmit_buffer.size - transmit_buffer.len;
    unsigned int to_copy = len;
    if (to_copy > avail) to_copy = avail;
    memcpy(transmit_buffer.data + transmit_buffer.len, data, to_copy);
    data += to_copy;
    len -= to_copy;
    transmit_buffer.len += to_copy;
    if (transmit_buffer.len >= transmit_buffer.size) {
      transmit_bulk();
    }
  }
  return len_in; // for now we are not detecting errors.
}

void MTP_class::write_finish() {
  if (transmit_buffer.data == NULL) {
    if (!write_transfer_open) return;
    printf("send a ZLP\n");
    allocate_transmit_bulk();
  }
  transmit_bulk();
}




//***************************************************************************
//  USB bulk endpoint low-level input & output
//***************************************************************************

#if defined(__MK20DX128__) || defined(__MK20DX256__) ||                        \
    defined(__MK64FX512__) || defined(__MK66FX1M0__)

bool MTP_class::receive_bulk(uint32_t timeout) { // T3
  elapsedMillis msec = 0;
  while (msec <= timeout) {
    usb_packet_t *packet = usb_rx(MTP_RX_ENDPOINT);
    if (packet) {
      receive_buffer.len = packet->len;
      receive_buffer.index = 0;
      receive_buffer.size = sizeof(packet->buf);
      receive_buffer.data = packet->buf;
      receive_buffer.usb = packet;
      return true;
    }
  }
  return false;
}

void MTP_class::free_received_bulk() { // T3
  if (receive_buffer.usb) {
    usb_free((usb_packet_t *)receive_buffer.usb);
  }
  receive_buffer.len = 0;
  receive_buffer.data = NULL;
  receive_buffer.usb = NULL;
}

void MTP_class::allocate_transmit_bulk() { // T3
  while (1) {
    usb_packet_t *packet = usb_malloc();
    if (packet) {
      transmit_buffer.len = 0;
      transmit_buffer.index = 0;
      transmit_buffer.size = sizeof(packet->buf);
      transmit_buffer.data = packet->buf;
      transmit_buffer.usb = packet;
      return;
    }
    mtp_yield();
  }
}

int MTP_class::transmit_bulk() { // T3
  usb_packet_t *packet = (usb_packet_t *)transmit_buffer.usb;
  int len = transmit_buffer.len;
  packet->len = len;
  write_transfer_open = (len == 64);
  usb_tx(MTP_TX_ENDPOINT, packet);
  transmit_buffer.len = 0;
  transmit_buffer.index = 0;
  transmit_buffer.data = NULL;
  transmit_buffer.usb = NULL;
  return len;
}

// TODO: core library not yet implementing cancel on Teensy 3.x
uint8_t MTP_class::usb_mtp_status = 0x01;


#elif defined(__IMXRT1062__)

bool MTP_class::receive_bulk(uint32_t timeout) { // T4
  if (usb_mtp_status != 0x01) {
    receive_buffer.data = NULL;
    return false;
  }
  receive_buffer.index = 0;
  receive_buffer.size = MTP_RX_SIZE;
  receive_buffer.usb = NULL;
  receive_buffer.len = usb_mtp_recv(rx_data_buffer, timeout);
  if (receive_buffer.len > 0) {
    // FIXME: need way to receive ZLP
    receive_buffer.data = rx_data_buffer;
    return true;
  } else {
    receive_buffer.data = NULL;
    return false;
  }
}

void MTP_class::free_received_bulk() { // T4
  receive_buffer.len = 0;
  receive_buffer.data = NULL;
}

void MTP_class::allocate_transmit_bulk() { // T4
  transmit_buffer.len = 0;
  transmit_buffer.index = 0;
  transmit_buffer.size = usb_mtp_txSize();
  transmit_buffer.data = tx_data_buffer;
  transmit_buffer.usb = NULL;
}

int MTP_class::transmit_bulk() { // T4
  int r = 0;
  if (usb_mtp_status == 0x01) {
    write_transfer_open = (transmit_buffer.len > 0 && (transmit_buffer.len & transmit_packet_size_mask) == 0);
    usb_mtp_send(transmit_buffer.data, transmit_buffer.len, 50);
  }
  transmit_buffer.len = 0;
  transmit_buffer.index = 0;
  transmit_buffer.data = NULL;
  return r;
}

#endif // __IMXRT1062__




//***************************************************************************
//  MTP Events - inform the host of changes Teensy makes to files
//***************************************************************************


#if USE_EVENTS == 1

#if defined(__MK20DX128__) || defined(__MK20DX256__) ||                        \
    defined(__MK64FX512__) || defined(__MK66FX1M0__)

#include "usb_mtp.h"
extern "C" {
usb_packet_t *tx_event_packet = NULL;

int usb_init_events(void) { // T3
  //     tx_event_packet = usb_malloc();
  //     if(tx_event_packet) return 1; else return 0;
  return 1;
}

#define EVENT_TX_PACKET_LIMIT 4

int usb_mtp_sendEvent(const void *buffer, uint32_t len, uint32_t timeout) { // T3
//  digitalWriteFast(4, HIGH);
  usb_packet_t *event_packet;
  // printf("usb_mtp_sendEvent: called %x %x\n", (uint32_t)buffer, len);
  struct MTPContainer {
    uint32_t len;            // 0
    uint16_t type;           // 4
    uint16_t op;             // 6
    uint32_t transaction_id; // 8
    uint32_t params[5];      // 12
  } __attribute__((__may_alias__));

  //const MTPContainer *pe = (const MTPContainer *)buffer;
  // printf("  op:%x len:%d type:%d tid:%d Params:  ", pe->op, pe->len,
  // pe->type, pe->transaction_id);
  //if(pe->len>12) printf(" %x", pe->params[0]);
  //if(pe->len>16) printf(" %x", pe->params[1]);
  //if(pe->len>20) printf(" %x", pe->params[2]);
  //printf("\n");

  if (!usb_configuration)
    return -1;
  elapsedMillis em = 0;
  while (1) {
    if (!usb_configuration) {
//      digitalWriteFast(4, LOW);
      return -1;
    }
    if (usb_tx_packet_count(MTP_EVENT_ENDPOINT) < EVENT_TX_PACKET_LIMIT) {
      event_packet = usb_malloc();
      if (event_packet)
        break;
    }
    if (em > timeout) {
//    digitalWriteFast(4, LOW);
      return -1;
    }
    yield();
  }

  memcpy(event_packet->buf, buffer, len);
  event_packet->len = len;
  usb_tx(MTP_EVENT_ENDPOINT, event_packet);
//  digitalWriteFast(4, LOW);
  return len;
}
} // extern c

#elif defined(__IMXRT1062__)
// keep this here until cores is upgraded

#include "usb_mtp.h"
extern "C" {
static transfer_t tx_event_transfer[1] __attribute__((used, aligned(32)));
static uint8_t tx_event_buffer[MTP_EVENT_SIZE]
    __attribute__((used, aligned(32)));

int usb_init_events(void) { // T4
  // usb_config_tx(MTP_EVENT_ENDPOINT, MTP_EVENT_SIZE, 0, txEvent_event);
  //
  // usb_config_rx(MTP_EVENT_ENDPOINT, MTP_EVENT_SIZE, 0, rxEvent_event);
  // usb_prepare_transfer(rx_event_transfer + 0, rx_event_buffer,
  // MTP_EVENT_SIZE, 0);
  // usb_receive(MTP_EVENT_ENDPOINT, rx_event_transfer + 0);
  return 1;
}

static int usb_mtp_wait(transfer_t *xfer, uint32_t timeout) { // T4
  uint32_t wait_begin_at = systick_millis_count;
  while (1) {
    if (!usb_configuration)
      return -1; // usb not enumerated by host
    uint32_t status = usb_transfer_status(xfer);
    if (!(status & 0x80))
      break; // transfer descriptor ready
    if (systick_millis_count - wait_begin_at > timeout)
      return 0;
    yield();
  }
  return 1;
}

int usb_mtp_recvEvent(void *buffer, uint32_t len, uint32_t timeout) { // T4
#if 0
      int ret= usb_mtp_wait(rx_event_transfer, timeout); if(ret<=0) return ret;

      memcpy(buffer, rx_event_buffer, len);
      memset(rx_event_transfer, 0, sizeof(rx_event_transfer));

      NVIC_DISABLE_IRQ(IRQ_USB1);
      usb_prepare_transfer(rx_event_transfer + 0, rx_event_buffer, MTP_EVENT_SIZE, 0);
      usb_receive(MTP_EVENT_ENDPOINT, rx_event_transfer + 0);
      NVIC_ENABLE_IRQ(IRQ_USB1);
#endif
  return MTP_EVENT_SIZE;
}

int usb_mtp_sendEvent(const void *buffer, uint32_t len, uint32_t timeout) { // T4
  transfer_t *xfer = tx_event_transfer;
  int ret = usb_mtp_wait(xfer, timeout);
  if (ret <= 0)
    return ret;

  uint8_t *eventdata = tx_event_buffer;
  memcpy(eventdata, buffer, len);
  usb_prepare_transfer(xfer, eventdata, len, 0);
  usb_transmit(MTP_EVENT_ENDPOINT, xfer);
  return len;
}
}  // extern "C"

#endif // __IMXRT1062__



const uint32_t EVENT_TIMEOUT = 60;

int MTP_class::send_Event(uint16_t eventCode) {
  printf("*MTP_class::send_Event(%x)\n", eventCode);
  MTPContainer event;
  event.len = 12;
  event.op = eventCode;
  event.type = MTP_CONTAINER_TYPE_EVENT;
  event.transaction_id = TID;
  event.params[0] = 0;
  event.params[1] = 0;
  event.params[2] = 0;
  return usb_mtp_sendEvent((const void *)&event, event.len, EVENT_TIMEOUT);
}
int MTP_class::send_Event(uint16_t eventCode, uint32_t p1) {
  printf("*MTP_class::send_Event(%x) %x\n", eventCode, p1);
  MTPContainer event;
  event.len = 16;
  event.op = eventCode;
  event.type = MTP_CONTAINER_TYPE_EVENT;
  event.transaction_id = TID;
  event.params[0] = p1;
  event.params[1] = 0;
  event.params[2] = 0;
  return usb_mtp_sendEvent((const void *)&event, event.len, EVENT_TIMEOUT);
}
int MTP_class::send_Event(uint16_t eventCode, uint32_t p1, uint32_t p2) {
  printf("*MTP_class::send_Event(%x) %x %x\n", eventCode, p1, p2);
  MTPContainer event;
  event.len = 20;
  event.op = eventCode;
  event.type = MTP_CONTAINER_TYPE_EVENT;
  event.transaction_id = TID;
  event.params[0] = p1;
  event.params[1] = p2;
  event.params[2] = 0;
  return usb_mtp_sendEvent((const void *)&event, event.len, EVENT_TIMEOUT);
}
int MTP_class::send_Event(uint16_t eventCode, uint32_t p1, uint32_t p2,
                     uint32_t p3) {
  printf("*MTP_class::send_Event(%x) %x %x %x\n", eventCode, p1, p2, p3);
  MTPContainer event;
  event.len = 24;
  event.op = eventCode;
  event.type = MTP_CONTAINER_TYPE_EVENT;
  event.transaction_id = TID;
  event.params[0] = p1;
  event.params[1] = p2;
  event.params[2] = p3;
  return usb_mtp_sendEvent((const void *)&event, event.len, EVENT_TIMEOUT);
}

int MTP_class::send_DeviceResetEvent(void) {
  storage_ids_sent_ = false;  // clear it for now
  return send_Event(MTP_EVENT_DEVICE_RESET);
}
// following WIP
int MTP_class::send_StorageInfoChangedEvent(uint32_t p1) {
  return send_Event(MTP_EVENT_STORAGE_INFO_CHANGED, Store2Storage(p1));
}

// following not tested
int MTP_class::send_addObjectEvent(uint32_t p1) {
  return send_Event(MTP_EVENT_OBJECT_ADDED, p1);
}
int MTP_class::send_removeObjectEvent(uint32_t p1) {
  return send_Event(MTP_EVENT_OBJECT_REMOVED, p1);
}

int MTP_class::send_StoreAddedEvent(uint32_t store) {
  if (!storage_ids_sent_) return 0; // Don't need to send.

  return send_Event(MTP_EVENT_STORE_ADDED, Store2Storage(store));
}

int MTP_class::send_StoreRemovedEvent(uint32_t store) {
  if (!storage_ids_sent_) return 0; // Don't need to send.
  return send_Event(MTP_EVENT_STORE_REMOVED, Store2Storage(store));
}

bool MTP_class::send_addObjectEvent(uint32_t store, const char *pathname) {
  bool node_added = false;
  uint32_t handle =
      storage_.MapFileNameToIndex(store, pathname, true, &node_added);
  printf("notifyFileCreated: %x:%x maps to handle: %x\n", store, pathname,
         handle);
  if (handle != 0xFFFFFFFFUL) {
    send_addObjectEvent(handle);
    return true;
  }
  return false;
}

bool MTP_class::send_removeObjectEvent(uint32_t store, const char *pathname) {
  uint32_t handle =
      storage_.MapFileNameToIndex(store, pathname, false, nullptr);
  printf("notifyFileRemoved: %x:%x maps to handle: %x\n", store, pathname,
         handle);
  if (handle != 0xFFFFFFFFUL) {
    send_removeObjectEvent(handle);
    return true;
  }
  return false;
}

#endif // USE_EVENTS




//***************************************************************************
//  Debug printing
//***************************************************************************


void MTP_class::printFilesystemsInfo(Stream &stream) {
  unsigned int count = storage_.get_FSCount();
  stream.println();
  stream.print("Storage List, ");
  stream.print(count);
  stream.println(" Filesystems");
  for (unsigned int i=0; i < count; i++) {
    FS *fs = storage_.getStoreFS(i);
    if (fs != nullptr) {
      stream.print("  store:");
      stream.print(i);
      stream.print(" storage:");
      stream.print(Store2Storage(i), HEX);
      stream.print(" present:");
      stream.print(storage_.isMediaPresent(i) ? "Yes" : "No ");
      stream.print(" fs:");
      stream.print((uint32_t)fs, HEX);
      stream.print(" name:\"");
      stream.print(storage_.get_FSName(i));
      stream.print("\" fsname:\"");
      const char *volname = fs->name(); // requires updated core lib
      if (!volname) volname = "Untitled";
      stream.print(volname);
      stream.println("\"");
    }
  }
}

void MTP_class::printContainer(const void *container, const char *msg) {
  const struct MTPContainer *c = (const struct MTPContainer *)container;
#ifndef MTP_VERBOSE_PRINT_CONTAINER
  printf("%x %d %d %d: ", c->op, c->len, c->type, c->transaction_id);
  if (c->len > 12) {
    printf(" %x", c->params[0]);
  }
  if (c->len > 16) {
    printf(" %x", c->params[1]);
  }
  if (c->len > 20) {
    printf(" %x", c->params[2]);
  }
  printf("\n");
}
#else // MTP_VERBOSE_PRINT_CONTAINER
  int print_property_name = -1; // no
  if (msg) {
    printf("%s", msg);
    DBGPRINTF("%s", msg);
  }
  printf("%u ", millis());
  switch (c->type) {
  default:
    printf(" UNKWN: %x\n", c->type);
    DBGPRINTF("UNKWN: %x l:%d\n", c->op, c->len);
    //MemoryHexDump(*printStream_, (void*)c, 512, true);
    printf(" UNKWN: %x\n", c->type);  // print it again...
    break;
  case MTP_CONTAINER_TYPE_COMMAND:
    printf(F("CMD: "));
    DBGPRINTF("CMD: %x l:%d\n", c->op, c->len);
    break;
  case MTP_CONTAINER_TYPE_DATA:
    printf(F("DATA:"));
    DBGPRINTF("DATA: %x l:%d\n", c->op, c->len);
    break;
  case MTP_CONTAINER_TYPE_RESPONSE:
    printf(F("RESP:"));
    DBGPRINTF("RESP: %x l:%d\n", c->op, c->len);
    break;
  case MTP_CONTAINER_TYPE_EVENT:
    printf(F("EVENT: "));
    DBGPRINTF("EVENT: %x\n", c->op);
    break;
  }
  printf(F("%x"), c->op);
  switch (c->op) {
  case MTP_OPERATION_GET_DEVICE_INFO:
    printf(F("(GET_DEVICE_INFO)"));
    break;
  case MTP_OPERATION_OPEN_SESSION:
    printf(F("(OPEN_SESSION)"));
    break;
  case MTP_OPERATION_CLOSE_SESSION:
    printf(F("(CLOSE_SESSION)"));
    break;
  case MTP_OPERATION_GET_STORAGE_IDS:
    printf(F("(GET_STORAGE_IDS)"));
    break;
  case MTP_OPERATION_GET_STORAGE_INFO:
    printf(F("(GET_STORAGE_INFO)"));
    break;
  case MTP_OPERATION_GET_NUM_OBJECTS:
    printf(F("(GET_NUM_OBJECTS)"));
    break;
  case MTP_OPERATION_GET_OBJECT_HANDLES:
    printf(F("(GET_OBJECT_HANDLES)"));
    break;
  case MTP_OPERATION_GET_OBJECT_INFO:
    printf(F("(GET_OBJECT_INFO)"));
    break;
  case MTP_OPERATION_GET_OBJECT:
    printf(F("(GET_OBJECT)"));
    break;
  case MTP_OPERATION_GET_THUMB:
    printf(F("(GET_THUMB)"));
    break;
  case MTP_OPERATION_DELETE_OBJECT:
    printf(F("(DELETE_OBJECT)"));
    break;
  case MTP_OPERATION_SEND_OBJECT_INFO:
    printf(F("(SEND_OBJECT_INFO)"));
    break;
  case MTP_OPERATION_SEND_OBJECT:
    printf(F("(SEND_OBJECT)"));
    break;
  case MTP_OPERATION_INITIATE_CAPTURE:
    printf(F("(INITIATE_CAPTURE)"));
    break;
  case MTP_OPERATION_FORMAT_STORE:
    printf(F("(FORMAT_STORE)"));
    break;
  case MTP_OPERATION_RESET_DEVICE:
    printf(F("(RESET_DEVICE)"));
    break;
  case MTP_OPERATION_SELF_TEST:
    printf(F("(SELF_TEST)"));
    break;
  case MTP_OPERATION_SET_OBJECT_PROTECTION:
    printf(F("(SET_OBJECT_PROTECTION)"));
    break;
  case MTP_OPERATION_POWER_DOWN:
    printf(F("(POWER_DOWN)"));
    break;
  case MTP_OPERATION_GET_DEVICE_PROP_DESC:
    printf(F("(GET_DEVICE_PROP_DESC)"));
    break;
  case MTP_OPERATION_GET_DEVICE_PROP_VALUE:
    printf(F("(GET_DEVICE_PROP_VALUE)"));
    break;
  case MTP_OPERATION_SET_DEVICE_PROP_VALUE:
    printf(F("(SET_DEVICE_PROP_VALUE)"));
    break;
  case MTP_OPERATION_RESET_DEVICE_PROP_VALUE:
    printf(F("(RESET_DEVICE_PROP_VALUE)"));
    break;
  case MTP_OPERATION_TERMINATE_OPEN_CAPTURE:
    printf(F("(TERMINATE_OPEN_CAPTURE)"));
    break;
  case MTP_OPERATION_MOVE_OBJECT:
    printf(F("(MOVE_OBJECT)"));
    break;
  case MTP_OPERATION_COPY_OBJECT:
    printf(F("(COPY_OBJECT)"));
    break;
  case MTP_OPERATION_GET_PARTIAL_OBJECT:
    printf(F("(GET_PARTIAL_OBJECT)"));
    break;
  case MTP_OPERATION_INITIATE_OPEN_CAPTURE:
    printf(F("(INITIATE_OPEN_CAPTURE)"));
    break;
  case MTP_OPERATION_GET_OBJECT_PROPS_SUPPORTED:
    printf(F("(GET_OBJECT_PROPS_SUPPORTED)"));
    break;
  case MTP_OPERATION_GET_OBJECT_PROP_DESC:
    printf(F("(GET_OBJECT_PROP_DESC)"));
    print_property_name = 0;
    break;
  case MTP_OPERATION_GET_OBJECT_PROP_VALUE:
    printf(F("(GET_OBJECT_PROP_VALUE)"));
    print_property_name = 1;
    break;
  case MTP_OPERATION_SET_OBJECT_PROP_VALUE:
    printf(F("(SET_OBJECT_PROP_VALUE)"));
    break;
  case MTP_OPERATION_GET_OBJECT_PROP_LIST:
    printf(F("(GET_OBJECT_PROP_LIST)"));
    break;
  case MTP_OPERATION_SET_OBJECT_PROP_LIST:
    printf(F("(SET_OBJECT_PROP_LIST)"));
    break;
  case MTP_OPERATION_GET_INTERDEPENDENT_PROP_DESC:
    printf(F("(GET_INTERDEPENDENT_PROP_DESC)"));
    break;
  case MTP_OPERATION_SEND_OBJECT_PROP_LIST:
    printf(F("(SEND_OBJECT_PROP_LIST)"));
    break;
  case MTP_OPERATION_GET_OBJECT_REFERENCES:
    printf(F("(GET_OBJECT_REFERENCES)"));
    break;
  case MTP_OPERATION_SET_OBJECT_REFERENCES:
    printf(F("(SET_OBJECT_REFERENCES)"));
    break;
  case MTP_OPERATION_SKIP:
    printf(F("(SKIP)"));
    break;
  // RESPONSES
  case MTP_RESPONSE_UNDEFINED:
    printf(F("(RSP:UNDEFINED)"));
    break;
  case MTP_RESPONSE_OK:
    printf(F("(RSP:OK)"));
    break;
  case MTP_RESPONSE_GENERAL_ERROR:
    printf(F("(RSP:GENERAL_ERROR)"));
    break;
  case MTP_RESPONSE_SESSION_NOT_OPEN:
    printf(F("(RSP:SESSION_NOT_OPEN)"));
    break;
  case MTP_RESPONSE_INVALID_TRANSACTION_ID:
    printf(F("(RSP:INVALID_TRANSACTION_ID)"));
    break;
  case MTP_RESPONSE_OPERATION_NOT_SUPPORTED:
    printf(F("(RSP:OPERATION_NOT_SUPPORTED)"));
    break;
  case MTP_RESPONSE_PARAMETER_NOT_SUPPORTED:
    printf(F("(RSP:PARAMETER_NOT_SUPPORTED)"));
    break;
  case MTP_RESPONSE_INCOMPLETE_TRANSFER:
    printf(F("(RSP:INCOMPLETE_TRANSFER)"));
    break;
  case MTP_RESPONSE_INVALID_STORAGE_ID:
    printf(F("(RSP:INVALID_STORAGE_ID)"));
    break;
  case MTP_RESPONSE_INVALID_OBJECT_HANDLE:
    printf(F("(RSP:INVALID_OBJECT_HANDLE)"));
    break;
  case MTP_RESPONSE_DEVICE_PROP_NOT_SUPPORTED:
    printf(F("(RSP:DEVICE_PROP_NOT_SUPPORTED)"));
    break;
  case MTP_RESPONSE_INVALID_OBJECT_FORMAT_CODE:
    printf(F("(RSP:INVALID_OBJECT_FORMAT_CODE)"));
    break;
  case MTP_RESPONSE_STORAGE_FULL:
    printf(F("(RSP:STORAGE_FULL)"));
    break;
  case MTP_RESPONSE_OBJECT_WRITE_PROTECTED:
    printf(F("(RSP:OBJECT_WRITE_PROTECTED)"));
    break;
  case MTP_RESPONSE_STORE_READ_ONLY:
    printf(F("(RSP:STORE_READ_ONLY)"));
    break;
  case MTP_RESPONSE_ACCESS_DENIED:
    printf(F("(RSP:ACCESS_DENIED)"));
    break;
  case MTP_RESPONSE_NO_THUMBNAIL_PRESENT:
    printf(F("(RSP:NO_THUMBNAIL_PRESENT)"));
    break;
  case MTP_RESPONSE_SELF_TEST_FAILED:
    printf(F("(RSP:SELF_TEST_FAILED)"));
    break;
  case MTP_RESPONSE_PARTIAL_DELETION:
    printf(F("(RSP:PARTIAL_DELETION)"));
    break;
  case MTP_RESPONSE_STORE_NOT_AVAILABLE:
    printf(F("(RSP:STORE_NOT_AVAILABLE)"));
    break;
  case MTP_RESPONSE_SPECIFICATION_BY_FORMAT_UNSUPPORTED:
    printf(F("(RSP:SPECIFICATION_BY_FORMAT_UNSUPPORTED)"));
    break;
  case MTP_RESPONSE_NO_VALID_OBJECT_INFO:
    printf(F("(RSP:NO_VALID_OBJECT_INFO)"));
    break;
  case MTP_RESPONSE_INVALID_CODE_FORMAT:
    printf(F("(RSP:INVALID_CODE_FORMAT)"));
    break;
  case MTP_RESPONSE_UNKNOWN_VENDOR_CODE:
    printf(F("(RSP:UNKNOWN_VENDOR_CODE)"));
    break;
  case MTP_RESPONSE_CAPTURE_ALREADY_TERMINATED:
    printf(F("(RSP:CAPTURE_ALREADY_TERMINATED)"));
    break;
  case MTP_RESPONSE_DEVICE_BUSY:
    printf(F("(RSP:DEVICE_BUSY)"));
    break;
  case MTP_RESPONSE_INVALID_PARENT_OBJECT:
    printf(F("(RSP:INVALID_PARENT_OBJECT)"));
    break;
  case MTP_RESPONSE_INVALID_DEVICE_PROP_FORMAT:
    printf(F("(RSP:INVALID_DEVICE_PROP_FORMAT)"));
    break;
  case MTP_RESPONSE_INVALID_DEVICE_PROP_VALUE:
    printf(F("(RSP:INVALID_DEVICE_PROP_VALUE)"));
    break;
  case MTP_RESPONSE_INVALID_PARAMETER:
    printf(F("(RSP:INVALID_PARAMETER)"));
    break;
  case MTP_RESPONSE_SESSION_ALREADY_OPEN:
    printf(F("(RSP:SESSION_ALREADY_OPEN)"));
    break;
  case MTP_RESPONSE_TRANSACTION_CANCELLED:
    printf(F("(RSP:TRANSACTION_CANCELLED)"));
    break;
  case MTP_RESPONSE_SPECIFICATION_OF_DESTINATION_UNSUPPORTED:
    printf(F("(RSP:SPECIFICATION_OF_DESTINATION_UNSUPPORTED)"));
    break;
  case MTP_RESPONSE_INVALID_OBJECT_PROP_CODE:
    printf(F("(RSP:INVALID_OBJECT_PROP_CODE)"));
    break;
  case MTP_RESPONSE_INVALID_OBJECT_PROP_FORMAT:
    printf(F("(RSP:INVALID_OBJECT_PROP_FORMAT)"));
    break;
  case MTP_RESPONSE_INVALID_OBJECT_PROP_VALUE:
    printf(F("(RSP:INVALID_OBJECT_PROP_VALUE)"));
    break;
  case MTP_RESPONSE_INVALID_OBJECT_REFERENCE:
    printf(F("(RSP:INVALID_OBJECT_REFERENCE)"));
    break;
  case MTP_RESPONSE_GROUP_NOT_SUPPORTED:
    printf(F("(RSP:GROUP_NOT_SUPPORTED)"));
    break;
  case MTP_RESPONSE_INVALID_DATASET:
    printf(F("(RSP:INVALID_DATASET)"));
    break;
  case MTP_RESPONSE_SPECIFICATION_BY_GROUP_UNSUPPORTED:
    printf(F("(RSP:SPECIFICATION_BY_GROUP_UNSUPPORTED)"));
    break;
  case MTP_RESPONSE_SPECIFICATION_BY_DEPTH_UNSUPPORTED:
    printf(F("(RSP:SPECIFICATION_BY_DEPTH_UNSUPPORTED)"));
    break;
  case MTP_RESPONSE_OBJECT_TOO_LARGE:
    printf(F("(RSP:OBJECT_TOO_LARGE)"));
    break;
  case MTP_RESPONSE_OBJECT_PROP_NOT_SUPPORTED:
    printf(F("(RSP:OBJECT_PROP_NOT_SUPPORTED)"));
    break;
  case MTP_EVENT_UNDEFINED:
    printf(F("(EVT:UNDEFINED)"));
    break;
  case MTP_EVENT_CANCEL_TRANSACTION:
    printf(F("(EVT:CANCEL_TRANSACTION)"));
    break;
  case MTP_EVENT_OBJECT_ADDED:
    printf(F("(EVT:OBJECT_ADDED)"));
    break;
  case MTP_EVENT_OBJECT_REMOVED:
    printf(F("(EVT:OBJECT_REMOVED)"));
    break;
  case MTP_EVENT_STORE_ADDED:
    printf(F("(EVT:STORE_ADDED)"));
    break;
  case MTP_EVENT_STORE_REMOVED:
    printf(F("(EVT:STORE_REMOVED)"));
    break;
  case MTP_EVENT_DEVICE_PROP_CHANGED:
    printf(F("(EVT:DEVICE_PROP_CHANGED)"));
    break;
  case MTP_EVENT_OBJECT_INFO_CHANGED:
    printf(F("(EVT:OBJECT_INFO_CHANGED)"));
    break;
  case MTP_EVENT_DEVICE_INFO_CHANGED:
    printf(F("(EVT:DEVICE_INFO_CHANGED)"));
    break;
  case MTP_EVENT_REQUEST_OBJECT_TRANSFER:
    printf(F("(EVT:REQUEST_OBJECT_TRANSFER)"));
    break;
  case MTP_EVENT_STORE_FULL:
    printf(F("(EVT:STORE_FULL)"));
    break;
  case MTP_EVENT_DEVICE_RESET:
    printf(F("(EVT:DEVICE_RESET)"));
    break;
  case MTP_EVENT_STORAGE_INFO_CHANGED:
    printf(F("(EVT:STORAGE_INFO_CHANGED)"));
    break;
  case MTP_EVENT_CAPTURE_COMPLETE:
    printf(F("(EVT:CAPTURE_COMPLETE)"));
    break;
  case MTP_EVENT_UNREPORTED_STATUS:
    printf(F("(EVT:UNREPORTED_STATUS)"));
    break;
  case MTP_EVENT_OBJECT_PROP_CHANGED:
    printf(F("(EVT:OBJECT_PROP_CHANGED)"));
    break;
  case MTP_EVENT_OBJECT_PROP_DESC_CHANGED:
    printf(F("(EVT:OBJECT_PROP_DESC_CHANGED)"));
    break;
  case MTP_EVENT_OBJECT_REFERENCES_CHANGED:
    printf(F("(EVT:OBJECT_REFERENCES_CHANGED)"));
    break;
  }
  printf("l: %d", c->len);
  printf(F(" T:%x"), c->transaction_id);
  if (c->len >= 16)
    printf(F(" : %x"), c->params[0]);
  if (c->len >= 20)
    printf(F(" %x"), c->params[1]);
  if (c->len >= 24)
    printf(F(" %x"), c->params[2]);
  if (c->len >= 28)
    printf(F(" %x"), c->params[3]);
  if (c->len >= 32)
    printf(F(" %x"), c->params[4]);
  if (print_property_name >= 0) {
    switch (c->params[print_property_name]) {
    case MTP_PROPERTY_STORAGE_ID:
      printf(" (STORAGE_ID)");
      break;
    case MTP_PROPERTY_OBJECT_FORMAT:
      printf(" (FORMAT)");
      break;
    case MTP_PROPERTY_PROTECTION_STATUS:
      printf(" (PROTECTION)");
      break;
    case MTP_PROPERTY_OBJECT_SIZE:
      printf(" (SIZE)");
      break;
    case MTP_PROPERTY_OBJECT_FILE_NAME:
      printf(" (OBJECT NAME)");
      break;
    case MTP_PROPERTY_DATE_CREATED:
      printf(" (CREATED)");
      break;
    case MTP_PROPERTY_DATE_MODIFIED:
      printf(" (MODIFIED)");
      break;
    case MTP_PROPERTY_PARENT_OBJECT:
      printf(" (PARENT)");
      break;
    case MTP_PROPERTY_PERSISTENT_UID:
      printf(" (PERSISTENT_UID)");
      break;
    case MTP_PROPERTY_NAME:
      printf(" (NAME)");
      break;
    }
  }
  printf("\n");
}
#endif // MTP_VERBOSE_PRINT_CONTAINER



#endif // USB_MTPDISK or USB_MTPDISK_SERIAL
