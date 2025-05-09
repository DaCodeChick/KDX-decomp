#include "UDigest.h"

#include "UMemory.h"

static constexpr unsigned f(unsigned x, unsigned y, unsigned z)
{
	return (x & y) | (~x & z);
}

static constexpr unsigned g(unsigned x, unsigned y, unsigned z)
{
	return (x & z) | (y & ~z);
}

static constexpr unsigned h(unsigned x, unsigned y, unsigned z)
{
	return x ^ y ^ z;
}

static constexpr unsigned i(unsigned x, unsigned y, unsigned z)
{
	return y ^ (x | ~z);
}

static constexpr void ff(unsigned &a, unsigned b, unsigned c, unsigned d, unsigned x, unsigned s,
                         unsigned ac)
{
	a += f(b, c, d) + x + ac;
	a = rotl(a, s);
	a += b;
}

static constexpr void gg(unsigned &a, unsigned b, unsigned c, unsigned d, unsigned x, unsigned s,
                         unsigned ac)
{
	a += g(b, c, d) + x + ac;
	a = rotl(a, s);
	a += b;
}

static constexpr void hh(unsigned &a, unsigned b, unsigned c, unsigned d, unsigned x, unsigned s,
                         unsigned ac)
{
	a += h(b, c, d) + x + ac;
	a = rotl(a, s);
	a += b;
}

