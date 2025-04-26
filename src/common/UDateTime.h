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
	static longlong GetMicroseconds();
	static longlong GetMilliseconds();
	static longlong GetEllapsedTime(longlong inEpoch);
	static longlong GetSeconds();
	static int DateToText(SCalendarDate &inInfo, void *outText, uint inMaxSize, uint inOptions);
};
