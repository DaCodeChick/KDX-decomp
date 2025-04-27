#pragma once

#include "typedefs.h"

class UDigest
{
public:
	static void MD5_Encode(const void *inData, uint inDataSize, void *outDigest);
	static void AugmentedMD5_Encode(const void *inData, uint inDataSize, void *outDigest);
};

class _MD5
{
public:
	_MD5();
	void Update(const byte *inData, uint inDataSize);
	void Report(void *outDigest);
	void Init();
	void Clear(uint inSize);

private:
	uint mState[4];
	uint mCount[2];
	byte mBuffer[64];
	uint mBufferLength;

	void Transform(const byte *inBlock);
};
