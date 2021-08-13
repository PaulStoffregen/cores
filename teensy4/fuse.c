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
