#include <cstring>
#include <gtest/gtest.h>

#include "../src/common/CTwofish.h"

TEST(Twofish, EncryptFast)
{
	CTwofish twofish("0123456789abcdef0123456789abcdefghijklmnop");
	uint8_t inData[16] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
	                      0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10};
	uint8_t outData[16] = {0x00};
	twofish.EncryptFast(inData, outData);
	EXPECT_EQ(std::memcmp(outData,
	                      "\x6f\x09\x0b\x0c\xb8\x0f\x0f\x10\x57\x02\x03\x04\xea\x06\x07\x08", 16),
	          0);
}

TEST(Twofish, EncryptFull)
{
	CTwofish twofish("0123456789abcdef0123456789abcdefghijklmnop");
	uint8_t inData[16] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
	                      0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10};
	uint8_t outData[16] = {0x00};
	twofish.EncryptFull(inData, outData);
	EXPECT_EQ(std::memcmp(outData,
	                      "\xad\x0b\x0b\x0c\xde\x0f\x0f\x10\x71\x00\x03\x04\xe8\x06\x07\x08", 16),
	          0);
}
