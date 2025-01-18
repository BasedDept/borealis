/**
 * @file wchar.h
 * @brief Extended multibyte and wide character utilities
 * @author George Witt
 * @date 2024-09-15
 *
 * ISO/IEC 9899:1999 ?
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: 
 */

#ifndef __STDDEF_H__
#define __STDDEF_H__
#include <stddef.h>
#undef __stddef_H__
#endif

#undef __wint_t__
#define __wint_t__ long long

#undef __WEOF__
#define __WEOF__ ((wint_t)(WCHAR_MIN - 1))

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#ifndef __WCHAR_H__
#define __WCHAR_H__ /* NOLINT(cert-dcl37-c,cert-dcl51-cpp) */

typedef __wint_t__ wint_t;

#define WEOF __WEOF__

#endif /* __WCHAR_H__ */
#endif
