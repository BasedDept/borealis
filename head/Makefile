# Makefile
# Precompiled header makefile
# Author: George Witt
# Date: 2024-02-11
#
# Copyright (c) 2024 George Witt
# SPDX-License-Identifier: BSD-2-Clause

.POSIX:

.PRECIOUS:
.SUFFIXES: .c .h .S .s .o .pch

PCHS=

all: $(PCHS)

clean:
	-rm -r $(PCHS)

.h.pch:
	$(CC) -cc1 $< -emit-pch -o $@
