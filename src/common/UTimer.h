#pragma once

#include "MoreTypes.h"

/// @brief Timer object
struct STimer;

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
	static STimer *New(TMessageProc inProc, void *inContext);

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
	static void Start(STimer *inRef, uint inMillisecs, uint inIsRepeating);

	/**
	 * @brief Create and start a timer
	 * 
	 * @param inProc
	 * @param inContext
	 * @param inMillisecs
	 * @param inIsRepeating
	 * @return STimer*
	 */
	static STimer *StartNew(TMessageProc inProc, void *inContext, uint inMillisecs,
	                        uint inIsRepeating);
	/**
	 * @brief Stop a timer
	 * 
	 * @param inRef 
	 */
	static void Stop(STimer *inRef);
};
