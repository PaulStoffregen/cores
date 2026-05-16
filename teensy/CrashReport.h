#pragma once

#include <Printable.h>
#include <WString.h>

class CrashReportClass: public Printable {
public:
	size_t printTo(Print& p) const override;
	void clear();
	operator bool();
};

extern CrashReportClass CrashReport;
