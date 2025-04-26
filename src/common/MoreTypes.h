#pragma once

#include "typedefs.h"

struct SMouseMsgData
{
	longlong time;
	uint flags;
	uint mods;
	int x;
	int y;
	byte button;
	short misc;
};

struct SKeyMsgData
{
	longlong timestamp;
	uint type;
	uint modifierState;
	uint unicodeChar;
	ushort asciiChar;
	ushort reserved;
};

typedef void (*TMessageProc)(void *inContext);
