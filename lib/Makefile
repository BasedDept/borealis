# Makefile
# Library makefile
# Author: George Witt
# Date: 2024-03-02
#
# Copyright (c) 2024 George Witt
# SPDX-License-Identifier: BSD-2-Clause
.POSIX:
.PHONY:

SUBDIRS= libc libada libfdt

all: buildlibs

clean: cleanlibs

buildlibs: $(SUBDIRS)

cleanlibs: $(SUBDIRS:=_CLEAN)

$(SUBDIRS): .PHONY
	@cd $@; $(MAKE); echo

$(SUBDIRS:=_CLEAN): .PHONY
	-@cd $(@:_CLEAN=) && $(MAKE) clean
	@echo

# Cross-directory dependencies
libada:
libc: libada
libfdt: libc

#-@rm *.a
#-@ln -s lib*/*.a ./
#-@rm *.so
#-@ln -s lib*/*.so ./
#-@rm *.a
#-@rm *.so
