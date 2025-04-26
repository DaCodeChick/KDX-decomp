#include "UDateTime.h"

static longlong _gLastRecorded, _gElapsed;

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

	int t = gettimeofday(&tv, &tz);
	return t ? 0 : tz.tz_minuteswest * -60;
#endif // _WIN32
}

longlong UDateTime::GetEllapsedTime(longlong inEpoch)
{
#ifdef _WIN32
	return (inEpoch / 10000) - 11644473600000LL;
#else
#endif // _WIN32
}

longlong UDateTime::GetMicroseconds()
{
#ifdef _WIN32
    FILETIME ft;
    longlong currentTime = *reinterpret_cast<longlong *>(&ft);

    GetSystemTimeAsFileTime(&ft);

    if (currentTime <= _gLastRecorded) 
    {
        _gLastRecorded = currentTime;
        return _gElapsed;
    }

    _gElapsed = (currentTime - _gLastRecorded) / 10;
    _gLastRecorded = currentTime;
    return _gElapsed;
#else
    timeval tv;
    timezone tz;

    if (gettimeofday(&tv, &tz) != 0)
	{
        tv.tv_sec = time(NULL);
        tv.tv_usec = 0;
    }

    longlong currentTime = tv.tv_sec * 1000000 + tv.tv_usec;

    if (currentTime <= _gLastRecorded)
    {
        _gLastRecorded = currentTime;
        return _gElapsed;
    }

    _gElapsed += currentTime - _gLastRecorded;
    _gLastRecorded = currentTime;
    return _gElapsed;
#endif // _WIN32
}
