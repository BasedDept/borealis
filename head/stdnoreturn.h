/**
 * @file stdnoreturn.h
 * @brief _Noreturn
 * @author George Witt
 * @date 2024-01-01
 *
 * ISO/IEC 9899:2011 7.23
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: 
 */

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#ifndef __STDNORETURN_H__
#define __STDNORETURN_H__ /* NOLINT(cert-dcl37-c,cert-dcl51-cpp) */

/**
 * @def noreturn
 *
 * ISO/IEC 9899:2011 7.23
 */
#define noreturn _Noreturn

#endif /* __STDNORETURN_H__ */
#endif
