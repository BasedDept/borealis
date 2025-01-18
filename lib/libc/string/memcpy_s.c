/**
 * @file string/memcpy_s.c
 * @brief memcpy_s
 * @author George Witt
 * @date 2024-03-02
 *
 * ISO/IEC 9899:1990 7.11.2.1
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#define __STDC_WANT_LIB_EXT1__ 1
#include <string.h>

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>

static errno_t _memcpy_s_handler(const char *restrict msg, void *restrict ptr,
                              errno_t error, void *restrict s1, rsize_t s1max)
{
    if (s1 != NULL && s1max <= RSIZE_MAX) {
        for (ptrdiff_t i = 0; i < (ptrdiff_t)s1max; i++) {
            ((unsigned char*)s1)[i] = 0;
        }
    }

    __constraint_handler_s(msg, ptr, error);

    return error;
}

errno_t memcpy_s(void *restrict s1, rsize_t s1max, const void *restrict s2,
                 rsize_t n)
{
    if (s1 == NULL) {
        return _memcpy_s_handler("Destination is a null pointer", (void *)&s1,
                                 EFAULT, s1, s1max);
    }
    else if (s2 == NULL) {
        return _memcpy_s_handler("Source is a null pointer", (void *)&s2,
                                 EFAULT, s1, s1max);
    }
    else if (s1max > RSIZE_MAX) {
        return _memcpy_s_handler("Destination size is out of range",
                                 (void *)&s1max, ERANGE, s1, s1max);
    }
    else if (n > RSIZE_MAX) {
        return _memcpy_s_handler("Source size is out of range", (void *)&n,
                                 ERANGE, s1, s1max);
    }
    else if (n > s1max) {
        return _memcpy_s_handler("Source is larger than destination",
                                 (void *)&s1max, EOVERFLOW, s1, s1max);
    }
    else if (((uintptr_t)s2 >= (uintptr_t)s1 &&
         (uintptr_t)s2 < (uintptr_t)s1 + n) ||
        ((uintptr_t)s2 + n > (uintptr_t)s1 &&
         (uintptr_t)s2 + n <= (uintptr_t)s1 + s1max)) {
        return _memcpy_s_handler("Destination overlaps with source",
                                 (void *)&s1, EOVERFLOW, s1, s1max);
    }

    for (ptrdiff_t i = 0; i < (ptrdiff_t)n; i++) {
        ((unsigned char*)s1)[i] = ((unsigned char*)s2)[i];
    }

    return 0;
}
