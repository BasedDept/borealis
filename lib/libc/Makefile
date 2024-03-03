# Makefile
# libc makefile
# Author: George Witt
# Date: 2024-03-02
#
# Copyright (c) 2024 George Witt
# SPDX-License-Identifier: BSD-2-Clause

.POSIX:

.PRECIOUS:
.SUFFIXES: .c .h .S .s .o

LIBA= libc.a
LIBSO= libc.so
OBJS= string/memcpy.o \
	string/memset.o \
	string/strnlen.o \
	string/strlen.o \
	string/strchr.o \
	string/strrchr.o \
	string/memchr.o \
	string/memcmp.o \
	string/memmove.o \
	string/strncmp.o \
	errno/errno.o \
	stdlib/strtoul.o \
	ctype/isspace.o \
	stdio/perror.o

CFLAGS= $(CFLAGS_GLOBAL) -std=c18 -Wall -ffreestanding -nostdinc \
        -I"$(PROJECTDIR)/head" -fpic
LDFLAGS= $(LDFLAGS_GLOBAL) -nostdlib -z relro -z now

all: $(LIBA)

clean:
	-rm -r $(OBJS) $(LIBA) $(LIBSO)

ctype/isspace.o: ctype/isspace.c
errno/errno.o: errno/errno.c
string/memcpy.o: string/memcpy.c
string/memset.o: string/memset.c
string/memset_explicit.o: string/memset_explicit.c
string/strnlen.o: string/strnlen.c
string/strlen.o: string/strlen.c
string/strncmp.o: string/strncmp.c
string/strrchr.o: string/strrchr.c
string/strchr.o: string/strchr.c
string/memchr.o: string/memchr.c
string/memcmp.o: string/memcmp.c
string/memmove.o: string/memmove.c
stdlib/strtoul.o: stdlib/strtoul.c
stdio/perror.o: stdio/perror.c

#include arch/$(TARGET_ARCH)/arch.mk

$(LIBA): $(OBJS)
	$(AR) -c -r -s $(LIBA) $(OBJS)

$(LIBSO): $(OBJS)
	$(LD) $(LDFLAGS) -shared -o $(LIBSO) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.S.o:
	$(CC) $(CFLAGS) -c $< -o $@
