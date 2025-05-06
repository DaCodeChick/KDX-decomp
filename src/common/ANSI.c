#include "ANSI.h"

unsigned pstrcpy(unsigned char *dst, const unsigned char *src)
{
	if (!dst || !src)
		return 0;
	dst[0] = src[0];
	for (unsigned i = 1; i <= dst[0]; i++)
		dst[i] = src[i];
	return dst[0];
}

unsigned pstrncpy(unsigned char *dst, const unsigned char *src, unsigned len)
{
	if (!dst || !src || !len)
		return 0;
	dst[0] = (src[0] < len) ? src[0] : len;
	for (unsigned i = 1; i <= dst[0]; i++)
		dst[i] = src[i];
	return dst[0];
}

unsigned pstrcat(unsigned char *dst, const unsigned char *src)
{
	if (!dst || !src)
		return 0;

	unsigned total_len = dst[0] + src[0];
	unsigned src_len = src[0];

	if (total_len > 255)
	{
		total_len = 255;
		src_len = 255 - dst[0];
	}

	dst[0] = (unsigned char)total_len;
	for (unsigned i = 1; i <= src_len; i++)
		dst[dst[0] + i] = src[i];
	return dst[0];
}

unsigned pstrncat(unsigned char *dst, const unsigned char *src, unsigned len)
{
	if (!dst || !src || !len)
		return 0;

	unsigned copy_len = (src[0] < len) ? src[0] : len;
	unsigned total_len = dst[0] + copy_len;

	if (total_len > 255)
	{
		total_len = 255;
		copy_len = 255 - dst[0];
	}

	dst[0] = (unsigned char)total_len;
	for (unsigned i = 1; i <= copy_len; i++)
		dst[dst[0] + i] = src[i];
	return dst[0];
}

bool pstrcmp(const unsigned char *str1, const unsigned char *str2)
{
	if (!str1 || !str2)
		return false;
	if (str1[0] != str2[0])
		return false;
	for (unsigned i = 1; i <= str1[0]; i++)
		if (str1[i] != str2[i])
			return false;
	return true;
}

bool pstrncmp(const unsigned char *str1, const unsigned char *str2, unsigned len)
{
	if (!str1 || !str2 || len == 0)
		return false;

	unsigned min_len = (str1[0] < len) ? str1[0] : len;
	min_len = (str2[0] < min_len) ? str2[0] : min_len;

	for (unsigned i = 1; i <= min_len; i++)
		if (str1[i] != str2[i])
			return false;
	return true;
}

unsigned char *pstrchr(const unsigned char *str, unsigned char chr)
{
	if (!str)
		return 0;
	for (unsigned i = 1; i <= str[0]; i++)
		if (str[i] == chr)
			return &str[i];
	return 0;
}

unsigned char *pstrrchr(const unsigned char *str, unsigned char chr)
{
	if (!str)
		return 0;
	for (unsigned i = str[0]; i > 0; i--)
		if (str[i] == chr)
			return &str[i];
	return 0;
}

void pstrrev(unsigned char *str)
{
	if (!str || str[0] == 0)
		return;

	unsigned len = str[0];
	for (unsigned i = 1, j = len; i < j; i++, j--)
	{
		unsigned char temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
}

unsigned char *pstrstr(const unsigned char *str, unsigned str_len, const unsigned char *pat,
                       unsigned pat_len)
{
	if (!str || !pat || !pat_len || str_len < pat_len)
		return 0;
	if (pat_len == 1)
	{
		for (unsigned i = 0; i < str_len; i++)
			if (str[i] == pat[0])
				return &str[i];
		return 0;
	}

	unsigned skip_table[256];
	for (unsigned i = 0; i < 256; i++)
		skip_table[i] = pat_len;
	for (unsigned i = 0; i < pat_len - 1; i++)
		skip_table[pat[i]] = pat_len - 1 - i;
		
	unsigned i = 0;
	while (i <= str_len - pat_len)
	{
		unsigned j = pat_len - 1;
		while (j < pat_len && str[i + j] == pat[j])
			j--;
		if (j == -1)
			return (unsigned char *)&str[i];
		i += skip_table[str[i + pat_len - 1]];
	}

	return 0;
}
