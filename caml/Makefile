include Makeconf

# The `all` target is moved to the end to use variables in its dependencies
.PHONY: default
default: all

TOP=$(abspath .)

_build:
	mkdir -p $@

# TOOLCHAIN
# We create prefix-gcc even when the actual compiler will be Clang because
# autoconf toolchain detection will pick the first compiler that exists in the
# list: prefix-gcc, gcc, prefix-cc, cc...
# Anyway, configure scripts always explicitly test whether the compiler defines
# Clang-specific macros when they want to distinguish GCC and Clang
ALLTOOLS := gcc cc ar as ld nm objcopy objdump ranlib readelf strip
ALLTOOLS := $(foreach tool,$(ALLTOOLS), \
                $(MAKECONF_TARGET_ARCH)-esperanto-ocaml-$(tool))

TOOLDIR_FOR_BUILD := _build/build-toolchain
TOOLCHAIN_FOR_BUILD := $(addprefix $(TOOLDIR_FOR_BUILD)/,$(ALLTOOLS))
TOOLDIR_FINAL := _build/toolchain
TOOLCHAIN_FINAL := $(addprefix $(TOOLDIR_FINAL)/,$(ALLTOOLS))

# Options for the build version of the tools
TOOLCHAIN_BUILD_CFLAGS :=
TOOLCHAIN_BUILD_LDFLAGS :=

# Options for the installed version of the tools
TOOLCHAIN_FINAL_CFLAGS := -I$(MAKECONF_SYSROOT)/include
TOOLCHAIN_FINAL_LDFLAGS := -L$(MAKECONF_SYSROOT)/lib

$(TOOLDIR_FOR_BUILD) $(TOOLDIR_FINAL):
	mkdir -p $@

$(TOOLDIR_FOR_BUILD)/$(MAKECONF_TARGET_ARCH)-esperanto-ocaml-%: \
    gen_toolchain_tool.sh | $(TOOLDIR_FOR_BUILD)
	ARCH="$(MAKECONF_TARGET_ARCH)" \
	  COSMOPOLITAN_TOOLCHAIN="$(MAKECONF_TOOLCHAIN)" \
	  OTHERTOOLPREFIX="$(MAKECONF_TOOLPREFIX)" \
	  TOOL_CFLAGS="$(TOOLCHAIN_BUILD_CFLAGS)" \
	  TOOL_LDFLAGS="$(TOOLCHAIN_BUILD_LDFLAGS)" \
	  sh $< $* > $@
	chmod +x $@

$(TOOLDIR_FINAL)/$(MAKECONF_TARGET_ARCH)-esperanto-ocaml-%: \
    gen_toolchain_tool.sh | $(TOOLDIR_FINAL)
	ARCH="$(MAKECONF_TARGET_ARCH)" \
	  COSMOPOLITAN_TOOLCHAIN="$(MAKECONF_TOOLCHAIN)" \
	  OTHERTOOLPREFIX="$(MAKECONF_TOOLPREFIX)" \
	  TOOL_CFLAGS="$(TOOLCHAIN_FINAL_CFLAGS)" \
	  TOOL_LDFLAGS="$(TOOLCHAIN_FINAL_LDFLAGS)" \
	  sh $< $* > $@
	chmod +x $@

.PHONY: toolchains
toolchains: $(TOOLCHAIN_FOR_BUILD) $(TOOLCHAIN_FINAL)

# OCAML
# Extract sources from the ocaml-src package and apply patches if there any in
# `patches/<OCaml version>/`
ocaml:
# First make sure the ocaml directory doesn't exist, otherwise the cp would
# create an ocaml-src subdirectory
	test ! -d $@
	cp -r "$$(ocamlfind query ocaml-src)" $@
	VERSION="$$(head -n1 ocaml/VERSION)" ; \
	if test -d "patches/$$VERSION" ; then \
	  git apply --directory=$@ "patches/$$VERSION"/*; \
	fi

ocaml/Makefile.config: $(LIBS) $(TOOLCHAIN_FOR_BUILD) | ocaml
	PATH="$$PWD/$(TOOLDIR_FOR_BUILD):$$PATH" ; \
	cd ocaml && \
	  ./configure \
		--target="$(MAKECONF_TARGET_ARCH)-esperanto-ocaml" \
		--prefix="$(MAKECONF_SYSROOT)" \
		--disable-shared \
		--disable-systhreads \
		--disable-instrumented-runtime \
		--disable-debug-runtime \
		--disable-ocamltest \
		--disable-ocamldoc \
		--without-zstd \
		$(MAKECONF_OCAML_CONFIGURE_OPTIONS)

OCAML_IS_BUILT := _build/ocaml_is_built
$(OCAML_IS_BUILT): ocaml/Makefile.config | _build
	PATH="$$PWD/$(TOOLDIR_FOR_BUILD):$$PATH" \
	  $(MAKE) -C ocaml crossopt OLDS="-o yacc/ocamlyacc -o lex/ocamllex"
	touch $@

# CONFIGURATION FILES
_build/esperanto.conf: gen_esperanto_conf.sh $(OCAML_IS_BUILT)
	PREFIX="$(MAKECONF_PREFIX)" ARCH="$(MAKECONF_TARGET_ARCH)" SYSROOT="$(MAKECONF_SYSROOT)" ./gen_esperanto_conf.sh > $@

_build/empty-META: | _build
	touch $@

# INSTALL
PACKAGES := $(basename $(wildcard *.opam))
INSTALL_FILES := $(foreach pkg,$(PACKAGES),$(pkg).install)

$(INSTALL_FILES): $(TOOLCHAIN_FINAL)
	./gen_dot_install.sh $(TOOLCHAIN_FINAL) > $@

# COMMANDS
.PHONY: install-ocaml
install-ocaml:
	ln -sf "$$(command -v ocamllex)" ocaml/lex/ocamllex
	ln -sf "$$(command -v ocamlyacc)" ocaml/yacc/ocamlyacc
	$(MAKE) -C ocaml installcross

PACKAGE := esperanto
.PHONY: install
install: $(PACKAGE).install install-ocaml
	opam-installer --prefix=$(MAKECONF_PREFIX) $<

.PHONY: clean
clean:
	$(RM) -rf _build
	if [ -d ocaml ] ; then $(MAKE) -C ocaml clean ; fi
	$(RM) -f $(INSTALL_FILES)

.PHONY: distclean
distclean: clean
	$(RM) -f Makeconf
# Don't remove the ocaml directory itself, to play nicer with
# development in there
	if [ -d ocaml ] ; then $(MAKE) -C ocaml distclean ; fi

.PHONY: all
all: $(LIBS) $(OCAML_IS_BUILT) \
     _build/esperanto.conf _build/empty-META \
     $(TOOLCHAIN_FINAL)

.PHONY: test
test:
	$(MAKE) -C nolibc test-headers \
	    "CC=$(MAKECONF_TOOLCHAIN)-cc" \
	    "FREESTANDING_CFLAGS=$(NOLIBC_CFLAGS)"
