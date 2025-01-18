/**
 * @file uchar.h
 * @brief Unicode utilities
 * @author George Witt
 * @date 2024-09-20
 *
 * ISO/IEC 9899:1999 ?
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: 
 */

#undef __char16_t__
#define __char16_t__ unsigned short

#undef __char32_t__
#define __char32_t__ unsigned int

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#ifndef __UCHAR_H__
#define __uCHAR_H__ /* NOLINT(cert-dcl37-c,cert-dcl51-cpp) */

//__STDC_UTF_16__ 1
//__STDC_UTF_32__ 1

typedef __char16_t__ char16_t;
typedef __char32_t__ char32_t;

#endif /* __UCHAR_H__ */
#endif
