#pragma once

#include "typedefs.h"

/**
 * @brief This macro is used to handle errors with a type
 * @param type The type of error
 * @param param2 The second parameter for the error
 */
#define Fail(type, param2) __Fail(type, param2, __LINE__)

/// This structure is used to represent an error
struct SError
{
	unsigned type; ///< Type of error
	const void *field2_0x8;
	unsigned line; ///< Line number where the error occurred
};

class HXAPI UError
{
public:
	/**
	 * @brief This function is used to get the error message
	 * @param inError The error structure
	 * @param outText The output text buffer
	 * @param inMaxSize The maximum size of the output text buffer
	 * @return The size of the error message
	 */
	static unsigned GetDetailMessage(SError &inError, void *outText, size_t inMaxSize);
};

enum
{
	error10001 = 0x10001,
	error_Param, ///< Error type for parameter errors
	error10003,
	error_Unimplemented, ///< Error type for unimplemented features
	error10008 = 0x10008,
	error_Corrupt,    ///< Error type for corrupt data
	error_OutOfRange, ///< Error type for out of range errors
	error1000C = 0x1000C,
	error1000D,
	error_Invalid = 0x10019, ///< Error type for invalid data
	error_Unknown = 0x1001B, ///< Error type for unknown errors
};

/**
 * @brief Function to handle errors with a type
 *
 * @param inType The type of error
 */
HXAPI void __Fail(unsigned inType);

HXAPI void __Fail(unsigned inType, const void *inParam2, unsigned inLine);
