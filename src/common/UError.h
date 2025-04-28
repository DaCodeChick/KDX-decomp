#pragma once

#include "typedefs.h"

/**
 * @brief This structure is used to represent an error
 */
struct SError
{
	uint type; ///< Type of error
	void *field2_0x8;
	uint line; ///< Line number where the error occurred
};

class UError
{
public:
	/**
	 * @brief This function is used to get the error message
	 * @param inError The error structure
	 * @param outText The output text buffer
	 * @param inMaxSize The maximum size of the output text buffer
	 * @return The size of the error message
	 */
	static uint GetDetailMessage(SError &inError, void *outText, uint inMaxSize);
};

enum
{
	error_Param = 0x10002 ///< Error type for parameter errors
};

/**
 * @brief Function to handle errors with a type
 *
 * @param inType The type of error
 */
void __Fail(uint inType);

void __Fail(uint inType, void *inParam2, uint inLine);
