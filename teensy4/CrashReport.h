#pragma once

#include <Printable.h>
#include <WString.h>

class CrashReportClass: public Printable {
public:
	virtual size_t printTo(Print& p) const;
	static void clear();
	operator bool();
	static void breadcrumb(unsigned int num, unsigned int value) {
		// crashreport_breadcrumbs_struct occupies exactly 1 cache row
		volatile struct crashreport_breadcrumbs_struct *bc =
			(struct crashreport_breadcrumbs_struct *)0x2027FFC0;
		if (num >= 1 && num <= 6) {
			num--;
			bc->value[num] = value;
			bc->bitmask |= (1 << num);
			bc->checksum = checksum(bc, 28);
			arm_dcache_flush((void *)bc, sizeof(struct crashreport_breadcrumbs_struct));
		}
	}
	static uint32_t checksum(volatile const void *data, int len) {
		volatile const uint16_t *p = (volatile const uint16_t *)data;
		uint32_t a=1, b=0; // Adler Fletcher kinda, len < 720 bytes
		while (len > 0) {
			a += *p++;
			b += a;
			len -= 2;
		}
		a = a & 65535;
		b = b & 65535;
		return a | (b << 16);
	}
};

extern CrashReportClass CrashReport;
