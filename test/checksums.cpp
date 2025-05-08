#include <cstring>
#include <gtest/gtest.h>

#include "../src/common/UMemory.h"

TEST(Checksums, AdlerSum)
{
	const char *testString = "Hello, World!";
	constexpr uint32_t expectedChecksum = 2969027416;

	auto checksum = UMemory::AdlerSum(testString, std::strlen(testString), 0xDEADBEEF);

	EXPECT_EQ(checksum, expectedChecksum)
	    << "Checksum mismatch! Expected: " << expectedChecksum << ", Got: " << checksum;
}

TEST(Checksums, CRC32)
{
	const char *testString = "Hello, World!";
	constexpr uint32_t expectedChecksum = 1142733377;

	auto checksum = UMemory::CRC(testString, std::strlen(testString), 0xDEADBEEF);

	EXPECT_EQ(checksum, expectedChecksum)
	    << "Checksum mismatch! Expected: " << expectedChecksum << ", Got: " << checksum;
}

TEST(Checksums, FNV1a)
{
	const char *testString = "Hello, World!";
	constexpr uint32_t expectedChecksum = 3532646626;

	auto checksum = UMemory::Checksum(testString, std::strlen(testString), 0xDEADBEEF);

	EXPECT_EQ(checksum, expectedChecksum)
	    << "Checksum mismatch! Expected: " << expectedChecksum << ", Got: " << checksum;
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
