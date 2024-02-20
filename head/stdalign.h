/**
 * @file stdalign.h
 * @brief Alignment
 * @author George Witt
 * @date 2024-02-11
 *
 * ISO/IEC 9899:2011 7.15
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: BSD-2-Clause
 */

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#ifndef __STDALIGN_H__
#define __STDALIGN_H__

/**
 * @def alignas
 *
 * ISO/IEC 9899:2011 7.15
 */
#define alignas _Alignas

/**
 * @def alignof
 *
 * ISO/IEC 9899:2011 7.15
 */
#define alignof _Alignof

/**
 * @def __alignas_is_defined
 *
 * ISO/IEC 9899:2011 7.15
 */
#define __alignas_is_defined 1

/**
 * @def __alignof_is_defined
 *
 * ISO/IEC 9899:2011 7.15
 */
#define __alignof_is_defined 1

#endif /* __STDALIGN_H__ */
#endif
