.PHONY: all clean install uninstall distclean ocaml

include Makeconf

all: ocaml esperanto.conf

TOP=$(abspath .)

# CFLAGS used to build ocaml runtime
LOCAL_CFLAGS=$(MAKECONF_CFLAGS)
# CFLAGS used by the OCaml compiler to build C stubs
GLOBAL_CFLAGS=""
# LIBS used by the OCaml compiler to link executables
GLOBAL_LIBS=$(MAKECONF_EXTRA_LIBS)

# OCAML
ocaml/Makefile:
	cp -r `opam var prefix`/lib/ocaml-src ./ocaml

# OCaml >= 4.08.0 uses an autotools-based build system. In this case we
# convince it to think it's using the Solo5 compiler as a cross compiler, and
# let the build system do its work with as little additional changes on our
# side as possible.
#
# Notes:
#
# - CPPFLAGS must be set for configure as well as CC, otherwise it complains
#   about headers due to differences of opinion between the preprocessor and
#   compiler.
# - ARCH must be overridden manually in Makefile.config due to the use of
#   hardcoded combinations in the OCaml configure.
# - We use LIBS with a stubbed out solo5 implementation to override the OCaml
# 	configure link test
# - We override OCAML_OS_TYPE since configure just hardcodes it to "Unix".
# - We must tweak runtime/sys.c and runtime/signals.c to correctly set internal
#   arrays to right **dynamic** values
OC_CFLAGS=$(LOCAL_CFLAGS)
OC_LIBS=-nostdlib $(MAKECONF_EXTRA_LIBS)
ocaml/Makefile.config: ocaml/Makefile esperanto_sys.c
# configure: Do not build dynlink
	sed -i -e 's/otherlibraries="dynlink"/otherlibraries=""/g' ocaml/configure
# configure: Allow precise input of flags and libs
	sed -i -e 's/oc_cflags="/oc_cflags="-z caml-startup $$OC_CFLAGS /g' ocaml/configure
	sed -i -e 's/ocamlc_cflags="/ocamlc_cflags="$$OCAMLC_CFLAGS /g' ocaml/configure
	sed -i -e 's/nativecclibs="$$cclibs $$DLLIBS"/nativecclibs="$$GLOBAL_LIBS"/g' ocaml/configure
# runtime/Makefile: Runtime rules: don't build libcamlrun.a and import ocamlrun from the system
	sed -i -e 's/^all: $$(BYTECODE_STATIC_LIBRARIES) $$(BYTECODE_SHARED_LIBRARIES)/all: primitives ld.conf/' ocaml/runtime/Makefile
	sed -i -e 's/^ocamlrun$$(EXE):.*/dummy:/g' ocaml/runtime/Makefile
	sed -i -e 's/^ocamlruni$$(EXE):.*/dummyi:/g' ocaml/runtime/Makefile
	sed -i -e 's/^ocamlrund$$(EXE):.*/dummyd:/g' ocaml/runtime/Makefile
# extern.c defines a static write function which is in conflict with Cosmopolitan [write] function
	sed -i -e 's/write(/_write(/' ocaml/runtime/extern.c
# roots_nats.c defines a link structure which is in conflict with Cosmopolitan [link] function
	sed -i -e 's/\([^_]\)link/\1link_t/g' ocaml/runtime/roots_nat.c
# externalize some functions needed by our [startup.o] into [sys.c] and [signals.c]
	cat esperanto_sys.c >> ocaml/runtime/sys.c
	cat esperanto_signals.c >> ocaml/runtime/signals.c
	cat esperanto_permission.c >> ocaml/otherlibs/unix/access.c
	cat esperanto_open.c >> ocaml/otherlibs/unix/open.c
	cat esperanto_socket.c >> ocaml/otherlibs/unix/socket.c
	cat esperanto_sockopt.c >> ocaml/otherlibs/unix/sockopt.c
	cat esperanto_unixsupport.c >> ocaml/otherlibs/unix/unixsupport.c
	cat esperanto_wait.c >> ocaml/otherlibs/unix/wait.c
	cat esperanto_unix_signals.c >> ocaml/otherlibs/unix/signals.c
	cat esperanto_systhreads_signals.c >> ocaml/otherlibs/systhreads/st_posix.h
	cat esperanto_termios.c >> ocaml/otherlibs/unix/termios.c
	patch ocaml/otherlibs/unix/gethost.c esperanto_gethost.patch
	patch ocaml/otherlibs/unix/socketaddr.c esperanto_socketaddr.$(MAKECONF_OCAML_VERSION).patch
