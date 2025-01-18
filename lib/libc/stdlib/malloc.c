/**
 * @file stdlib/malloc.c
 * @brief malloc
 * @author George Witt
 * @date 2024-09-06
 *
 * ISO/IEC 9899:1990 7.10.3.3
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

struct heap_frame {
    size_t n;
    struct heap *prev;
    max_align_t obj;
};

extern struct heap_frame *__hp;

void *malloc(size_t size)
{
    // We assume that __hp is properly set at program start
    assert(__hp != NULL);

}

