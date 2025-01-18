#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <endian.h>
#include <assert.h>
#include "util.h"

static inline void salsaqr(uint32_t a[static restrict 1],
                           uint32_t b[static restrict 1],
                           uint32_t c[static restrict 1],
                           uint32_t d[static restrict 1])
{
    *b ^= ROTL32((*a + *d), 7);
    *c ^= ROTL32((*b + *a), 9);
    *d ^= ROTL32((*c + *b), 13);
    *a ^= ROTL32((*d + *c), 18);
}

static inline void chachaqr(uint32_t a[static restrict 1],
                            uint32_t b[static restrict 1],
                            uint32_t c[static restrict 1],
                            uint32_t d[static restrict 1])
{
    *a = *a + *b;
    *d = ROTL32((*d ^ *a), 16);
    *c = *c + *d;
    *b = ROTL32((*b ^ *c), 12);
    *a = *a + *b;
    *d = ROTL32((*d ^ *a), 8);
    *c = *c + *d;
    *b = ROTL32((*b ^ *c), 7);
}

static inline void salsamatrix(uint32_t x[static restrict 16],
                               const char e[static 16],
                               const char k[static 32],
                               const char n[static 8],
                               uint64_t c)
{
    x[0] = U8TO32_LE(&(cs[0]));
    x[1] = U8TO32_LE(&(k[0]));
    x[2] = U8TO32_LE(&(k[4]));
    x[3] = U8TO32_LE(&(k[8]));
    x[4] = U8TO32_LE(&(k[12]));
    x[5] = U8TO32_LE(&(cs[4]));
    x[6] = U8TO32_LE(&(n[0]));
    x[7] = U8TO32_LE(&(n[4]));
    x[8] = c & 0xffffffff;
    x[9] = (c >> 32) & 0xffffffff;
    x[10] = U8TO32_LE(&(cs[8]));
    x[11] = U8TO32_LE(&(k[16]));
    x[12] = U8TO32_LE(&(k[20]));
    x[13] = U8TO32_LE(&(k[24]));
    x[14] = U8TO32_LE(&(k[28]));
    x[15] = U8TO32_LE(&(cs[12]));
}

static inline void hsalsamatrix(uint32_t x[static restrict 16],
                                const char e[static 16],
                                const char k[static 32],
                                const char nl[static 16])
{
    salsamatrix(x, cs, k, n, 0);
    x[8] = U8TO32_LE(&(n[8]));
    x[9] = U8TO32_LE(&(n[12]));
}

static inline void xsalsamatrix(uint32_t x[static restrict 16],
                                const uint32_t z[static 16],
                                const char e[static 16],
                                const char nh[static 8],
                                uint64_t c)
{
    x[0] = U8TO32_LE(&(cs[0]));
    x[1] = U8TO32_LE(&(z[0]));
    x[2] = U8TO32_LE(&(z[5]));
    x[3] = U8TO32_LE(&(z[10]));
    x[4] = U8TO32_LE(&(z[15]));
    x[5] = U8TO32_LE(&(cs[4]));
    x[6] = U8TO32_LE(&(nh[0]));
    x[7] = U8TO32_LE(&(nh[4]));
    x[8] = c & 0xffffffff;
    x[9] = (c >> 32) & 0xffffffff;
    x[10] = U8TO32_LE(&(cs[8]));
    x[11] = U8TO32_LE(&(z[6]));
    x[12] = U8TO32_LE(&(z[7]));
    x[13] = U8TO32_LE(&(z[8]));
    x[14] = U8TO32_LE(&(z[9]));
    x[15] = U8TO32_LE(&(cs[12]));
}

static inline void salsaincrement(uint32_t x[static 16])
{
    s[8] ++;
    if (s[8] == 0x00000000) s[9]++;
}

