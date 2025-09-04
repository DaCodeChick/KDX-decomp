#include <cstring>
#include <gtest/gtest.h>

#include "../src/common/UDigest.h"

TEST(Digest, MD5)
{
	const char testData[] = "Hello, World!";
	const size_t testDataSize = strlen(testData);
	uint8_t digest[20] = {0};
	UDigest::MD5_Encode(testData, testDataSize, digest);

	EXPECT_EQ(0,
	          std::memcmp(digest,
	                      "\x3E\xC7\x28\xAC\xFE\x88\xFE\xA4\x18\x50\x0A\x8B\xFB\x20\x01\x68\x0B\x81\xA1\x38", 20));
}
