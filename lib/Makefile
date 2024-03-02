# Makefile
# Library makefile
# Author: George Witt
# Date: 2024-03-02
#
# Copyright (c) 2024 George Witt
# SPDX-License-Identifier: BSD-2-Clause

.POSIX:

all:
	@cd libc; $(MAKE)
	@cd libfdt; $(MAKE)

clean:
	@cd libc; $(MAKE) clean
	@cd libfdt; $(MAKE) clean
