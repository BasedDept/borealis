/**
 * @file errno.h
 * @brief Errors
 * @author George Witt
 * @date 2024-02-24
 *
 * ISO/IEC 9899:1990 7.1.4
 * ISO/IEC 9899:1990/AMD 1:1995
 * ISO/IEC 9899:2011 K.3.2
 * ISO/IEC 9945:2009 XBD.13 errno.h
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: 
 */

#ifndef __ERRNO_H__
#define __ERRNO_H__ /* NOLINT(cert-dcl37-c,cert-dcl51-cpp) */

#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 700
#define _NLTS_SOURCE 0 /* NOLINT(cert-dcl37-c,cert-dcl51-cpp) */

/**
 * @def EDOM
 * @def ERANGE
 *
 * ISO/IEC 9899:1990 7.1.4
 */
#define EDOM 33
#define ERANGE 34

/**
 * @def errno
 *
 * ISO/IEC 9899:1990 7.1.4
 */
#define errno (*__errno())


#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199409L

/**
 * @def EILSEQ
 *
 * ISO/IEC 9899:1990/AMD 1:1995 7.1.4
 */
#define EILSEQ 84

#endif

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#if defined(__STDC_WANT_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ == 0
#else

/**
 * @typedef errno_t
 *
 * ISO/IEC 9899:2011 K.3.2
 */
typedef int errno_t;

#endif
#endif

#if (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200809L) || \
    (defined(_XOPEN_SOURCE) && _XOPEN_SOURCE >= 700)

/**
 * @def ENOENT
 * @def ENOMEM
 * @def EFAULT
 * @def EINVAL
 * @def EOVERFLOW
 * @def ENOTRECOVERABLE
 *
 * ISO/IEC 9945:2009 XBD.13 errno.h
 */
#define ENOENT (2)
#define ENOMEM (12)
#define EFAULT (14)
#define EINVAL (22)
#define ENOSYS (38)
#define EOVERFLOW (75)
#define ENOTRECOVERABLE (131)

#endif

#if defined(_NLTS_SOURCE) && _NLTS_SOURCE >= 0
#define EEASTEREGG (451)
#endif

extern int *__errno(void); /* NOLINT(cert-dcl37-c,cert-dcl51-cpp) */

#endif /* __ERRNO_H__ */
