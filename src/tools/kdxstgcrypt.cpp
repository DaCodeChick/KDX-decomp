#include <fstream>
#include <iostream>
#include <string>

#include "../client/Client.h"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: kdxstgcrypt <filename>" << std::endl;
		return 1;
	}

	std::ifstream file(argv[1], std::ios::binary);
	if (!file)
	{
		std::cerr << "Error opening file: " << argv[1] << std::endl;
		return 1;
	}

	file.seekg(0, std::ios::end);
	auto fileSize = file.tellg();
	file.seekg(0, std::ios::beg);
	auto data = new uint8_t[fileSize];
	if (!data)
	{
		std::cerr << "Memory allocation failed" << std::endl;
		return 1;
	}
	file.read(reinterpret_cast<char *>(data), fileSize);
	file.close();
	SettingsCrypt(data, fileSize);

	std::ofstream outFile("decrypted_" + std::string(argv[1]), std::ios::binary);
	outFile.write(reinterpret_cast<const char *>(data), fileSize);
	outFile.close();
	delete[] data;

	return 0;
}