/**
 * @file ctype.h
 * @brief Character handling
 * @author George Witt
 * @date 2024-11-30
 *
 * ISO/IEC 9899:1990 7.3
 * ISO/IEC 9899:1999 7.4
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: 
 */

#ifndef __CTYPE_H__
#define __CTYPE_H__ /* NOLINT(cert-dcl37-c,cert-dcl51-cpp) */

/**
 * @fn isalnum
 * @param c
 * @return
 */
int isalnum(int c);

/**
 * @fn isalpha
 * @param c
 * @return
 */
int isalpha(int c);

/**
 * @fn iscntrl
 * @param c
 * @return
 */
int iscntrl(int c);

/**
 * @fn isdigit
 * @param c
 * @return
 */
int isdigit(int c);

/**
 * @fn isgraph
 * @param c
 * @return
 */
int isgraph(int c);

/**
 * @fn islower
 * @param c
 * @return
 */
int islower(int c);

/**
 * @fn isprint
 * @param c
 * @return
 */
int isprint(int c);

/**
 * @fn ispunct
 * @param c
 * @return
 */
int ispunct(int c);

/**
 * @fn isspace
 * @param c
 * @return
 */
int isspace(int c);

/**
 * @fn isupper
 * @param c
 * @return
 */
int isupper(int c);

/**
 * @fn isxdigit
 * @param c
 * @return
 */
int isxdigit(int c);

/**
 * @fn tolower
 * @param c
 * @return
 */
int tolower(int c);

/**
 * @fn toupper
 * @param c
 * @return
 */
int toupper(int c);

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L

/**
 * @fn isblank
 * @param c
 * @return
 */
int isblank(int c);

#endif

#endif /* __CTYPE_H__ */
