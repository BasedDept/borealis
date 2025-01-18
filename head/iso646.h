/**
 * @file iso646.h
 * @brief Alternative spellings
 * @author George Witt
 * @date 2024-01-01
 *
 * ISO/IEC 9899:1990/AMD 1:1995
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: 
 */

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199409L
#ifndef __ISO646_H__
#define __ISO646_H__ /* NOLINT(cert-dcl37-c,cert-dcl51-cpp) */

/**
 * @def and
 * @def and_eq
 * @def bitand
 * @def bitor
 * @def compl
 * @def not
 * @def not_eq
 * @def or
 * @def or_eq
 * @def xor
 * @def xor_eq
 *
 * ISO/IEC 9899:1990/AMD 1:1995
 */
#define and &&
#define and_eq &=
#define bitand &
#define bitor |
#define compl ~
#define not !
#define not_eq !=
#define or ||
#define or_eq |=
#define xor ^
#define xor_eq ^=

#endif /* __ISO646_H__ */
#endif
