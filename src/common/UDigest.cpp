#include "UDigest.h"

#include "UMemory.h"

constexpr size_t _MD5_BLOCK_LENGTH = 64;

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

static constexpr void ff(unsigned &a, unsigned b, unsigned c, unsigned d, unsigned x, 
                         unsigned ac)
{
	a += f(b, c, d) + x + ac;
	a = rotl(a, 5);
	a += b;
}

static constexpr void gg(unsigned &a, unsigned b, unsigned c, unsigned d, unsigned x, 
                         unsigned ac)
{
	a += g(b, c, d) + x + ac;
	a = rotl(a, 5);
	a += b;
}

static constexpr void hh(unsigned &a, unsigned b, unsigned c, unsigned d, unsigned x, 
                         unsigned ac)
{
	a += h(b, c, d) + x + ac;
	a = rotl(a, 5);
	a += b;
}

static constexpr void ii(unsigned &a, unsigned b, unsigned c, unsigned d, unsigned x, 
                         unsigned ac)
{
	a += i(b, c, d) + x + ac;
	a = rotl(a, 5);
	a += b;
}

void _MD5::Init()
{
	mState[0] = 0x67452301;
	mState[1] = 0xEFCDAB89;
	mState[2] = 0x98BADCFE;
	mState[3] = 0x10325476;
	mState[4] = 0xC3D2E1F0;
	mCount = mBufferLength = 0;
}

void _MD5::Update(const uint8_t *inData, size_t inDataSize)
{
	if (mBufferLength)
	{
        size_t available = 64 - mBufferLength;
        auto toCopy = min(inDataSize, available);

        UMemory::Move(mBuffer + mBufferLength, inData, toCopy);
        mBufferLength += toCopy;
        inData += toCopy;
        inDataSize -= toCopy;

        if (mBufferLength == _MD5_BLOCK_LENGTH)
		{
            Transform(mBuffer);
            mCount++;
            mBufferLength = 0;
        }
    }

    while (inDataSize >= _MD5_BLOCK_LENGTH)
	{
        Transform(inData);
        mCount++;
        inData += _MD5_BLOCK_LENGTH;
        inDataSize -= _MD5_BLOCK_LENGTH;
    }

    if (inDataSize)
	{
        UMemory::Move(mBuffer, inData, inDataSize);
        mBufferLength = inDataSize;
    }
}

