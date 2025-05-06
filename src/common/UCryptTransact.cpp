#include "UCryptTransact.h"

struct STwofish
{
	uint32_t sbox[4][256];
	uint32_t keys[40];
};

void UCryptTransact::TwofishEncrypt(STwofish &ioCtx, const void *inData, void *outData)
{
	auto plaintext = reinterpret_cast<const uint8_t *>(inData);
	auto ciphertext = reinterpret_cast<uint8_t *>(outData);

	auto a = *reinterpret_cast<const uint32_t *>(plaintext) ^ ioCtx.keys[0];
	auto b = *reinterpret_cast<const uint32_t *>(plaintext + 4) ^ ioCtx.keys[1];
	auto c = *reinterpret_cast<const uint32_t *>(plaintext + 8) ^ ioCtx.keys[2];
	auto d = *reinterpret_cast<const uint32_t *>(plaintext + 12) ^ ioCtx.keys[3];

	for (auto round = 0; round < 16; round += 2)
	{
		auto bMix = (ioCtx.sbox[0][(b >> 0) & 0xFF] + ioCtx.sbox[1][(b >> 8) & 0xFF]) ^
		            (ioCtx.sbox[2][(b >> 16) & 0xFF] + ioCtx.sbox[3][(b >> 24) & 0xFF]);

		auto aMix = (ioCtx.sbox[0][(a >> 8) & 0xFF] + ioCtx.sbox[1][(a >> 0) & 0xFF]) ^
		            (ioCtx.sbox[2][(a >> 24) & 0xFF] + ioCtx.sbox[3][(a >> 16) & 0xFF]);

		auto f1 = bMix + aMix;
		auto f2 = bMix + (1 << aMix);

		d = rotr(d ^ (f1 + ioCtx.keys[4 + (1 << round) + 8]), 1);
		c = rotl(c, 1) ^ (f2 + ioCtx.keys[4 + (1 << round) + 9]);

		auto dMix = (ioCtx.sbox[0][(d >> 0) & 0xFF] + ioCtx.sbox[1][(d >> 8) & 0xFF]) ^
		            (ioCtx.sbox[2][(d >> 16) & 0xFF] + ioCtx.sbox[3][(d >> 24) & 0xFF]);

		auto cMix = (ioCtx.sbox[0][(c >> 8) & 0xFF] + ioCtx.sbox[1][(c >> 0) & 0xFF]) ^
		            (ioCtx.sbox[2][(c >> 24) & 0xFF] + ioCtx.sbox[3][(c >> 16) & 0xFF]);

		auto f3 = dMix + cMix;
		auto f4 = dMix + (1 << cMix);

		b = rotr(b ^ (f3 + ioCtx.keys[4 + (1 << round) + 10]), 1);
		a = rotl(a, 1) ^ (f4 + ioCtx.keys[4 + (1 << round) + 11]);
	}

	*(uint32_t *)ciphertext = c ^ ioCtx.keys[4];
	*(uint32_t *)(ciphertext + 4) = d ^ ioCtx.keys[5];
	*(uint32_t *)(ciphertext + 8) = a ^ ioCtx.keys[6];
	*(uint32_t *)(ciphertext + 12) = b ^ ioCtx.keys[7];
}

void UCryptTransact::TwofishEncryptSimple(STwofish &ioCtx, const void *inData, void *outData)
{
	auto plaintext = static_cast<const uint8_t *>(inData);
	auto *ciphertext = static_cast<uint8_t *>(outData);

	auto a = *reinterpret_cast<const uint32_t *>(plaintext) ^ ioCtx.keys[0];
	auto b = *reinterpret_cast<const uint32_t *>(plaintext + 4) ^ ioCtx.keys[1];
	auto c = *reinterpret_cast<const uint32_t *>(plaintext + 8) ^ ioCtx.keys[2];
	auto d = *reinterpret_cast<const uint32_t *>(plaintext + 12) ^ ioCtx.keys[3];

	for (auto round = 0; round < 16; ++round)
	{
		auto bMix = ioCtx.sbox[0][(b >> 24) & 0xFF] ^ ioCtx.sbox[1][(b >> 16) & 0xFF] ^
		            ioCtx.sbox[2][(b >> 8) & 0xFF] ^ ioCtx.sbox[3][b & 0xFF];

		auto aMix = ioCtx.sbox[0][(a >> 24) & 0xFF] ^ ioCtx.sbox[1][(a >> 16) & 0xFF] ^
		            ioCtx.sbox[2][(a >> 8) & 0xFF] ^ ioCtx.sbox[3][a & 0xFF];

		auto f1 = bMix + aMix;
		auto f2 = bMix + (1 << aMix);

		auto newD = d ^ (f1 + ioCtx.keys[8 + (1 << round)]);
		d = c;
		c = rotr(newD, 1);

		auto newB = b ^ (f2 + ioCtx.keys[8 + (1 << round) + 1]);
		b = a;
		a = rotl(newB, 1);
	}

	*(uint32_t *)(ciphertext) = c ^ ioCtx.keys[4];
	*(uint32_t *)(ciphertext + 4) = d ^ ioCtx.keys[5];
	*(uint32_t *)(ciphertext + 8) = a ^ ioCtx.keys[6];
	*(uint32_t *)(ciphertext + 12) = b ^ ioCtx.keys[7];
}

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