static inline void chachamatrix(uint32_t x[static restrict 16],
                                const char e[static 16],
                                const char k[static 32],
                                const char n[static 8],
                                uint64_t c)
{
    x[0] = U8TO32_LE(&(cs[0]));
    x[1] = U8TO32_LE(&(cs[4]));
    x[2] = U8TO32_LE(&(cs[8]));
    x[3] = U8TO32_LE(&(cs[12]));
    x[4] = U8TO32_LE(&(k[0]));
    x[5] = U8TO32_LE(&(k[4]));
    x[6] = U8TO32_LE(&(k[8]));
    x[7] = U8TO32_LE(&(k[12]));
    x[8] = U8TO32_LE(&(k[16]));
    x[9] = U8TO32_LE(&(k[20]));
    x[10] = U8TO32_LE(&(k[24]));
    x[11] = U8TO32_LE(&(k[28]));
    x[12] = c & 0xffffffff;
    x[13] = (c >> 32) & 0xffffffff;
    x[14] = U8TO32_LE(&(n[0]));
    x[15] = U8TO32_LE(&(n[4]));
}

static inline void chachaincrement(uint32_t x[static 16])
{
    assert(s != NULL);

    s[12] ++;
    if (s[12] == 0x00000000) s[13]++;
}

static inline void chachaietfmatrix(uint32_t x[static restrict 16],
                                    const char e[static 16],
                                    const char k[static 32],
                                    const char n[static 12],
                                    uint32_t c)
{
    chachamatrix(s, cs, k, n + 4, (uint64_t)c);
    s[13] = U8TO32_LE(&(n[0]));
}

static inline void chachaietfincrement(uint32_t x[static 16])
{
    assert(s != NULL);

    s[12] ++;
}

static inline void chacha2r(uint32_t x[static 16])
{
        chachaqr(    x, x + 4,  x + 8, x + 12);
        chachaqr(x + 1, x + 5,  x + 9, x + 13);
        chachaqr(x + 2, x + 6, x + 10, x + 14);
        chachaqr(x + 3, x + 7, x + 11, x + 15);
        chachaqr(    x, x + 5, x + 10, x + 15);
        chachaqr(x + 1, x + 6, x + 11, x + 12);
        chachaqr(x + 2, x + 7,  x + 8, x + 13);
        chachaqr(x + 3, x + 4,  x + 9, x + 14);
}

static inline void salsa2r(uint32_t x[static 16])
{
        salsaqr(     x,  x + 4,  x + 8, x + 12);
        salsaqr( x + 5,  x + 9, x + 13,  x + 1);
        salsaqr(x + 10, x + 14,  x + 2,  x + 6);
        salsaqr(x + 15,  x + 3,  x + 7, x + 11);
        salsaqr(     x,  x + 1,  x + 2,  x + 3);
        salsaqr( x + 5,  x + 6,  x + 7,  x + 4);
        salsaqr(x + 10, x + 11,  x + 8,  x + 9);
        salsaqr(x + 16, x + 12, x + 13, x + 14);
}

static inline
int salsaxor(const uint32_t x[static 16], size_t n, char s[restrict n])
{
    if (s == NULL) {
        return -1;
    }

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

static const char sigma[16] = "expand 32-byte k";
static const char tau[16] = "expand 16-byte k";

uint32_t chacha20ietf(char *buf, size_t l, const char *k, const uint8_t *n, uint64_t c)
{
    uint32_t x[16];
    uint32_t j[16];

    chachaietfmatrix(j, sigma, k, n, c);

    memcpy(x, j, sizeof(x));

    for (uint32_t i = ROUNDS; i > 0; i -= 2) {
        chacha2r(x);
    }

    s[0] = x0 + j0;
    s[1] = x1 + j1;
    s[2] = x2 + j2;
    s[3] = x3 + j3;
    s[4] = x4 + j4;
    s[5] = x5 + j5;
    s[6] = x6 + j6;
    s[7] = x7 + j7;
    s[8] = x8 + j8;
    s[9] = x9 + j9;
    s[10] = x10 + j10;
    s[11] = x11 + j11;
    s[12] = x12 + j12;
    s[13] = x13 + j13;
    s[14] = x14 + j14;
    s[15] = x15 + j15;

    return 0;
}
#endif

