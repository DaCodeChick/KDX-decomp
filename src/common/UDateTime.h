#pragma once

#include "typedefs.h"

/// @brief Structure to hold calendar date information.
struct SCalendarDate
{
	short field0_0x0;
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
	static int GetTimeZoneOffset();

	/**
	 * @brief Get current time in microseconds since epoch
	 *
	 * @return Current time in microseconds since epoch
	 */
	static int64_t GetMicroseconds();

	/**
	 * @brief Get current time in milliseconds since epoch
	 *
	 * @return Current time in milliseconds since epoch
	 */
	static int64_t GetMilliseconds();

	/**
	 * @brief Get elapsed time since a given epoch in microseconds
	 *
	 * @param inEpoch Epoch time in microseconds
	 * @return Elapsed time in microseconds since the given epoch
	 */
	static int64_t GetElapsedTime(int64_t inEpoch);

	/**
	 * @brief Get current time in seconds since epoch
	 *
	 * @return Current time in seconds since epoch
	 */
	static int64_t GetSeconds();

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
};