static constexpr void ii(unsigned &a, unsigned b, unsigned c, unsigned d, unsigned x, unsigned s,
                         unsigned ac)
{
	a += i(b, c, d) + x + ac;
	a = rotl(a, s);
	a += b;
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

void _MD5::Clear(size_t inSize)
{
	UMemory::Clear(this, inSize);
}

void _MD5::Update(const uint8_t *inData, size_t inDataSize)
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
			if (!inDataSize)
				return;
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

void _MD5::Transform(const uint8_t *inBlock)
{
	auto a = mState[0];
	auto b = mState[1];
	auto c = mState[2];
	auto d = mState[3];
	uint32_t x[16];

	for (auto i = 0; i < 16; i++)
	{
		x[i] = *reinterpret_cast<const uint32_t *>(inBlock + (i << 2));
		x[i] = htonl(x[i]);
	}

	ff(a, b, c, d, x[0], 7, 0xd76aa478);
	ff(d, a, b, c, x[1], 12, 0xe8c7b756);
	ff(c, d, a, b, x[2], 17, 0x242070db);
	ff(b, c, d, a, x[3], 22, 0xc1bdceee);
	ff(a, b, c, d, x[4], 7, 0xf57c0faf);
	ff(d, a, b, c, x[5], 12, 0x4787c62a);
	ff(c, d, a, b, x[6], 17, 0xa8304613);
	ff(b, c, d, a, x[7], 22, 0xfd469501);
	ff(a, b, c, d, x[8], 7, 0x698098d8);
	ff(d, a, b, c, x[9], 12, 0x8b44f7af);
	ff(c, d, a, b, x[10], 17, 0xffff5bb1);
	ff(b, c, d, a, x[11], 22, 0x895cd7be);
	ff(a, b, c, d, x[12], 7, 0x6b901122);
	ff(d, a, b, c, x[13], 12, 0xfd987193);
	ff(c, d, a, b, x[14], 17, 0xa679438e);
	ff(b, c, d, a, x[15], 22, 0x49b40821);

	gg(a, b, c, d, x[1], 5, 0xf61e2562);
	gg(d, a, b, c, x[6], 9, 0xc040b340);
	gg(c, d, a, b, x[11], 14, 0x265e5a51);
	gg(b, c, d, a, x[0], 20, 0xe9b6c7aa);
	gg(a, b, c, d, x[5], 5, 0xd62f105d);
	gg(d, a, b, c, x[10], 9, 0x02441453);
	gg(c, d, a, b, x[15], 14, 0xd8a1e681);
	gg(b, c, d, a, x[4], 20, 0xe7d3fbc8);
	gg(a, b, c, d, x[9], 5, 0x21e1cde6);
	gg(d, a, b, c, x[14], 9, 0xc33707d6);
	gg(c, d, a, b, x[3], 14, 0xf4d50d87);
	gg(b, c, d, a, x[8], 20, 0x455a14ed);
	gg(a, b, c, d, x[13], 5, 0xa9e3e905);
	gg(d, a, b, c, x[2], 9, 0xfcefa3f8);
	gg(c, d, a, b, x[7], 14, 0x676f02d9);
	gg(b, c, d, a, x[12], 20, 0x8d2a4c8a);

	hh(a, b, c, d, x[5], 4, 0xfffa3942);
	hh(d, a, b, c, x[8], 11, 0x8771f681);
	hh(c, d, a, b, x[11], 16, 0x6d9d6122);
	hh(b, c, d, a, x[14], 23, 0xfde5380c);
	hh(a, b, c, d, x[1], 4, 0xa4beea44);
	hh(d, a, b, c, x[4], 11, 0x4bdecfa9);
	hh(c, d, a, b, x[7], 16, 0xf6bb4b60);
	hh(b, c, d, a, x[10], 23, 0xbebfbc70);
	hh(a, b, c, d, x[13], 4, 0x289b7ec6);
	hh(d, a, b, c, x[0], 11, 0xeaa127fa);
	hh(c, d, a, b, x[3], 16, 0xd4ef3085);
	hh(b, c, d, a, x[6], 23, 0x04881d05);
	hh(a, b, c, d, x[9], 4, 0xd9d4d039);
	hh(d, a, b, c, x[12], 11, 0xe6db99e5);
	hh(c, d, a, b, x[15], 16, 0x1fa27cf8);
	hh(b, c, d, a, x[2], 23, 0xc4ac5665);

	ii(a, b, c, d, x[0], 6, 0xf4292244);
	ii(d, a, b, c, x[7], 10, 0x432aff97);
	ii(c, d, a, b, x[14], 15, 0xab9423a7);
	ii(b, c, d, a, x[5], 21, 0xfc93a039);
	ii(a, b, c, d, x[12], 6, 0x655b59c3);
	ii(d, a, b, c, x[3], 10, 0x8f0ccc92);
	ii(c, d, a, b, x[10], 15, 0xffeff47d);
	ii(b, c, d, a, x[1], 21, 0x85845dd1);
	ii(a, b, c, d, x[8], 6, 0x6fa87e4f);
	ii(d, a, b, c, x[15], 10, 0xfe2ce6e0);
	ii(c, d, a, b, x[6], 15, 0xa3014314);
	ii(b, c, d, a, x[13], 21, 0x4e0811a1);
	ii(a, b, c, d, x[4], 6, 0xf7537e82);
	ii(d, a, b, c, x[11], 10, 0xbd3af235);
	ii(c, d, a, b, x[2], 15, 0x2ad7d2bb);
	ii(b, c, d, a, x[9], 21, 0xeb86d391);

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

	auto bitCount =
	    (static_cast<size_t>(mCount[1]) << 29) + (mCount[0] << 3) + (mBufferLength << 3);

	mBuffer[mBufferLength++] = 0x80;
	if (mBufferLength > 56)
	{
		while (mBufferLength < 64)
			mBuffer[mBufferLength++] = 0;
		Transform(mBuffer);
		mBufferLength = 0;
	}
	while (mBufferLength < 56)
		mBuffer[mBufferLength++] = 0;

	for (auto i = 0; i < 8; ++i)
		mBuffer[56 + i] = static_cast<uint8_t>(bitCount >> (i << 3));

	Transform(mBuffer);

	for (auto i = 0; i < 4; ++i)
		((uint32_t *)outDigest)[i] = htonl(mState[i]);

	Clear(0x5c);
}

void UDigest::MD5_Encode(const void *inData, size_t inDataSize, void *outDigest)
{
	_MD5 md5;

	md5.Update(reinterpret_cast<const uint8_t *>(inData), inDataSize);
	md5.Report(outDigest);
}

void UDigest::AugmentedMD5_Encode(const void *inData, size_t inDataSize, void *outDigest)
{
	auto digest32 = reinterpret_cast<uint32_t *>(outDigest);
	if (!inDataSize)
	{
		digest32[0] = 0xeea339da;
		digest32[1] = 0x6ebeaeca;
		digest32[2] = 0xd4b6b5e;
		digest32[3] = 0xba298eba;
		digest32[4] = 0xefbf5532;
		digest32[5] = 0xc4b5a218;
		digest32[6] = 0x90186095;
		digest32[7] = 0x907d8af;
		return;
	}

	_MD5 md5;

	md5.Update(reinterpret_cast<const byte *>(inData), inDataSize);
	md5.Report(outDigest);
	digest32[5] = digest32[0];
	digest32[6] = digest32[1];
	digest32[7] = htonl(UMemory::Checksum(inData, inDataSize, 1));
}

bool UDigest::AugmentedMD5_IsDefault(const void *inDigest)
{
	uint8_t defaultDigest[32] = {0};

	AugmentedMD5_Encode(NULL, 0, defaultDigest);
	return UMemory::Compare(inDigest, defaultDigest, 32);
}
