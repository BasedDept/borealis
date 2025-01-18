#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L && (!defined(__STDC_NO_ATOMICS__) || __STDC_NO_ATOMICS__ != 1)
#ifndef __STDATOMIC_H__
#define __STDATOMIC_H__ /* NOLINT(cert-dcl37-c,cert-dcl51-cpp) */

#include <stdint.h>
#include <stddef.h>

#define ATOMIC_BOOL_LOCK_FREE
#define ATOMIC_CHAR_LOCK_FREE
#define ATOMIC_CHAR8_T_LOCK_FREE
#define ATOMIC_CHAR16_T_LOCK_FREE
#define ATOMIC_CHAR32_T_LOCK_FREE
#define ATOMIC_WCHAR_T_LOCK_FREE
#define ATOMIC_SHORT_LOCK_FREE
#define ATOMIC_INT_LOCK_FREE
#define ATOMIC_LONG_LOCK_FREE
#define ATOMIC_LLONG_LOCK_FREE
#define ATOMIC_POINTER_LOCK_FREE

#define ATOMIC_FLAG_INIT

typedef enum {} memory_order;
typedef struct {} atomic_flag;

#define atomic_init(obj, value) ((void)((obj)->__val = (value)))

typedef _Atomic _Bool               atomic_bool;
typedef _Atomic char                atomic_char;
typedef _Atomic signed char         atomic_schar;
typedef _Atomic unsigned char       atomic_uchar;
typedef _Atomic short               atomic_short;
typedef _Atomic unsigned short      atomic_ushort;
typedef _Atomic int                 atomic_int;
typedef _Atomic unsigned int        atomic_uint;
typedef _Atomic long                atomic_long;
typedef _Atomic unsigned long       atomic_ulong;
typedef _Atomic long long           atomic_llong;
typedef _Atomic unsigned long long  atomic_ullong;
typedef _Atomic uint_least16_t      atomic_char16_t;
typedef _Atomic uint_least32_t      atomic_char32_t;
typedef _Atomic wchar_t             atomic_wchar_t;
typedef _Atomic int_least8_t        atomic_int_least8_t;
typedef _Atomic uint_least8_t       atomic_uint_least8_t;
typedef _Atomic int_least16_t       atomic_int_least16_t;
typedef _Atomic uint_least16_t      atomic_uint_least16_t;
typedef _Atomic int_least32_t       atomic_int_least32_t;
typedef _Atomic uint_least32_t      atomic_uint_least32_t;
typedef _Atomic int_least64_t       atomic_int_least64_t;
typedef _Atomic uint_least64_t      atomic_uint_least64_t;
typedef _Atomic int_fast8_t         atomic_int_fast8_t;
typedef _Atomic uint_fast8_t        atomic_uint_fast8_t;
typedef _Atomic int_fast16_t        atomic_int_fast16_t;
typedef _Atomic uint_fast16_t       atomic_uint_fast16_t;
typedef _Atomic int_fast32_t        atomic_int_fast32_t;
typedef _Atomic uint_fast32_t       atomic_uint_fast32_t;
typedef _Atomic int_fast64_t        atomic_int_fast64_t;
typedef _Atomic uint_fast64_t       atomic_uint_fast64_t;
typedef _Atomic intptr_t            atomic_intptr_t;
typedef _Atomic uintptr_t           atomic_uintptr_t;
typedef _Atomic size_t              atomic_size_t;
typedef _Atomic ptrdiff_t           atomic_ptrdiff_t;
typedef _Atomic intmax_t            atomic_intmax_t;
typedef _Atomic uintmax_t           atomic_uintmax_t;



#endif /* __STDATOMIC_H__ */
#endif
