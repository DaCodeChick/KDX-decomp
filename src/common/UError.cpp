#include "UError.h"

#include "UMemory.h"

static constexpr uint _OSToGenError(uint inType)
{
	switch (inType)
	{
#ifdef _WIN32
#else
#endif // _WIN32
	}
}

void __Fail(uint inType)
{
	SError err;
	UMemory::Clear(&err, sizeof(err));
	err.type = inType;

	throw err;
}

void __Fail(uint inType, void *inParam2, uint inLine)
{
	SError err;
	UMemory::Clear(&err, sizeof(err));
	err.type = inType;
	err.field2_0x8 = inParam2;
	err.line = inLine;

	throw err;
}