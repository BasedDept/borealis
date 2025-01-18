/**
 * @file stdfix.h
 * @brief Fixed-point arithmetic
 * @author George Witt
 * @date 2024-09-21
 *
 * ISO/IEC TR 18037:2008 4
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: 
 */

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#ifndef __STDFIX_H__
#define __STDFIX_H__ /* NOLINT(cert-dcl37-c,cert-dcl51-cpp) */

#define fract _Fract
#define accum _Accum
#define sat _Sat

typedef short _Fract int_hr_t;
typedef _Fract int_r_t;
typedef long _Fract int_lr_t;
typedef long long _Fract int_llr_t;
typedef short _Accum int_hk_t;
typedef _Accum int_k_t;
typedef long _Accum int_lk_t;
typedef long long _Accum int_llk_t;
typedef unsigned short _Fract int_uhr_t;
typedef unsigned _Fract int_ur_t;
typedef unsigned long _Fract int_ulr_t;
typedef unsigned long long _Fract int_ullr_t;
typedef unsigned short _Accum int_uhk_t;
typedef unsigned _Accum int_uk_t;
typedef unsigned long _Accum int_ulk_t;
typedef unsigned long long _Accum int_ullk_t;

#endif /* __STDFIX_H__ */
#endif
