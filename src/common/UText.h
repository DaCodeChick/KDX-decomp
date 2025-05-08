#pragma once

#include "typedefs.h"

typedef const uint8_t *(*TNextTokenProc)(STokenizer &ioContext, size_t *outSize,
                                         uint8_t *outDelimiters);

/// @brief A structure representing a tokenizer context.
struct STokenizer
{
	static constexpr unsigned kDefaultOptions = 0;      ///< Default options for tokenization.
	static constexpr unsigned kWithDelimiters = 1 << 0; ///< Option to include delimiters in tokens.
	static constexpr unsigned kTrimWhitespace = 1 << 1; ///< Option to trim whitespace from tokens.

	TNextTokenProc nextTokenProc; ///< Function pointer for getting the next token.
	const uint8_t *start;         ///< Pointer to the start of the text.
	const uint8_t *end;           ///< Pointer to the end of the text.
	unsigned flags;               ///< Flags for tokenizer options.
	size_t pos;                   ///< Current position in the text.
	unsigned delimiterBits[7];    ///< Array of bits representing delimiters.
};

/// @brief A class for text manipulation and formatting.
class UText
{
public:
	/**
	 * @brief Tokenize a string into tokens based on delimiters.
	 *
	 * @param ioContext
	 * @param inText
	 * @param inTextSize
	 * @param inDelimiters
	 * @param inOptions
	 */
	static void InitTokenizer(STokenizer &ioContext, const void *inText, size_t inTextSize,
	                          const void *inDelimiters, unsigned inOptions);

	/**
	 * @brief Get the next token from the tokenizer context.
	 *
	 * @param ioContext
	 * @param outSize
	 * @param outDelimiters
	 * @return const void*
	 */
	static const void *GetNextToken(STokenizer &ioContext, size_t *outSize, void *outDelimiters);

	/**
	 * @brief Format a string with a given format and arguments.
	 *
	 * @param outText
	 * @param inMaxSize
	 * @param inFormat
	 * @param ...
	 */
	static void Format(void *outText, size_t inMaxSize, const char *inFormat, ...);

	/**
	 * @brief Format an integer to a string.
	 *
	 * @param inInteger
	 * @param outText
	 * @param inMaxSize
	 * @param inOptions
	 * @return uint
	 */
	static size_t IntegerToText(unsigned inInteger, void *outText, size_t inMaxSize,
	                            unsigned inOptions);

	/**
	 * @brief Convert a string to an integer.
	 *
	 * @param inText
	 * @param inTextSize
	 * @param inOptions
	 * @return uint
	 */
	[[nodiscard]] static unsigned TextToInteger(const void *inText, size_t inTextSize,
	                                            unsigned inOptions);

	/**
	 * @brief Converts a character to lowercase.
	 *
	 * @param inChar
	 * @return constexpr uint
	 */
	[[nodiscard]] static constexpr unsigned ToLower(unsigned inChar);

	/**
	 * @brief Converts a string to lowercase.
	 *
	 * @param inText
	 * @param inTextSize
	 * @param outText
	 * @param inMaxSize
	 */
	static void ToLower(const void *inText, size_t inTextSize, void *outText, size_t inMaxSize);

	/**
	 * @brief Converts a character to uppercase.
	 *
	 * @param inChar
	 * @return constexpr uint
	 */
	[[nodiscard]] static constexpr unsigned ToUpper(unsigned inChar);

	[[nodiscard]] static constexpr bool IsHex(unsigned inChar);

	static unsigned EncodeUTF8(unsigned inChar, void *outText, size_t inMaxSize);

	static unsigned DecodeUTF8(const void *inText, size_t inTextSize, unsigned &outChar);

	static unsigned FilterUTF8(const void *inFilter, const void *inText, size_t inTextSize,
	                           const void *outText, size_t inOutTextSize);

	static size_t ValidateUTF8(const void *inText, size_t inTextSize);
};
