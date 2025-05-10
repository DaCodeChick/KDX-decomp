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

TEST(Twofish, EncryptCBC)
{
	CTwofish twofish("0123456789abcdef0123456789abcdefghijklmnop");
	uint8_t inData[40] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
	                      0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14,
	                      0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e,
	                      0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28};
	uint8_t outData[40] = {0x00};
	size_t outSize = 0;
	twofish.EncryptCBC(outData, outSize, inData, 40, "0123456789abcdef0123456789abcdefghijklmnop");
	EXPECT_EQ(
	    std::memcmp(
	        outData,
	        "\xad\x0b\x0b\x0c\xde\x0f\x0f\x10\x71\x00\x03\x04\xe8\x06\x07\x08\x27\x19\x1b\x1c\x55"
	        "\x1e\x1f\x20\x58\x10\x13\x14\x7a\x14\x17\x18\x21\x22\x23\x24\x25\x26\x27\x28",
	        40),
	    0);
}
