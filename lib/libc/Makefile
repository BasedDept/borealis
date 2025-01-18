# Makefile
# libc makefile
# Author: George Witt
# Date: 2024-03-02
#
# Copyright (c) 2024 George Witt
# SPDX-License-Identifier: BSD-2-Clause

.POSIX:

LIBA= libc.a
LIBSO= libc.so

CFLAGS= $(CFLAGS_GLOBAL) -std=c18 -Wall -ffreestanding -nostdinc -fpic
LDFLAGS= $(LDFLAGS_GLOBAL) -nostdlib -z relro -z now

OBJS= crt1.o \
	string/memcpy.o \
	assert/assert.o \
	string/memcpy_s.o \
	string/memset.o \
	string/strnlen.o \
	string/strlen.o \
	string/strchr.o \
	string/strncpy.o \
	string/strrchr.o \
	string/memchr.o \
	string/memcmp.o \
	string/memmove.o \
	string/strncmp.o \
	errno/errno.o \
	stdlib/strtoul.o \
	stdlib/atoi.o \
	stdlib/set_constraint_handler_s.o \
	stdlib/ignore_handler_s.o \
	ctype/isalnum.o \
	ctype/isalpha.o \
	ctype/isblank.o \
	ctype/iscntrl.o \
	ctype/isdigit.o \
	ctype/isgraph.o \
	ctype/islower.o \
	ctype/isprint.o \
	ctype/ispunct.o \
	ctype/isspace.o \
	ctype/isupper.o \
	ctype/isxdigit.o \
	ctype/tolower.o \
	ctype/toupper.o \
	stdio/fileno.o \
	stdio/perror.o \
	stdio/putchar.o \
	stdio/putc.o \
	stdio/fputc.o \
	stdio/puts.o \
	stdio/fputs.o \
	stdio/printf_s.o \
	stdio/printf.o \
	stdio/vprintf_s.o \
	stdio/vprintf.o \
	stdio/fprintf_s.o \
	stdio/fprintf.o \
	stdio/stdio_static.o \
	stdio/vfprintf_s.o \
	stdio/vfprintf.o \
	unistd/write.o

all: $(LIBA)

crt1.o: crt1.c

assert/assert.o: assert/assert.c $(PROJECTDIR)/head/assert.h

ctype/isalnum.o:  ctype/isalnum.c $(PROJECTDIR)/head/ctype.h
ctype/isalpha.o:  ctype/isalpha.c $(PROJECTDIR)/head/ctype.h
ctype/isblank.o:  ctype/isblank.c $(PROJECTDIR)/head/ctype.h
ctype/iscntrl.o:  ctype/iscntrl.c $(PROJECTDIR)/head/ctype.h
ctype/isdigit.o:  ctype/isdigit.c $(PROJECTDIR)/head/ctype.h
ctype/isgraph.o:  ctype/isgraph.c $(PROJECTDIR)/head/ctype.h
ctype/islower.o:  ctype/islower.c $(PROJECTDIR)/head/ctype.h
ctype/isprint.o:  ctype/isprint.c $(PROJECTDIR)/head/ctype.h
ctype/ispunct.o:  ctype/ispunct.c $(PROJECTDIR)/head/ctype.h
ctype/isspace.o:  ctype/isspace.c $(PROJECTDIR)/head/ctype.h
ctype/isupper.o:  ctype/isupper.c $(PROJECTDIR)/head/ctype.h
ctype/isxdigit.o: ctype/isxdigit.c $(PROJECTDIR)/head/ctype.h
ctype/tolower.o:  ctype/tolower.c $(PROJECTDIR)/head/ctype.h
ctype/toupper.o:  ctype/toupper.c $(PROJECTDIR)/head/ctype.h

errno/errno.o: errno/errno.c
string/memcpy.o: string/memcpy.c
string/memcpy_s.o: string/memcpy_s.c
string/memset.o: string/memset.c
string/memset_explicit.o: string/memset_explicit.c
string/strnlen.o: string/strnlen.c
string/strlen.o: string/strlen.c
string/strncmp.o: string/strncmp.c
string/strncpy.o: string/strncpy.c
string/strrchr.o: string/strrchr.c
string/strchr.o: string/strchr.c
string/memchr.o: string/memchr.c
string/memcmp.o: string/memcmp.c
string/memmove.o: string/memmove.c
stdlib/strtoul.o: stdlib/strtoul.c
stdlib/atoi.o: stdlib/atoi.c
stdlib/__constraint_handler_s.o: stdlib/set_constraint_handler_s.c
stdlib/ignore_handler_s.o: stdlib/ignore_handler_s.c
stdio/fileno.o: stdio/fileno.c
stdio/perror.o: stdio/perror.c
stdio/putchar.o: stdio/putchar.c
stdio/putc.o: stdio/putc.c
stdio/fputc.o: stdio/fputc.c
stdio/puts.o: stdio/puts.c
stdio/fputs.o: stdio/fputs.c
stdio/printf_s.o: stdio/printf_s.c
stdio/printf.o: stdio/printf.c
stdio/vprintf_s.o: stdio/vprintf_s.c stdio/stdio_static.h
stdio/stdio_static.o: stdio/stdio_static.c
stdio/vprintf.o: stdio/vprintf.c stdio/stdio_static.h
stdio/fprintf_s.o: stdio/fprintf_s.c
stdio/fprintf.o: stdio/fprintf.c
stdio/vfprintf_s.o: stdio/vfprintf_s.c stdio/stdio_static.h
stdio/vfprintf.o: stdio/vfprintf.c stdio/stdio_static.h
unistd/write.o: unistd/write.c

include $(PROJECTDIR)/mk/lib.mk
include $(PROJECTDIR)/mk/lang_c_std.mk
include $(PROJECTDIR)/mk/lang_asm.mk
