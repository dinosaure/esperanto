#!/bin/sh

prog_NAME="$(basename $0)"

err()
{
    echo "${prog_NAME}: ERROR: $@" 1>&2
}

die()
{
    echo "${prog_NAME}: ERROR: $@" 1>&2
    exit 1
}

usage()
{
    cat <<EOM 1>&2
usage: ${prog_NAME} [ OPTIONS ]
Configures the ocaml-esperanto build system.
Options:
    --prefix=DIR:
        Installation prefix (default: /usr/local).
    --target=TARGET
        Cosmopolitan compiler toolchain to use.
    --ocaml-configure-option=OPTION
        Add an option to the OCaml compiler configuration.
EOM
    exit 1
}

OCAML_CONFIGURE_OPTIONS=
OCAML_VERSION=$(ocamlopt -version)
MAKECONF_PREFIX="/usr/local"
CC=cc

while [ $# -gt 0 ]; do
    OPT="$1"

    case "${OPT}" in
        --target=*)
            CONFIG_TARGET="${OPT##*=}"
            ;;
        --ocaml-configure-option=*)
            OCAML_CONFIGURE_OPTIONS="${OCAML_CONFIGURE_OPTIONS} ${OPT##*=}"
            ;;
        --prefix=*)
            MAKECONF_PREFIX="${OPT##*=}"
            ;;
        --help)
            usage
            ;;
        *)
            err "Unknown option: '${OPT}'"
            usage
            ;;
    esac

    shift
done

[ -z "${CONFIG_TARGET}" ] && die "The --target option needs to be specified."

MAKECONF_CFLAGS=
MAKECONF_CC="$CONFIG_TARGET-cc"
MAKECONF_LD="$CONFIG_TARGET-ld"
MAKECONF_AS="$MAKECONF_CC -c"

BUILD_TRIPLET="$($MAKECONF_CC -dumpmachine)"
OCAML_BUILD_ARCH=

case "${BUILD_TRIPLET}" in
    amd64-*|x86_64-*)
        BUILD_ARCH="x86_64"
        OCAML_BUILD_ARCH="amd64"
        ;;
    aarch64-*)
        BUILD_ARCH="aarch64"
        OCAML_BUILD_ARCH="arm64"
        ;;
    *)
        die "Unsupported target architecture: ${BUILD_TRIPLET}"
        ;;
esac

TRIPLET="$($CC -dumpmachine)"
ARCH=

case "${TRIPLET}" in
    amd64-*|x86_64-*)
        ARCH="x86_64"
        ;;
    aarch64-*)
        die "The Cosmoplitan distribution works only on x86_64 architecture"
        ;;
    *)
        die "Unsupported host architecture: ${TRIPLET}"
        ;;
esac

# cosmocross takes care about extra libs (despite ocaml-solo5/solo5)
EXTRA_LIBS=

cat <<EOM >Makeconf
MAKECONF_PREFIX=${MAKECONF_PREFIX}
MAKECONF_CFLAGS=${MAKECONF_CFLAGS}
MAKECONF_CC=${MAKECONF_CC}
MAKECONF_LD=${MAKECONF_LD}
MAKECONF_AS=${MAKECONF_AS}
MAKECONF_ARCH=${ARCH}
MAKECONF_BUILD_ARCH=${BUILD_ARCH}
MAKECONF_OCAML_BUILD_ARCH=${OCAML_BUILD_ARCH}
MAKECONF_OCAML_CONFIGURE_OPTIONS=${OCAML_CONFIGURE_OPTIONS}
MAKECONF_OCAML_VERSION=${OCAML_VERSION}
MAKECONF_EXTRA_LIBS=${EXTRA_LIBS}
EOM
