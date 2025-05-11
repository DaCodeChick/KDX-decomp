#pragma once

#include "typedefs.h"

enum
{
	kYear_Days = 365,     ///< Number of days in a common year
	kLeapYear_Days = 366, ///< Number of days in a leap year
	kDay_Seconds = 86400, ///< Number of seconds in a day
	kHour_Seconds = 3600, ///< Number of seconds in an hour
	kMinute_Seconds = 60, ///< Number of seconds in a minute
};

/// @brief Structure to hold calendar date information.
struct SCalendarDate
{
	short offs00;
	short utcOffset; ///< UTC offset in seconds
	short year;      ///< Year (e.g., 2023)
	short month;     ///< Month (1-12)
	short day;       ///< Day of the month (1-31)
	short hour;      ///< Hour (0-23)
	short minute;    ///< Minute (0-59)
	short second;    ///< Second (0-59)
	short weekDay;   ///< Day of the week (0-6, where 0 = Sunday)
};

/// @brief Class to handle date and time operations.
class UDateTime
{
public:
	/**
	 * @brief Get the current time zone offset in seconds
	 *
	 * @return Time zone offset in seconds
	 */
	[[nodiscard]] static int GetTimeZoneOffset();

	/**
	 * @brief Get current time in microseconds since epoch
	 *
	 * @return Current time in microseconds since epoch
	 */
	[[nodiscard]] static int64_t GetMicroseconds();

	/**
	 * @brief Get current time in milliseconds since epoch
	 *
	 * @return Current time in milliseconds since epoch
	 */
	[[nodiscard]] static int64_t GetMilliseconds();

	/**
	 * @brief Get current time in seconds since epoch
	 *
	 * @return Current time in seconds since epoch
	 */
	[[nodiscard]] static int64_t GetSeconds();

	/**
	 * @brief Get the current date and time in a human-readable format
	 *
	 * @param inInfo Reference to SCalendarDate structure to fill with date and time information
	 * @param outText Pointer to a buffer to store the formatted date and time string
	 * @param inMaxSize Size of the output buffer
	 * @param inOptions Options for formatting the date and time (e.g., 0 for default format)
	 * @return int
	 */
	static int DateToText(SCalendarDate &inInfo, void *outText, size_t inMaxSize,
	                      unsigned inOptions);

	/**
	 * @brief
	 *
	 * @param inTimestamp Timestamp in microseconds since epoch
	 * @param outInfo Reference to SCalendarDate structure to fill with date and time information
	 */
	static void TimestampToDate(uint64_t inTimestamp, SCalendarDate &outInfo);

	/**
	 * @brief Get elapsed time since a given epoch in microseconds
	 *
	 * @param inEpoch Epoch time in microseconds
	 * @return Elapsed time in microseconds since the given epoch
	 */
	[[nodiscard]] static constexpr int64_t GetElapsedTime(int64_t inEpoch)
	{
#ifdef _WIN32
		return (inEpoch / 10000) - 11644473600000LL;
#else
#endif // _WIN32
	}
};
