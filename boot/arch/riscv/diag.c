/**
 * @file arch/riscv/diag.c
 * @brief RISC-V diagnostics HAL
 * @author George Witt
 * @date 2024-12-08
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier:
 */
#include "arch/riscv/riscv_sbi.h"
#include <string.h>
#include <stdalign.h>
#include <sys/cdefs.h>
#include <hal.h>

int diag_safe_print(const char *s)
{
    struct sbiret res = sbi_debug_console_write(strlen(s), (unsigned long)s, 0);
    return res.value;
}

int diag_safe_printx(unsigned long x)
{
    int res = 0;
    char xs[17];
    res += diag_safe_print("0x");
    int cnt = 0;
    for (int i = (sizeof(x) << 3) - 4; i >= 0; i-=4) {
        uint8_t nibble = (x >> i) & 0xf;
        if (nibble > 9) {
            xs[cnt] = nibble + 'a' - 10;
        }
        else {
            xs[cnt] = nibble + '0';
        }
        cnt++;
    }
    xs[cnt] = '\0';
    res += diag_safe_print(xs);
    return res;
}

int diag_print_stack_trace(const void *fp, const void *stack)
{
    int res = 0;
    while (fp < stack) {
        unsigned long ra = ((unsigned long *)fp)[-1];
        res += diag_safe_printx(ra);
        res += diag_safe_print("\n");
        fp = (const void *)((unsigned long *)fp)[-2];
    }
    return res;
}

#define asm_wait_ asm ("wfi");

struct asm_regs {
    unsigned long x0;
    unsigned long x1;
    unsigned long x2;
    unsigned long x3;
    unsigned long x4;
    unsigned long x5;
    unsigned long x6;
    unsigned long x7;
    unsigned long x8;
    unsigned long x9;
    unsigned long x10;
    unsigned long x11;
    unsigned long x12;
    unsigned long x13;
    unsigned long x14;
    unsigned long x15;
    unsigned long x16;
    unsigned long x17;
    unsigned long x18;
    unsigned long x19;
    unsigned long x20;
    unsigned long x21;
    unsigned long x22;
    unsigned long x23;
    unsigned long x24;
    unsigned long x25;
    unsigned long x26;
    unsigned long x27;
    unsigned long x28;
    unsigned long x29;
    unsigned long x30;
    unsigned long x31;
    unsigned long pc;
};

static struct asm_regs reg_dump;

void _panic_c(void);

[[noreturn]]
void _diag_panic(void)
{
    //&reg_dump;
    _panic_c();
    for (;;) asm_wait_;
}

[[gnu::naked]]
void _diag_dump_regs(void)
{
    __asm__ ("addi sp, sp, -32 \n\t"
             "sd ra, 24(sp) \n\t"
             "sd s0, 16(sp) \n\t"
             "sd s1, 8(sp) \n\t"
             "addi s0, sp, 32");

    __asm__ ("la s1, reg_dump");

    __asm__ ("sd x0, 0(s1) \n\t"
             "sd x3, 24(s1) \n\t"
             "sd x4, 32(s1) \n\t"
             "sd x5, 40(s1) \n\t"
             "sd x6, 48(s1) \n\t"
             "sd x7, 56(s1)");

    __asm__ ("sd x10, 80(s1) \n\t"
             "sd x11, 88(s1) \n\t"
             "sd x12, 96(s1) \n\t"
             "sd x13, 104(s1) \n\t"
             "sd x14, 112(s1) \n\t"
             "sd x15, 120(s1) \n\t"
             "sd x16, 128(s1) \n\t"
             "sd x17, 136(s1) \n\t"
             "sd x18, 144(s1) \n\t"
             "sd x19, 152(s1) \n\t"
             "sd x20, 160(s1) \n\t"
             "sd x21, 168(s1) \n\t"
             "sd x22, 176(s1) \n\t"
             "sd x23, 184(s1) \n\t"
             "sd x24, 192(s1) \n\t"
             "sd x25, 200(s1) \n\t"
             "sd x26, 208(s1) \n\t"
             "sd x27, 216(s1) \n\t"
             "sd x28, 224(s1) \n\t"
             "sd x29, 232(s1) \n\t"
             "sd x30, 240(s1) \n\t"
             "sd x31, 248(s1)");

    // ra
    __asm__ ("ld t0, 24(s0) \n\t"
             "sd t0, 8(s1)");

    // sp
    __asm__ ("addi t0, sp, 32 \n\t"
             "sd t0, 16(s1)");

    // fp
    __asm__ ("ld t0, 8(s0) \n\t"
             "sd t0, 64(s1)");

    // s1
    __asm__ ("ld t0, 16(s0) \n\t"
             "sd t0, 72(s1)");

    // pc
    __asm__ ("ld t0, 0(s0) \n\t"
             "addi t0, t0, -4 \n\t"
             "sd t0, 256(s1)");

    __asm__ ("addi sp, s0, -32 \n\t"
             "ld ra, 24(sp) \n\t"
             "ld s0, 16(sp) \n\t"
             "ld s1, 8(sp) \n\t"
             "addi sp, sp, 32 \n\t"
             "ret");
}


