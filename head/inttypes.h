/**
 * @file inttypes.h
 * @brief Format conversion of integer types
 * @author George Witt
 * @date 2024-11-30
 *
 * ISO/IEC 9899:1999 7.8
 * ISO/IEC 9899:2024 7.8
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: 
 */

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#ifndef __INTTYPES_H__
#define __INTTYPES_H__ /* NOLINT(cert-dcl37-c,cert-dcl51-cpp) */

#include <stdint.h>

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L

/**
 * @def __STDC_VERSION_INTTYPES_H__
 */
#define __STDC_VERSION_INTTYPES_H__ 202311L

#endif

#endif /* __INTTYPES_H__ */
#endif
