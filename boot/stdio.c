/**
 * @file stdio.c
 * @brief Statically linked stdio.h functions
 * @author George Witt
 * @date 2024-08-03
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <stdint.h>
#include <stdio.h>

#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <ctype.h>
#include <errno.h>
#include "arch.h"
#include "panic.h"

#define CONSOLE_BOLD "\x1b[1m"
#define CONSOLE_RESET "\x1b[0m"

#include <assert.h>

#include <stdnoreturn.h>
#include <stdio.h>
#include <stdlib.h>

static inline void _putd(long x, FILE* stream)
{
    long y = x;
    char str[22];
    short i = sizeof(str) - 2;
    short off = 1;

    str[21] = '\0';

    if (y < 0) {
        y = -y;
        off--;
    }

    for (; i > 0; i--) {
        str[i] = (char)(y % 10) + '0';
        y /= 10;
        if (0 == y) break;
    }

    i--;
    str[i] = '-';
    off += i;

    fputs(str + off, stream);
}

noreturn void __assert_fail(const char *expr, const char *file, int line)
{
    //fprintf(stderr, "Assertion failed: %s, file %s, line %d",
    //        expr, file, line);

    abort();
}

noreturn void __assert_fail_v199901(const char *expr, const char *file,
                                    int line, const char *func)
{
    fputs("Assertion failed: ", stderr);
    fputs(expr, stderr);
    fputs(", function ", stderr);
    fputs(func, stderr);
    fputs(", file ", stderr);
    fputs(file, stderr);
    fputs(", line ", stderr);
    _putd(line, stderr);
    fputs("\n", stderr);

    for (;;);
}

#if 0
enum fmt_flags {
    FMT_FLAG_DEFAULT = 0,
    FMT_FLAG_LEFT_JUSTIFY = 1,
    FMT_FLAG_ALWAYS_SIGN = 1 << 1,
    FMT_FLAG_PREPEND_SPACE = 1 << 2,
    FMT_FLAG_ALTERNATE = 1 << 3,
    FMT_FLAG_LEADING_ZEROES = 1 << 4
};

enum fmt_spec {
    FMT_SPEC_NONE = 0,
    FMT_SPEC_c = 1,
    FMT_SPEC_s = 2,
    FMT_SPEC_d = 3,
    FMT_SPEC_i = 4,
    FMT_SPEC_o = 5,
    FMT_SPEC_x = 6,
    FMT_SPEC_X = 7,
    FMT_SPEC_u = 8,
    FMT_SPEC_f = 9,
    FMT_SPEC_F = 10,
    FMT_SPEC_e = 11,
    FMT_SPEC_E = 12,
    FMT_SPEC_a = 13,
    FMT_SPEC_A = 14,
    FMT_SPEC_g = 15,
    FMT_SPEC_G = 16,
    FMT_SPEC_n = 17,
    FMT_SPEC_p = 18,
    FMT_MOD_hh = 1 << 5,
    FMT_MOD_h = 2 << 5,
    FMT_MOD_l = 3 << 5,
    FMT_MOD_ll = 4 << 5,
    FMT_MOD_j = 5 << 5,
    FMT_MOD_z = 6 << 5,
    FMT_MOD_t = 7 << 5,
    FMT_MOD_L = 8 << 5
};

static const char d_hints[201] = "00010203040506070809"
                                 "10111213141516171819"
                                 "20212223242526272829"
                                 "30313233343536373839"
                                 "40414243444546474849"
                                 "50515253545556575859"
                                 "60616263646566676869"
                                 "70717273747576777879"
                                 "80818283848586878889"
                                 "90919293949596979899";
char *_fmt_hhd(char *s, size_t n, signed char d, enum fmt_flags flags, int width, int precision)
{
    int precision_l = precision < 0 ? 1 : precision;
    if (width > 0 && width > n - 1) return NULL;
    signed char val = d >= 0 ? d : -d;

    char *s_out = s + n - 1;
    if (s_out < s) return NULL;
    *s_out = '\0';

    while (val >= 100) {
        s_out -= 2;
        if (s_out < s) return NULL;
        short pos = val % 100;
        val /= 100;
        memcpy_s(s_out, s + n - s_out, (d_hints + (pos << 1)), 2);
    }
    while (val > 0) {
        s_out --;
        if (s_out < s) return NULL;
        *s_out = '0' + (val % 10);
        val /= 10;
    }

    size_t val_width = s + n - s_out - 1;
    while (val_width < precision_l) {
        s_out --;
        if (s_out < s) return NULL;
        *s_out = '0';
        val_width ++;
    }

    ptrdiff_t width_rem = width - val_width;
    if (flags & FMT_LEADING_ZEROES && width_rem - 1 > 0 &&
        (flags & FMT_LEFT_JUSTIFY) == 0) {
        s_out -= width_rem - 1;
        if (s_out < s) return NULL;
        memset(s_out, '0', width_rem - 1);
        width_rem = 1;
    }

    if (d < 0) {
        s_out --;
        if (s_out < s) return NULL;
        *s_out = '-';
        width_rem --;
        val_width ++;
    }
    else {
        if (flags & FMT_ALWAYS_SIGN && d != 0) {
            s_out --;
            if (s_out < s) return NULL;
            *s_out = '+';
            width_rem --;
            val_width ++;
        }
        else if (flags & FMT_PREPEND_SPACE) {
            s_out --;
            if (s_out < s) return NULL;
            *s_out = ' ';
            width_rem --;
            val_width ++;
        }
        else if (flags & FMT_LEADING_ZEROES &&
                 (flags & FMT_LEFT_JUSTIFY) == 0 && width_rem > 0) {
            s_out --;
            if (s_out < s) return NULL;
            *s_out = '0';
            width_rem --;
        }
    }

    if (flags & FMT_LEFT_JUSTIFY && width > val_width) {
        memmove(s, s_out, val_width);
        s_out = s;
        memset(s_out + val_width, ' ', width - val_width);
    }
    else if (width_rem > 0) {
        s_out -= width_rem;
        if (s_out < s) return NULL;
        memset(s_out, ' ', width_rem);
    }

    return s_out;

}

char *_fmt_d(char *s, size_t n, int d, enum fmt_flags flags, int width, int precision)
{
    int precision_l = precision < 0 ? 1 : precision;
    if (width > 0 && width > n - 1) return NULL;
    int val = d >= 0 ? d : -d;

    char *s_out = s + n - 1;
    if (s_out < s) return NULL;
    *s_out = '\0';

    while (val >= 100) {
        s_out -= 2;
        if (s_out < s) return NULL;
        short pos = val % 100;
        val /= 100;
        memcpy_s(s_out, s + n - s_out, (d_hints + (pos << 1)), 2);
    }
    while (val > 0) {
        s_out --;
        if (s_out < s) return NULL;
        *s_out = '0' + (val % 10);
        val /= 10;
    }

    size_t val_width = s + n - s_out - 1;
    while (val_width < precision_l) {
        s_out --;
        if (s_out < s) return NULL;
        *s_out = '0';
        val_width ++;
    }

    ptrdiff_t width_rem = width - val_width;
    if (flags & FMT_LEADING_ZEROES && width_rem - 1 > 0 &&
        (flags & FMT_LEFT_JUSTIFY) == 0) {
        s_out -= width_rem - 1;
        if (s_out < s) return NULL;
        memset(s_out, '0', width_rem - 1);
        width_rem = 1;
    }

    if (d < 0) {
        s_out --;
        if (s_out < s) return NULL;
        *s_out = '-';
        width_rem --;
        val_width ++;
    }
    else {
        if (flags & FMT_ALWAYS_SIGN && d != 0) {
            s_out --;
            if (s_out < s) return NULL;
            *s_out = '+';
            width_rem --;
            val_width ++;
        }
        else if (flags & FMT_PREPEND_SPACE) {
            s_out --;
            if (s_out < s) return NULL;
            *s_out = ' ';
            width_rem --;
            val_width ++;
        }
        else if (flags & FMT_LEADING_ZEROES &&
                 (flags & FMT_LEFT_JUSTIFY) == 0 && width_rem > 0) {
            s_out --;
            if (s_out < s) return NULL;
            *s_out = '0';
            width_rem --;
        }
    }

    if (flags & FMT_LEFT_JUSTIFY && width > val_width) {
        memmove(s, s_out, val_width);
        s_out = s;
        memset(s_out + val_width, ' ', width - val_width);
    }
    else if (width_rem > 0) {
        s_out -= width_rem;
        if (s_out < s) return NULL;
        memset(s_out, ' ', width_rem);
    }

    return s_out;

}

char *_fmt_hd(char *s, size_t n, short d, enum fmt_flags flags, int width, int precision)
{
    return _fmt_d(s, n, d, flags, width, precision);
}

char *_fmt_lld(char *s, size_t n, long long d, enum fmt_flags flags, int width, int precision)
{
    int precision_l = precision < 0 ? 1 : precision;
    if (width > 0 && width > n - 1) return NULL;
    short val = d >= 0 ? d : -d;

    char *s_out = s + n - 1;
    if (s_out < s) return NULL;
    *s_out = '\0';

    while (val >= 100) {
        s_out -= 2;
        if (s_out < s) return NULL;
        short pos = val % 100;
        val /= 100;
        memcpy_s(s_out, s + n - s_out, (d_hints + (pos << 1)), 2);
    }
    while (val > 0) {
        s_out --;
        if (s_out < s) return NULL;
        *s_out = '0' + (val % 10);
        val /= 10;
    }

    size_t val_width = s + n - s_out - 1;
    while (val_width < precision_l) {
        s_out --;
        if (s_out < s) return NULL;
        *s_out = '0';
        val_width ++;
    }

    ptrdiff_t width_rem = width - val_width;
    if (flags & FMT_LEADING_ZEROES && width_rem - 1 > 0 &&
        (flags & FMT_LEFT_JUSTIFY) == 0) {
        s_out -= width_rem - 1;
        if (s_out < s) return NULL;
        memset(s_out, '0', width_rem - 1);
        width_rem = 1;
    }

    if (d < 0) {
        s_out --;
        if (s_out < s) return NULL;
        *s_out = '-';
        width_rem --;
        val_width ++;
    }
    else {
        if (flags & FMT_ALWAYS_SIGN && d != 0) {
            s_out --;
            if (s_out < s) return NULL;
            *s_out = '+';
            width_rem --;
            val_width ++;
        }
        else if (flags & FMT_PREPEND_SPACE) {
            s_out --;
            if (s_out < s) return NULL;
            *s_out = ' ';
            width_rem --;
            val_width ++;
        }
        else if (flags & FMT_LEADING_ZEROES &&
                 (flags & FMT_LEFT_JUSTIFY) == 0 && width_rem > 0) {
            s_out --;
            if (s_out < s) return NULL;
            *s_out = '0';
            width_rem --;
        }
    }

    if (flags & FMT_LEFT_JUSTIFY && width > val_width) {
        memmove(s, s_out, val_width);
        s_out = s;
        memset(s_out + val_width, ' ', width - val_width);
    }
    else if (width_rem > 0) {
        s_out -= width_rem;
        if (s_out < s) return NULL;
        memset(s_out, ' ', width_rem);
    }

    return s_out;
}

char *_fmt_ld(char *s, size_t n, long d, enum fmt_flags flags, int width, int precision)
{
    return _fmt_lld(s, n, d, flags, width, precision);
}

int _fmt_os(char *s, size_t n, unsigned short o)
{
}
int _fmt_o(char *s, size_t n, unsigned int o)
{
}
int _fmt_ol(char *s, size_t n, unsigned long o)
{
}
int _fmt_oll(char *s, size_t n, unsigned long long o)
{
}
int _fmt_us(char *s, size_t n, unsigned short u)
{
}
int _fmt_u(char *s, size_t n, unsigned int u)
{
}
int _fmt_ul(char *s, size_t n, unsigned long u)
{
}
int _fmt_ull(char *s, size_t n, unsigned long long u)
{
}
int _fmt_xs(char *s, size_t n, unsigned short x)
{
}
int _fmt_x(char *s, size_t n, unsigned int x)
{
}
int _fmt_xl(char *s, size_t n, unsigned long x)
{
}
int _fmt_xll(char *s, size_t n, unsigned long long x)
{
}
#endif
#if 0
int fputc(int c, FILE *stream)
{
    return firmware_putchar(c) >= 0 ? c : EOF;
}

int fputs(const char *restrict s, FILE *restrict stream)
{
    return firmware_puts(s) >= 0 ? 0 : EOF;
}
#endif
#if 0
static inline enum fmt_flags conv_flags(const char **s_p)
{
    enum fmt_flags out = FMT_FLAG_DEFAULT;
    while (**s_p != '\0') {
        switch (**s_p) {
            case '-':
                if (out && FMT_FLAG_LEFT_JUSTIFY != 0) return out;
                out |= FMT_FLAG_LEFT_JUSTIFY;
                break;
            case '+':
                if (out && FMT_FLAG_ALWAYS_SIGN != 0) return out;
                out |= FMT_FLAG_ALWAYS_SIGN;
                break;
            case ' ':
                if (out && FMT_FLAG_PREPEND_SPACE != 0) return out;
                out |= FMT_FLAG_PREPEND_SPACE;
                break;
            case '#':
                if (out && FMT_FLAG_ALTERNATE != 0) return out;
                out |= FMT_FLAG_ALTERNATE;
                break;
            case '0':
                if (out && FMT_FLAG_LEADING_ZEROES != 0) return out;
                out |= FMT_FLAG_LEADING_ZEROES;
                break;
            default:
                return out;
        }
        (*s_p) ++;
    }
    return out;
}

static inline int conv_width_precision(const char **s_p, va_list *l_p)
{
    if (**s_p == '*') {
        (*s_p) ++;
        return va_arg(*l_p, int);
    }
    int out = 0;
    int neg = 0;
    while (isspace(**s_p)) (*s_p) ++;
    if (**s_p == '+') (*s_p) ++;
    else if (**s_p == '-') {
        neg = 1;
        (*s_p) ++;
    }
    while (**s_p >= '0' && **s_p <= '9') {
        out *= 10;
        out += **s_p - '0';
        (*s_p) ++;
    }
    if (neg) {
        out = 0 - out;
    }
    return out;
}

static void conv_single_char()
{
}

static void conv_string()
{
}

static void conv_signed_dec()
{
}

static void conv_unsigned_oct()
{
}

static void conv_unsigned_hex()
{
}

static void conv_unsigned_dec()
{
}

static void conv_float_dec()
{
}

static void conv_float_exp()
{
}

static void conv_float_hex()
{
}

static void conv_float_prec()
{
}

static void conv_print_number()
{
}

static void conv_pointer()
{
}

static inline void conv_char()
{
    switch (**s_p) {
        case 'd':
        case 'i':
        case 'o':
        case 'x':
        case 'X':
        case 'u':
        case 'n':
        default:
            break;
    }
}

static inline void conv_short()
{
    switch (**s_p) {
        case 'd':
        case 'i':
        case 'o':
        case 'x':
        case 'X':
        case 'u':
        case 'n':
        default:
            break;
    }
}

static inline void conv_int()
{
    switch (**s_p) {
        case 'c':
            **out_p = (unsigned char)va_arg(*l_p, int);
            **out_p ++;
            break;
        case 's':
        case 'd':
        case 'i':
        case 'o':
        case 'x':
        case 'X':
        case 'u':
        case 'f':
        case 'F':
        case 'e':
        case 'E':
        case 'a':
        case 'A':
        case 'g':
        case 'G':
        case 'n':
        case 'p':
        default:
            break;
    }
}

static inline void conv_long()
{
    switch (**s_p) {
        case 'c':
        case 's':
        case 'd':
        case 'i':
        case 'o':
        case 'x':
        case 'X':
        case 'u':
        case 'f':
        case 'F':
        case 'e':
        case 'E':
        case 'a':
        case 'A':
        case 'g':
        case 'G':
        case 'n':
        default:
            break;
    }
}

static inline void conv_long_long()
{
    switch (**s_p) {
        case 'd':
        case 'i':
        case 'o':
        case 'x':
        case 'X':
        case 'u':
        case 'n':
        default:
            break;
    }
}

static inline void conv_max()
{
    switch (**s_p) {
        case 'd':
        case 'i':
        case 'o':
        case 'x':
        case 'X':
        case 'u':
        case 'n':
        default:
            break;
    }
}

static inline void conv_size()
{
    switch (**s_p) {
        case 'd':
        case 'i':
        case 'o':
        case 'x':
        case 'X':
        case 'u':
        case 'n':
        default:
            break;
    }
}

static inline void conv_ptrdiff()
{
    switch (**s_p) {
        case 'd':
        case 'i':
        case 'o':
        case 'x':
        case 'X':
        case 'u':
        case 'n':
        default:
            break;
    }
}

static inline void conv_long_double()
{
    switch (**s_p) {
        case 'f':
        case 'F':
        case 'e':
        case 'E':
        case 'a':
        case 'A':
        case 'g':
        case 'G':
        default:
            break;
    }
}

static inline char strwalkr(const char **s_p)
{
    assert(s_p != NULL);

    const char *s = *s_p;
    assert(s != NULL);

    if (*s == 0) s_p ++;

    return *s;
}

static inline void conv_spec(const char **out_p, const char **in_p, va_list *l_p)
{
    assert(out_p != NULL);
    assert(in_p != NULL);
    assert(l_p != NULL);

    assert(*out_p != NULL);
    assert(*in_p != NULL);

    switch (**s_p) {
        case 'h':
            (*s_p) ++;
            if (**s_p == 'h') {
                (*s_p) ++;
                conv_char();
                break;
            }
            conv_short();
            break;
        case 'l':
            (*s_p) ++;
            if (**s_p == 'l') {
                (*s_p) ++;
                conv_long_long();
                break;
            }
            conv_long();
            break;
        case 'j':
            conv_max();
            break;
        case 'z':
            conv_size();
            break;
        case 't':
            conv_ptrdiff();
            break;
        case 'L':
            conv_long_double();
            break;
        default:
            assert(0);
    }
}



int vsnprintf_s(char * restrict s,
                rsize_t n,
                const char * restrict format,
                va_list arg)
{
    return _vxprintf(1, NULL, s, n, n, format, arg);
}

int vsprintf_s(char * restrict s,
               rsize_t n,
               const char * restrict format,
               va_list arg)
{
    return _vxprintf(1, NULL, s, 0, n, format, arg);
}

int snprintf_s(char * restrict s, rsize_t n, const char * restrict format, ...)
{
    va_list arg;
    va_start(arg, format);

    int out = vsnprintf_s(s, n, format, arg);

    va_end(arg);
    return out;
}

int sprintf_s(char * restrict s, rsize_t n, const char * restrict format, ...)
{
    va_list arg;
    va_start(arg, format);

    int out = vsprintf_s(s, n, format, arg);

    va_end(arg);
    return out;
}



int printf(const char *restrict format, ...)
{
    va_list l;
    va_start (l, format);
    ptrdiff_t i = 0;
    int cnt = 0;
    while (format[i] != '\0') {
        if (format[i] == '%') {
            if (format[i + 1] == '%') {
                putchar(format[i]);
                cnt ++;
                i += 2;
                continue;
            }

            // TODO: check for null
            enum fmt_flags flags = FMT_DEFAULT;
        next_flag:
            i ++;
            switch (format[i]) {
                case '-':
                    flags |= FMT_LEFT_JUSTIFY;
                    goto next_flag;
                case '+':
                    flags |= FMT_ALWAYS_SIGN;
                    goto next_flag;
                case ' ':
                    flags |= FMT_PREPEND_SPACE;
                    goto next_flag;
                case '#':
                    flags |= FMT_PREFIX;
                    goto next_flag;
                case '0':
                    flags |= FMT_LEADING_ZEROES;
                    goto next_flag;
                default:
                    break;
            }

            char width_s[5];
            ptrdiff_t j = 0;
            while ((format[i] >= '0' && format[i] <= '9') ||
                   format[i] == '-' || format[i] == '+') {
                if (j > 4) return 0;
                width_s[j] = format[i];
                i ++;
                j ++;
            }
            width_s[j] = '\0';
            int width = atoi(width_s);
            if (format[i] == '*') {
                width = va_arg(l, int);
                i ++;
            }
            if (width < 0) {
                flags |= FMT_LEFT_JUSTIFY;
                width = -width;
            }

            int precision = -1;
            if (format[i] == '.') {
                i ++;
                char precision_s[5];
                j = 0;
                while ((format[i] >= '0' && format[i] <= '9') ||
                       format[i] == '-' || format[i] == '+') {
                    if (j > 4) return 0;
                    precision_s[j] = format[i];
                    i ++;
                    j ++;
                }
                precision_s[j] = '\0';
                precision = atoi(precision_s);
                if (format[i] == '*') {
                    width = va_arg(l, int);
                    i ++;
                }
            }

            i --;
            enum fmt_spec spec = FMT_NONE;
        next_spec:
            i ++;
            switch (format[i]) {
                case 'h':
                    spec = spec == FMT_h ? FMT_hh : FMT_h;
                    goto next_spec;
                case 'l':
                    spec = spec == FMT_l ? FMT_ll : FMT_l;
                    goto next_spec;
                case 'j':
                    spec = FMT_j;
                    goto next_spec;
                case 'z':
                    spec = FMT_z;
                    goto next_spec;
                case 't':
                    spec = FMT_t;
                    goto next_spec;
                case 'L':
                    spec = FMT_L;
                    goto next_spec;
                case 'c':
                    spec |= FMT_c;
                    break;
                case 's':
                    spec |= FMT_s;
                    break;
                case 'd':
                case 'i':
                    spec |= FMT_d;
                    break;
                case 'o':
                    spec |= FMT_o;
                    break;
                case 'x':
                    spec |= FMT_x;
                    break;
                case 'X':
                    spec |= FMT_X;
                    break;
                case 'u':
                    spec |= FMT_u;
                    break;
                case 'f':
                case 'F':
                    spec |= FMT_f;
                    break;
                case 'e':
                    spec |= FMT_e;
                    break;
                case 'E':
                    spec |= FMT_E;
                    break;
                case 'a':
                    spec |= FMT_a;
                    break;
                case 'A':
                    spec |= FMT_A;
                    break;
                case 'g':
                    spec |= FMT_g;
                    break;
                case 'G':
                    spec |= FMT_G;
                    break;
                case 'n':
                    spec |= FMT_n;
                    break;
                case 'p':
                    spec |= FMT_p;
                    break;
                default:
                    return 0;
            }

            char sub[64];
            memset(sub, 0, 64);
            char *str = 0;
            switch ((int)spec) {
                case FMT_d | FMT_hh:
                    str = _fmt_hhd(sub, 64, (signed char)va_arg(l, int), flags,
                                   width, precision);
                    break;
                case FMT_d | FMT_h:
                    str = _fmt_hd(sub, 64, (short)va_arg(l, int), flags, width,
                             precision);
                    break;
                case FMT_d:
                    str = _fmt_d(sub, 64, (int)va_arg(l, int), flags, width,
                           precision);
                    break;
                case FMT_d | FMT_l:
                    str = _fmt_ld(sub, 64, (long)va_arg(l, long), flags, width,
                             precision);
                    break;
                case FMT_d | FMT_ll:
                    str = _fmt_lld(sub, 64, (long long)va_arg(l, long long),
                                   flags, width, precision);
                    break;
                default:
                    return 0;
            }

            if (str == NULL) return 0;
            puts(str);
            // TODO: perf
            cnt += strlen(str);
        }
        else {
            putchar(format[i]);
            cnt ++;
        }
        i ++;
    }
    va_end(l);
    return cnt;
}
#endif
