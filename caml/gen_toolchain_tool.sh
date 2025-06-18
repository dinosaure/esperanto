#!/bin/sh

# Generate a wrapper for Cosmopolitan (G)CC, ld, objcopy and any other binutil
# Expected argument: the tool to generate
# Expected environment variables:
#   ARCH: the target architecture (x86_64 or aarch64)
#   TOOL_CFLAGS and TOOL_LDFLAGS: extra flags
#   COSMOPOLITAN_TOOLCHAIN: the target for the wrapped Cosmopolitan toolchain
#   OTHERTOOLPREFIX: the prefix for tools not in the Cosmopolitan toolchain
#   TARGET_X: overrides the command for binutil X

gen_cc() {
  # Note that -nostdlib is not required, as it is injected by Cosmopolitan' cc, ld

  CFLAGS="$TOOL_CFLAGS"
  LDFLAGS="$TOOL_LDFLAGS"
  EXTRALIBS=""

  # We only use GCC on our Esperanto toolchain
  # case "$ARCH" in
  #   aarch64)
  #     EXTRALIBS="-lgcc"
  #     ;;
  # esac

  # # Add the -Wno-unused-command-line-argument option for clang, as we always
  # # give it compiling options, even if it will be only linking
  # # Reuse the test from Solo5 to detect clang
  # if "$COSMOPOLITAN_TOOLCHAIN-cc" -dM -E - </dev/null | grep -Eq '^#define __clang__ 1$'
  # then CFLAGS="-Wno-unused-command-line-argument $CFLAGS"
  # fi

  cat << EOF
#!/bin/sh

# Just like the Cosmopolitan cc, we assume that we are linking, unless we find an
# argument suggesting we are compiling but we call Cosmopolitan' cc regardless

compiling=
for arg in "\$@"; do
  case "\$arg" in
    -[cSE])
      compiling="\$arg"
      break
      ;;
  esac
done

set -- \\
  $CFLAGS \\
  "\$@"

if [ -z "\$compiling" ]; then
  # linking options
  set -- \\
    "\$@" \\
    $LDFLAGS \\
    -Wl,--start-group \\
    $EXTRALIBS \\
    -Wl,--end-group
fi

[ -n "\${__V}" ] && set -x
exec "$COSMOPOLITAN_TOOLCHAIN-cc" "\$@"
EOF
}

gen_tool() {
  TOOL="$1"
  case "$TOOL" in
    ar)
      TARGET_TOOL="$TARGET_AR"
      ;;
    as)
      TARGET_TOOL="$TARGET_AS"
      ;;
    ld)
      TARGET_TOOL="$TARGET_LD"
      ;;
    nm)
      TARGET_TOOL="$TARGET_NM"
      ;;
    objcopy)
      TARGET_TOOL="$TARGET_OBJCOPY"
      ;;
    objdump)
      TARGET_TOOL="$TARGET_OBJDUMP"
      ;;
    ranlib)
      TARGET_TOOL="$TARGET_RANLIB"
      ;;
    readelf)
      TARGET_TOOL="$TARGET_READELF"
      ;;
    strip)
      TARGET_TOOL="$TARGET_STRIP"
      ;;
  esac
  if test "$TARGET_TOOL" ; then
    TOOL="$TARGET_TOOL"
  elif command -v -- "$COSMOPOLITAN_TOOLCHAIN-$TOOL" > /dev/null; then
    TOOL="$COSMOPOLITAN_TOOLCHAIN-$TOOL"
  else
    case "$TOOL" in
      as)
        TOOL="$COSMOPOLITAN_TOOLCHAIN-cc -c"
        ;;
      *)
        if command -v -- "$OTHERTOOLPREFIX$TOOL" > /dev/null; then
          TOOL="$OTHERTOOLPREFIX$TOOL"
        fi
        ;;
    esac
  fi

  cat << EOF
#!/bin/sh
exec $TOOL "\$@"
EOF
}

case "$1" in
  cc|gcc)
    gen_cc
    ;;
  *)
    gen_tool "$1"
    ;;
esac
