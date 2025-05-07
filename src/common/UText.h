#pragma once

#include "typedefs.h"

struct STokenizer;

/// @brief A class for text manipulation and formatting.
class UText
{
public:
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

	static unsigned FilterUTF8(const void *inFilter, const void *inText, size_t inTextSize, const void *outText, size_t inOutTextSize);

	static size_t ValidateUTF8(const void *inText, size_t inTextSize);
};
