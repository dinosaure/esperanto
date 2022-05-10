# Copyright (c) 2015-2021 Contributors as noted in the AUTHORS file
#
# This file is part of Esperanto, a build-once run-anywhere toolchain
#
# Permission to use, copy, modify, and/or distribute this software
# for any purpose with or without fee is hereby granted, provided
# that the above copyright notice and this permission notice appear
# in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
# WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
# AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
# CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
# OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
# NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
# CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

export TOPDIR := $(abspath .)

$(TOPDIR)/Makeconf:
	$(error Makeconf not found, please run ./configure.sh)

ifndef TOPDIR
$(error TOPDIR must be set, run $(MAKE) from the top of the source tree or set it manually)
endif
include $(TOPDIR)/Makefile.common

.PHONY: all
all:
all_TARGETS := bin/$(CONFIG_TARGET_TRIPLE)-cc \
    bin/$(CONFIG_TARGET_TRIPLE)-ld \
    bin/$(CONFIG_TARGET_TRIPLE)-objcopy \
    lib/cosmopolitan \
    include/cosmopolitan/cosmopolitan.h

SHELL     := /bin/sh
cosmopolitan_OBJECTS := $(shell ./extract.com list)
HEADER    := $(filter %.h,$(cosmopolitan_OBJECTS))
ARCHIVE   := $(filter %.a,$(cosmopolitan_OBJECTS))
OBJECTS   := $(filter %.o,$(cosmopolitan_OBJECTS)) 
LINK      := $(filter %.lds,$(cosmopolitan_OBJECTS)) 

.SUFFIXES:
$(V).SILENT:

bin:
	mkdir -p $@

bin/$(CONFIG_TARGET_TRIPLE)-%: %.in | bin
	@echo "SUBST $@"
	@sed -e 's!@@CONFIG_TARGET_ARCH@@!$(CONFIG_TARGET_ARCH)!g' \
	    -e 's!@@CONFIG_TARGET_TRIPLE@@!$(CONFIG_TARGET_TRIPLE)!g' \
	    -e 's!@@CONFIG_TARGET_CC@@!$(CONFIG_TARGET_CC)!g' \
	    -e 's!@@CONFIG_TARGET_CC_CFLAGS@@!$(CONFIG_TARGET_CC_CFLAGS)!g' \
	    -e 's!@@CONFIG_TARGET_CC_LDFLAGS@@!$(CONFIG_TARGET_CC_LDFLAGS)!g' \
	    -e 's!@@CONFIG_TARGET_LD@@!$(CONFIG_TARGET_LD)!g' \
	    -e 's!@@CONFIG_TARGET_LD_LDFLAGS@@!$(CONFIG_TARGET_LD_LDFLAGS)!g' \
	    -e 's!@@CONFIG_TARGET_LD_MAX_PAGE_SIZE@@!$(CONFIG_TARGET_LD_MAX_PAGE_SIZE)!g' \
	    -e 's!@@CONFIG_TARGET_OBJCOPY@@!$(CONFIG_TARGET_OBJCOPY)!g' \
	    $< >$@
	@chmod +x $@

include/cosmopolitan/cosmopolitan.h: $(HEADER)
	@echo "GEN $@"
	@cp $< $@
	@echo "PATCH $@"
	@echo '' >> $@
	@echo '#include "esperanto.h"' >> $@

%.o: %.c include/cosmopolitan/cosmopolitan.h
	$(HOSTCOMPILE.c)

lib/cosmopolitan: $(ARCHIVE) $(LINK) $(OBJECTS) startup.o
	@echo "GEN $@"
	@mkdir -p $@
	@cp $^ $@

$(cosmopolitan_OBJECTS): cosmopolitan.zip extract.com
	@echo "UNZIP $< for $@"
	@$(shell ./extract.com $< dst)

all: $(all_TARGETS)

DESTDIR ?=
PREFIX := $(CONFIG_PREFIX)
DESTINATION := $(DESTDIR)$(PREFIX)
TOOLCHAIN_LIBDIR := $(DESTINATION)/lib/$(CONFIG_TARGET_TRIPLE)
TOOLCHAIN_INCDIR := $(DESTINATION)/include/$(CONFIG_TARGET_TRIPLE)
TOOLCHAIN_SYSDIR := $(DESTINATION)/include/$(CONFIG_TARGET_TRIPLE)/sys
INSTALL := install -p

.PHONY: install
install: all
	@echo "INSTALL toolchain"
	@mkdir -p $(DESTINATION)/bin
	$(INSTALL) -m 0755 bin/$(CONFIG_TARGET_TRIPLE)-cc $(DESTINATION)/bin
	$(INSTALL) -m 0755 bin/$(CONFIG_TARGET_TRIPLE)-ld $(DESTINATION)/bin
	$(INSTALL) -m 0755 bin/$(CONFIG_TARGET_TRIPLE)-objcopy $(DESTINATION)/bin
	@mkdir -p $(TOOLCHAIN_LIBDIR) $(TOOLCHAIN_INCDIR) $(TOOLCHAIN_SYSDIR)
	cd lib/cosmopolitan && \
		find . -type f -exec $(INSTALL) -m 0644 \
		"{}" "$(TOOLCHAIN_LIBDIR)/{}" \;
	cd include/cosmopolitan && \
		find . -type f -exec $(INSTALL) -m 0644 "{}" \
		"$(TOOLCHAIN_INCDIR)/{}" \;
	cd include/cosmopolitan/sys && \
		find . -type f -exec $(INSTALL) -m 0644 "{}" \
		"$(TOOLCHAIN_SYSDIR)/{}" \;

.PHONY: clean
clean:
	@echo "CLEAN toolchain"
	$(RM) -r dst/ bin/ lib/
	$(RM) include/cosmopolitan/cosmopolitan.h
	$(RM) startup.o startup.d

.PHONY: distclean
distclean: clean
	@echo "DISTCLEAN toolchain"
	$(RM) Makeconf
	$(RM) Makeconf.sh
