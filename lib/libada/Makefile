# Makefile
# libada makefile
# Author: George Witt
# Date: 2024-03-02
#
# Copyright (c) 2024 George Witt
# SPDX-License-Identifier: BSD-2-Clause

.POSIX:

.PRECIOUS:
.SUFFIXES: .c .h .S .s .adb .ads .o .ali

LIBA= libada.a

CFLAGS= $(CFLAGS_GLOBAL) -std=c99 -Wall -ffreestanding -nostdinc \
        -I"$(PROJECTDIR)/head" -fpic $(CFLAGS_ARCH)
ADAFLAGS= $(ADAFLAGS_GLOBAL) -nostdlib -fpic -I"$(PROJECTDIR)/head" \
          $(ADAFLAGS_ARCH)
LDFLAGS= $(LDFLAGS_GLOBAL) $(LDFLAGS_ARCH)

OBJS= s-stalib.o binding.o $(OBJS_ARCH)
ALIS= s-stalib.ali $(ALIS_ARCH)
LIBS= "$(PROJECTDIR)/head/ada.o" "$(PROJECTDIR)/head/system.o"

all: $(LIBA)

clean:
	-rm -r $(OBJS) $(ALIS) b_$(PROG).o b_$(PROG).ali b_$(PROG).adb \
	       b_$(PROG).ads $(LIBA)

s-stalib.o: s-stalib.adb
binding.o: binding.c

#include arch/$(TARGET_ARCH)/arch.mk

$(LIBA): $(OBJS)
	$(AR) -c -r -s $(LIBA) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.adb.o:
	$(GNAT) $(ADAFLAGS) -ffunction-sections -fdata-sections \
	        -gnatg -Wl,--gc-sections -c $< -o $@

b_$(PROG).o:
	$(GNATBIND) -I"$(PROJECTDIR)/head" -n $(ALIS) -o $*.adb
	$(GNAT) $(ADAFLAGS) -c b_$(PROG).adb -o $@
