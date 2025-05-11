#pragma once

struct SWindow;

class UWindow
{
public:
	/// @brief Initializes the window system.
	static void Init();

	static bool IsVisible(SWindow *inRef);
};
