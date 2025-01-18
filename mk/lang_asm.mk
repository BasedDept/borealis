# lang_asm.mk
# Assembly build system
# Author: George Witt
# Date: 2024-09-07
#
# Copyright (c) 2024 George Witt
# SPDX-License-Identifier: BSD-2-Clause

.SUFFIXES: .S .s .h .o

.S.o:
	@echo "[AS]       $@"
	@$(CC) -nostdinc -I$(PROJECTDIR)/head $(CFLAGS) -c $< -o $@

