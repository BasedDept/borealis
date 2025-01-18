/**
 * @file stdio/stdio_static.h
 * @brief stdio static defs
 * @author George Witt
 * @date 2024-11-27
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#define __STDC_WANT_LIB_EXT1__ 1
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <wchar.h>

enum flags {
    FLAGS_NONE = 0,
    FLAGS_LEFT = (1 << 0),
    FLAGS_SIGN = (1 << 1),
    FLAGS_SPACE = (1 << 2),
    FLAGS_ALT = (1 << 3),
    FLAGS_ZERO = (1 << 4),
    FLAGS_PRECISION = (1 << 5)
};

enum length {
    LENGTH_NONE = 0,
    LENGTH_L,
    LENGTH_LL,
    LENGTH_LD
};

union handle {
    struct {
        FILE *fp;
    } f;
    struct {
        char *s;
        size_t n;
    } s;
};

union iarg {
    int i;
    unsigned int ui;
    long l;
    unsigned long ul;
    long long ll;
    unsigned long long ull;
};

union darg {
    double d;
    long double ld;
};

static int fprint(union handle *h, const char *s) {
    return fputs(s, h->f.fp);
}

static int sprint(union handle *h, const char *s) {
    const char *l_s = s;
    int count = 0;

    while (h->s.n > 1) {
        if (h->s.n <= 0) return EOF;
        *(h->s.s) = *l_s;
        if (*l_s == '\0') break;
        h->s.s++;
        h->s.n--;
        l_s++;
        count++;
    }
    return count;
}

#define UINT_DEC_DIG 10
#define UINT_BIN_DIG 32
#define UINT_OCT_DIG 11
#define UINT_HEX_DIG 8
#define ULONG_DEC_DIG 20
#define ULONG_BIN_DIG 64
#define ULONG_OCT_DIG 22
#define ULONG_HEX_DIG 16
#define ULLONG_DEC_DIG 20
#define ULLONG_BIN_DIG 64
#define ULLONG_OCT_DIG 22
#define ULLONG_HEX_DIG 16

static char *itoa(size_t n, char s[n], char c, unsigned int v,
                  int p, int *w_p)
{
    ptrdiff_t off = n - 1;
    s[off] = '\0';
    off--;

    switch (c) {
    case 'd':
    case 'i':
    case 'u':
        p = p > UINT_DEC_DIG ? UINT_DEC_DIG : p;
        break;
    case 'b':
    case 'B':
        p = p > UINT_BIN_DIG ? UINT_BIN_DIG : p;
        break;
    case 'o':
        p = p > UINT_OCT_DIG ? UINT_OCT_DIG : p;
        break;
    case 'x':
    case 'X':
        p = p > UINT_HEX_DIG ? UINT_HEX_DIG : p;
        break;
    default:
        assert(0);
    }

    while (v > 0 || p > 0) {
        char d;
        switch (c) {
        case 'd':
        case 'i':
        case 'u':
            d = '0' + (v % 10);
            assert(v == 0 && p > 0 ? d == '0' : 1);
            v /= 10;
            break;
        case 'b':
        case 'B':
            d = '0' + (v & 1);
            v >>= 1;
            break;
        case 'o':
            d = '0' + (v & 7);
            v >>= 3;
            break;
        case 'x':
            d = (v & 15) < 10
                ? '0' + (v & 15)
                : 'a' + ((v - 10) & 15);
            v >>= 4;
            break;
        case 'X':
            d = (v & 15) < 10
                ? '0' + (v & 15)
                : 'A' + ((v - 10) & 15);
            v >>= 4;
            break;
        default:
            assert(0);
        }

        s[off] = d;
        off--;
        (*w_p)--;
        p--;
    }
    assert(p <= 0);

    return s + off + 1;
}

static char *ltoa(size_t n, char s[n], char c, unsigned long v,
                  int p, int *w_p)
{
    ptrdiff_t off = n - 1;
    s[off] = '\0';
    off--;

    switch (c) {
    case 'd':
    case 'i':
    case 'u':
        p = p > ULONG_DEC_DIG ? ULONG_DEC_DIG : p;
        break;
    case 'b':
    case 'B':
        p = p > ULONG_BIN_DIG ? ULONG_BIN_DIG : p;
        break;
    case 'o':
        p = p > ULONG_OCT_DIG ? ULONG_OCT_DIG : p;
        break;
    case 'x':
    case 'X':
        p = p > ULONG_HEX_DIG ? ULONG_HEX_DIG : p;
        break;
    default:
        assert(0);
    }

    while (v > 0 || p > 0) {
        char d;
        switch (c) {
        case 'd':
        case 'i':
        case 'u':
            d = '0' + v % 10;
            v /= 10;
            break;
        case 'b':
        case 'B':
            d = '0' + (v & 1);
            v >>= 1;
            break;
        case 'o':
            d = '0' + (v & 7);
            v >>= 3;
            break;
        case 'x':
            d = (v & 15) < 10
                ? '0' + (v & 15)
                : 'a' + ((v - 10) & 15);
            v >>= 4;
            break;
        case 'X':
            d = (v & 15) < 10
                ? '0' + (v & 15)
                : 'A' + ((v - 10) & 15);
            v >>= 4;
            break;
        default:
            assert(0);
        }

        s[off] = d;
        off--;
        (*w_p)--;
        p--;
    }
    assert(p <= 0);

    return s + off + 1;
}

static char *lltoa(size_t n, char s[n], char c, unsigned long long v,
                   int p, int *w_p)
{
    ptrdiff_t off = n - 1;
    s[off] = '\0';
    off--;

    switch (c) {
    case 'd':
    case 'i':
    case 'u':
        p = p > ULLONG_DEC_DIG ? ULLONG_DEC_DIG : p;
        break;
    case 'b':
    case 'B':
        p = p > ULLONG_BIN_DIG ? ULLONG_BIN_DIG : p;
        break;
    case 'o':
        p = p > ULLONG_OCT_DIG ? ULLONG_OCT_DIG : p;
        break;
    case 'x':
    case 'X':
        p = p > ULLONG_HEX_DIG ? ULLONG_HEX_DIG : p;
        break;
    default:
        assert(0);
    }

    while (v > 0 || p > 0) {
        char d;
        switch (c) {
        case 'd':
        case 'i':
        case 'u':
            d = '0' + v % 10;
            v /= 10;
            break;
        case 'b':
        case 'B':
            d = '0' + (v & 1);
            v >>= 1;
            break;
        case 'o':
            d = '0' + (v & 7);
            v >>= 3;
            break;
        case 'x':
            d = (v & 15) < 10
                ? '0' + (v & 15)
                : 'a' + ((v - 10) & 15);
            v >>= 4;
            break;
        case 'X':
            d = (v & 15) < 10
                ? '0' + (v & 15)
                : 'A' + ((v - 10) & 15);
            v >>= 4;
            break;
        default:
            assert(0);
        }

        s[off] = d;
        off--;
        (*w_p)--;
        p--;
    }
    assert(p <= 0);

    return s + off + 1;
}

static int print_i(int (*print)(union handle *h, const char *s),
                   union handle *h, enum flags f, int w,
                   int p, enum length l, char c, union iarg v)
{
    char buf[ULLONG_DEC_DIG + 1] = {0};
    int count = 0;
    if (!(f & FLAGS_PRECISION)) p = 1;

    int sign = 1;
    if (c == 'd' || c == 'i') {
        switch (l) {
        case LENGTH_NONE:
            if (v.i < 0) {
                sign = -1;
                v.i = -v.i;
            }
            break;
        case LENGTH_L:
            if (v.l < 0) {
                sign = -1;
                v.l = -v.l;
            }
            break;
        case LENGTH_LL:
            if (v.ll < 0) {
                sign = -1;
                v.ll = -v.ll;
            }
            break;
        default:
            assert(0);
        }
    }

    char *istr = NULL;
    switch (l) {
    case LENGTH_NONE:
        istr = itoa(sizeof(buf), buf, c, v.ui, p, &w);
        break;
    case LENGTH_L:
        istr = ltoa(sizeof(buf), buf, c, v.ul, p, &w);
        break;
    case LENGTH_LL:
        istr = lltoa(sizeof(buf), buf, c, v.ull, p, &w);
        break;
    default:
        assert(0);
    }

    char prefix[3] = "0 ";
    w -= 2;
    if (f & FLAGS_ALT) {
        switch (c) {
        case 'b':
            prefix[1] = 'b';
            break;
        case 'B':
            prefix[1] = 'B';
            break;
        case 'o':
            prefix[1] = '\0';
            w++;
            break;
        case 'x':
            prefix[1] = 'x';
            break;
        case 'X':
            prefix[1] = 'X';
            break;
        default:
            prefix[0] = '\0';
            w += 2;
        }
    }
    else {
        prefix[0] = '\0';
        w += 2;
    }

    while (!(f & FLAGS_LEFT) && !(f & FLAGS_ZERO) && w > 1) {
        int res = print(h, " ");
        if (res == EOF) return res;
        count += res;
        w--;
    }
    if (sign < 0) {
        int res = print(h, "-");
        if (res == EOF) return res;
        count += res;
        w--;
    }
    else {
        if (f & FLAGS_SIGN) {
            int res = print(h, "+");
            if (res == EOF) return res;
            count += res;
            w--;
        }
        else if (f & FLAGS_SPACE || (!(f & FLAGS_LEFT)
                 && !(f & FLAGS_ZERO) && w > 0)) {
            int res = print(h, " ");
            if (res == EOF) return res;
            count += res;
            w--;
        }
    }

    int res = print(h, prefix);
    if (res == EOF) return res;
    count += res;

    while (!(f & FLAGS_LEFT) && f & FLAGS_ZERO && w > 0) {
        int res = print(h, "0");
        if (res == EOF) return res;
        count += res;
        w--;
    }

    res = print(h, istr);
    if (res == EOF) return res;
    count += res;

    if (f & FLAGS_LEFT) {
        while (w > 0) {
            int res = print(h, " ");
            if (res == EOF) return res;
            count += res;
            w--;
        }
    }
    return count;
}

static int aptoi(const char *restrict *s)
{
    assert(s != NULL);
    assert(*s != NULL);
    int n = 0;
    while (isdigit(**s)) {
        n *= 10;
        n += **s - '0';
        (*s)++;
    }
    return n;
}

static inline union iarg intmux(enum length l, va_list *arg_p)
{
    switch (l) {
        case LENGTH_NONE:
            return (union iarg){.i = va_arg(*arg_p, int)};
        case LENGTH_L:
            return (union iarg){.l = va_arg(*arg_p, long)};
        case LENGTH_LL:
            return (union iarg){.ll = va_arg(*arg_p, long long)};
        default:
            assert(0);
    }
}

static inline union iarg uintmux(enum length l, va_list *arg_p)
{
    switch (l) {
        case LENGTH_NONE:
            return (union iarg){.ui = va_arg(*arg_p, unsigned int)};
        case LENGTH_L:
            return (union iarg){.ul = va_arg(*arg_p, unsigned long)};
        case LENGTH_LL:
            return (union iarg){.ull = va_arg(*arg_p, unsigned long long)};
        default:
            assert(0);
    }
}

static int seekprint(int (*print)(union handle *h, const char *s),
                     union handle *h, const char *restrict *s,
                     const char *restrict tok)
{
    assert(s != NULL);
    assert(*s != NULL);
    assert(tok != NULL);
    char buf[9] = {0};
    int bufcnt = 0;
    int count = 0;
    int res = EOF;
    while (**s != '\0') {
        for (int i = 0; tok[i] != '\0'; i++) {
            if (**s == tok[i]) {
                buf[bufcnt] = '\0';
                res = print(h, buf);
                if (res == EOF) return res;
                return count + res;
            }
        }
        if (bufcnt >= sizeof(buf) - 1) {
            buf[sizeof(buf) - 1] = '\0';
            res = print(h, buf);
            if (res == EOF) return res;
            count = count + res;
            bufcnt = 0;
        }
        buf[bufcnt] = **s;
        bufcnt++;
        (*s)++;
    }
    buf[bufcnt] = '\0';
    res = print(h, buf);
    if (res == EOF) return res;
    return count + res;
}

int _vfsprintf(int k,
               FILE *restrict stream,
               char *restrict s,
               size_t n,
               rsize_t max,
               const char *restrict format,
               va_list arg)
{
    int count = 0;
    int (*print)(union handle *h, const char *s);
    union handle h_v;

    if (stream != NULL) {
        print = &fprint;
        h_v.f.fp = stream;
    }
    else if (s != NULL) {
        print = &sprint;
        h_v.s.s = s;
        h_v.s.n = n;
    }
    else {
        errno = EINVAL;
        return EOF;
    }

    if (format == NULL) {
        return EOF;
    }

    enum flags f = FLAGS_NONE;
    enum length l = LENGTH_NONE;
    int w = 0;
    int p;
    while (*format != '\0') {
        int res = seekprint(print, &h_v, &format, "%");
        if (res == EOF) return res;
        count += res;

        if (*format != '%') continue;;

        assert(*format == '%');
        while (*format != '\0') {
            format++;
            switch (*format) {
            case '-':
                f |= FLAGS_LEFT;
                break;
            case '+':
                f |= FLAGS_SIGN;
                break;
            case ' ':
                f |= FLAGS_SPACE;
                break;
            case '#':
                f |= FLAGS_ALT;
                break;
            case '0':
                f |= FLAGS_ZERO;
                break;
            default:
                goto break_flags;
            }
        }
    break_flags:

        assert(*format != '\0');
        if (*format == '*') {
            w = va_arg(arg, int);
            format++;
        }
        else {
            w = aptoi(&format);
        }

        if (w < 0) {
            w = -w;
            f |= FLAGS_LEFT;
        }

        assert(*format != '\0');
        if (*format == '.') {
            format++;
            assert(*format != '\0');
            if (*format == '*') {
                p = va_arg(arg, int);
                format++;
            }
            else {
                p = aptoi(&format);
            }
            if (p >= 0) {
                f |= FLAGS_PRECISION;
            }
        }

        assert(*format != '\0');
        switch (*format) {
        case 'h':
            format++;
            assert(*format != '\0');
            if (*format == 'h');
            else format--;
            break;
        case 'l':
            l = LENGTH_L;
            format++;
            assert(*format != '\0');
            if (*format == 'l') l = LENGTH_LL;
            else format--;
            break;
        case 'j':
            l = LENGTH_LL;
            break;
        case 'z':
            l = LENGTH_L;
            break;
        case 't':
            l = LENGTH_L;
            break;
        case 'w':
            format++;
            assert(*format != '\0');
            if (*format == 'f') {
                format++;
                int bits = aptoi(&format);
                if (bits == 64) l = LENGTH_L;
            }
            else {
                int bits = aptoi(&format);
                if (bits == 64) l = LENGTH_L;
            }
            format--;
            break;
        case 'L':
            l = LENGTH_LD;
            break;
        case 'H':
            break;
        case 'D':
            format++;
            assert(*format != '\0');
            if (*format == 'D') l = LENGTH_LD;
            else format--;
            break;
        default:
            format--;
            break;
        }
        format++;

        res = EOF;
        assert(*format != '\0');
        switch (*format) {
        case 'd':
        case 'i':
            res = print_i(print, &h_v, f, w, p, l, *format, intmux(l, &arg));
            break;
        case 'b':
        case 'B':
        case 'o':
        case 'u':
        case 'x':
        case 'X':
            res = print_i(print, &h_v, f, w, p, l, *format, uintmux(l, &arg));
            break;
        case 'f':
        case 'F':
        case 'e':
        case 'E':
        case 'g':
        case 'G':
        case 'a':
        case 'A':
            break;
        case 'c':
            break;
        case 's':
            break;
        case 'p':
            break;
        case 'n':
            break;
        case '%':
            res = print(&h_v, "%");
            break;
        }
        if (res == EOF) return res;
        count += res;
        format++;
    }

    return count;
}



