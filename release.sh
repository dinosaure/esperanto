#!/bin/sh

GIT_VERSION=$(git -C . describe --dirty --tags --always)
GIT_OLDBRANCH=$(git rev-parse --abbrev-ref HEAD)

git checkout -b distrib/${GIT_VERSION}
git commit --allow-empty -m "Release tarball for ${GIT_VERSION}"
git archive --format=tar.gz --prefix=esperanto-${GIT_VERSION}/ distrib/${GIT_VERSION} >esperanto-${GIT_VERSION}.tar.gz
git checkout ${GIT_OLDBRANCH}
git branch -D distrib/${GIT_VERSION}

# (c) Martin Lucina
# This script is used to generate OPAM metadata for publishing a Solo5 release
# to ocaml/opam-repository. It should be run from the root of a clean, tagged
# Solo5 git repository.

if [ ! -d "./opam" ]; then
    echo "ERROR: missing ./opam. Run this from the root of a Esperanto repository."
    exit 1
fi

DEV=
if ! echo "$GIT_VERSION" | egrep -q '^v[0-9]+.[0-9]+.[0-9]+$'; then
    echo "WARNING: Not a clean Git release: $GIT_VERSION"
    echo "WARNING: This is almost certainly not what you want."
    DEV=~dev
fi

TARBALL="esperanto-${GIT_VERSION}.tar.gz"
if [ ! -f ${TARBALL} ]; then
    echo "ERROR: Release tarball ${TARBALL} not found."
    echo "ERROR: Did you run 'make distrib'?"
    exit 1
fi
echo "Using tarball: ${TARBALL}"
CHECKSUM="$(sha512sum ${TARBALL} | cut -d' ' -f1)"

OPAM_VERSION=$(echo -n "${GIT_VERSION}" | cut -d- -f1 | tr -d v)
[ -n "${DEV}" ] && OPAM_VERSION="${OPAM_VERSION}${DEV}"
echo "OPAM version: ${OPAM_VERSION}"

OUTPUT_DIR=./opam/release
if [ -d ${OUTPUT_DIR} ]; then
    echo "Deleting existing output directory: ${OUTPUT_DIR}"
    rm -rf ${OUTPUT_DIR}
fi
mkdir -p ${OUTPUT_DIR}/tmp
cat <<EOM >${OUTPUT_DIR}/tmp/url
url {
  src: "https://github.com/dinosaure/esperanto/releases/download/${GIT_VERSION}/${TARBALL}"
  checksum: "sha512=${CHECKSUM}"
}
EOM

for PACKAGE in 'esperanto-cosmopolitan' 'x86_64-esperanto' 'aarch64-esperanto'; do
    PKG_DIR=${OUTPUT_DIR}/packages/${PACKAGE}/${PACKAGE}.${OPAM_VERSION}
    mkdir -p ${PKG_DIR} || exit 1
    cat opam/${PACKAGE}.opam ${OUTPUT_DIR}/tmp/url \
        > ${PKG_DIR}/opam || exit 1
    opam lint ${PKG_DIR}/opam || exit 1
done

echo "Done. Submit ${OUTPUT_DIR}/packages as a PR to opam-repository."
echo "Example: cp -r opam/release/packages path/to/opam-repository"
echo "         cd path/to/opam/repository"
echo "         git checkout -b esperanto.${OPAM_VERSION}"
echo "         git add ."
