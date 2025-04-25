#include "ANSI.h"

unsigned pstrcpy(unsigned char *dst, const unsigned char *src)
{
    if (!dst || !src) return 0;
    dst[0] = src[0];
    for (unsigned char i = 1; i <= dst[0]; i++)
        dst[i] = src[i];
    return dst[0];
}
