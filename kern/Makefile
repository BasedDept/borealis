# Makefile
# Kernel makefile
# Author: George Witt
# Date: 2024-02-24
#
# Copyright (c) 2024 George Witt
# SPDX-License-Identifier: BSD-2-Clause

.POSIX:

.PRECIOUS:
.SUFFIXES: .c .h .S .s .o

CFLAGS= $(CFLAGS_GLOBAL)

LDFLAGS= $(LDFLAGS_GLOBAL)

PROG= kern
OBJS=
LIBS=

all:

clean:
	-rm -r $(OBJS) $(PROG)

$(PROG): $(OBJS)
	$(LD) $(LDFLAGS) -o $(PROG) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.S.o:
	$(CC) $(CFLAGS) -c $< -o $@
