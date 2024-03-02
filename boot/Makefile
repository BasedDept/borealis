# Makefile
# Boot stub makefile
# Author: George Witt
# Date: 2024-03-02
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
	-I"."

LDFLAGS= $(LDFLAGS_GLOBAL) \
	 $(LDFLAGS_ARCH) \
	 -nostdlib \
	 -Tarch/$(TARGET_ARCH)/loader.ld

PROG= kernimg
OBJS= main.o stdio.o panic.o $(OBJS_ARCH)
LIBS= "$(PROJECTDIR)/lib/libfdt/libfdt.a" \
	"$(PROJECTDIR)/lib/libc/stdlib/strtoul.o" \
	"$(PROJECTDIR)/lib/libc/string/memcpy.o" \
	"$(PROJECTDIR)/lib/libc/string/memmove.o" \
	"$(PROJECTDIR)/lib/libc/string/memcmp.o" \
	"$(PROJECTDIR)/lib/libc/string/strncmp.o" \
	"$(PROJECTDIR)/lib/libc/string/memchr.o" \
	"$(PROJECTDIR)/lib/libc/string/strchr.o" \
	"$(PROJECTDIR)/lib/libc/string/strrchr.o" \
	"$(PROJECTDIR)/lib/libc/string/memset.o" \
	"$(PROJECTDIR)/lib/libc/string/strlen.o" \
	"$(PROJECTDIR)/lib/libc/string/strnlen.o" \
	"$(PROJECTDIR)/lib/libc/ctype/isspace.o" \
	"$(PROJECTDIR)/lib/libc/errno/errno.o" \
	"$(PROJECTDIR)/lib/libc/stdio/perror.o"

all: $(PROG)

clean:
	-rm -r $(OBJS) $(PROG)

main.o: main.c
stdio.o: stdio.c
panic.o: panic.c

include arch/$(TARGET_ARCH)/arch.mk

$(PROG): $(OBJS) arch/$(TARGET_ARCH)/loader.ld
	$(LD) $(LDFLAGS) -o $(PROG) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.S.o:
	$(CC) $(CFLAGS) -c $< -o $@
