# Makefile
# libfdt makefile
# Author: George Witt
# Date: 2024-03-02
#
# Copyright (c) 2024 George Witt
# SPDX-License-Identifier: BSD-2-Clause

.POSIX:

.PRECIOUS:
.SUFFIXES: .c .h .S .s .o

LIBA= libfdt.a
LIBSO= libfdt.so
OBJS= fdt_addresses.o fdt.o fdt_check.o fdt_empty_tree.o fdt_overlay.o fdt_ro.o fdt_rw.o fdt_strerror.o fdt_sw.o fdt_wip.o
LIBS= "$(PROJECTDIR)/lib/libc/libc.a"

CFLAGS= $(CFLAGS_GLOBAL) -std=c2x -Wall -nostdinc -D_POSIX_C_SOURCE=200809L -I"$(PROJECTDIR)/head" -I. -fpic
LDFLAGS= $(LDFLAGS_GLOBAL) -nostdlib -z relro -z now

all: $(LIBA)

clean:
	-rm -r $(OBJS) $(LIBA) $(LIBSO)

fdt_addresses.o: fdt_addresses.c
fdt.o: fdt.c
fdt_check.o: fdt_check.c
fdt_empty_tree.o: fdt_empty_tree.c
fdt_overlay.o: fdt_overlay.c
fdt_ro.o: fdt_ro.c
fdt_rw.o: fdt_rw.c
fdt_strerror.o: fdt_strerror.c
fdt_sw.o: fdt_sw.c
fdt_wip.o: fdt_wip.c

#include arch/$(TARGET_ARCH)/arch.mk

$(LIBA): $(OBJS)
	$(AR) -c -r -s $(LIBA) $(OBJS)

$(LIBSO): $(OBJS)
	$(LD) $(LDFLAGS) -shared -o $(LIBSO) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.S.o:
	$(CC) $(CFLAGS) -c $< -o $@

