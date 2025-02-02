#ifndef BLAKE2_IMPL_H
#define BLAKE2_IMPL_H

#include <stdint.h>
#include <endian.h>

static inline uint32_t load32(const void* src)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    return *(uint32_t*)(src);
#else
    const uint8_t* p = (uint8_t*)src;
    uint32_t w = *p++;
    w |= (uint32_t)(*p++) << 8;
    w |= (uint32_t)(*p++) << 16;
    w |= (uint32_t)(*p++) << 24;
    return w;
#endif
}

static inline uint64_t load64(const void* src)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    return *(uint64_t*)(src);
#else
    const uint8_t* p = (uint8_t*)src;
    uint64_t w = *p++;
    w |= (uint64_t)(*p++) << 8;
    w |= (uint64_t)(*p++) << 16;
    w |= (uint64_t)(*p++) << 24;
    w |= (uint64_t)(*p++) << 32;
    w |= (uint64_t)(*p++) << 40;
    w |= (uint64_t)(*p++) << 48;
    w |= (uint64_t)(*p++) << 56;
    return w;
#endif
}

static inline void store32(void* dst, uint32_t w)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    *(uint32_t*)(dst) = w;
#else
    uint8_t* p = (uint8_t*)dst;
    *p++ = (uint8_t)w;
    w >>= 8;
    *p++ = (uint8_t)w;
    w >>= 8;
    *p++ = (uint8_t)w;
    w >>= 8;
    *p++ = (uint8_t)w;
#endif
}

static inline void store64(void* dst, uint64_t w)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    *(uint64_t*)(dst) = w;
#else
    uint8_t* p = (uint8_t*)dst;
    *p++ = (uint8_t)w;
    w >>= 8;
    *p++ = (uint8_t)w;
    w >>= 8;
    *p++ = (uint8_t)w;
    w >>= 8;
    *p++ = (uint8_t)w;
    w >>= 8;
    *p++ = (uint8_t)w;
    w >>= 8;
    *p++ = (uint8_t)w;
    w >>= 8;
    *p++ = (uint8_t)w;
    w >>= 8;
    *p++ = (uint8_t)w;
#endif
}

static inline uint64_t load48(const void* src)
{
    const uint8_t* p = (const uint8_t*)src;
    uint64_t w = *p++;
    w |= (uint64_t)(*p++) << 8;
    w |= (uint64_t)(*p++) << 16;
    w |= (uint64_t)(*p++) << 24;
    w |= (uint64_t)(*p++) << 32;
    w |= (uint64_t)(*p++) << 40;
    return w;
}

static inline void store48(void* dst, uint64_t w)
{
    uint8_t* p = (uint8_t*)dst;
    *p++ = (uint8_t)w;
    w >>= 8;
    *p++ = (uint8_t)w;
    w >>= 8;
    *p++ = (uint8_t)w;
    w >>= 8;
    *p++ = (uint8_t)w;
    w >>= 8;
    *p++ = (uint8_t)w;
    w >>= 8;
    *p++ = (uint8_t)w;
}

static inline uint32_t rotl32(const uint32_t w, const unsigned c) { return (w << c) | (w >> (32 - c)); }

static inline uint64_t rotl64(const uint64_t w, const unsigned c) { return (w << c) | (w >> (64 - c)); }

static inline uint32_t rotr32(const uint32_t w, const unsigned c) { return (w >> c) | (w << (32 - c)); }

static inline uint64_t rotr64(const uint64_t w, const unsigned c) { return (w >> c) | (w << (64 - c)); }

/* prevents compiler optimizing out memset() */
static inline void secure_zero_memory(void* v, size_t n)
{
    volatile uint8_t* p = (volatile uint8_t*)v;

    while (n--)
        *p++ = 0;
}

#endif

