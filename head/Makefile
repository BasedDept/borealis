# Makefile
# Precompiled header makefile
# Author: George Witt
# Date: 2024-03-02
#
# Copyright (c) 2024 George Witt
# SPDX-License-Identifier: BSD-2-Clause

.POSIX:

.PHONY:

.PRECIOUS:
.SUFFIXES: .c .h .S .s .ads .o .pch .ali

ADAFLAGS= $(ADAFLAGS_GLOBAL) -nostdlib

PCHS= ada.o system.o
ALIS= ada.ali system.ali

all: $(PCHS)

clean:
	-rm -r $(PCHS) $(ALIS)

ada.o: ada.ads
system.o: system.ads

.h.pch:
	$(CC) -cc1 $< -emit-pch -o $@

.ads.o:
	$(GNAT) $(ADAFLAGS) -ffunction-sections -fdata-sections \
	                    -gnatg -Wl,--gc-sections -c $< -o $@
