#pragma once

#include "typedefs.h"

class UDigest
{
public:
	static void * MD5_Encode(const void *inData, uint inDataSize, uint *outDataSize);
};

class _MD5Digest
{
public:
	_MD5Digest();
	~_MD5Digest();
private:
	byte mData[16];
};

class _MD5
{
public:
	_MD5();
	virtual ~_MD5();
	void Update(const byte *inData, uint inDataSize);
	void Report(_MD5Digest &outDigest);
	void Init();
	void Clear();
private:
	uint mState[4];
	uint mCount[2];
	byte mBuffer[64];
	uint mBufferLength;

	void Transform(const byte *inBlock);
};
