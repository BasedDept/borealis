# Makefile
# Boot stub makefile
# Author: George Witt
# Date: 2024-02-24
#
# Copyright (c) 2024 George Witt
# SPDX-License-Identifier: BSD-2-Clause

.POSIX:

.PRECIOUS:
.SUFFIXES: .c .h .S .s .o

CFLAGS= $(CFLAGS_GLOBAL) \
	$(CFLAGS_ARCH) \
	-std=c18 \
	-Wall \
	-fno-builtin \
	-fvisibility=hidden \
	-nostdinc \
	-fstack-protector-all \
	-I"$(PROJECTDIR)/head" \
	-D__PROGNAME=\"$(PROG)\" \
	-I"." \
	-I"./fdt" \

LDFLAGS= $(LDFLAGS_GLOBAL) \
	 $(LDFLAGS_ARCH) \
	 -nostdlib \
	 -Tarch/$(TARGET_ARCH)/loader.ld

PROG= kernimg
OBJS= main.o errno.o string.o stdio.o panic.o stdlib.o ctype.o \
      fdt/fdt_addresses.o fdt/fdt.o fdt/fdt_check.o fdt/fdt_empty_tree.o \
      fdt/fdt_overlay.o fdt/fdt_ro.o fdt/fdt_rw.o fdt/fdt_strerror.o \
      fdt/fdt_sw.o fdt/fdt_wip.o $(OBJS_ARCH)
LIBS=

all: $(PROG)

clean:
	-rm -r $(OBJS) $(PROG)

main.o: main.c
errno.o: errno.c
string.o: string.c
stdio.o: stdio.c
panic.o: panic.c
stdlib.o: stdlib.c
ctype.o: ctype.c
fdt/fdt_addresses.o: fdt/fdt_addresses.c
fdt/fdt.o: fdt/fdt.c
fdt/fdt_check.o: fdt/fdt_check.c
fdt/fdt_empty_tree.o: fdt/fdt_empty_tree.c
fdt/fdt_overlay.o: fdt/fdt_overlay.c
fdt/fdt_ro.o: fdt/fdt_ro.c
fdt/fdt_rw.o: fdt/fdt_rw.c
fdt/fdt_strerror.o: fdt/fdt_strerror.c
fdt/fdt_sw.o: fdt/fdt_sw.c
fdt/fdt_wip.o: fdt/fdt_wip.c

include arch/$(TARGET_ARCH)/arch.mk

# TODO: customize outputs

$(PROG): $(OBJS) arch/$(TARGET_ARCH)/loader.ld
	$(LD) $(LDFLAGS) -o $(PROG) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.S.o:
	$(CC) $(CFLAGS) -c $< -o $@
