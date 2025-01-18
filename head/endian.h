/**
 * @file endian.h
 * @brief System endianness
 * @author George Witt
 * @date 2024-09-15
 *
 * IEEE 1003.1-2024 XBD.14 endian.h
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: 
 */

#if (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 202405L) || \
    (defined(_XOPEN_SOURCE) && _XOPEN_SOURCE >= 800)
#ifndef __ENDIAN_H__
#define __ENDIAN_H__ /* NOLINT(cert-dcl37-c,cert-dcl51-cpp) */

#define LITTLE_ENDIAN 0x0001
#define BIG_ENDIAN 0x0100

#ifndef __STDINT_H__
#define __STDINT_H__
#include <stdint.h>
#undef __STDINT_H__
#endif

typedef __uint16_t__ uint16_t;
typedef __uint32_t__ uint32_t;
typedef __uint64_t__ uint64_t;

#ifdef __riscv
#define BYTE_ORDER LITTLE_ENDIAN
#else
#define BYTE_ORDER
#endif

static inline uint16_t be16toh(uint16_t x)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    return x >> 8 |
           x << 8;
#elif BYTE_ORDER == BIG_ENDIAN
    return x;
#else
    return x;
#endif
}

static inline uint32_t be32toh(uint32_t x)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    return x >> 24 |
           (x >> 16 & 0xff) << 8 |
           (x >> 8 & 0xff) << 16 |
           x << 24;
#elif BYTE_ORDER == BIG_ENDIAN
    return x;
#else
    return x;
#endif
}

static inline uint64_t be64toh(uint64_t x)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    return x >> 56 |
           (x >> 48 & 0xff) << 8 |
           (x >> 40 & 0xff) << 16 |
           (x >> 32 & 0xff) << 24 |
           (x >> 24 & 0xff) << 32 |
           (x >> 16 & 0xff) << 40 |
           (x >> 8 & 0xff) << 48 |
           x << 56;
#elif BYTE_ORDER == BIG_ENDIAN
    return x;
#else
    return x;
#endif
}


static inline uint16_t htobe16(uint16_t y)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    return y << 8 |
           y >> 8;
#elif BYTE_ORDER == BIG_ENDIAN
    return y;
#else
    return y;
#endif
}

static inline uint32_t htobe32(uint32_t y)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    return y << 24 |
           (y >> 8 & 0xff) << 16 |
           (y >> 16 & 0xff) << 8 |
           y >> 24;
#elif BYTE_ORDER == BIG_ENDIAN
    return y;
#else
    return y;
#endif
}

static inline uint64_t htobe64(uint64_t y)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    return y << 56 |
           (y >> 8 & 0xff) << 48 |
           (y >> 16 & 0xff) << 40 |
           (y >> 24 & 0xff) << 32 |
           (y >> 32 & 0xff) << 24 |
           (y >> 40 & 0xff) << 16 |
           (y >> 48 & 0xff) << 8 |
           y >> 56;
#elif BYTE_ORDER == BIG_ENDIAN
    return y;
#else
    return y;
#endif
}


static inline uint16_t htole16(uint16_t y)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    return y;
#elif BYTE_ORDER == BIG_ENDIAN
    return y >> 8 |
           y << 8;
#else
    return y;
#endif
}

static inline uint32_t htole32(uint32_t y)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    return y;
#elif BYTE_ORDER == BIG_ENDIAN
    return y >> 24 |
           (y >> 16 & 0xff) << 8 |
           (y >> 8 & 0xff) << 16 |
           y << 24;
#else
    return y;
#endif
}

static inline uint64_t htole64(uint64_t y)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    return y;
#elif BYTE_ORDER == BIG_ENDIAN
    return y >> 56 |
           (y >> 48 & 0xff) << 8 |
           (y >> 40 & 0xff) << 16 |
           (y >> 32 & 0xff) << 24 |
           (y >> 24 & 0xff) << 32 |
           (y >> 16 & 0xff) << 40 |
           (y >> 8 & 0xff) << 48 |
           y << 56;
#else
    return y;
#endif
}


static inline uint16_t le16toh(uint16_t x)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    return x;
#elif BYTE_ORDER == BIG_ENDIAN
    return x << 8 |
           x >> 8;
#else
    return x;
#endif
}

static inline uint32_t le32toh(uint32_t x)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    return x;
#elif BYTE_ORDER == BIG_ENDIAN
    return x << 24 |
           (x >> 8 & 0xff) << 16 |
           (x >> 16 & 0xff) << 8 |
           x >> 24;
#else
    return x;
#endif
}

static inline uint64_t le64toh(uint64_t x)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    return x;
#elif BYTE_ORDER == BIG_ENDIAN
    return x << 56 |
           (x >> 8 & 0xff) << 48 |
           (x >> 16 & 0xff) << 40 |
           (x >> 24 & 0xff) << 32 |
           (x >> 32 & 0xff) << 24 |
           (x >> 40 & 0xff) << 16 |
           (x >> 48 & 0xff) << 8 |
           x >> 56;
#else
    return x;
#endif
}


#endif /* __ENDIAN_H__ */
#endif
