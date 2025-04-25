#pragma once

#include "typedefs.h"

struct STwofish;

class UCryptTransact
{
public:
	static void TwofishEncrypt(STwofish &ioCtx, const void *inData, void *outData);
	static void TwofishEncryptSimple(STwofish &ioCtx, const void *inData, void *outData);
};