#include "UDigest.h"

#include "UMemory.h"

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

#define FF(a, b, c, d, x, s, ac) { \
    (a) += F((b), (c), (d)) + (x) + (uint)(ac); \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b); \
}

#define GG(a, b, c, d, x, s, ac) { \
    (a) += G((b), (c), (d)) + (x) + (uint)(ac); \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b); \
}

#define HH(a, b, c, d, x, s, ac) { \
    (a) += H((b), (c), (d)) + (x) + (uint)(ac); \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b); \
}

#define II(a, b, c, d, x, s, ac) { \
    (a) += I((b), (c), (d)) + (x) + (uint)(ac); \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b); \
}

_MD5::_MD5()
{
	Init();
}

void _MD5::Init()
{
	mState[0] = 0x67452301;
	mState[1] = 0xEFCDAB89;
	mState[2] = 0x98BADCFE;
	mState[3] = 0x10325476;
	mCount[0] = 0xC3D2E1F0;
	mCount[1] = mBufferLength = 0;
}

void _MD5::Clear(uint inSize)
{
	UMemory::Clear(this, inSize);
}

void _MD5::Update(const byte *inData, uint inDataSize)
{
	if (mBufferLength == 64)
	{
		Transform(mBuffer);
		mBufferLength = 0;
		mCount[1]++;
	}
	if (!inData)
	{
		if (mBufferLength)
		{
			while (inDataSize && (mBufferLength < 64))
			{
				mBuffer[mBufferLength++] = *(inData++);
				inDataSize--;
			}
			if (mBufferLength == 64)
			{
				Transform(mBuffer);
				mBufferLength = 0;
				mCount[1]++;
			}
			if (!inDataSize) return;
		}
		for (; 63 < inDataSize; inDataSize -= 64, inData += 64)
		{
			Transform(inData);
			mBufferLength = 0;
			mCount[1]++;
		}
		while (inDataSize && (mBufferLength < 64))
		{
			mBuffer[mBufferLength++] = *(inData++);
			inDataSize--;
		}
	}
}

