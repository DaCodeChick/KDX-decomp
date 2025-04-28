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

/**
 * @brief swap bytes in 16-bit value
 * 
 * @param x 16-bit value to swap
 * @return swapped 16-bit value
 */
constexpr ushort bswap16(ushort x) noexcept
{
	return ((x & 0xFF00) >> 8) | ((x & 0x00FF) << 8);
}

/**
 * @brief swap bytes in 32-bit value
 * 
 * @param x 32-bit value to swap
 * @return swapped 32-bit value
 */
constexpr uint bswap32(uint x) noexcept
{
	return ((x & 0xFF000000) >> 24) | ((x & 0x00FF0000) >> 8) | ((x & 0x0000FF00) << 8) |
	       ((x & 0x000000FF) << 24);
}

/**
 * @brief swap bytes in 64-bit value
 * 
 * @param x 64-bit value to swap
 * @return swapped 64-bit value
 */
constexpr ulonglong bswap64(ulonglong x) noexcept
{
	return ((x & 0xFF00000000000000ULL) >> 56) | ((x & 0x00FF000000000000ULL) >> 40) |
	       ((x & 0x0000FF0000000000ULL) >> 24) | ((x & 0x000000FF00000000ULL) >> 8) |
	       ((x & 0x00000000FF000000ULL) << 8) | ((x & 0x0000000000FF0000ULL) << 24) |
	       ((x & 0x000000000000FF00ULL) << 40) | ((x & 0x00000000000000FFULL) << 56);
}


/**
 * @brief Host to Network Short
 * 
 * @param x 16-bit value to convert
 * @return converted 16-bit value
 */
constexpr ushort htons(ushort x) noexcept
{
#ifdef IS_LITTLE_ENDIAN
	return bswap16(x);
#else
	return x;
#endif // IS_LITTLE_ENDIAN
}

/**
 * @brief Host to Network Long
 * 
 * @param x 32-bit value to convert
 * @return converted 32-bit value
 */
constexpr uint htonl(uint x) noexcept
{
#ifdef IS_LITTLE_ENDIAN
	return bswap32(x);
#else
	return x;
#endif // IS_LITTLE_ENDIAN
}

/**
 * @brief Host to Network Long Long
 * 
 * @param x 64-bit value to convert
 * @return converted 64-bit value
 */
constexpr ulonglong htonll(ulonglong x) noexcept
{
#ifdef IS_LITTLE_ENDIAN
	return bswap64(x);
#else
	return x;
#endif // IS_LITTLE_ENDIAN
}

/**
 * @brief Network to Host Short
 * 
 * @param x 16-bit value to convert
 * @return converted 16-bit value
 */
constexpr ushort ntohs(ushort x) noexcept
{
#ifdef IS_LITTLE_ENDIAN
	return bswap16(x);
#else
	return x;
#endif // IS_LITTLE_ENDIAN
}

/**
 * @brief Network to Host Long
 * 
 * @param x 32-bit value to convert
 * @return converted 32-bit value
 */
constexpr uint ntohl(uint x) noexcept
{
#ifdef IS_LITTLE_ENDIAN
	return bswap32(x);
#else
	return x;
#endif // IS_LITTLE_ENDIAN
}

/**
 * @brief Network to Host Long Long
 * 
 * @param x 64-bit value to convert
 * @return converted 64-bit value
 */
constexpr ulonglong ntohll(ulonglong x) noexcept
{
#ifdef IS_LITTLE_ENDIAN
	return bswap64(x);
#else
	return x;
#endif // IS_LITTLE_ENDIAN
}

/**
 * @brief Rotate left
 * 
 * @param x value to rotate
 * @param n number of bits to rotate
 * @return rotated value
 */
template <class T> constexpr T rotl(T x, uint n)
{
	return (x << n) | (x >> ((sizeof(T) << 3) - n));
}

/**
 * @brief Rotate right
 * 
 * @param x value to rotate
 * @param n number of bits to rotate
 * @return rotated value
 */
template <class T> constexpr T rotr(T x, uint n)
{
	return (x >> n) | (x << ((sizeof(T) << 3) - n));
}
