#pragma once

#include "typedefs.h"

/// @brief A class that tokenizes a string based on specified delimiters.
class CTokenizer
{
public:
	/**
	 * @brief Constructor for CTokenizer.
	 * 
	 * @param inText The text to be tokenized.
	 * @param inTextSize The size of the text.
	 * @param inDelimiters The delimiters used for tokenization.
	 * @param inOptions Options for tokenization.
	 */
	CTokenizer(const void *inText, size_t inTextSize, const void *inDelimiters, unsigned inOptions);
private:
	typedef uint8_t *(*TNextTokenProc)(CTokenizer *inContext, size_t *outSize, uint8_t *outDelimiters);

	TNextTokenProc *mNextTokenProc;
	const uint8_t *mStart;
	const uint8_t *mEnd;
	unsigned mFlags;
	size_t mPos;
	unsigned mDelimiterBits[7];

	uint8_t *GetNextToken(size_t *outSize, uint8_t *outDelimiter);
	uint8_t *GetNextTokenWithDelimiters(CTokenizer *inContext, size_t *outSize, uint8_t *outDelimiter);
	uint8_t *GetNextTokenTrimmingWhitespace(CTokenizer *inContext, size_t *outSize, uint8_t *outDelimiter);
};
