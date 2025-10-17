/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2019 PJRC.COM, LLC.
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

#include "core_pins.h"
#include "imxrt.h"

uint32_t IMXRTfuseRead(volatile uint32_t *fuses)
{
  if (((uint32_t)fuses & 0x0F) != 0) return 0; // illegal address
  uint32_t addr = ((uint32_t)fuses - (uint32_t)&HW_OCOTP_LOCK) >> 4;
  if (addr > 0x2F) return 0; // illegal address
  if (HW_OCOTP_CTRL & HW_OCOTP_CTRL_ERROR) {
    HW_OCOTP_CTRL_CLR = HW_OCOTP_CTRL_ERROR;
  }
  HW_OCOTP_CTRL = HW_OCOTP_CTRL_ADDR(addr);
  HW_OCOTP_READ_CTRL = HW_OCOTP_READ_CTRL_READ_FUSE;
  while (HW_OCOTP_CTRL & HW_OCOTP_CTRL_BUSY) ; // wait
  return HW_OCOTP_READ_FUSE_DATA;
}

void IMXRTfuseWrite(volatile uint32_t *fuses, uint32_t value)
{
  if (((uint32_t)fuses & 0x0F) != 0) return; // illegal address
  uint32_t oldvalue = IMXRTfuseRead(fuses);
  if ((oldvalue | value) == oldvalue) return; // no write needed
  uint32_t addr = ((uint32_t)fuses - (uint32_t)&HW_OCOTP_LOCK) >> 4;
  if (addr > 0x2F) return; // illegal address
  if (HW_OCOTP_CTRL & HW_OCOTP_CTRL_ERROR) {
    HW_OCOTP_CTRL_CLR = HW_OCOTP_CTRL_ERROR;
  }
  // TODO: abort writing to certain fuses known to brick Lockable Teensy
  HW_OCOTP_CTRL = HW_OCOTP_CTRL_WR_UNLOCK(0x3E77) | HW_OCOTP_CTRL_ADDR(addr);
  HW_OCOTP_DATA = value;
  while (HW_OCOTP_CTRL & HW_OCOTP_CTRL_BUSY) ; // wait
  delayMicroseconds(2);
  if (HW_OCOTP_CTRL & HW_OCOTP_CTRL_ERROR) return;
  *fuses = IMXRTfuseRead(fuses); // update shadow register
}

void IMXRTfuseReload()
{
  if (HW_OCOTP_CTRL & HW_OCOTP_CTRL_ERROR) {
    HW_OCOTP_CTRL_CLR = HW_OCOTP_CTRL_ERROR;
  }
  HW_OCOTP_CTRL = HW_OCOTP_CTRL_RELOAD_SHADOWS;
  while (HW_OCOTP_CTRL & (HW_OCOTP_CTRL_BUSY | HW_OCOTP_CTRL_RELOAD_SHADOWS)) ;
}
