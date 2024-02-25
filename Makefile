# Makefile
# Project root makefile
# Author: George Witt
# Date: 2024-02-11
#
# Copyright (c) 2024 George Witt
# SPDX-License-Identifier: BSD-2-Clause

include config.mk

.POSIX:
.PHONY:

SUBDIRS=head lib boot kern

all: buildworld

clean: cleanworld

install:

uninstall:

buildworld: $(SUBDIRS)

cleanworld: $(SUBDIRS:=_CLEAN)


$(SUBDIRS): .PHONY
	@export PATH=$(TOOLCHAIN)/bin:$(PATH); \
	 cd $@ && $(CROSSENV) $(MAKE)

$(SUBDIRS:=_CLEAN): .PHONY
	-@cd $(@:_CLEAN=) && $(CROSSENV) $(MAKE) clean

# Cross-directory dependencies
head: 
lib: head
boot: head
kern: head lib
cmd: head lib
