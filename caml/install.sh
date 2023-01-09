#!/bin/sh -ex

prefix=${1:-$PREFIX}
if [ "$prefix" = "" ]; then
    prefix=`opam var prefix`
fi

SYSROOT=${prefix}/esperanto-sysroot
mkdir -p ${SYSROOT}

# OCaml
MAKE=${MAKE:=make}
${MAKE} -C ocaml install

# findlib
mkdir -p ${prefix}/lib/findlib.conf.d
cp esperanto.conf ${prefix}/lib/findlib.conf.d/esperanto.conf

# dummy packages
mkdir -p ${SYSROOT}/lib/threads
cat >${SYSROOT}/lib/threads/META <<EOF
version = "[distributed with Ocaml]"
description = "Multi-threading"
requires(mt,mt_vm) = "threads.vm"
requires(mt,mt_posix) = "threads.posix"
directory = "^"
type_of_threads = "posix"

browse_interfaces = ""

warning(-mt) = "Linking problems may arise because of the missing -thread or -vmthread switch"
warning(-mt_vm,-mt_posix) = "Linking problems may arise because of the missing -thread or -vmthread switch"

package "vm" (
  # --- Bytecode-only threads:
  requires = "unix"
  directory = "+vmthreads"
  exists_if = "threads.cma"
  archive(byte,mt,mt_vm) = "threads.cma"
  version = "[internal]"
)

package "posix" (
  # --- POSIX-threads:
  requires = "unix"
  directory = "+threads"
  exists_if = "threads.cma"
  archive(byte,mt,mt_posix) = "threads.cma"
  archive(native,mt,mt_posix) = "threads.cmxa"
  version = "[internal]"
)

package "none" (
  error = "threading is not supported on this platform"
  version = "[internal]"
)
EOF
mkdir -p ${SYSROOT}/lib/is_esperanto
touch ${SYSROOT}/lib/is_esperanto/META
