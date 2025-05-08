#include "UText.h"

#include "UMemory.h"

#include <cctype>

typedef const uint8_t *(*TNextTokenProc)(STokenizer &ioContext, size_t *outSize, uint8_t *outDelimiters);

struct STokenizer
{
	TNextTokenProc nextTokenProc;
	const uint8_t *start;
	const uint8_t *end;
	unsigned flags;
	size_t pos;
	unsigned delimiterBits[7];
};

static const uint8_t *_GetNextToken(STokenizer &ioContext, size_t *outSize, uint8_t *outDelimiter)
{
    if (ioContext.start >= ioContext.end)
	{
        if (outSize) *outSize = 0;
        return NULL;
    }

    auto current = ioContext.start;

    // Check if the first character is a delimiter
    if ((1 << (*current & 7)) & ioContext.delimiterBits[*current >> 3])
	{
        if (outDelimiter) *outDelimiter = *current;
        if (outSize) *outSize = 1;
        ioContext.start = current + 1;
        return current;
    }

    // Find the next delimiter
    while (current < ioContext.end && !((1 << (*current & 7)) & ioContext.delimiterBits[*current >> 3]))
        ++current;

    if (outSize) *outSize = current - ioContext.start;
    if (outDelimiter) *outDelimiter = 0;
    ioContext.start = current;

    return ioContext.start;
}

static const uint8_t *_GetNextTokenWithDelimiters(STokenizer &ioContext, size_t *outSize, uint8_t *outDelimiter)
{
    if (ioContext.start >= ioContext.end)
	{
        if (outSize) *outSize = 0;
        return NULL;
    }

    auto current = ioContext.start;

    // Skip leading delimiters
    while (current < ioContext.end && ((1 << (*current & 7)) & ioContext.delimiterBits[*current >> 3]))
        ++current;

    auto tokenStart = current;

    // Find the next delimiter
    while (current < ioContext.end && !((1 << (*current & 7)) & ioContext.delimiterBits[*current >> 3]))
        ++current;

    if (outSize) *outSize = current - tokenStart;
    if (outDelimiter) *outDelimiter = 0;
    ioContext.start = current;

    return tokenStart;
}

static const uint8_t *_GetNextTokenTrimmingWhitespace(STokenizer &ioContext, size_t *outSize, uint8_t *outDelimiter)
{
    if (ioContext.start >= ioContext.end)
	{
        if (outSize) *outSize = 0;
        return NULL;
    }

    auto current = ioContext.start;

    // Skip leading whitespace
    while (current < ioContext.end && std::isspace(*current))
        ++current;

    auto tokenStart = current;

    // Find the next delimiter or end of token
    while (current < ioContext.end && !((1 << (*current & 7)) & ioContext.delimiterBits[*current >> 3]) && !std::isspace(*current))
        ++current;

    if (outSize) *outSize = current - tokenStart;
    if (outDelimiter) *outDelimiter = 0;
    ioContext.start = current;

    return tokenStart;
}

void UText::InitTokenizer(STokenizer &ioContext, const void *inText, size_t inTextSize, const void *inDelimiters, unsigned inOptions)
{
	ioContext.start = reinterpret_cast<const uint8_t *>(inText);
    ioContext.end = ioContext.start + inTextSize;
    ioContext.flags = inOptions;
    ioContext.pos = 0;

    UMemory::Clear(&ioContext.delimiterBits, sizeof(ioContext.delimiterBits));

    if (inDelimiters)
	{
        auto delimiters = reinterpret_cast<const uint8_t *>(inDelimiters);
        for (auto i = 0; delimiters[i]; ++i)
            ioContext.delimiterBits[delimiters[i]] |= (1 << (delimiters[i] & 7));

    }

    if (inOptions & kTokenizeWithDelimiters)
        ioContext.nextTokenProc = _GetNextToken;
	else if (inOptions & kTokenizeTrimWhitespace)
		ioContext.nextTokenProc = _GetNextTokenTrimmingWhitespace;
	else
		ioContext.nextTokenProc = _GetNextTokenWithDelimiters;
}

const void *UText::GetNextToken(STokenizer &ioContext, size_t *outSize, void *outDelimiters)
{
	return static_cast<const void *>(ioContext.nextTokenProc(ioContext, outSize, reinterpret_cast<uint8_t *>(outDelimiters)));
}
