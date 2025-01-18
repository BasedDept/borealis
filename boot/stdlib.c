/**
 * @file stdlib.c
 * @brief stdlib
 * @author George Witt
 * @date 2024-09-06
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <stdint.h>
#include <stdlib.h>

#include <stddef.h>
#include <stdalign.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include "hal.h"

struct heap_frame {
    size_t n;
    size_t max;
    struct heap_frame *prev;
    max_align_t obj;
};

extern struct heap_frame *__hp;

static inline int _is_valid_align(size_t alignment)
{
    return (alignment && !(alignment & (alignment - 1))) && alignment >= sizeof(void *);
}

static inline int _is_aligned(void *ptr, size_t alignment)
{
    return ((uintptr_t)ptr & ~(alignment - 1)) == (uintptr_t)ptr;
}

static inline void *_align_ceil(void *ptr, size_t alignment)
{
    assert(ptr != NULL);
    assert(_is_valid_align(alignment));

    if (!_is_aligned(ptr, alignment)) {
        return (void *)(((uintptr_t)ptr & ~(alignment - 1)) + alignment);
    }

    return ptr;
}

void *aligned_alloc(size_t alignment, size_t size)
{
    // We assume that __hp is properly set at program start
    assert(__hp != NULL);

    if (!_is_valid_align(alignment) || !_is_aligned((void *)size, alignment)) {
        errno = EINVAL;
        return NULL;
    }

    if (alignment >= alignof(max_align_t)) {
        void *new = _align_ceil(&(__hp->obj), alignment);
        assert(new != NULL);
        struct heap_frame *a = new - offsetof(struct heap_frame, obj);

        if (a <= __hp || (void *)a > read_sp()) {
            errno = ENOMEM;
            return NULL;
        }

        assert(a != NULL);
        if (__hp->prev == NULL) {
            __hp->n = 0;
            a->prev = __hp;
        }
        else a->prev = __hp->prev;
        __hp = a;

        assert(__hp->prev != NULL);
        __hp->prev->max = (void *)__hp - (void *)&(__hp->prev->obj); 
    }

    void *ptr = malloc(size);
    if (ptr == NULL) {
        //TODO: undo
    }
    return ptr;
}

void *calloc(size_t nmemb, size_t size)
{
    assert(__hp != NULL);

    if (size && nmemb > (SIZE_MAX / size)) {
        errno = EINVAL;
        return NULL;
    }

    void *ptr = malloc(nmemb * size);
    if (ptr != NULL) {
        memset(ptr, 0, size);
    }

    return ptr;
}

void free(void *ptr)
{
    assert(__hp != NULL);

    if (ptr == NULL) return;

    assert(ptr != NULL);
    struct heap_frame *f = ptr - offsetof(struct heap_frame, obj);
    f->n = 0;

    while (__hp->prev != NULL && __hp->prev->n == 0) {
        assert(__hp->prev != NULL);
        __hp = __hp->prev;
    }
    //TODO: resize top of heap to prev->n
}

void *malloc(size_t size)
{
    assert(__hp != NULL);

    if (size == 0 || size > (void *)SIZE_MAX - (void *)&(__hp->obj)) {
        errno = EINVAL;
        return NULL;
    }

    assert(size != 0);
    assert(size > (void *)SIZE_MAX - (void *)&(__hp->obj));
    struct heap_frame *new_hp = _align_ceil((void *)&(__hp->obj) + size, alignof(struct heap_frame));
    if ((void *)new_hp > read_sp()) {
        errno = ENOMEM;
        return NULL;
    }

    __hp->n = size;
    __hp->max = (void *)new_hp - (void *)&(__hp->obj); 
    assert(new_hp != NULL);
    new_hp->prev = __hp;
    __hp = new_hp;

    return &(__hp->prev->obj);
}

void *realloc(void *ptr, size_t size)
{
    assert(__hp != NULL);

    if (ptr == NULL) {
        if (size != 0) return malloc(size);
        else return NULL;
    }

    if (size == 0) {
        errno = EINVAL;
        return NULL;
    }

    assert(ptr != NULL);
    struct heap_frame *r = ptr - offsetof(struct heap_frame, obj);

    assert(size != 0);
    if (size <= r->max) {
        r->n = size;
        if (r == __hp->prev) {
            struct heap_frame *new_hp = _align_ceil((void *)&(r->obj) + size, alignof(struct heap_frame));
            assert(new_hp != NULL);
            r->max = (void *)new_hp - (void *)&(r->obj);
            new_hp->prev = __hp;
            __hp = new_hp;
        }
        return &(r->obj);
    }

    void *new = malloc(size);
    if (new == NULL) return new;

    (void)memcpy(new, &(r->obj), r->n);

    free(ptr);

    assert(new != NULL);
    return new;
}

extern _Noreturn void _halt(void);

_Noreturn void abort(void)
{
    _halt();
}

