#include "ANSI.h"

unsigned pstrcpy(unsigned char *dst, const unsigned char *src)
{
	if (!dst || !src) return 0;
	dst[0] = src[0];
	for (unsigned char i = 1; i <= dst[0]; i++)
		dst[i] = src[i];
	return dst[0];
}

unsigned pstrncpy(unsigned char *dst, const unsigned char *src, unsigned len)
{
}

unsigned pstrcat(unsigned char *dst, const unsigned char *src)
{
}

unsigned pstrncat(unsigned char *dst, const unsigned char *src, unsigned len)
{
}

bool pstrcmp(const unsigned char *str1, const unsigned char *str2)
{
}

unsigned char *pstrchr(const unsigned char *str, unsigned char chr)
{
}

unsigned char *pstrrchr(const unsigned char *str, unsigned char chr)
{
}
