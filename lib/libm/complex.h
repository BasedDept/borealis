/**
 * @file complex.h
 * @brief Complex arithmetic
 * @author George Witt
 * @date 2024-11-30
 *
 * ISO/IEC 9899:1999 7.3
 * ISO/IEC 9899:2011 7.3
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */


#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L && \
    (!defined(__STDC_NO_COMPLEX__) || __STDC_NO_COMPLEX__ != 1)
#ifndef __COMPLEX_H__
#define __COMPLEX_H__ /* NOLINT(cert-dcl37-c,cert-dcl51-cpp) */

#define complex _Complex
#define _Complex_I _Complex 1.0fi
#if defined(__STDC_IEC_559_COMPLEX__) && __STDC_IEC_559_COMPLEX__ == 1
#define imaginary _Imaginary
#define _Imaginary_I _Imaginary 1.0fi
#define I _Imaginary_I
#else
#define I _Complex_I
#endif

typedef union {
        float complex z;
        float parts[2];
} float_complex;

typedef union {
        double complex z;
        double parts[2];
} double_complex;

typedef union {
        long double complex z;
        long double parts[2];
} long_double_complex;

#endif /* __COMPLEX_H__ */
#endif
