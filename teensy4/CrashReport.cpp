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


size_t CrashReportClass::printTo(Print& p) const
{
	struct arm_fault_info_struct *info = (struct arm_fault_info_struct *)0x2027FF80;

	p.println("CrashReport ... Hello World");
	p.print("  length: ");
	p.println(info->len);
	p.print("  IPSR: ");
	p.println(info->ipsr, HEX);
	p.print("  CFSR: ");
	p.println(info->cfsr, HEX);
	p.print("  HTSR: ");
	p.println(info->hfsr, HEX);
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
	return 1;
}

CrashReportClass CrashReport;

