#ifndef UTIL_H
#define UTIL_H

#include <stddef.h>
#include <stdint.h>
#include <endian.h>

#define ROTL64(x, c) __rotl64(x, c)
#define ROTL32(x, c) __rotl32(x, c)
#define ROTL16(x, c) __rotl16(x, c)
#define ROTL8(x, c) __rotl8(x, c)
#define ROTR64(x, c) __rotr64(x, c)
#define ROTR32(x, c) __rotr32(x, c)
#define ROTR16(x, c) __rotr16(x, c)
#define ROTR8(x, c) __rotr8(x, c)

#define U8TO64_LE(x) __u8tole64(x)
#define U8TO32_LE(x) __u8tole32(x)
#define U9TO16_LE(x) __u8tole16(x)
#define U64TO8_LE(y, x) __leu64to8(y, x)
#define U32TO8_LE(y, x) __leu32to8(y, x)
#define U16TO8_LE(y, x) __leu16to8(y, x)
#define U8TO64_BE(x) __u8tobe64(x)
#define U8TO32_BE(x) __u8tobe32(x)
#define U8TO16_BE(x) __u8tobe16(x)
#define U64TO8_BE(y, x) __beu64to8(y, x)
#define U32TO8_BE(y, x) __beu32to8(y, x)
#define U16TO8_BE(y, x) __beu16to8(y, x)

#if BYTE_ORDER == LITTLE_ENDIAN
#define U8TO64(x) __u8tole64(x)
#define U8TO32(x) __u8tole32(x)
#define U8TO16(x) __u8tole16(x)
#define U64TO8(y, x) __leu64to8(y, x)
#define U32TO8(y, x) __leu32to8(y, x)
#define U16TO8(y, x) __leu16to8(y, x)
#elif BYTE_ORDER == BIG_ENDIAN
#define U8TO64(x) __u8tobe64(x)
#define U8TO32(x) __u8tobe32(x)
#define U8TO16(x) __u8tobe16(x)
#define U64TO8(y, x) __beu64to8(y, x)
#define U32TO8(y, x) __beu32to8(y, x)
#define U16TO8(y, x) __beu16to8(y, x)
#else
#endif

static inline uint64_t __rotl64(uint64_t x, uint8_t c)
{
    return UINT64_MAX & (x << (c % 64) | x >> (64 - (c % 64)));
}

static inline uint32_t __rotl32(uint32_t x, uint8_t c)
{
    return UINT32_MAX & (x << (c % 32) | x >> (32 - (c % 32)));
}

static inline uint16_t __rotl16(uint16_t x, uint8_t c)
{
    return UINT16_MAX & (x << (c % 16) | x >> (16 - (c % 16)));
}

static inline uint8_t __rotl8(uint8_t x, uint8_t c)
{
    return UINT8_MAX & (x << (c % 8) | x >> (8 - (c % 8)));
}

static inline uint64_t __rotr64(uint64_t x, uint8_t c)
{
    return UINT64_MAX & (x >> (c % 64) | x << (64 - (c % 64)));
}

static inline uint32_t __rotr32(uint32_t x, uint8_t c)
{
    return UINT32_MAX & (x >> (c % 32) | x << (32 - (c % 32)));
}

static inline uint16_t __rotr16(uint16_t x, uint8_t c)
{
    return UINT16_MAX & (x >> (c % 16) | x << (16 - (c % 16)));
}

static inline uint8_t __rotr8(uint8_t x, uint8_t c)
{
    return UINT8_MAX & (x >> (c % 8) | x << (8 - (c % 8)));
}

static inline uint64_t __u8tole64(const uint8_t x[static 8])
{
    return (uint64_t)x[0] | 
           (uint64_t)x[1] << 8 | 
           (uint64_t)x[2] << 16 | 
           (uint64_t)x[3] << 24 | 
           (uint64_t)x[4] << 32 | 
           (uint64_t)x[5] << 40 | 
           (uint64_t)x[6] << 48 | 
           (uint64_t)x[7] << 56;
}

static inline uint32_t __u8tole32(const uint8_t x[static 4])
{
    return (uint32_t)x[0] | 
           (uint32_t)x[1] << 8 | 
           (uint32_t)x[2] << 16 | 
           (uint32_t)x[3] << 24;
}

static inline uint16_t __u8tole16(const uint8_t x[static 2])
{
    return (uint16_t)x[0] | 
           (uint16_t)x[1] << 8;
}

