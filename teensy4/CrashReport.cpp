#include <Arduino.h>
#include <CrashReport.h>

/* Crash report info stored in the top 128 bytes of OCRAM (at 0x2027FF80)
struct arm_fault_info_struct {
        uint32_t len;
        uint32_t ipsr;
        uint32_t cfsr;
        uint32_t hfsr;
        uint32_t mmfar;
        uint32_t bfar;
        uint32_t ret;
        uint32_t xpsr;
        uint32_t crc;
}; */
extern unsigned long _ebss;

size_t CrashReportClass::printTo(Print& p) const
{
  struct arm_fault_info_struct *info = (struct arm_fault_info_struct *)0x2027FF80;
  uint32_t i, crc;
  const uint32_t *pp, *end;
  crc = 0xFFFFFFFF;
  pp = (uint32_t *)info;
  end = pp + (sizeof(*info) / 4 - 1);
  while (pp < end) {
    crc ^= *pp++;
    for (i=0; i < 32; i++) crc = (crc >> 1) ^ (crc & 1)*0xEDB88320;
  }

  if( info->crc == crc ) {
    p.println("CrashReport ... Hello World");
    p.print("  length: ");
    p.println(info->len);
    p.print("  IPSR: ");
    p.println(info->ipsr, HEX);

    uint32_t _CFSR = info->cfsr;
    if (_CFSR > 0) {
      p.print("  CFSR: ");
      p.println(info->cfsr, HEX);
      if ((_CFSR & 0xff) > 0) {
      //Memory Management Faults
      if ((_CFSR & 1) == 1) {
        p.println("\t(IACCVIOL) Instruction Access Violation");
      } else  if (((_CFSR & (0x02)) >> 1) == 1) {
        p.println("\t(DACCVIOL) Data Access Violation");
      } else if (((_CFSR & (0x08)) >> 3) == 1) {
        p.println("\t(MUNSTKERR) MemMange Fault on Unstacking");
      } else if (((_CFSR & (0x10)) >> 4) == 1) {
        p.println("\t(MSTKERR) MemMange Fault on stacking");
      } else if (((_CFSR & (0x20)) >> 5) == 1) {
        p.println("\t(MLSPERR) MemMange Fault on FP Lazy State");
      }
      if (((_CFSR & (0x80)) >> 7) == 1) {
        p.print("\t(MMARVALID) Accessed Address: 0x");
        p.print(info->mmfar, HEX);
        if (info->mmfar < 32) p.print(" (nullptr)");
        if ((info->mmfar >= (uint32_t)&_ebss) && (info->mmfar < (uint32_t)&_ebss + 32))
        p.print(" (Stack problem)\n\tCheck for stack overflows, array bounds, etc.");
        p.println();
      }
      }
      //Bus Fault Status Register BFSR
      if (((_CFSR & 0x100) >> 8) == 1) {
      p.println("\t(IBUSERR) Instruction Bus Error");
      } else  if (((_CFSR & (0x200)) >> 9) == 1) {
      p.println("\t(PRECISERR) Data bus error(address in BFAR)");
      } else if (((_CFSR & (0x400)) >> 10) == 1) {
      p.println("\t(IMPRECISERR) Data bus error but address not related to instruction");
      } else if (((_CFSR & (0x800)) >> 11) == 1) {
      p.println("\t(UNSTKERR) Bus Fault on unstacking for a return from exception");
      } else if (((_CFSR & (0x1000)) >> 12) == 1) {
      p.println("\t(STKERR) Bus Fault on stacking for exception entry");
      } else if (((_CFSR & (0x2000)) >> 13) == 1) {
      p.println("\t(LSPERR) Bus Fault on FP lazy state preservation");
      }
      if (((_CFSR & (0x8000)) >> 15) == 1) {
      p.print("\t(BFARVALID) Accessed Address: 0x");
      p.println(info->bfar, HEX);
      }
      //Usage Fault Status Register UFSR
      if (((_CFSR & 0x10000) >> 16) == 1) {
      p.println("\t(UNDEFINSTR) Undefined instruction");
      } else  if (((_CFSR & (0x20000)) >> 17) == 1) {
      p.println("\t(INVSTATE) Instruction makes illegal use of EPSR)");
      } else if (((_CFSR & (0x40000)) >> 18) == 1) {
      p.println("\t(INVPC) Usage fault: invalid EXC_RETURN");
      } else if (((_CFSR & (0x80000)) >> 19) == 1) {
      p.println("\t(NOCP) No Coprocessor");
      } else if (((_CFSR & (0x1000000)) >> 24) == 1) {
      p.println("\t(UNALIGNED) Unaligned access UsageFault");
      } else if (((_CFSR & (0x2000000)) >> 25) == 1) {
      p.println("\t(DIVBYZERO) Divide by zero");
      }
    }

    uint32_t _HFSR = info->hfsr;
    if (_HFSR > 0) {
      p.print("  HTSR: ");
      p.println(info->hfsr, HEX);
      //Memory Management Faults
      if (((_HFSR & (0x02)) >> 1) == 1) {
      p.println("\t(VECTTBL) Bus Fault on Vec Table Read");
      } else if (((_HFSR & (0x40000000)) >> 30) == 1) {
       p.println("\t(FORCED) Forced Hard Fault");
      } else if (((_HFSR & (0x80000000)) >> 31) == 31) {
       p.println("\t(DEBUGEVT) Reserved for Debug");
      }
    }

    p.print("  MMFAR: ");
    p.println(info->mmfar, HEX);
    p.print("  BFAR: ");
    p.println(info->bfar, HEX);
    p.print("  return address: ");
    p.println(info->ret, HEX);
    p.print("  XPSR: ");
    p.println(info->xpsr, HEX);
    p.print("  crc: ");
    p.println(info->crc, HEX);
  } else {
    // p.println("Crash Report not Available");
  }
  return 1;
}

bool CrashReportClass::clear()
{
  struct arm_fault_info_struct *info = (struct arm_fault_info_struct *)0x2027FF80;
  uint32_t i, crc;
  const uint32_t *pp, *end;
  crc = 0xFFFFFFFF;
  pp = (uint32_t *)info;
  end = pp + (sizeof(*info) / 4 - 1);
  while (pp < end) {
    crc ^= *pp++;
    for (i=0; i < 32; i++) crc = (crc >> 1) ^ (crc & 1)*0xEDB88320;
  }

  if( info->crc == crc ) {
    info->len = 0;
    info->cfsr  = 0;
    arm_dcache_flush_delete(info, sizeof(*info));
    return true; // Crash was cleared
  }
  else
    return false; // Crash not present to be cleared
}

CrashReportClass CrashReport;
