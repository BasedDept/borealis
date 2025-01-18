# features.mk
# libc features
# Author: George Witt
# Date: 2024-09-08
#
# Copyright (c) 2024 George Witt
# SPDX-License-Identifier: BSD-2-Clause

LIBC_PATH= $(PROJECTDIR)/lib/libc

OBJS_ctype= $(OBJS_ctype_1) $(OBJS_ctype_2)
OBJS_ctype_1= $(LIBC_PATH)/ctype/isspace.o
OBJS_ctype_2= $(LIBC_PATH)/ctype/tolower.o \
			  $(LIBC_PATH)/ctype/toupper.o

OBJS_errno= $(LIBC_PATH)/errno/errno.o

OBJS_stdio= $(OBJS_stdio_6) $(OBJS_stdio_7) $(OBJS_stdio_10)
OBJS_stdio_6= $(LIBC_PATH)/stdio/fprintf.o \
			  $(LIBC_PATH)/stdio/printf.o \
			  $(LIBC_PATH)/stdio/vfprintf.o \
			  $(LIBC_PATH)/stdio/vprintf.o
OBJS_stdio_7= $(LIBC_PATH)/stdio/fputc.o \
			  $(LIBC_PATH)/stdio/fputs.o \
			  $(LIBC_PATH)/stdio/putc.o \
			  $(LIBC_PATH)/stdio/putchar.o \
			  $(LIBC_PATH)/stdio/puts.o
OBJS_stdio_10= $(LIBC_PATH)/stdio/perror.o
