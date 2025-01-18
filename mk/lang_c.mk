# lang_c.mk
# C language support
# Author: George Witt
# Date: 2024-09-07
#
# Copyright (c) 2024 George Witt
# SPDX-License-Identifier: BSD-2-Clause

.SUFFIXES: .c .h .o .pch

.c.o:
	@echo "[CC]       $@"
	@$(CC) -nostdinc -I$(PROJECTDIR)/head $(CFLAGS) -c $< -o $@

.h.pch:
	@echo "[PCH]      $@"
	@$(CC) -cc1 $< -emit-pch -o $@
