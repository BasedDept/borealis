#include <stdint.h>
#include <stdalign.h>

#if __riscv_xlen == 64

typedef uint64_t pte_t;
static_assert(sizeof(pte_t) * 8 == 64, "");
static_assert(alignof(pte_t) * 8 == 64, "");

struct sv39 {
    pte_t v : 1;
    pte_t r : 1;
    pte_t w : 1;
    pte_t x : 1;
    pte_t u : 1;
    pte_t g : 1;
    pte_t a : 1;
    pte_t d : 1;
    pte_t rsw : 2;
    pte_t ppn0 : 9;
    pte_t ppn1 : 9;
    pte_t ppn2 : 26;
    pte_t reserved0_54 : 7;
    pte_t pbmt : 2;
    pte_t n : 1;
};
static_assert(sizeof(struct sv39) == sizeof(pte_t), "");
static_assert(alignof(struct sv39) == alignof(pte_t), "");

struct sv48 {
    pte_t v : 1;
    pte_t r : 1;
    pte_t w : 1;
    pte_t x : 1;
    pte_t u : 1;
    pte_t g : 1;
    pte_t a : 1;
    pte_t d : 1;
    pte_t rsw : 2;
    pte_t ppn0 : 9;
    pte_t ppn1 : 9;
    pte_t ppn2 : 9;
    pte_t ppn3 : 17;
    pte_t reserved0_54 : 7;
    pte_t pbmt : 2;
    pte_t n : 1;
};
static_assert(sizeof(struct sv48) == sizeof(pte_t), "");
static_assert(alignof(struct sv48) == alignof(pte_t), "");

struct sv57 {
    pte_t v : 1;
    pte_t r : 1;
    pte_t w : 1;
    pte_t x : 1;
    pte_t u : 1;
    pte_t g : 1;
    pte_t a : 1;
    pte_t d : 1;
    pte_t rsw : 2;
    pte_t ppn0 : 9;
    pte_t ppn1 : 9;
    pte_t ppn2 : 9;
    pte_t ppn3 : 9;
    pte_t ppn4 : 8;
    pte_t reserved0_54 : 7;
    pte_t pbmt : 2;
    pte_t n : 1;
};
static_assert(sizeof(struct sv57) == sizeof(pte_t), "");
static_assert(alignof(struct sv57) == alignof(pte_t), "");

typedef uintptr_t ppn_t;
static_assert(sizeof(ppn_t) * 8 >= 1 << 44, "");

typedef uintptr_t vpn_t;
static_assert(sizeof(vpn_t) * 8 >= 1 << 45, "");

typedef struct {
    alignas(4096) pte_t page[512];
} pgt_t;
static_assert(sizeof(pgt_t) == 4096, "");
static_assert(alignof(pgt_t) == 4096, "");

#elif __riscv_xlen == 32

typedef uint32_t pte_t;
static_assert(sizeof(pte_t) * 8 == 32, "");
static_assert(alignof(pte_t) * 8 == 32, "");

struct sv32 {
    pte_t v : 1;
    pte_t r : 1;
    pte_t w : 1;
    pte_t x : 1;
    pte_t u : 1;
    pte_t g : 1;
    pte_t a : 1;
    pte_t d : 1;
    pte_t rsw : 2;
    pte_t ppn0 : 10;
    pte_t ppn1 : 12;
};
static_assert(sizeof(struct sv32) == sizeof(pte_t), "");
static_assert(alignof(struct sv32) == alignof(pte_t), "");

typedef uintptr_t ppn_t;
static_assert(sizeof(ppn_t) * 8 >= 1 << 22, "");

typedef uintptr_t vpn_t;
static_assert(sizeof(vpn_t) * 8 >= 1 << 20, "");

typedef struct {
    alignas(4096) pte_t page[1024];
} pgt_t;
static_assert(sizeof(pgt_t) == 4096, "");
static_assert(alignof(pgt_t) == 4096, "");

#endif

