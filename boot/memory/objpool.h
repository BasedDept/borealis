#include <stddef.h>
#include <stdint.h>

struct objpool {
    void *pool;
    size_t obj_size;
    ptrdiff_t capacity;
    uint32_t *occupied;
    uint_fast32_t used;
};

struct objpool objpool_init(void *pool_buf, uint32_t *occ_buf,
                            size_t obj_size, ptrdiff_t capacity);
void *objpool_alloc(struct objpool *ctx);
void objpool_free(struct objpool *ctx, void *obj);

#define OBJPOOL_DEFINE(name, type, capacity) \
static struct objpool name ## _obj_pool; \
static inline void name ## _obj_init_pool(void) \
{ \
    static type buf[(capacity)]; \
    static uint32_t occupied[(capacity) / sizeof(uint32_t) * 2]; \
    name ## _obj_pool = objpool_init(buf, occupied, sizeof(type), capacity); \
} \
/* NOLINTNEXTLINE(bugprone-macro-parentheses) */\
static inline type * name ## _obj_request(void) \
{ \
    return (type *)objpool_alloc(&(name ## _obj_pool)); \
} \
/* NOLINTNEXTLINE(bugprone-macro-parentheses) */\
static inline void name ## _obj_release(type *obj) \
{\
    objpool_free(&(name ## _obj_pool), (void *)obj); \
}

