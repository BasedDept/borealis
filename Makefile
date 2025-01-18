# Makefile
# Project root makefile
# Author: George Witt
# Date: 2024-02-11
#
# Copyright (c) 2024 George Witt
# SPDX-License-Identifier: BSD-2-Clause
.POSIX:
.PHONY:

#.NOTPARALLEL:

include config.mk

SUBDIRS=head lib boot kern

all: buildworld

clean: cleanworld

install:

uninstall:

buildworld: $(SUBDIRS)
	@echo Build complete.

cleanworld: $(SUBDIRS:=_CLEAN)

$(SUBDIRS): .PHONY
	@export PATH=$(TOOLCHAIN)/bin:$(PATH); \
	 cd $@ && $(CROSSENV) $(MAKE); echo

$(SUBDIRS:=_CLEAN): .PHONY
	-@cd $(@:_CLEAN=) && $(CROSSENV) $(MAKE) clean
	@echo

# Cross-directory dependencies
head: 
lib: head
boot: head lib
kern: head lib
cmd: head lib
