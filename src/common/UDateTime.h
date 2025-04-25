#pragma once

#include "typedefs.h"

struct SCalendarDate
{
	short field0_0x0;
	short utcOffset;
	short year;
	short month;
	short day;
	short hour;
	short minute;
	short second;
	short weekDay;
};

class UDateTime
{
public:
	static int GetTimeZoneOffset();
	static ulonglong GetSeconds();
};
