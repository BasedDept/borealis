# Makefile
# libada makefile
# Author: George Witt
# Date: 2024-03-02
#
# Copyright (c) 2024 George Witt
# SPDX-License-Identifier: BSD-2-Clause

.POSIX:

LIBA= libada.a
LIBSO= libada.so

CFLAGS= $(CFLAGS_GLOBAL) -std=c99 -Wall -fpic $(CFLAGS_ARCH)
ADAFLAGS= $(ADAFLAGS_GLOBAL) -nostdlib -fpic -I"$(PROJECTDIR)/head" \
          $(ADAFLAGS_ARCH)
LDFLAGS= $(LDFLAGS_GLOBAL) $(LDFLAGS_ARCH)

OBJS= libada.o s-stalib.o binding.o $(OBJS_ARCH)
ALIS= libada.ali s-stalib.ali $(ALIS_ARCH)
LIBS= "$(PROJECTDIR)/head/ada.o" "$(PROJECTDIR)/head/system.o"

GNATBIND_OBJ= b_$(LIBSO:%.so=%.o)

all:
all: $(LIBA)

s-stalib.o: s-stalib.adb
binding.o: binding.c
libada.o: libada.adb libada.ads
	@echo "[GNAT]     $@"
	@$(GNAT) -nostdlib -I$(PROJECTDIR)/head $(ADAFLAGS) -c $< -o $@

#include arch/$(TARGET_ARCH)/arch.mk

include $(PROJECTDIR)/mk/lib.mk
include $(PROJECTDIR)/mk/lang_c.mk
#include $(PROJECTDIR)/mk/lang_asm.mk
include $(PROJECTDIR)/mk/lang_ada_std.mk

