#include <cstring>
#include <cstdio>
#include <gtest/gtest.h>

#include "../src/common/CTwofish.h"
#include "../src/common/UCryptTransact.h"

TEST(Twofish, Encrypt)
{
	uint8_t key[32] = {0};
	uint8_t data[16] = {0};
	UCryptTransact::GenerateKey("May your progress bars smile at you.", 37, key);
	UCryptTransact::GenerateKey("To download, or not to download, that is the question.", 55, data);
	CTwofish twofish(key);
	uint8_t outData[16] = {0x00};
	twofish.Encrypt(data, outData);

	for (int i = 0; i < 16; ++i)
	{
		printf("\\x%02X", outData[i]);
	}

	EXPECT_EQ(std::memcmp(outData,
	                      "\x3F\x49\xCD\x20\xF0\xA2\x0D\x2A\x92\x81\xFC\x9F\x0F\xC5\xA3\x83", 16),
	          0);
}

TEST(Twofish, EncryptCBC)
{
	uint8_t key[32] = { 0};
	UCryptTransact::GenerateKey("I am Gopher Boy, pondering reality", 35, key);
	
	for (int i = 0; i < 32; ++i)
	{
		printf("%02X", key[i]);
	}
	
	CTwofish twofish(key);
	uint8_t inData[] = "Look, no bigger than a chestnut, but he eats as if his siesta depended on it!";
	uint8_t outData[78] = {0x00};
	size_t outSize = 0;
	twofish.EncryptCBC(outData, outSize, inData, 78);
	
	for (int i = 0; i < 78; ++i)
	{
		printf("\\x%02X", outData[i]);
	}
	
	EXPECT_EQ(
	    std::memcmp(
	        outData,
	        "\x8A\x62\x69\x67\x24\x64\x72\x20\x9C\x6C\x6F\x6B\xBE\x20\x6E\x6F\xCF\x66\x73\x74\x18\x76\x74\x2C\xFB\x68\x61\x6E\x9A\x62\x20\x63\xF9\x61\x74\x73\x97\x61\x73\x20\xA0\x61\x75\x74\xAF\x6A\x65\x20\x4F\x65\x73\x74\x57\x23\x64\x65\x7C\x64\x20\x68\x38\x71\x20\x73\x70\x65\x6E\x64\x65\x64\x20\x6F\x6E\x20\x69\x74\x21\x00",
	        78),
	    0);
}
