#include "CTwofish.h"

void CTwofish::Encrypt(const void *inData, void *outData)
{
	auto plaintext = reinterpret_cast<const uint8_t *>(inData);
	auto ciphertext = reinterpret_cast<uint8_t *>(outData);

	auto a = *reinterpret_cast<const uint32_t *>(plaintext) ^ mKey[0];
	auto b = *reinterpret_cast<const uint32_t *>(plaintext + 4) ^ mKey[1];
	auto c = *reinterpret_cast<const uint32_t *>(plaintext + 8) ^ mKey[2];
	auto d = *reinterpret_cast<const uint32_t *>(plaintext + 12) ^ mKey[3];

	for (auto round = 0; round < 16; round += 2)
	{
		auto bMix = (mSBox[0][(b >> 0) & 0xFF] + mSBox[1][(b >> 8) & 0xFF]) ^
		            (mSBox[2][(b >> 16) & 0xFF] + mSBox[3][(b >> 24) & 0xFF]);

		auto aMix = (mSBox[0][(a >> 8) & 0xFF] + mSBox[1][(a >> 0) & 0xFF]) ^
		            (mSBox[2][(a >> 24) & 0xFF] + mSBox[3][(a >> 16) & 0xFF]);

		auto f1 = bMix + aMix;
		auto f2 = bMix + (1 << aMix);

		d = rotr(d ^ (f1 + mKey[4 + (1 << round) + 8]), 1);
		c = rotl(c, 1) ^ (f2 + mKey[4 + (1 << round) + 9]);

		auto dMix = (mSBox[0][(d >> 0) & 0xFF] + mSBox[1][(d >> 8) & 0xFF]) ^
		            (mSBox[2][(d >> 16) & 0xFF] + mSBox[3][(d >> 24) & 0xFF]);

		auto cMix = (mSBox[0][(c >> 8) & 0xFF] + mSBox[1][(c >> 0) & 0xFF]) ^
		            (mSBox[2][(c >> 24) & 0xFF] + mSBox[3][(c >> 16) & 0xFF]);

		auto f3 = dMix + cMix;
		auto f4 = dMix + (1 << cMix);

		b = rotr(b ^ (f3 + mKey[4 + (1 << round) + 10]), 1);
		a = rotl(a, 1) ^ (f4 + mKey[4 + (1 << round) + 11]);
	}

	*(uint32_t *)ciphertext = c ^ mKey[4];
	*(uint32_t *)(ciphertext + 4) = d ^ mKey[5];
	*(uint32_t *)(ciphertext + 8) = a ^ mKey[6];
	*(uint32_t *)(ciphertext + 12) = b ^ mKey[7];
}

void CTwofish::Encrypt(const void *inData, void *outData)
{
	auto plaintext = reinterpret_cast<const uint8_t *>(inData);
	auto *ciphertext = reinterpret_cast<uint8_t *>(outData);

	auto a = *reinterpret_cast<const uint32_t *>(plaintext) ^ mKey[0];
	auto b = *reinterpret_cast<const uint32_t *>(plaintext + 4) ^ mKey[1];
	auto c = *reinterpret_cast<const uint32_t *>(plaintext + 8) ^ mKey[2];
	auto d = *reinterpret_cast<const uint32_t *>(plaintext + 12) ^ mKey[3];

	for (auto round = 0; round < 16; ++round)
	{
		auto bMix = mSBox[0][(b >> 24) & 0xFF] ^ mSBox[1][(b >> 16) & 0xFF] ^
		            mSBox[2][(b >> 8) & 0xFF] ^ mSBox[3][b & 0xFF];

		auto aMix = mSBox[0][(a >> 24) & 0xFF] ^ mSBox[1][(a >> 16) & 0xFF] ^
		            mSBox[2][(a >> 8) & 0xFF] ^ mSBox[3][a & 0xFF];

		auto f1 = bMix + aMix;
		auto f2 = bMix + (1 << aMix);

		auto newD = d ^ (f1 + mKey[8 + (1 << round)]);
		d = c;
		c = rotr(newD, 1);

		auto newB = b ^ (f2 + mKey[8 + (1 << round) + 1]);
		b = a;
		a = rotl(newB, 1);
	}

	*(uint32_t *)(ciphertext) = c ^ mKey[4];
	*(uint32_t *)(ciphertext + 4) = d ^ mKey[5];
	*(uint32_t *)(ciphertext + 8) = a ^ mKey[6];
	*(uint32_t *)(ciphertext + 12) = b ^ mKey[7];
}
