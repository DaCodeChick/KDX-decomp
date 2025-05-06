#include "UDateTime.h"

static int64_t _gLastRecorded, _gElapsed;

#ifndef _WIN32
#include <ctime>
#include <sys/time.h>
#endif // _WIN32

int UDateTime::GetTimeZoneOffset()
{
#ifdef _WIN32
	TIME_ZONE_INFORMATION tzi;

	if (GetTimeZoneInformation(&tzi) == TIME_ZONE_ID_DAYLIGHT)
		tzi.Bias += tzi.DaylightBias;
	return tzi.Bias * -60;
#else
	timeval tv;
	timezone tz;

	auto t = gettimeofday(&tv, &tz);
	return t ? 0 : tz.tz_minuteswest * -60;
#endif // _WIN32
}

int64_t UDateTime::GetMicroseconds()
{
#ifdef _WIN32
	FILETIME ft;
	auto currentTime = *reinterpret_cast<int64_t *>(&ft);

	GetSystemTimeAsFileTime(&ft);

	if (currentTime <= _gLastRecorded)
	{
		_gLastRecorded = currentTime;
		return _gElapsed;
	}

	_gElapsed = (currentTime - _gLastRecorded) / 10;
#else
	timeval tv;
	timezone tz;

	if (gettimeofday(&tv, &tz) != 0)
	{
		tv.tv_sec = time(NULL);
		tv.tv_usec = 0;
	}

	auto currentTime = tv.tv_sec * 1000000 + tv.tv_usec;

	if (currentTime <= _gLastRecorded)
	{
		_gLastRecorded = currentTime;
		return _gElapsed;
	}

	_gElapsed += currentTime - _gLastRecorded;
#endif // _WIN32
	_gLastRecorded = currentTime;
	return _gElapsed;
}
