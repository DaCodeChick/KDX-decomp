#include "UCryptTransact.h"

#include "UDigest.h"

void UCryptTransact::BlockCrypt6E7DFD34(void *ioData, bool isDecrypt)
{
	if (!ioData)
		return;

	auto block = reinterpret_cast<uint32_t *>(ioData);

	auto v1 = htonl(block[0]);
	auto v2 = htonl(block[1]);
	auto v3 = htonl(block[2]);
	auto v4 = htonl(block[3]);

	if (isDecrypt)
	{
		v3 = rotl(v3 ^ 0x6E7DFD34, 13);
		v2 = rotr(v2 ^ 0xE152DA04, 6);
		v4 = rotr(v4 ^ 0xA95A759B, 7);
		v1 = rotl(v1 ^ 0x06992E25, 3);
	}
	else
	{
		v3 = rotr(v3, 13) ^ 0x6E7DFD34;
		v2 = rotl(v2, 6) ^ 0xE152DA04;
		v4 = rotl(v4, 7) ^ 0xA95A759B;
		v1 = rotr(v1, 3) ^ 0x06992E25;
	}

	block[0] = ntohl(v1);
	block[1] = ntohl(v2);
	block[2] = ntohl(v3);
	block[3] = ntohl(v4);
}

void UCryptTransact::BlockCrypt1B20E200(void *ioData, bool isDecrypt)
{
	if (!ioData)
		return;

	auto block = reinterpret_cast<uint32_t *>(ioData);

	auto v1 = ntohl(block[0]);
	auto v2 = ntohl(block[1]);
	auto v3 = ntohl(block[2]);
	auto v4 = ntohl(block[3]);

	if (isDecrypt)
	{
		v1 = rotr(v1 ^ 0x1B20E200, 7);
		v2 = rotr(v2 ^ 0x5F547A17, 15);
		v3 = rotr(v3 ^ 0x69C83E35, 4);
		v4 = rotr(v4 ^ 0x8022E8D1, 5);
	}
	else
	{
		v1 = rotl(v1, 7) ^ 0x1B20E200;
		v2 = rotl(v2, 15) ^ 0x5F547A17;
		v3 = rotl(v3, 4) ^ 0x69C83E35;
		v4 = rotl(v4, 5) ^ 0x8022E8D1;
	}

	block[0] = htonl(v1);
	block[1] = htonl(v2);
	block[2] = htonl(v3);
	block[3] = htonl(v4);
}

void UCryptTransact::DataCrypt(void *ioData, size_t inDataSize, unsigned inInit,
                               unsigned inMultiplier, unsigned inAddend)
{
	if (!ioData || !inDataSize || inDataSize & 3)
		return;

	auto data = reinterpret_cast<uint32_t *>(ioData);
	auto numBlocks = inDataSize >> 2;

	for (auto i = 0; i < numBlocks; i++)
	{
		data[i] = htonl(data[i] ^ inInit);
		inInit = (inInit * inMultiplier + inAddend);
	}
}

void UCryptTransact::TCPPacketCrypt(unsigned inInit, void *ioData, size_t inDataSize)
{
	if (!ioData || !inDataSize || inDataSize & 3)
		return;

	auto data = reinterpret_cast<uint32_t *>(ioData);
	auto numBlocks = inDataSize >> 2;

	for (auto i = 0; i < numBlocks; i++)
	{
		inInit = (inInit << 1) + 0x4878;
		data[i] ^= htonl(inInit);
	}
}

void UCryptTransact::GenerateKey(const void *inData, size_t inDataSize, void *outKey)
{
	if (!inDataSize)
	{
		UMemory::Move(outKey, sDefaultKey, 32);
		return;
	}

	auto key = reinterpret_cast<uint32_t *>(outKey);
	_MD5 md5;

	md5.Update(reinterpret_cast<const byte *>(inData), inDataSize);
	md5.Report(outKey);
	key[5] = key[0];
	key[6] = key[1];
	key[7] = htonl(UMemory::Checksum(inData, inDataSize, 1));
}
