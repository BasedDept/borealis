# Makefile
# Boot stub makefile
# Author: George Witt
# Date: 2024-03-02
#
# Copyright (c) 2024 George Witt
# SPDX-License-Identifier: BSD-2-Clause

.POSIX:

.PRECIOUS:
.SUFFIXES: .c .h .S .s .o .adb .ads .ali

CFLAGS= $(CFLAGS_GLOBAL) \
        $(CFLAGS_ARCH) \
        -std=c18 \
        -Wall \
        -fno-builtin \
        -fvisibility=hidden \
        -nostdinc \
        -fstack-protector-all \
        -I"$(PROJECTDIR)/head" \
        -D__PROGNAME=\"$(PROG)\" \
        -I"."

ADAFLAGS= $(ADAFLAGS_GLOBAL) \
          -nostdlib \
          -I"$(PROJECTDIR)/head" \
          $(ADAFLAGS_ARCH)

LDFLAGS= $(LDFLAGS_GLOBAL) \
         $(LDFLAGS_ARCH) \
         -nostdlib \
         -Tarch/$(TARGET_ARCH)/loader.ld

PROG= kernimg
OBJS= main.o stdio.o panic.o dummy.o $(OBJS_ARCH)
LIBS= "$(PROJECTDIR)/lib/libfdt/libfdt.a" \
      "$(PROJECTDIR)/lib/libc/stdlib/strtoul.o" \
      "$(PROJECTDIR)/lib/libc/string/memcpy.o" \
      "$(PROJECTDIR)/lib/libc/string/memmove.o" \
      "$(PROJECTDIR)/lib/libc/string/memcmp.o" \
      "$(PROJECTDIR)/lib/libc/string/strncmp.o" \
      "$(PROJECTDIR)/lib/libc/string/memchr.o" \
      "$(PROJECTDIR)/lib/libc/string/strchr.o" \
      "$(PROJECTDIR)/lib/libc/string/strrchr.o" \
      "$(PROJECTDIR)/lib/libc/string/memset.o" \
      "$(PROJECTDIR)/lib/libc/string/strlen.o" \
      "$(PROJECTDIR)/lib/libc/string/strnlen.o" \
      "$(PROJECTDIR)/lib/libc/ctype/isspace.o" \
      "$(PROJECTDIR)/lib/libc/errno/errno.o" \
      "$(PROJECTDIR)/lib/libc/stdio/perror.o" \
      "$(PROJECTDIR)/lib/libada/libada.a"

ALIS= dummy.ali $(ALIS_ARCH)

all: $(PROG)

clean:
	-rm -r $(OBJS) $(PROG) $(ALIS) b_$(PROG).o b_$(PROG).ali b_$(PROG).adb \
	       b_$(PROG).ads

main.o: main.c
stdio.o: stdio.c
panic.o: panic.c
dummy.o: dummy.adb dummy.ads

include arch/$(TARGET_ARCH)/arch.mk

$(PROG): $(OBJS) arch/$(TARGET_ARCH)/loader.ld b_$(PROG).o
	$(LD) $(LDFLAGS) -o $(PROG) $(OBJS) $(LIBS) b_$(PROG).o

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.S.o:
	$(CC) $(CFLAGS) -c $< -o $@

.adb.o:
	$(GNAT) $(ADAFLAGS) -c $< -o $@

b_$(PROG).o: $(OBJS)
	$(GNATBIND) -I"$(PROJECTDIR)/head" \
	            -I"$(PROJECTDIR)/head/arch/$(TARGET_ARCH)" \
	            -I"$(PROJECTDIR)/lib/libada" \
	            -I"$(PROJECTDIR)/lib/libada/arch/$(TARGET_ARCH)" \
	            -n $(ALIS) -o $*.adb
	$(GNAT) $(ADAFLAGS) -c b_$(PROG).adb -o $@