void _MD5::Transform(const byte *inBlock)
{
    uint a = mState[0];
    uint b = mState[1];
    uint c = mState[2];
    uint d = mState[3];
    
    uint x[16];
    for (int i = 0; i < 16; i++)
	{
        x[i] = *(uint *)(inBlock + (i << 2));
        x[i] = HTONL(x[i]);
    }

    FF(a, b, c, d, x[0],  7, 0xd76aa478);
    FF(d, a, b, c, x[1], 12, 0xe8c7b756);
    FF(c, d, a, b, x[2], 17, 0x242070db);
    FF(b, c, d, a, x[3], 22, 0xc1bdceee);
    FF(a, b, c, d, x[4],  7, 0xf57c0faf);
    FF(d, a, b, c, x[5], 12, 0x4787c62a);
    FF(c, d, a, b, x[6], 17, 0xa8304613);
    FF(b, c, d, a, x[7], 22, 0xfd469501);
    FF(a, b, c, d, x[8],  7, 0x698098d8);
    FF(d, a, b, c, x[9], 12, 0x8b44f7af);
    FF(c, d, a, b, x[10],17, 0xffff5bb1);
    FF(b, c, d, a, x[11],22, 0x895cd7be);
    FF(a, b, c, d, x[12], 7, 0x6b901122);
    FF(d, a, b, c, x[13],12, 0xfd987193);
    FF(c, d, a, b, x[14],17, 0xa679438e);
    FF(b, c, d, a, x[15],22, 0x49b40821);

    GG(a, b, c, d, x[1],  5, 0xf61e2562);
    GG(d, a, b, c, x[6],  9, 0xc040b340);
    GG(c, d, a, b, x[11],14, 0x265e5a51);
    GG(b, c, d, a, x[0], 20, 0xe9b6c7aa);
    GG(a, b, c, d, x[5],  5, 0xd62f105d);
    GG(d, a, b, c, x[10], 9, 0x02441453);
    GG(c, d, a, b, x[15],14, 0xd8a1e681);
    GG(b, c, d, a, x[4], 20, 0xe7d3fbc8);
    GG(a, b, c, d, x[9],  5, 0x21e1cde6);
    GG(d, a, b, c, x[14], 9, 0xc33707d6);
    GG(c, d, a, b, x[3], 14, 0xf4d50d87);
    GG(b, c, d, a, x[8], 20, 0x455a14ed);
    GG(a, b, c, d, x[13], 5, 0xa9e3e905);
    GG(d, a, b, c, x[2],  9, 0xfcefa3f8);
    GG(c, d, a, b, x[7], 14, 0x676f02d9);
    GG(b, c, d, a, x[12],20, 0x8d2a4c8a);

    HH(a, b, c, d, x[5],  4, 0xfffa3942);
    HH(d, a, b, c, x[8], 11, 0x8771f681);
    HH(c, d, a, b, x[11],16, 0x6d9d6122);
    HH(b, c, d, a, x[14],23, 0xfde5380c);
    HH(a, b, c, d, x[1],  4, 0xa4beea44);
    HH(d, a, b, c, x[4], 11, 0x4bdecfa9);
    HH(c, d, a, b, x[7], 16, 0xf6bb4b60);
    HH(b, c, d, a, x[10],23, 0xbebfbc70);
    HH(a, b, c, d, x[13], 4, 0x289b7ec6);
    HH(d, a, b, c, x[0], 11, 0xeaa127fa);
    HH(c, d, a, b, x[3], 16, 0xd4ef3085);
    HH(b, c, d, a, x[6], 23, 0x04881d05);
    HH(a, b, c, d, x[9],  4, 0xd9d4d039);
    HH(d, a, b, c, x[12],11, 0xe6db99e5);
    HH(c, d, a, b, x[15],16, 0x1fa27cf8);
    HH(b, c, d, a, x[2], 23, 0xc4ac5665);

    II(a, b, c, d, x[0],  6, 0xf4292244);
    II(d, a, b, c, x[7], 10, 0x432aff97);
    II(c, d, a, b, x[14],15, 0xab9423a7);
    II(b, c, d, a, x[5], 21, 0xfc93a039);
    II(a, b, c, d, x[12], 6, 0x655b59c3);
    II(d, a, b, c, x[3], 10, 0x8f0ccc92);
    II(c, d, a, b, x[10],15, 0xffeff47d);
    II(b, c, d, a, x[1], 21, 0x85845dd1);
    II(a, b, c, d, x[8],  6, 0x6fa87e4f);
    II(d, a, b, c, x[15],10, 0xfe2ce6e0);
    II(c, d, a, b, x[6], 15, 0xa3014314);
    II(b, c, d, a, x[13],21, 0x4e0811a1);
    II(a, b, c, d, x[4],  6, 0xf7537e82);
    II(d, a, b, c, x[11],10, 0xbd3af235);
    II(c, d, a, b, x[2], 15, 0x2ad7d2bb);
    II(b, c, d, a, x[9], 21, 0xeb86d391);

    mState[0] += a;
    mState[1] += b;
    mState[2] += c;
    mState[3] += d;
    
    mCount[0] += 64;
    if (mCount[0] < 64)
        mCount[1]++;
}

void _MD5::Report(void *outDigest)
{
    Update(NULL, 0);

    ulonglong bitCount = ((ulonglong)mCount[1] << 29) + (mCount[0] << 3) + (mBufferLength << 3);

    mBuffer[mBufferLength++] = 0x80;
    if (mBufferLength > 56) {
        while (mBufferLength < 64)
            mBuffer[mBufferLength++] = 0;
        Transform(mBuffer);
        mBufferLength = 0;
    }
    while (mBufferLength < 56)
        mBuffer[mBufferLength++] = 0;

    for (int i = 0; i < 8; ++i)
        mBuffer[56 + i] = (uchar)(bitCount >> (i << 3));

    Transform(mBuffer);

    for (int i = 0; i < 4; ++i)
        ((uint *)outDigest)[i] = HTONL(mState[i]);

    Clear(0x5c);
}

void UDigest::MD5_Encode(const void *inData, uint inDataSize, void *outDigest)
{
	_MD5 md5;

	md5.Update((const byte *)inData, inDataSize);
	md5.Report(outDigest);
}
