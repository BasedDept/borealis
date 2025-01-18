# prog_boot.mk
# Boot program targets
# Author: George Witt
# Date: 2024-09-07
#
# Copyright (c) 2024 George Witt
# SPDX-License-Identifier: BSD-2-Clause

$(PROG): $(OBJS) $(LDS) $(GNATBIND_OBJ)
	@echo "[LD]       $@"
	@$(LD) -nostdlib -L$(PROJECTDIR)/lib/libc -L$(PROJECTDIR)/lib/libm -T$(LDS) $(LDFLAGS) -o $(PROG) $(OBJS) $(LIBS) $(GNATBIND_OBJ)


clean:
	@echo "[CLEAN]    $(PROG)"
	-@rm -r $(PROG) $(OBJS) $(GNATBIND_OBJ) $(ALIS) $(GNATBIND_OBJ:%.o=%.ali) $(GNATBIND_OBJ:%.o=%.adb) $(GNATBIND_OBJ:%.o=%.ads) || true
