#pragma once

#include "typedefs.h"

class UKeyboard
{
public:
	/**
	 * @brief Converts a key code to a character based on the current keyboard layout and mode.
	 *
	 * @param inKeyCode The key code to convert.
	 * @param inMode The mode to use for conversion (e.g., uppercase, lowercase, etc.).
	 * @return The character representation of the key code in the specified mode.
	 */
	static unsigned KeyToChar(unsigned inKeyCode, unsigned inMode);
};
