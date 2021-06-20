#pragma once

#include <Printable.h>
#include <WString.h>

class CrashReportClass: public Printable {
public:
	virtual size_t printTo(Print& p) const;
};

extern CrashReportClass CrashReport;
