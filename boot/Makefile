# Makefile
# Boot stub makefile
# Author: George Witt
# Date: 2024-03-02
#
# Copyright (c) 2024 George Witt
# SPDX-License-Identifier: BSD-2-Clause

.POSIX:

#.PRECIOUS:

PROG= kernimg

CFLAGS= $(CFLAGS_GLOBAL) \
	    $(CFLAGS_ARCH) \
	    -std=c23 \
	    -Wall \
	    -fno-builtin \
	    -fvisibility=hidden \
	    -fstack-protector-all \
	    -D__PROGNAME=\"$(PROG)\" \
	    -I"."

ADAFLAGS= $(ADAFLAGS_GLOBAL) \
	      $(ADAFLAGS_ARCH)

LDFLAGS= $(LDFLAGS_GLOBAL) \
	     $(LDFLAGS_ARCH)

LDS= arch/$(TARGET_ARCH)/loader.ld

OBJS= main.o stdio.o stdlib.o panic.o memory.o memory/objpool.o hal.o $(OBJS_ARCH)
LIBS= "$(PROJECTDIR)/lib/libfdt/libfdt.a" \
	  "$(PROJECTDIR)/lib/libc/crt1.o" \
	  "$(PROJECTDIR)/lib/libc/stdlib/strtoul.o" \
	  "$(PROJECTDIR)/lib/libc/stdlib/ignore_handler_s.o" \
	  "$(PROJECTDIR)/lib/libc/stdlib/set_constraint_handler_s.o" \
	  "$(PROJECTDIR)/lib/libc/stdlib/atoi.o" \
	  "$(PROJECTDIR)/lib/libc/string/memcpy.o" \
	  "$(PROJECTDIR)/lib/libc/string/memcpy_s.o" \
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
	  "$(PROJECTDIR)/lib/libc/ctype/isdigit.o" \
	  "$(PROJECTDIR)/lib/libc/ctype/toupper.o" \
	  "$(PROJECTDIR)/lib/libc/errno/errno.o" \
	  "$(PROJECTDIR)/lib/libc/stdio/fileno.o" \
	  "$(PROJECTDIR)/lib/libc/stdio/perror.o" \
	  "$(PROJECTDIR)/lib/libc/stdio/putchar.o" \
	  "$(PROJECTDIR)/lib/libc/stdio/fputc.o" \
	  "$(PROJECTDIR)/lib/libc/stdio/putc.o" \
	  "$(PROJECTDIR)/lib/libc/stdio/puts.o" \
	  "$(PROJECTDIR)/lib/libc/stdio/fputs.o" \
	  "$(PROJECTDIR)/lib/libc/stdio/printf_s.o" \
	  "$(PROJECTDIR)/lib/libc/stdio/printf.o" \
	  "$(PROJECTDIR)/lib/libc/stdio/stdio_static.o" \
	  "$(PROJECTDIR)/lib/libc/stdio/vprintf_s.o" \
	  "$(PROJECTDIR)/lib/libc/stdio/vprintf.o" \
	  "$(PROJECTDIR)/lib/libc/stdio/fprintf_s.o" \
	  "$(PROJECTDIR)/lib/libc/stdio/fprintf.o" \
	  "$(PROJECTDIR)/lib/libc/stdio/vfprintf_s.o" \
	  "$(PROJECTDIR)/lib/libc/stdio/vfprintf.o" \
	  "$(PROJECTDIR)/lib/libada/libada.a"
ALIS= $(ALIS_ARCH)

GNATBIND_OBJ= b_$(PROG).o

all: $(PROG)

main.o: main.c
stdio.o: stdio.c
hal.o: hal.c
stdlib.o: stdlib.c
panic.o: panic.c
memory/objpool.o: memory/objpool.c memory/objpool.h
memory.o: memory.c memory.h

include arch/$(TARGET_ARCH)/arch.mk

include $(PROJECTDIR)/mk/prog_boot.mk
include $(PROJECTDIR)/mk/lang_c.mk
include $(PROJECTDIR)/mk/lang_asm.mk
include $(PROJECTDIR)/mk/lang_ada.mk
