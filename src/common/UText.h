#pragma once

#include "typedefs.h"

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
	static void Format(void *outText, uint inMaxSize, const char *inFormat, ...);

	/**
	 * @brief Format an integer to a string.
	 * 
	 * @param inInteger
	 * @param outText 
	 * @param inMaxSize 
	 * @param inOptions 
	 * @return uint 
	 */
	static uint IntegerToText(uint inInteger, void *outText, uint inMaxSize, uint inOptions);

	/**
	 * @brief Convert a string to an integer.
	 * 
	 * @param inText 
	 * @param inTextSize 
	 * @param inOptions 
	 * @return uint 
	 */
	static uint TextToInteger(const void *inText, uint inTextSize, uint inOptions);

	/**
	 * @brief Converts a character to lowercase.
	 * 
	 * @param inChar
	 * @return constexpr uint 
	 */
	static constexpr uint ToLower(uint inChar);

	/**
	 * @brief Converts a string to lowercase.
	 * 
	 * @param inText
	 * @param inTextSize 
	 * @param outText 
	 * @param inMaxSize 
	 */
	static void ToLower(const void *inText, uint inTextSize, void *outText, uint inMaxSize);

	/**
	 * @brief Converts a character to uppercase.
	 * 
	 * @param inChar 
	 * @return constexpr uint 
	 */
	static constexpr uint ToUpper(uint inChar);
	static constexpr bool IsHex(uint inChar);
};
