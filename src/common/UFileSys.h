#pragma once

#include "typedefs.h"

struct SFileSysRef
{
#ifdef _WIN32
	HANDLE h;
#else
	int h;
#endif // _WIN32
	uint tag; // 0x1ca6c39a
	wchar_t *path;
	uint pathSize;
	uint pathFlags;
	uint flags;
};

class UFileSys
{
public:
	static void Open(SFileSysRef *inRef);
	static void * Read(SFileSysRef *inRef, uint inOffset, uint inMaxSize, void *outData, uint inOptions);
	static void Write(SFileSysRef *inRef, const void *inData, uint inDataSize, uint inOptions);
	static ulonglong GetFileSize(SFileSysRef *inRef, uint inOptions);
	static bool ValidateFilePath(char *ioPath, uint inPathSize);
};
