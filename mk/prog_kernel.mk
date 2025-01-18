# c.mk
# C build system
# Author: George Witt
# Date: 2024-09-07
#
# Copyright (c) 2024 George Witt
# SPDX-License-Identifier: BSD-2-Clause

.PRECIOUS:
.SUFFIXES: .c .h .S .s .o .adb .ads .ali

none:

clean:
	-rm -r $(OBJS) $(PROG) $(ALIS) b_$(PROG).o b_$(PROG).ali b_$(PROG).adb \
	       b_$(PROG).ads

$(PROG): $(OBJS) $(DEPS) b_$(PROG).o
	$(LD) -nostdlib -L$(PROJECTDIR)/lib $(LDFLAGS) -o $(PROG) $(OBJS) $(LIBS) b_$(PROG).o

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
	            -n "$(PROJECTDIR)/lib/libada/libada.ali" $(ALIS) -o $*.adb
	$(GNAT) $(ADAFLAGS) -c b_$(PROG).adb -o $@

