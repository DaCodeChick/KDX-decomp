#pragma once

#include "typedefs.h"

struct SMouseMsgData
{
	ulonglong time;
	uint flags;
	uint mods;
	int x;
	int y;
	byte button;
	short misc;
};

struct SKeyMsgData
{
	ulonglong timestamp;
	uint type;
	uint modifierState;
	uint unicodeChar;
	ushort asciiChar;
	ushort reserved;
};

typedef void (*TMessageProc)(void *inContext);
