#pragma once

#include "typedefs.h"

struct SError
{
	uint type;
	SError *next;
	void *field2_0x8;
	uint line;
};

enum
{
	error_Param = 0x10002
};

void __Fail(uint inType);
void __Fail(uint inType, void *inParam2, uint inLine);
