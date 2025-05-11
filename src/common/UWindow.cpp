#include "UWindow.h"

#include "typedefs.h"

#ifdef __APPLE__
#include <CoreGraphics/CoreGraphics.h>
#endif // __APPLE__

constexpr unsigned kWindowTag = 0xf0168873;

struct SWindow
{
	unsigned tag;
#ifdef _WIN32
	HWND hwnd;
#elif defined(__APPLE__)
	CGWindowID macWin;
#else
#endif // _WIN32
};

bool UWindow::IsVisible(SWindow *inRef)
{
#ifdef _WIN32
	return IsWindowVisible(inRef->hwnd);
#else
	return false;
#endif // _WIN32
}