static inline uint64_t __u8tobe64(const uint8_t x[static 8])
{
    return (uint64_t)x[7] | 
           (uint64_t)x[6] << 8 | 
           (uint64_t)x[5] << 16 | 
           (uint64_t)x[4] << 24 | 
           (uint64_t)x[3] << 32 | 
           (uint64_t)x[2] << 40 | 
           (uint64_t)x[1] << 48 | 
           (uint64_t)x[0] << 56;
}

static inline uint32_t __u8tobe32(const uint8_t x[static 4])
{
    return (uint32_t)x[3] | 
           (uint32_t)x[2] << 8 | 
           (uint32_t)x[1] << 16 | 
           (uint32_t)x[0] << 24;
}

static inline uint16_t __u8tobe16(const uint8_t x[static 2])
{
    return (uint16_t)x[1] | 
           (uint16_t)x[0] << 8;
}

static inline void __leu64to8(uint8_t y[static 8], uint64_t x)
{
    y[0] = (uint8_t)(x & 0xff);
    y[1] = (uint8_t)(x >> 8 & 0xff);
    y[2] = (uint8_t)(x >> 16 & 0xff);
    y[3] = (uint8_t)(x >> 24 & 0xff);
    y[4] = (uint8_t)(x >> 32 & 0xff);
    y[5] = (uint8_t)(x >> 40 & 0xff);
    y[6] = (uint8_t)(x >> 48 & 0xff);
    y[7] = (uint8_t)(x >> 56 & 0xff);
}

static inline void __leu32to8(uint8_t y[static 4], uint32_t x)
{
    y[0] = (uint8_t)(x & 0xff);
    y[1] = (uint8_t)(x >> 8 & 0xff);
    y[2] = (uint8_t)(x >> 16 & 0xff);
    y[3] = (uint8_t)(x >> 24 & 0xff);
}

static inline void __leu16to8(uint8_t y[static 2], uint16_t x)
{
    y[0] = (uint8_t)(x & 0xff);
    y[1] = (uint8_t)(x >> 8 & 0xff);
}

static inline void __beu64to8(uint8_t y[static 8], uint64_t x)
{
    y[7] = (uint8_t)(x & 0xff);
    y[6] = (uint8_t)(x >> 8 & 0xff);
    y[5] = (uint8_t)(x >> 16 & 0xff);
    y[4] = (uint8_t)(x >> 24 & 0xff);
    y[3] = (uint8_t)(x >> 32 & 0xff);
    y[2] = (uint8_t)(x >> 40 & 0xff);
    y[1] = (uint8_t)(x >> 48 & 0xff);
    y[0] = (uint8_t)(x >> 56 & 0xff);
}

static inline void __beu32to8(uint8_t y[static 4], uint32_t x)
{
    y[3] = (uint8_t)(x & 0xff);
    y[2] = (uint8_t)(x >> 8 & 0xff);
    y[1] = (uint8_t)(x >> 16 & 0xff);
    y[0] = (uint8_t)(x >> 24 & 0xff);
}

static inline void __beu16to8(uint8_t y[static 2], uint16_t x)
{
    y[1] = (uint8_t)(x & 0xff);
    y[0] = (uint8_t)(x >> 8 & 0xff);
}

static inline void secure_zero(char *buf, size_t n)
{
    char *l_buf = buf;
    if (l_buf >= buf + n) return;

    if ((uintptr_t)l_buf >> 1 != (uintptr_t)l_buf) {
        *((uint8_t *)l_buf) = 0;
        l_buf += sizeof(uint8_t);
        if (l_buf >= buf + n) return;
    }
    if ((uintptr_t)l_buf >> 2 != (uintptr_t)l_buf) {
        *((uint16_t *)l_buf) = 0;
        l_buf += sizeof(uint16_t);
        if (l_buf >= buf + n) return;
    }
    if ((uintptr_t)l_buf >> 3 != (uintptr_t)l_buf) {
        *((uint32_t *)l_buf) = 0;
        l_buf += sizeof(uint32_t);
        if (l_buf >= buf + n) return;
    }
    while (l_buf + sizeof(uint64_t) <= buf + n) {
        *((uint64_t *)l_buf) = 0;
        l_buf += sizeof(uint64_t);
    }
    if (l_buf + sizeof(uint32_t) <= buf + n) {
        *((uint32_t *)l_buf) = 0;
        l_buf += sizeof(uint32_t);
    }
    if (l_buf + sizeof(uint16_t) <= buf + n) {
        *((uint16_t *)l_buf) = 0;
        l_buf += sizeof(uint16_t);
    }
    if (l_buf + sizeof(uint8_t) <= buf + n) {
        *((uint8_t *)l_buf) = 0;
        l_buf += sizeof(uint8_t);
    }
}

#endif

