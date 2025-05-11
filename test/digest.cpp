#include <cstring>
#include <gtest/gtest.h>

#include "../src/common/UDigest.h"

TEST(Digest, MD5)
{
	const char testData[] = "Hello, World!";
	const size_t testDataSize = strlen(testData);
	uint8_t digest[16] = {0};
	UDigest::MD5_Encode(testData, testDataSize, digest);
	EXPECT_EQ(0,
	          std::memcmp(digest,
	                      "\x24\x80\xFC\x9F\x93\xC5\xA3\x83\xBE\x4A\xCD\x20\x77\xA2\x0D\x2A", 16));
}
