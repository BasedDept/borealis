#define __MISRAC_COMPLIANT__ 1
#define __STDC_WANT_LIB_EXT1__ 1
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/endian.h>
#include <crypto/common.h>

static inline void sipround(uint64_t *x0, uint64_t *x1, uint64_t *x2, uint64_t *x3)
{
    *x0 += *x1;
    *x1 = ROTL64(*x1, 13);
    *x1 ^= *x0;
    *x0 = ROTL64(*x0, 32);
    *x2 += *x3;
    *x3 = ROTL64(*x3, 16);
    *x3 ^= *x2;
    *x0 += *x3;
    *x3 = ROTL64(*x3, 21);
    *x3 ^= *x0;
    *x2 += *x1;
    *x1 = ROTL64(*x1, 17);
    *x1 ^= *x2;
    *x2 = ROTL64(*x2, 32);
}

#ifdef SIPHASH
uint32_t SIPHASH(uint8_t *out, const uint8_t *in, uint64_t inlen, const uint8_t *k)
{
    /* "somepseudorandomlygeneratedbytes" */
    uint64_t v0 = 0x736f6d6570736575ULL;
    uint64_t v1 = 0x646f72616e646f6dULL;
    uint64_t v2 = 0x6c7967656e657261ULL;
    uint64_t v3 = 0x7465646279746573ULL;
    uint64_t b;
    uint64_t k0 = U8TO64(k);
    uint64_t k1 = U8TO64(k + 8);
    uint64_t m;
    int i;
    const uint8_t *end = in + inlen - (inlen % sizeof(uint64_t));
    const int left = inlen & 7;
    b = ((uint64_t)inlen) << 56;
    v3 ^= k1;
    v2 ^= k0;
    v1 ^= k1;
    v0 ^= k0;

#ifdef DOUBLE
    v1 ^= 0xee;
#endif

    for (; in != end; in += 8) {
        m = U8TO64(in);
        v3 ^= m;
        
        for (i = 0; i < cROUNDS; ++i)
            sipround(&v0, &v1, &v2, &v3);
        
        v0 ^= m;
    }
    
    switch (left) {
    case 7:
        b |= ((uint64_t)in[6]) << 48;
    case 6:
        b |= ((uint64_t)in[5]) << 40;
    case 5:
        b |= ((uint64_t)in[4]) << 32;
    case 4:
        b |= ((uint64_t)in[3]) << 24;
    case 3:
        b |= ((uint64_t)in[2]) << 16;
    case 2:
        b |= ((uint64_t)in[1]) << 8;
    case 1:
        b |= ((uint64_t)in[0]);
        break;
    case 0:
        break;
    }

    v3 ^= b;

    for (i = 0; i < cROUNDS; ++i)
        sipround(&v0, &v1, &v2, &v3);

    v0 ^= b;

#ifndef DOUBLE
    v2 ^= 0xff;
#else
    v2 ^= 0xee;
#endif

    for (i = 0; i < dROUNDS; ++i)
        sipround(&v0, &v1, &v2, &v3);

    b = v0 ^ v1 ^ v2 ^ v3;
    U64TO8(out, b);

#ifdef DOUBLE
    v1 ^= 0xdd;

    for (i = 0; i < dROUNDS; ++i)
        sipround(&v0, &v1, &v2, &v3);

    b = v0 ^ v1 ^ v2 ^ v3;
    U64TO8(out + 8, b);
#endif

    return 0;
}
#endif

