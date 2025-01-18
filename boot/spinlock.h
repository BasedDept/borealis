/**
 * @file spinlock.h
 * @brief Spinlock mutual exclusion
 * @author George Witt
 * @date 2024-11-16
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#ifndef SPINLOCK_H
#define SPINLOCK_H

#include <stdint.h>

typedef struct {
    uint8_t locked; // atomic
} spinlock_t;

extern void spinlock_destroy(spinlock_t *mtx);
extern int spinlock_init(spinlock_t *mtx);
extern int spinlock_lock(spinlock_t *mtx);
extern int spinlock_trylock(spinlock_t *mtx);
extern int spinlock_unlock(spinlock_t *mtx);

#endif
