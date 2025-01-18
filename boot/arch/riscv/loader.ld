/*
    loader.ld
    Linker script for boot stub (riscv)
    Author: George Witt
    Date: 2024-02-24
    
    Copyright (c) 2024 George Witt
    SPDX-License-Identifier: BSD-2-Clause
*/

OUTPUT_ARCH(riscv)
ENTRY(_mbr)
STACK_SIZE = 0x10000;
MEMORY
{
    rom (rx) : ORIGIN = 0x00001000, LENGTH = 60K
    flash (rwx) : ORIGIN = 0x20000000, LENGTH = 64M
    /* ram (rwx) : ORIGIN = 0x80000000, LENGTH = 2M */
    ram (rwx) : ORIGIN = 0x80080000, LENGTH = 0x1c0000
}
SECTIONS
{
    .boot : ALIGN(4K) {
        __boot_start = .;
        KEEP(*(.boot))
        . = __boot_start + 512;
    } >ram

    .text : {
        __executable_start = .;
        *(.text)
        *(.text*)
        _etext = .;
    } >ram

    .rodata : {
        *(.rodata)
        *(.rodata*)
    } >ram

    .data : {
        PROVIDE(__global_pointer$ = .);
        *(.data)
        *(.data*)
    } >ram

    .bss (NOLOAD) : {
        *(.bss)
        *(.bss*)
    } >ram

    .heap (NOLOAD) : ALIGN(16) {
        PROVIDE(__heap = .);
    } >ram

    .stack (NOLOAD) : {
        . += STACK_SIZE;
        PROVIDE(__stack = .);
    } >ram
}
