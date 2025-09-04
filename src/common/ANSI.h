#pragma once

#include "typedefs.h"

HXAPI size_t pstrcpy(uint8_t *dst, const uint8_t *src);
HXAPI size_t pstrncpy(uint8_t *dst, const uint8_t *src, size_t len);
HXAPI size_t pstrcat(uint8_t *dst, const uint8_t *src);
HXAPI size_t pstrncat(uint8_t *dst, const uint8_t *src, size_t len);
HXAPI bool pstrcmp(const uint8_t *str1, const uint8_t *str2);
HXAPI bool pstrncmp(const uint8_t *str1, const uint8_t *str2, size_t len);
HXAPI const uint8_t *pstrchr(const uint8_t *str, uint8_t chr);
HXAPI const uint8_t *pstrrchr(const uint8_t *str, uint8_t chr);
HXAPI void pstrrev(uint8_t *str);
HXAPI const uint8_t *pstrstr(const uint8_t *str, size_t str_len, const uint8_t *pat, size_t pat_len);
HXAPI uint8_t *pstrndup(const uint8_t *str, size_t len);
HXAPI uint8_t *pstrdup(const uint8_t *str);
