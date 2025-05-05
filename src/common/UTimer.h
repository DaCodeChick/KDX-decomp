#pragma once

#include "MoreTypes.h"

/// @brief Timer object
struct STimer;

/// @brief Timer callback function type
#if defined(__APPLE__) || defined(_WIN32)
typedef TMessageProc TTimerProc;
#else
typedef void (*TTimerProc)(sigval inContext);
#endif // defined(__APPLE__) || defined(_WIN32)

class UTimer
{
public:
	/**
	 * @brief Create a new timer object
	 *
	 * @param inProc
	 * @param inContext
	 * @return STimer*
	 */
	static STimer *New(TTimerProc inProc, void *inContext);

	/**
	 * @brief Dispose of a timer object
	 *
	 * @param inRef
	 */
	static void Dispose(STimer *inRef);

	/**
	 * @brief Start a timer
	 *
	 * @param inRef
	 * @param inMillisecs
	 * @param inIsRepeating
	 */
	static void Start(STimer *inRef, unsigned inMillisecs, int inIsRepeating);

	/**
	 * @brief Create and start a timer
	 *
	 * @param inProc
	 * @param inContext
	 * @param inMillisecs
	 * @param inIsRepeating
	 * @return STimer*
	 */
	static STimer *StartNew(TTimerProc inProc, void *inContext, unsigned inMillisecs,
	                        int inIsRepeating);
	/**
	 * @brief Stop a timer
	 *
	 * @param inRef
	 */
	static void Stop(STimer *inRef);
};