void _MD5::Transform(const uint8_t *inBlock)
{
	static constexpr uint32_t rounds[4] = {
		0x5a827999, 0x6ed9eba1, 0x8f1bbcdc, 0xca62c1d6,
	};

    auto a = mState[0];
    auto b = mState[1];
    auto c = mState[2];
    auto d = mState[3];
    auto e = mState[4];
    uint8_t x[16];

    for (auto i = 0; i < 16; i++)
        x[i] = ntohl(inBlock[i]);

    ff(a, b, c, d, x[0], rounds[0]); e += a; b = rotl(b, 30);
    ff(d, a, b, c, x[1], rounds[0]); e += d; a = rotl(a, 30);
    ff(c, d, a, b, x[2], rounds[0]); e += c; d = rotl(d, 30);
    ff(b, c, d, a, x[3], rounds[0]); e += b; c = rotl(c, 30);
    ff(a, b, c, d, x[4], rounds[0]); e += a; b = rotl(b, 30);
    ff(d, a, b, c, x[5], rounds[0]); e += d; a = rotl(a, 30);
    ff(c, d, a, b, x[6], rounds[0]); e += c; d = rotl(d, 30);
    ff(b, c, d, a, x[7], rounds[0]); e += b; c = rotl(c, 30);
    ff(a, b, c, d, x[8], rounds[0]); e += a; b = rotl(b, 30);
    ff(d, a, b, c, x[9], rounds[0]); e += d; a = rotl(a, 30);
    ff(c, d, a, b, x[10], rounds[0]); e += c; d = rotl(d, 30);
    ff(b, c, d, a, x[11], rounds[0]); e += b; c = rotl(c, 30);
    ff(a, b, c, d, x[12], rounds[0]); e += a; b = rotl(b, 30);
    ff(d, a, b, c, x[13], rounds[0]); e += d; a = rotl(a, 30);
    ff(c, d, a, b, x[14], rounds[0]); e += c; d = rotl(d, 30);
    ff(b, c, d, a, x[15], rounds[0]); e += b; c = rotl(c, 30);

    gg(a, b, c, d, x[0], rounds[1]); e += a; b = rotl(b, 30);
    gg(d, a, b, c, x[1], rounds[1]); e += d; a = rotl(a, 30);
    gg(c, d, a, b, x[2], rounds[1]); e += c; d = rotl(d, 30);
    gg(b, c, d, a, x[3], rounds[1]); e += b; c = rotl(c, 30);
    gg(a, b, c, d, x[4], rounds[1]); e += a; b = rotl(b, 30);
    gg(d, a, b, c, x[5], rounds[1]); e += d; a = rotl(a, 30);
    gg(c, d, a, b, x[6], rounds[1]); e += c; d = rotl(d, 30);
    gg(b, c, d, a, x[7], rounds[1]); e += b; c = rotl(c, 30);
    gg(a, b, c, d, x[8], rounds[1]); e += a; b = rotl(b, 30);
    gg(d, a, b, c, x[9], rounds[1]); e += d; a = rotl(a, 30);
    gg(c, d, a, b, x[10], rounds[1]); e += c; d = rotl(d, 30);
    gg(b, c, d, a, x[11], rounds[1]); e += b; c = rotl(c, 30);
    gg(a, b, c, d, x[12], rounds[1]); e += a; b = rotl(b, 30);
    gg(d, a, b, c, x[13], rounds[1]); e += d; a = rotl(a, 30);
    gg(c, d, a, b, x[14], rounds[1]); e += c; d = rotl(d, 30);
    gg(b, c, d, a, x[15], rounds[1]); e += b; c = rotl(c, 30);

    hh(a, b, c, d, x[0], rounds[2]); e += a; b = rotl(b, 30);
    hh(d, a, b, c, x[1], rounds[2]); e += d; a = rotl(a, 30);
    hh(c, d, a, b, x[2], rounds[2]); e += c; d = rotl(d, 30);
    hh(b, c, d, a, x[3], rounds[2]); e += b; c = rotl(c, 30);
    hh(a, b, c, d, x[4], rounds[2]); e += a; b = rotl(b, 30);
    hh(d, a, b, c, x[5], rounds[2]); e += d; a = rotl(a, 30);
    hh(c, d, a, b, x[6], rounds[2]); e += c; d = rotl(d, 30);
    hh(b, c, d, a, x[7], rounds[2]); e += b; c = rotl(c, 30);
    hh(a, b, c, d, x[8], rounds[2]); e += a; b = rotl(b, 30);
    hh(d, a, b, c, x[9], rounds[2]); e += d; a = rotl(a, 30);
    hh(c, d, a, b, x[10], rounds[2]); e += c; d = rotl(d, 30);
    hh(b, c, d, a, x[11], rounds[2]); e += b; c = rotl(c, 30);
    hh(a, b, c, d, x[12], rounds[2]); e += a; b = rotl(b, 30);
    hh(d, a, b, c, x[13], rounds[2]); e += d; a = rotl(a, 30);
    hh(c, d, a, b, x[14], rounds[2]); e += c; d = rotl(d, 30);
    hh(b, c, d, a, x[15], rounds[2]); e += b; c = rotl(c, 30);

    ii(a, b, c, d, x[0], rounds[3]); e += a; b = rotl(b, 30);
    ii(d, a, b, c, x[1], rounds[3]); e += d; a = rotl(a, 30);
    ii(c, d, a, b, x[2], rounds[3]); e += c; d = rotl(d, 30);
    ii(b, c, d, a, x[3], rounds[3]); e += b; c = rotl(c, 30);
    ii(a, b, c, d, x[4], rounds[3]); e += a; b = rotl(b, 30);
    ii(d, a, b, c, x[5], rounds[3]); e += d; a = rotl(a, 30);
    ii(c, d, a, b, x[6], rounds[3]); e += c; d = rotl(d, 30);
    ii(b, c, d, a, x[7], rounds[3]); e += b; c = rotl(c, 30);
    ii(a, b, c, d, x[8], rounds[3]); e += a; b = rotl(b, 30);
    ii(d, a, b, c, x[9], rounds[3]); e += d; a = rotl(a, 30);
    ii(c, d, a, b, x[10], rounds[3]); e += c; d = rotl(d, 30);
    ii(b, c, d, a, x[11], rounds[3]); e += b; c = rotl(c, 30);
    ii(a, b, c, d, x[12], rounds[3]); e += a; b = rotl(b, 30);
    ii(d, a, b, c, x[13], rounds[3]); e += d; a = rotl(a, 30);
    ii(c, d, a, b, x[14], rounds[3]); e += c; d = rotl(d, 30);
    ii(b, c, d, a, x[15], rounds[3]); e += b; c = rotl(c, 30);

    mState[0] += a;
    mState[1] += b;
    mState[2] += c;
    mState[3] += d;
    mState[4] += e;
}

void _MD5::Report(void *outDigest)
{
    Update(NULL, 0);

    const auto bitLength = (static_cast<uint64_t>(mCount) << 6) + 
                              (mBufferLength << 3);

    mBuffer[mBufferLength++] = 0x80;
    if (mBufferLength > 56)
	{
        UMemory::Clear(mBuffer + mBufferLength, 64 - mBufferLength);
        Update(NULL, 0);
        UMemory::Clear(mBuffer, 56);
    }
	else
        UMemory::Clear(mBuffer + mBufferLength, 56 - mBufferLength);

    *reinterpret_cast<uint64_t*>(mBuffer + 56) = ntohll(bitLength);
    Transform(mBuffer);

    for (auto i = 0; i < 5; i++)
        reinterpret_cast<uint32_t *>(outDigest)[i] = ntohl(mState[i]);

    // Clear sensitive data
    Clear(sizeof(_MD5));
}

void UDigest::MD5_Encode(const void *inData, size_t inDataSize, void *outDigest)
{
	_MD5 md5;

	md5.Update(reinterpret_cast<const uint8_t *>(inData), inDataSize);
	md5.Report(outDigest);
}
