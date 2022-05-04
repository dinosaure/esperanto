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
touch ${SYSROOT}/lib/threads/META # for ocamlfind
mkdir -p ${SYSROOT}/lib/is_esperanto
touch ${SYSROOT}/lib/is_esperanto/META
