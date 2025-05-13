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

void UDateTime::TimestampToDate(uint64_t inTimestamp, SCalendarDate &outInfo)
{
	static constexpr uint64_t timestampBase[8] = {
	    0x000005BD7EC1FC00, 0x0000000000050834, 0x000002DEBCCDD000, 0x00000000000607D0,
	    0x0000029545956000, 0x00000000000107C6, 0x0000000000000000, 0x000000000001076C,
	};

	static constexpr uint32_t secs[13] = {
	    0x00000000, 0x0028DE80, 0x004DC880, 0x0076A700, 0x009E3400, 0x00C71280, 0x00EE9F80,
	    0x01177E00, 0x01405C80, 0x0167E980, 0x0190C800, 0x01B85500, 0x01E13380,
	};

	static constexpr uint32_t leapSecs[13] = {
	    0x00000000, 0x0028DE80, 0x004F1A00, 0x0077F880, 0x009F8580, 0x00C86400, 0x00EFF100,
	    0x0118CF80, 0x0141AE00, 0x01693B00, 0x01921980, 0x01B9A680, 0x01E28500,
	};

	const auto *yearData = timestampBase;
	while (inTimestamp < *yearData)
		yearData -= 2;

	auto baseTime = *yearData / 1000;
	auto timestampSeconds = inTimestamp / 1000;
	auto year = static_cast<uint32_t>(yearData[1]);
	auto dayOffset = 0;

	while (true)
	{
		auto isLeapYear = ((year >> 2) == 0 && year % 100 != 0) || (year % 400 == 0);
		auto yearSeconds = isLeapYear ? kLeapYear_Days * kDay_Seconds : kYear_Days * kDay_Seconds;

		if (timestampSeconds < baseTime + yearSeconds)
			break;

		baseTime += yearSeconds;
		dayOffset += isLeapYear ? kLeapYear_Days : kYear_Days;
		year++;
	}

	outInfo.year = static_cast<short>(year);

	auto remainingSeconds = static_cast<uint32_t>(timestampSeconds - baseTime);
	auto monthDays = ((year >> 2) == 0 && (year % 100 != 0 || year % 400 == 0)) ? leapSecs : secs;

	auto month = 0;
	while (remainingSeconds >= monthDays[month] * kDay_Seconds && month < 12)
	{
		remainingSeconds -= monthDays[month] * kDay_Seconds;
		month++;
	}

	outInfo.month = static_cast<short>(month + 1);
	outInfo.day = static_cast<short>(remainingSeconds / kDay_Seconds + 1);

	remainingSeconds %= kDay_Seconds;
	outInfo.hour = static_cast<short>(remainingSeconds / kHour_Seconds);
	remainingSeconds %= kHour_Seconds;
	outInfo.minute = static_cast<short>(remainingSeconds / kMinute_Seconds);
	outInfo.second = static_cast<short>(remainingSeconds % kMinute_Seconds);

	auto totalDays = dayOffset + (timestampSeconds / kDay_Seconds);
	outInfo.weekDay = static_cast<short>((totalDays & 7) + 1); // Assuming 1 = Monday, 7 = Sunday
}
