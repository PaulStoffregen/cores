#pragma once

#include <Printable.h>
#include <WString.h>

class CrashReportClass: public Printable {
public:
	virtual size_t printTo(Print& p) const;
	virtual void clear();
};

extern CrashReportClass CrashReport;