extern char __stack;
alignas(4096) char _safe_stack[2040];

void _panic_c(void)
{
    const char reg_names[][13] = { "x0/zero:    ",
                                   "x1/ra:      ",
                                   "x2/sp:      ",
                                   "x3/gp:      ",
                                   "x4/tp:      ",
                                   "x5/t0:      ",
                                   "x6/t1:      ",
                                   "x7/t2:      ",
                                   "x8/s0/fp:   ",
                                   "x9/s1:      ",
                                   "x10/a0:     ",
                                   "x11/a1:     ",
                                   "x12/a2:     ",
                                   "x13/a3:     ",
                                   "x14/a4:     ",
                                   "x15/a5:     ",
                                   "x16/a6:     ",
                                   "x17/a7:     ",
                                   "x18/s2:     ",
                                   "x19/s3:     ",
                                   "x20/s4:     ",
                                   "x21/s5:     ",
                                   "x22/s6:     ",
                                   "x23/s7:     ",
                                   "x24/s8:     ",
                                   "x25/s9:     ",
                                   "x26/s10:    ",
                                   "x27/s11:    ",
                                   "x28/t3:     ",
                                   "x29/t4:     ",
                                   "x30/t5:     ",
                                   "x31/t6:     ",
                                   "pc:         " };

    (void)diag_safe_print("--- Registers ---\n");

    for (int i = 0; i < 33; i+= 2) {
        (void)diag_safe_print(reg_names[i]);
        (void)diag_safe_printx(((unsigned long *)&reg_dump)[i]);
        if (i + 1 < 33) {
            (void)diag_safe_print("      ");
            (void)diag_safe_print(reg_names[i + 1]);
            (void)diag_safe_printx(((unsigned long *)&reg_dump)[i + 1]);
        }
        (void)diag_safe_print("\n");
    }

    #if 0
    (void)diag_safe_print("--- Stack Trace ---\n");
    (void)diag_print_stack_trace((void *)(_reg_dump[8]), &__stack);
    (void)diag_safe_print("-- end\n");
    #endif
}
#if 0
[[gnu::naked, noreturn]]
void panic_test(void)
{
    asm ("csrw sscratch, x2 \n\t"
         "la x2, _reg_dump \n\t"
         "sd x0, 0(x2) \n\t"
         "sd x1, 8(x2) \n\t"
         "sd x3, 24(x2) \n\t"
         "sd x4, 32(x2) \n\t"
         "sd x5, 40(x2) \n\t"
         "csrr x5, sscratch \n\t"
         "sd x5, 16(x2) \n\t"
         "sd x6, 48(x2) \n\t"
         "sd x7, 56(x2) \n\t"
         "sd x8, 64(x2) \n\t"
         "sd x9, 72(x2) \n\t"
         "sd x10, 80(x2) \n\t"
         "sd x11, 88(x2) \n\t"
         "sd x12, 96(x2) \n\t"
         "sd x13, 104(x2) \n\t"
         "sd x14, 112(x2) \n\t"
         "sd x15, 120(x2) \n\t"
         "sd x16, 128(x2) \n\t"
         "sd x17, 136(x2) \n\t"
         "sd x18, 144(x2) \n\t"
         "sd x19, 152(x2) \n\t"
         "sd x20, 160(x2) \n\t"
         "sd x21, 168(x2) \n\t"
         "sd x22, 176(x2) \n\t"
         "sd x23, 184(x2) \n\t"
         "sd x24, 192(x2) \n\t"
         "sd x25, 200(x2) \n\t"
         "sd x26, 208(x2) \n\t"
         "sd x27, 216(x2) \n\t"
         "sd x28, 224(x2) \n\t"
         "sd x29, 232(x2) \n\t"
         "sd x30, 240(x2) \n\t"
         "sd x31, 248(x2)");

    asm ("la sp, _safe_stack \n\t"
         "addi sp, sp, 2040");

    asm ("call _panic_c");

    asm ("csrw sie, zero \n\t"
         "csrw sip, zero \n\t"
         "l_halt:        \n\t"
         "    wfi        \n\t"
         "    j l_halt       ");
}
#endif
