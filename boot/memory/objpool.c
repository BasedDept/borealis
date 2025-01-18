#include "objpool.h"

#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <assert.h>
#include <stdio.h>

struct objpool objpool_init(void *pool_buf, uint32_t *occ_buf, 
                            size_t obj_size, ptrdiff_t capacity)
{
    if (pool_buf == NULL || occ_buf == NULL) {
        errno = EINVAL;
        goto leave;
    }

    for (ptrdiff_t i = 0; i < capacity / sizeof(uint32_t) * 2; i++) {
        occ_buf[i] = 0;
    }

    struct objpool out = {.pool = pool_buf,
                          .obj_size = obj_size,
                          .capacity = capacity,
                          .occupied = occ_buf,
                          .used = 0};
    return out;

leave:;
    struct objpool err = {.pool     = NULL,
                          .obj_size = 0,
                          .capacity = 0,
                          .occupied = NULL,
                          .used     = 0};
    return err;
}

#define BIT_ARRAYU32(arr, x)       (((arr)[(x) >> 5] >> ((x) & 0x1f)) & 1)
#define PAIR_ARRAYU32(arr, x)      (((arr)[(x) >> 5] >> ((x) & 0x1f)) & 3)
#define SET_BIT_ARRAYU32(arr, x)   ((arr)[(x) >> 5] |= 1 << ((x) & 0x1f))
#define RESET_BIT_ARRAYU32(arr, x) ((arr)[(x) >> 5] &= ~(1 << ((x) & 0x1f)))

void *objpool_alloc(struct objpool *ctx)
{
    // clangdeeznuts
    if (ctx == NULL) {
        errno = EINVAL;
        return NULL;
    }

    uint32_t cur = 1;

    if (BIT_ARRAYU32(ctx->occupied, cur)) {
        errno = ENOMEM;
        return NULL;
    }

    for (cur = 2; cur < ctx->capacity; cur <<= 1) {
        uint8_t child = PAIR_ARRAYU32(ctx->occupied, cur);
        if (child == 1) {
            cur++;
        }
    }
    cur >>= 1;

    for (; cur > 0; cur >>= 1) {
        SET_BIT_ARRAYU32(ctx->occupied, cur);
        uint8_t child = PAIR_ARRAYU32(ctx->occupied, cur);
        if (child != 3) break;
    }

    ctx->used++;
    return &(ctx->pool[(cur - (ctx->capacity >> 2)) * ctx->obj_size]);
}

void objpool_free(struct objpool *ctx, void *obj)
{
    if (ctx == NULL || obj == NULL) {
        errno = EINVAL;
        return;
    }

    uint32_t cur = (ptrdiff_t)(((uintptr_t)obj - (uintptr_t)ctx->pool)) / ctx->obj_size +
                              (ctx->capacity >> 2);

    if (cur < 0 || cur >= ctx->capacity) {
        errno = EINVAL;
        return;
    }

    for (; cur > 0; cur >>= 1) {
        RESET_BIT_ARRAYU32(ctx->occupied, cur);
    }

    ctx->used--;
}

