/**
 * @file arch/riscv/riscv.h
 * @brief RISC-V helpers
 * @author George Witt
 * @date 2024-09-06
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: BSD-2-Clause
 */
#ifndef BOOT_ARCH_RISCV_RISCV_H
#define BOOT_ARCH_RISCV_RISCV_H

extern void *riscv_read_sp(void);
/*
__riscv 1
__riscv_xlen 32 64 128
__riscv_flen 32 54 128
__riscv_32e 1
__riscv_64e 1
__riscv_vector 1
__riscv_v_min_vlen N
__riscv_v_elen N
__riscv_v_elen_fp N
__riscv_misaligned_fast 1
__riscv_misaligned_slow 1
__riscv_misaligned_avoid 1
__riscv_i 1
__riscv_e 1
__riscv_m 1
__riscv_a 1
__riscv_f 1
__riscv_d 1
__riscv_c 1
__riscv_abi_rve 1
__riscv_float_abi_soft 1
__riscv_float_abi_single 1
__riscv_float_abi_double 1
__riscv_float_abi_quad 1
__riscv_cmodel_medlow 1
__riscv_cmodel_medany 1
__riscv_cmodel_large 1
__PIC__
__PIE__
[[gnu::naked]]
[[gnu::interrupt]]
[[gnu::interrupt("user")]]
[[gnu::interrupt("supervisor")]]
[[gnu::interrupt("machine")]]
[[gnu::target("arch=")]]
[[gnu::target("tune=")]]
[[gnu::target("cpu=")]]
[[gnu::target_clones("arch=", "default")]]
[[gnu::target_version("arch=")]]
[[gnu::target_version("default")]]
[[riscv::vector_cc]]

__asm__
m
An address that is held in a general-purpose register with offset.
A
An address that is held in a general-purpose register.
r
General purpose register
f
Floating-point register
i
Immediate integer operand
I
12-bit signed immediate integer operand
K
5-bit unsigned immediate integer operand
J
Zero integer immediate operand
s
symbol or label reference with a constant offset
vr
Vector register
vd
Vector register, excluding v0
vm
Vector register, only v0
z
Print zero (x0) register for immediate 0, typically used with constraints J
i
Print i if corresponding operand is immediate.


struct {
    unsigned length;
    unsigned long long features[];
} __riscv_feature_bits;

struct {
    unsigned length;
    unsigned long long features[];
} __riscv_vendor_feature_bits;

struct {
  unsigned mvendorid;
  unsigned long long marchid;
  unsigned long long mimpid;
} __riscv_cpu_model;

void __init_riscv_feature_bits(void *);

__riscv_feature_bits.features[0]
a
0
0

c
0
2

d
0
3

f
0
5

i
0
8

m
0
12

v
0
21

zacas
0
26

zba
0
27

zbb
0
28

zbc
0
29

zbkb
0
30

zbkc
0
31

zbkx
0
32

zbs
0
33

zfa
0
34

zfh
0
35

zfhmin
0
36

zicboz
0
37

zicond
0
38

zihintntl
0
39

zihintpause
0
40

zknd
0
41

zkne
0
42

zknh
0
43

zksed
0
44

zksh
0
45

zkt
0
46

ztso
0
47

zvbb
0
48

zvbc
0
49

zvfh
0
50

zvfhmin
0
51

zvkb
0
52

zvkg
0
53

zvkned
0
54

zvknha
0
55

zvknhb
0
56

zvksed
0
57

zvksh
0
58

zvkt
0
59

zve32x
0
60

zve32f
0
61

zve64x
0
62

zve64f
0
63

zve64d
1
0

zimop
1
1

zca
1
2

zcb
1
3

zcd
1
4

zcf
1
5

zcmop
1
6

zawrs
1
7
*/
#endif
