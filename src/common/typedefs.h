#pragma once

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

typedef unsigned char byte;
typedef long long longlong;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;
typedef unsigned short ushort;

#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__)
    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        #define IS_LITTLE_ENDIAN
    #endif
#elif defined(_WIN32) || defined(__i386__) || defined(__x86_64__)
    #define IS_LITTLE_ENDIAN
#endif

#define BSWAP16(x) \
    ((((x) & 0xff00) >> 8) | \
    (((x) & 0x00ff) << 8))

#define BSWAP32(x) \
	((((x) & 0xff000000) >> 24) | \
	(((x) & 0x00ff0000) >>  8) | \
	(((x) & 0x0000ff00) <<  8) | \
	(((x) & 0x000000ff) << 24))

#define BSWAP64(x) \
	((((x) & 0xff00000000000000ULL) >> 56) | \
	(((x) & 0x00ff000000000000ULL) >> 40) | \
	(((x) & 0x0000ff0000000000ULL) >> 24) | \
	(((x) & 0x000000ff00000000ULL) >>  8) | \
	(((x) & 0x00000000ff000000ULL) <<  8) | \
	(((x) & 0x0000000000ff0000ULL) << 24) | \
	(((x) & 0x000000000000ff00ULL) << 40) | \
	(((x) & 0x00000000000000ffULL) << 56))

#ifdef IS_LITTLE_ENDIAN
#define NTOHS(x) BSWAP16(x)
#define NTOHL(x) BSWAP32(x)
#define NTOHLL(x) BSWAP64(x)
#define HTONS(x) BSWAP16(x)
#define HTONL(x) BSWAP32(x)
#define HTONLL(x) BSWAP64(x)
#else
#define NTOHS(x) (x)
#define NTOHL(x) (x)
#define NTOHLL(x) (x)
#define HTONS(x) (x)
#define HTONL(x) (x)
#define HTONLL(x) (x)
#endif // IS_LITTLE_ENDIAN
