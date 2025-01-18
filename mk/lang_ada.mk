# lang_ada.mk
# Ada language support
# Author: George Witt
# Date: 2024-09-07
#
# Copyright (c) 2024 George Witt
# SPDX-License-Identifier: BSD-2-Clause

.SUFFIXES: .adb .ads .ali .o

.adb.o:
	@echo "[GNAT]     $@"
	@$(GNAT) -nostdlib -I$(PROJECTDIR)/head $(ADAFLAGS) -c $< -o $@

.ads.o:
	@echo "[GNAT]     $@"
	@$(GNAT) $(ADAFLAGS) -ffunction-sections -fdata-sections \
	                    -gnatg -Wl,--gc-sections -c $< -o $@

$(GNATBIND_OBJ): $(OBJS)
	@echo "[GNATBIND] $*.adb"
	@$(GNATBIND) -I"$(PROJECTDIR)/head" \
	            -I"$(PROJECTDIR)/head/arch/$(TARGET_ARCH)" \
	            -I"$(PROJECTDIR)/lib/libada" \
	            -I"$(PROJECTDIR)/lib/libada/arch/$(TARGET_ARCH)" \
	            -n "$(PROJECTDIR)/lib/libada/libada.ali" $(ALIS) -o $*.adb
	@echo "[GNAT]     $@"
	@$(GNAT) -nostdlib -I$(PROJECTDIR)/head $(ADAFLAGS) -c $*.adb -o $@

