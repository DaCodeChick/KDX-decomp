#include "CTokenizer.h"

#include "UMemory.h"

CTokenizer::CTokenizer(const void *inText, size_t inTextSize, const void *inDelimiters, unsigned inOptions)
{
    mStart = reinterpret_cast<const uint8_t *>(inText);
    mEnd = mStart + inTextSize;
    mFlags = inOptions;
    mPos = 0;

    UMemory::Clear(&mDelimiterBits, sizeof(mDelimiterBits));

    if (inDelimiters)
	{
        auto delimiters = reinterpret_cast<const uint8_t *>(inDelimiters);
        for (auto i = 0; delimiters[i]; ++i)
            mDelimiterBits[delimiters[i]] |= (1 << (delimiters[i] & 7));

    }

    if (inOptions & 1)
        mNextTokenProc = GetNextToken;
	else if (inOptions & 2)
		mNextTokenProc = GetNextTokenWithDelimiters;
    else
		mNextTokenProc = GetNextTokenTrimmingWhitespace;
}
