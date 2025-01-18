# lib.mk
# Library targets
# Author: George Witt
# Date: 2024-09-07
#
# Copyright (c) 2024 George Witt
# SPDX-License-Identifier: BSD-2-Clause

$(LIBA): $(OBJS)
	@echo "[AR]       $@"
	@$(AR) -c -r -s $(LIBA) $(OBJS)

$(LIBSO): $(OBJS) $(GNATBIND_OBJ)
	@echo "[LD]       $@"
	@$(LD) -nostdlib -L$(PROJECTDIR)/lib $(LDFLAGS) -shared -o $(LIBSO) $(OBJS) $(LIBS) $(GNATBIND_OBJ)


clean:
	@echo "[CLEAN]    $(LIBA:%.a=%)"
	-@rm -r $(LIBA) $(LIBSO) $(OBJS) $(GNATBIND_OBJ) $(ALIS) $(GNATBIND_OBJ:%.o=%.ali) $(GNATBIND_OBJ:%.o=%.adb) $(GNATBIND_OBJ:%.o=%.ads) || true
