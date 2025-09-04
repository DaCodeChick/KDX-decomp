#pragma once

#include "typedefs.h"

struct SWindow;

class HXAPI UWindow
{
public:
	/**
	 * @brief
	 * 
	 * @param inRef 
	 * @return true 
	 * @return false 
	 */
	static bool IsVisible(SWindow *inRef);
};
