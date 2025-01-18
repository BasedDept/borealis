/**
 * @file assert.c
 * @brief assert
 * @author George Witt
 * @date 2024-09-08
 *
 * ISO/IEC 9899:1990 7.2.1.1
 * ISO/IEC 9899:1999 7.2.1.1
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <assert.h>

#include <stdnoreturn.h>
#include <stdio.h>
#include <stdlib.h>

noreturn void __assert_fail(const char *expr, const char *file, int line)
{
    fprintf(stderr, "Assertion failed: %s, file %s, line %d",
            expr, file, line);

    abort();
}

noreturn void __assert_fail_v199901(const char *expr, const char *file,
                                    int line, const char *func)
{
    fprintf(stderr, "Assertion failed: %s, function %s, file %s, line %d",
            expr, func, file, line);

    abort();
}
