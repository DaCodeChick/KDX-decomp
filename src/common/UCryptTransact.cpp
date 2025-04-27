#include "UCryptTransact.h"

struct STwofish
{
	uint sbox[4][256];
	uint keys[40];
};

void UCryptTransact::TwofishEncrypt(STwofish &ioCtx, const void *inData, void *outData)
{
	const byte *plaintext = static_cast<const byte *>(inData);
	byte *ciphertext = static_cast<byte *>(outData);

	uint a = *reinterpret_cast<const uint *>(plaintext) ^ ioCtx.keys[0];
	uint b = *reinterpret_cast<const uint *>(plaintext + 4) ^ ioCtx.keys[1];
	uint c = *reinterpret_cast<const uint *>(plaintext + 8) ^ ioCtx.keys[2];
	uint d = *reinterpret_cast<const uint *>(plaintext + 12) ^ ioCtx.keys[3];

	for (int round = 0; round < 16; round += 2)
	{
		uint bMix = (ioCtx.sbox[0][(b >> 0) & 0xFF] + ioCtx.sbox[1][(b >> 8) & 0xFF]) ^
		            (ioCtx.sbox[2][(b >> 16) & 0xFF] + ioCtx.sbox[3][(b >> 24) & 0xFF]);

		uint aMix = (ioCtx.sbox[0][(a >> 8) & 0xFF] + ioCtx.sbox[1][(a >> 0) & 0xFF]) ^
		            (ioCtx.sbox[2][(a >> 24) & 0xFF] + ioCtx.sbox[3][(a >> 16) & 0xFF]);

		uint f1 = bMix + aMix;
		uint f2 = bMix + (1 << aMix);

		d = rotr(d ^ (f1 + ioCtx.keys[4 + (1 << round) + 8]), 1);
		c = rotl(c, 1) ^ (f2 + ioCtx.keys[4 + (1 << round) + 9]);

		uint dMix = (ioCtx.sbox[0][(d >> 0) & 0xFF] + ioCtx.sbox[1][(d >> 8) & 0xFF]) ^
		            (ioCtx.sbox[2][(d >> 16) & 0xFF] + ioCtx.sbox[3][(d >> 24) & 0xFF]);

		uint cMix = (ioCtx.sbox[0][(c >> 8) & 0xFF] + ioCtx.sbox[1][(c >> 0) & 0xFF]) ^
		            (ioCtx.sbox[2][(c >> 24) & 0xFF] + ioCtx.sbox[3][(c >> 16) & 0xFF]);

		uint f3 = dMix + cMix;
		uint f4 = dMix + (1 << cMix);

		b = rotr(b ^ (f3 + ioCtx.keys[4 + (1 << round) + 10]), 1);
		a = rotl(a, 1) ^ (f4 + ioCtx.keys[4 + (1 << round) + 11]);
	}

	*reinterpret_cast<uint *>(ciphertext) = c ^ ioCtx.keys[4];
	*reinterpret_cast<uint *>(ciphertext + 4) = d ^ ioCtx.keys[5];
	*reinterpret_cast<uint *>(ciphertext + 8) = a ^ ioCtx.keys[6];
	*reinterpret_cast<uint *>(ciphertext + 12) = b ^ ioCtx.keys[7];
}

void UCryptTransact::TwofishEncryptSimple(STwofish &ioCtx, const void *inData, void *outData)
{
	const byte *plaintext = static_cast<const byte *>(inData);
	byte *ciphertext = static_cast<byte *>(outData);

	uint a = *reinterpret_cast<const uint *>(plaintext) ^ ioCtx.keys[0];
	uint b = *reinterpret_cast<const uint *>(plaintext + 4) ^ ioCtx.keys[1];
	uint c = *reinterpret_cast<const uint *>(plaintext + 8) ^ ioCtx.keys[2];
	uint d = *reinterpret_cast<const uint *>(plaintext + 12) ^ ioCtx.keys[3];

	for (int round = 0; round < 16; ++round)
	{
		// Compute F function for b and a
		uint bMix = ioCtx.sbox[0][(b >> 24) & 0xFF] ^ ioCtx.sbox[1][(b >> 16) & 0xFF] ^ ioCtx.sbox[2][(b >> 8) & 0xFF] ^
		            ioCtx.sbox[3][b & 0xFF];

		uint aMix = ioCtx.sbox[0][(a >> 24) & 0xFF] ^ ioCtx.sbox[1][(a >> 16) & 0xFF] ^ ioCtx.sbox[2][(a >> 8) & 0xFF] ^
		            ioCtx.sbox[3][a & 0xFF];

		uint f1 = bMix + aMix;
		uint f2 = bMix + (1 << aMix);

		uint newD = d ^ (f1 + ioCtx.keys[8 + (1 << round)]);
		d = c;
		c = rotr(newD, 1);

		uint newB = b ^ (f2 + ioCtx.keys[8 + (1 << round) + 1]);
		b = a;
		a = rotl(newB, 1);
	}

	*reinterpret_cast<uint *>(ciphertext) = c ^ ioCtx.keys[4];
	*reinterpret_cast<uint *>(ciphertext + 4) = d ^ ioCtx.keys[5];
	*reinterpret_cast<uint *>(ciphertext + 8) = a ^ ioCtx.keys[6];
	*reinterpret_cast<uint *>(ciphertext + 12) = b ^ ioCtx.keys[7];
}