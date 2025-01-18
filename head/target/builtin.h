//_BUILTIN_

#define __STDC_HOSTED__
#define __STDC_VERSION__
#define __STDC_NO_COMPLEX__
#define __STDC_LIB_EXT1__
#define __STDC_IEC_60559_BFP__
#define __STDC_IEC_60559_DFP__
#define __STDC_IEC_559__
#define __STDC_IEC_60559_COMPLEX__
#define __STDC_IEC_559_COMPLEX__
#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 700

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L && \
    (!defined(_POSIX_C_SOURCE) || !defined(_XOPEN_SOURCE) || \
    !defined(_NLTS_SOURCE))
#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 700
#define _NLTS_SOURCE 0 /* NOLINT(cert-dcl37-c,cert-dcl51-cpp) */
#endif


#if defined(__STDC_LIB_EXT1__)
#endif
