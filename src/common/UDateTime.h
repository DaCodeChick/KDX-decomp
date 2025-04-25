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
	static ulonglong GetMicroseconds();
	static ulonglong GetMilliseconds();
	static ulonglong GetSeconds();
	static ulonglong GetUptime();
	static int DateToText(SCalendarDate &inInfo, void *outText, uint inMaxSize, uint inOptions);
};
