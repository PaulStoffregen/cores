#pragma once

#include <Printable.h>
#include <WString.h>

class CrashReportClass: public Printable {
public:
	virtual size_t printTo(Print& p) const;
	void clear();
	operator bool();
	void breadcrumb(unsigned int num, unsigned int value) {
		// crashreport_breadcrumbs_struct occupies exactly 1 cache row
		volatile struct crashreport_breadcrumbs_struct *bc =
			(struct crashreport_breadcrumbs_struct *)0x2027FFC0;
		if (num >= 1 && num <= 6) {
			num--;
			bc->value[num] = value;
			bc->bitmask |= (1 << num);
			arm_dcache_flush((void *)bc, sizeof(struct crashreport_breadcrumbs_struct));
		}
	}
};

extern CrashReportClass CrashReport;
