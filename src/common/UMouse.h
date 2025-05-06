#pragma once

#include "GrafTypes.h"

/// @brief The UMouse class provides methods to interact with the mouse.
class UMouse
{
public:
	/**
	 * @brief Returns the time interval for double-click detection.
	 *
	 * @return The time interval in milliseconds.
	 */
	[[nodiscard]] static unsigned GetDoubleClickTime();

	/**
	 * @brief Returns the current image ID.
	 *
	 * @return The current image ID.
	 */
	[[nodiscard]] static constexpr unsigned GetImage()
	{
		return sCurCursorID;
	}

	/**
	 * @brief Sets the mouse image to the specified ID.
	 *
	 * @param inID The ID of the image to set.
	 */
	static void SetImage(unsigned inID);

	/**
	 * @brief Returns the current mouse location.
	 *
	 * @param outLoc A reference to an SPoint structure to store the mouse location.
	 */
	static void GetLocation(SPoint &outLoc);

private:
	static unsigned sCurCursorID;
};
