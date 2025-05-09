#include "ANSI.h"

#include "UMemory.h"

size_t pstrcpy(uint8_t *dst, const uint8_t *src)
{
	if (!dst || !src)
		return 0;
	dst[0] = src[0];
	for (auto i = 1; i <= dst[0]; i++)
		dst[i] = src[i];
	return dst[0];
}

size_t pstrncpy(uint8_t *dst, const uint8_t *src, size_t len)
{
	if (!dst || !src || !len)
		return 0;
	dst[0] = (src[0] < len) ? src[0] : len;
	for (auto i = 1; i <= dst[0]; i++)
		dst[i] = src[i];
	return dst[0];
}

size_t pstrcat(uint8_t *dst, const uint8_t *src)
{
	if (!dst || !src)
		return 0;

	size_t total_len = dst[0] + src[0];
	size_t src_len = src[0];

	if (total_len > 255)
	{
		total_len = 255;
		src_len = 255 - dst[0];
	}

	dst[0] = static_cast<uint8_t>(total_len);
	for (auto i = 1; i <= src_len; i++)
		dst[dst[0] + i] = src[i];
	return dst[0];
}

size_t pstrncat(uint8_t *dst, const uint8_t *src, size_t len)
{
	if (!dst || !src || !len)
		return 0;

	auto copy_len = (src[0] < len) ? src[0] : len;
	auto total_len = dst[0] + copy_len;

	if (total_len > 255)
	{
		total_len = 255;
		copy_len = 255 - dst[0];
	}

	dst[0] = static_cast<uint8_t>(total_len);
	for (auto i = 1; i <= copy_len; i++)
		dst[dst[0] + i] = src[i];
	return dst[0];
}

bool pstrcmp(const uint8_t *str1, const uint8_t *str2)
{
	if (!str1 || !str2)
		return false;
	if (str1[0] != str2[0])
		return false;
	for (auto i = 1; i <= str1[0]; i++)
		if (str1[i] != str2[i])
			return false;
	return true;
}

bool pstrncmp(const uint8_t *str1, const uint8_t *str2, size_t len)
{
	if (!str1 || !str2 || len == 0)
		return false;

	auto min_len = (str1[0] < len) ? str1[0] : len;
	min_len = (str2[0] < min_len) ? str2[0] : min_len;

	for (auto i = 1; i <= min_len; i++)
		if (str1[i] != str2[i])
			return false;
	return true;
}

const uint8_t *pstrchr(const uint8_t *str, uint8_t chr)
{
	if (!str)
		return NULL;
	for (auto i = 1; i <= str[0]; i++)
		if (str[i] == chr)
			return &str[i];
	return NULL;
}

const uint8_t *pstrrchr(const uint8_t *str, uint8_t chr)
{
	if (!str)
		return NULL;
	for (auto i = str[0]; i > 0; i--)
		if (str[i] == chr)
			return &str[i];
	return NULL;
}

void pstrrev(uint8_t *str)
{
	if (!str || str[0] == 0)
		return;

	for (int i = 1, j = str[0]; i < j; i++, j--)
	{
		uint8_t temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
}

const uint8_t *pstrstr(const uint8_t *str, size_t str_len, const uint8_t *pat, size_t pat_len)
{
	if (!str || !pat || !pat_len || str_len < pat_len)
		return 0;
	if (pat_len == 1)
	{
		for (auto i = 0; i < str_len; i++)
			if (str[i] == pat[0])
				return &str[i];
		return 0;
	}

	size_t skip_table[256];
	for (auto i = 0; i < 256; i++)
		skip_table[i] = pat_len;
	for (auto i = 0; i < pat_len - 1; i++)
		skip_table[pat[i]] = pat_len - 1 - i;

	auto i = 0;
	while (i <= str_len - pat_len)
	{
		auto j = pat_len - 1;
		while (j < pat_len && str[i + j] == pat[j])
			j--;
		if (j == -1)
			return &str[i];
		i += skip_table[str[i + pat_len - 1]];
	}

	return 0;
}

uint8_t *pstrndup(const uint8_t *str, size_t len)
{
	if (!str || !len)
		return NULL;
	if (len > 255)
		len = 255;

	auto new_str = static_cast<uint8_t *>(UMemory::New(len + 1));
	if (!new_str)
		return NULL;

	new_str[0] = len;
	for (auto i = 1; i < (len + 1); i++)
		new_str[i] = str[i];
	return new_str;
}

uint8_t *pstrdup(const uint8_t *str)
{
	if (!str || str[0] == 0)
		return NULL;
	auto new_str = static_cast<uint8_t *>(UMemory::New(str[0] + 1));
	if (!new_str)
		return NULL;

	new_str[0] = str[0];
	for (auto i = 1; i <= (str[0] + 1); i++)
		new_str[i] = str[i];

	return new_str;
}
