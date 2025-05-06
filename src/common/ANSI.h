#pragma once

#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

	unsigned pstrcpy(unsigned char *dst, const unsigned char *src);
	unsigned pstrncpy(unsigned char *dst, const unsigned char *src, unsigned len);
	unsigned pstrcat(unsigned char *dst, const unsigned char *src);
	unsigned pstrncat(unsigned char *dst, const unsigned char *src, unsigned len);
	bool pstrcmp(const unsigned char *str1, const unsigned char *str2);
	bool pstrncmp(const unsigned char *str1, const unsigned char *str2, unsigned len);
	unsigned char *pstrchr(const unsigned char *str, unsigned char chr);
	unsigned char *pstrrchr(const unsigned char *str, unsigned char chr);
	void pstrrev(unsigned char *str);
	unsigned char *pstrstr(const unsigned char *str1, unsigned len1, const unsigned char *str2,
	                       unsigned len2);

#ifdef __cplusplus
}
#endif // __cplusplus
