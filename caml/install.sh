#!/bin/sh -ex

die()
{
    echo "${prog_NAME}: ERROR: $@" 1>&2
    exit 1
}

prefix=${1:-$PREFIX}
build_arch=${2:-$BUILD_ARCH}
if [ "$prefix" = "" ]; then
    prefix=`opam var prefix`
fi
[ -z "${build_arch}" ] && die "The build architecture is required."

SYSROOT=${prefix}/${build_arch}-esperanto-sysroot
mkdir -p ${SYSROOT}

# OCaml
MAKE=${MAKE:=make}
${MAKE} -C ocaml install

# findlib
mkdir -p ${prefix}/lib/findlib.conf.d
cp ${build_arch}-esperanto.conf ${prefix}/lib/findlib.conf.d/${build_arch}-esperanto.conf
mkdir -p ${SYSROOT}/lib/threads
cp META ${SYSROOT}/lib/threads
