#include "UError.h"

#include "UMemory.h"

static constexpr unsigned _OSToGenError(int inType)
{
	switch (inType)
	{
#ifdef _WIN32
#else
#endif // _WIN32
		default:
			return 0;
	}
}

void __Fail(unsigned inType)
{
	SError err;

	UMemory::Clear(&err, sizeof(SError));
	err.type = inType;

	throw err;
}

void __Fail(unsigned inType, const void *inParam2, unsigned inLine)
{
	SError err;

	UMemory::Clear(&err, sizeof(SError));
	err.type = inType;
	err.field2_0x8 = inParam2;
	err.line = inLine;

	throw err;
}