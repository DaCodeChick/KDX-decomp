#pragma once

#include "typedefs.h"

struct SError
{
	uint type;
	SError *next;
};

enum
{
	error_Param = 0x10002
};

void __Fail(uint inType);
