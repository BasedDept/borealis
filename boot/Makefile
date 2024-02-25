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

LDFLAGS= $(LDFLAGS_GLOBAL) \
	 $(LDFLAGS_ARCH) \
	 -nostdlib \
	 -Tarch/$(TARGET_ARCH)/loader.ld

PROG= kernimg
OBJS= main.o errno.o string.o stdio.o panic.o $(OBJS_ARCH)
LIBS=

all: $(PROG)

clean:
	-rm -r $(OBJS) $(PROG)

main.o: main.c
errno.o: errno.c
string.o: string.c
stdio.o: stdio.c
panic.o: panic.c

include arch/$(TARGET_ARCH)/arch.mk

$(PROG): $(OBJS) arch/$(TARGET_ARCH)/loader.ld
	$(LD) $(LDFLAGS) -o $(PROG) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.S.o:
	$(CC) $(CFLAGS) -c $< -o $@
