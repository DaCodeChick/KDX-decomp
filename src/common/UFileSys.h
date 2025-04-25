#pragma once

#include "typedefs.h"

struct SFileSysRef;

class UFileSys
{
public:
	static void Open(SFileSysRef *inRef);
	static void * Read(SFileSysRef *inRef, uint inOffset, uint inMaxSize, void *outData, uint inOptions);
	static void Write(SFileSysRef *inRef, const void *inData, uint inDataSize, uint inOptions);
	static ulonglong GetFileSize(SFileSysRef *inRef, uint inOptions);
	static bool ValidateFilePath(char *ioPath, uint inPathSize);
};