# We must comment [alloc], [callback] and [flush] which are `#define` by Cosmopolitan
	sed -i -e '/ alloc /s/^/\/\//' ocaml/runtime/caml/compatibility.h
	sed -i -e '/ callback /s/^/\/\//' ocaml/runtime/caml/compatibility.h
	sed -i -e '/ flush /s/^/\/\//' ocaml/runtime/caml/compatibility.h
	sed -i -e '/pthread_mutexattr_settype/s/^/\/\//' ocaml/otherlibs/systhreads/st_posix.h
	echo -e "ocamlrun:\n\tcp $(shell which ocamlrun) .\n" >> ocaml/runtime/Makefile
	echo -e "ocamlrund:\n\tcp $(shell which ocamlrund) .\n" >> ocaml/runtime/Makefile
	echo -e "ocamlruni:\n\tcp $(shell which ocamlruni) .\n" >> ocaml/runtime/Makefile
	touch ocaml/runtime/libcamlrun.a ocaml/runtime/libcamlrund.a ocaml/runtime/libcamlruni.a
# Comment a CAML_STATIC_ASSERT which emits warnings ("variably modified 'static_assertion_failure_line_XX'")
	@if [ "$(MAKECONF_OCAML_VERSION)" = "4.14.0" ] ; then \
	  sed -i -e "56,58 s/^/\/\//" ocaml/runtime/caml/domain_state.h; \
	else \
	  sed -i -e "48,50 s/^/\/\//" ocaml/runtime/caml/domain_state.h; \
	fi
# yacc/Makefile: import ocamlyacc from the system
	sed -i -e 's/^ocamlyacc$$(EXE):.*/dummy:/g' ocaml/yacc/Makefile
	echo -e "ocamlyacc:\n\tcp $(shell which ocamlyacc) .\n" >> ocaml/yacc/Makefile
# tools/Makefile: stub out objinfo_helper
	echo -e "objinfo_helper:\n\ttouch objinfo_helper\n" >> ocaml/tools/Makefile
# av_cv_libm_cos=no is passed to configure to prevent -lm being used (which
# would use the host system libm instead of the freestanding openlibm, see
# https://github.com/mirage/ocaml-solo5/issues/101
	cd ocaml && \
		CC="$(MAKECONF_CC)" \
		OC_CFLAGS="$(OC_CFLAGS)" \
		OCAMLC_CFLAGS="$(GLOBAL_CFLAGS)" \
		AS="$(MAKECONF_AS)" \
		ASPP="$(MAKECONF_CC) $(OC_CFLAGS) -c" \
		CPPFLAGS="$(OC_CFLAGS)" \
		LIBS="$(OC_LIBS)"\
		GLOBAL_LIBS="$(GLOBAL_LIBS)" \
		LD="$(MAKECONF_LD)" \
		ac_cv_prog_DIRECT_LD="$(MAKECONF_LD)" \
		ac_cv_lib_m_cos="no" \
	  ./configure \
		-host=$(MAKECONF_BUILD_ARCH)-unknown-none \
		-prefix $(MAKECONF_PREFIX)/esperanto-sysroot \
		-disable-shared\
		-disable-instrumented-runtime\
		-disable-ocamltest\
		-disable-ocamldoc\
		-disable-debugger\
		$(MAKECONF_OCAML_CONFIGURE_OPTIONS)
	echo "ARCH=$(MAKECONF_OCAML_BUILD_ARCH)" >> ocaml/Makefile.config
	echo 'SAK_CC=cc' >> ocaml/Makefile.config
	echo 'SAK_CFLAGS=' >> ocaml/Makefile.config
	echo 'SAK_LINK=cc $(SAK_CFLAGS) $$(OUTPUTEXE)$$(1) $$(2)' >> ocaml/Makefile.config
	echo '#undef OCAML_OS_TYPE' >> ocaml/runtime/caml/s.h
	echo '#define OCAML_OS_TYPE "None"' >> ocaml/runtime/caml/s.h

# NOTE: ocaml/tools/make-version-header.sh is integrated into OCaml's ./configure script starting from OCaml 4.14
ifneq (,$(wildcard ocaml/tools/make-version-header.sh))
ocaml/runtime/caml/version.h: ocaml/Makefile.config
	ocaml/tools/make-version-header.sh > $@
else
ocaml/runtime/caml/version.h: ocaml/Makefile.config
	@
endif

ocaml: ocaml/Makefile.config ocaml/runtime/caml/version.h
	$(MAKE) -C ocaml world
	$(MAKE) -C ocaml opt

# CONFIGURATION FILES
esperanto.conf: esperanto.conf.in
	sed -e 's!@@PREFIX@@!$(MAKECONF_PREFIX)!' \
	    esperanto.conf.in > $@

# COMMANDS
install: all
	MAKE=$(MAKE) PREFIX=$(MAKECONF_PREFIX) ./install.sh

uninstall:
	./uninstall.sh

clean:
	$(RM) -r ocaml/
	$(RM) esperanto.conf
	$(RM) -r cosmopolitan

distclean: clean
	rm Makeconf
