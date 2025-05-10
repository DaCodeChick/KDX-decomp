#include <cstring>
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>

#include "../src/common/UText.h"

TEST(Tokenizer, TrimWhitespace)
{
	STokenizer tokenizer;
	std::vector<std::string> tokens;
	const char text[] = "The brown fox jumps over the lazy dog";
	const char delimiters[] = " .";
	UText::InitTokenizer(tokenizer, text, std::strlen(text), delimiters, 0);

	std::string token = static_cast<const char *>(UText::GetNextToken(tokenizer, nullptr, nullptr));
	while (!token.empty())
	{
		std::cout << "Token: " << token << std::endl;
		tokens.push_back(token);
		token = static_cast<const char *>(UText::GetNextToken(tokenizer, nullptr, nullptr));
	}

	std::cout << "Tokens: ";
	for (const auto &t : tokens)
	{
		std::cout << t << " ";
	}
	std::cout << std::endl;

	EXPECT_EQ(tokens.size(), 9);
}
