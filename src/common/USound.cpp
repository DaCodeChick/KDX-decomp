#include "USound.h"

#include "typedefs.h"

void USound::Beep()
{
#ifdef _WIN32
	MessageBeep(MB_OK);
#endif // _WIN32
}
