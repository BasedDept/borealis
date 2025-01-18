# Makefile
# Precompiled header makefile
# Author: George Witt
# Date: 2024-03-02
#
# Copyright (c) 2024 George Witt
# SPDX-License-Identifier: 
.POSIX:
.PHONY:

.PRECIOUS: .h .ads

ADAFLAGS= $(ADAFLAGS_GLOBAL) -nostdlib

PCHS= ada.o system.o
ALIS= ada.ali system.ali

all: $(PCHS)

clean:
	-rm -r $(PCHS) $(ALIS)

ada.o: ada.ads
system.o: system.ads

include $(PROJECTDIR)/mk/lang_c_std.mk
include $(PROJECTDIR)/mk/lang_ada_std.mk
