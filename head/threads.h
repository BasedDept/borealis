#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L && (!defined(__STDC_NO_THREADS__) || __STDC_NO_THREADS__ != 1)
#ifndef __THREADS_H__
#define __THREADS_H__ /* NOLINT(cert-dcl37-c,cert-dcl51-cpp) */

#define thread_local _Thread_local

#endif /* __THREADS_H__ */
#endif
