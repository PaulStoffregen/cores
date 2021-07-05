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
        float  temp;
        uint32_t time;
        uint32_t crc;
}; */
extern unsigned long _ebss;
extern "C" bool temperature_is_safe(void);
extern "C" uint32_t set_arm_clock(uint32_t frequency); // clockspeed.c

static int isvalid(const struct arm_fault_info_struct *info);
static void cleardata(struct arm_fault_info_struct *info);

FLASHMEM
size_t CrashReportClass::printTo(Print& p) const
{
  struct arm_fault_info_struct *info = (struct arm_fault_info_struct *)0x2027FF80;

  if (isvalid(info)) {
    p.println("CrashReport:");
    uint8_t ss = info->time % 60;
    info->time /= 60;
    uint8_t mm = info->time % 60;
    info->time /= 60;
    uint8_t hh = info->time % 24;
    p.print("  A problem occurred at (system time) ");
    p.print(hh);
    p.print(":");
    p.print(mm);
    p.print(":");
    p.println(ss);
    p.print("  Code was executing from address 0x");
    p.println(info->ret, HEX);
    //p.print("  length: ");
    //p.println(info->len);
    //p.print("  IPSR: ");
    //p.println(info->ipsr, HEX);

    uint32_t _CFSR = info->cfsr;
    if (_CFSR > 0) {
      p.print("  CFSR: ");
      p.println(info->cfsr, HEX);
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
        if (info->mmfar < 32) {
          p.print(" (nullptr)\n\t  Check code at 0x");
          p.print(info->ret, HEX);
          p.print(" - very likely a bug!\n\t  Run \"addr2line -e mysketch.ino.elf 0x");
          p.print(info->ret, HEX);
          p.print("\" for filename & line number.");
            // TODO: in some perfect future, maybe we'll build part of the ELF debug_line
            // section (maybe just the .ino files) into CrashReport and be able to report
            // the actual filename and line number.  Wouldn't that be awesome?!
        } else if ((info->mmfar >= (uint32_t)&_ebss) && (info->mmfar < (uint32_t)&_ebss + 32)) {
          p.print(" (Stack problem)\n\t  Check for stack overflows, array bounds, etc.");
        }
        p.println();
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

    p.print("  Temperature inside the chip was ");
    p.print(info->temp);
    p.print(" °C\n");

    // TODO: fault handler should read the CCM & PLL registers to log actual speed at crash
    p.print("  Startup CPU clock speed is ");
    p.print( F_CPU_ACTUAL/1000000);
    p.print( "MHz\n");


    //p.print("  MMFAR: ");
    //p.println(info->mmfar, HEX);
    //p.print("  BFAR: ");
    //p.println(info->bfar, HEX);
    //p.print("  return address: ");
    //p.println(info->ret, HEX);
    //p.print("  XPSR: ");
    //p.println(info->xpsr, HEX);
    //p.print("  crc: ");
    //p.println(info->crc, HEX);
  } else {
    p.println("No Crash Data To Report");
    p.println("  Hopefully all is well, but certain types of crashes can't be reported:");
    p.println("\tstuck in an infinite loop (technically, hardware still running properly)");
    p.println("\tremaining in a low power sleep mode");
    p.println("\taccess to certain peripherals without their clock enabled (eg, FlexIO)");
    p.println("\tchange of CPU or bus clock speed without use of glitchless mux");
  }
  uint32_t SRSR = SRC_SRSR;
  if (SRSR & SRC_SRSR_LOCKUP_SYSRESETREQ) {
    // use SRC_GPR5 to distinguish cases.  See pages 1290 & 1294 in ref manual
    uint32_t gpr5 = SRC_GPR5;
    if (gpr5 == 0x0BAD00F1) {
      p.println("  Reboot was caused by auto reboot after fault or bad interrupt detected");
    } else {
      p.println("  Reboot was caused by software write to SCB_AIRCR or CPU lockup");
    }
  }
  if (SRSR & SRC_SRSR_CSU_RESET_B) {
    p.println("  Reboot was caused by security monitor");
  }
  if (SRSR & SRC_SRSR_IPP_USER_RESET_B) {
    // This case probably can't occur on Teensy 4.x
    // because the bootloader chip monitors 3.3V power
    // and manages DCDC_PSWITCH and RESET, causing the
    // power on event to appear as a normal reset.
    p.println("  Reboot was caused by power on/off button");
  }
  if (SRSR & SRC_SRSR_WDOG_RST_B) {
    p.println("  Reboot was caused by watchdog 1 or 2");
  }
  if (SRSR & SRC_SRSR_JTAG_RST_B) {
    p.println("  Reboot was caused by JTAG boundary scan");
  }
  if (SRSR & SRC_SRSR_JTAG_SW_RST) {
    p.println("  Reboot was caused by JTAG debug");
  }
  if (SRSR & SRC_SRSR_WDOG3_RST_B) {
    p.println("  Reboot was caused by watchdog 3");
  }
  if (SRSR & SRC_SRSR_TEMPSENSE_RST_B) {
    p.println("  Reboot was caused by temperature sensor");
	  SRC_SRSR &= ~0x100u; /* Write 0 to clear. */
	  p.println("Panic Temp Exceeded Shutting Down");
	  p.println("Can be caused by Overclocking w/o Heatsink or other unknown reason");
	  IOMUXC_GPR_GPR16 = 0x00000007;
	  SNVS_LPCR |= SNVS_LPCR_TOP; //Switch off now
	  asm volatile ("dsb":::"memory");
	  while (1) asm ("wfi");
  }
  cleardata(info);
  return 1;
}

FLASHMEM
void CrashReportClass::clear()
{
  struct arm_fault_info_struct *info = (struct arm_fault_info_struct *)0x2027FF80;
  cleardata(info);
}

FLASHMEM
CrashReportClass::operator bool()
{
	struct arm_fault_info_struct *info = (struct arm_fault_info_struct *)0x2027FF80;
	if (isvalid(info)) return true;
	return false;
}

FLASHMEM
static int isvalid(const struct arm_fault_info_struct *info)
{
	uint32_t i, crc;
	const uint32_t *data, *end;

	if (info->len != sizeof(*info) / 4) return 0;
	data = (uint32_t *)info;
	end = data + (sizeof(*info) / 4 - 1);
	crc = 0xFFFFFFFF;
	while (data < end) {
		crc ^= *data++;
		for (i=0; i < 32; i++) crc = (crc >> 1) ^ (crc & 1)*0xEDB88320;
	}
	if (crc != info->crc) return 0;
	return 1;
}

FLASHMEM
static void cleardata(struct arm_fault_info_struct *info)
{
	info->len = 0;
	info->ipsr  = 0;
	info->cfsr  = 0;
	info->hfsr  = 0;
	info->mmfar = 0;
	info->bfar  = 0;
	info->ret = 0;
	info->xpsr  = 0;
	info->crc = 0;
	arm_dcache_flush_delete(info, sizeof(*info));
	SRC_SRSR = SRC_SRSR; // zeros all write-1-to-clear bits
	SRC_GPR5 = 0;
}



CrashReportClass CrashReport;
