<h1 align="center">Esperanto</h1>
<h4 align="center">Build-once Run-anywhere OCaml programs</h4>
<br>

Esperanto makes OCaml a build-once run-anywhere language, like itself, except
it doesn't need an interpreter or virtual machine. Indeed, OCaml is able to
produce a **native** executable which requires few libraries:
- a C library
- `libasmrun.a`
- probably `libunix.a` if you depend on `unix.cmxa`

Esperanto replaces the host's C library by [Cosmopolitan][cosmopolitan]. Then,
it outputs a POSIX-approved polyglot format that runs on:
- Linux
- Mac
- Windows
- FreeBSD
- OpenBSD
- NetBSD
- BIOS

For more details, please read the [αcτµαlly pδrταblε εxεcµταblε][ape]

## Getting Started

You can install the project with OPAM:
```sh
$ opam pin add -y https://github.com/dinosaure/esperanto.git
```

Then, you can take your favorite project and compile executables with the
Esperanto toolchain. You need to specify a new option `-z caml-startup`
and you need to specify a new `dune-workspace`:
```sh
$ git clone https://github.com/dinosaure/hxd.git
$ cd hxd
$ cat >esperanto.patch<<EOF
diff --git a/bin/dune b/bin/dune
index 7a34f15..145a159 100644
--- a/bin/dune
+++ b/bin/dune
@@ -2,8 +2,17 @@
  (name xxd)
  (public_name hxd.xxd)
  (modules xxd)
+ (link_flags :standard -cclib "-z caml-startup")
  (libraries hxd cmdliner hxd_unix))
 
+(rule
+ (target xxd.com)
+ (enabled_if
+  (= %{context_name} esperanto))
+ (mode promote)
+ (deps xxd.exe)
+ (action (run objcopy -S -O binary %{deps} %{target})))
+
 (executable
  (name caml)
  (public_name hxd.caml)
EOF
$ git apply < esperanto.patch
$ cat >dune-project<<EOF
(lang dune 2.0)

(context (default))

(context
 (default
  (name esperanto)
  (toolchain esperanto)
  (merlin)
  (host default)))
EOF
```

Finally, as a static program, you must fetch dependencies with
[opam monorepo][opam-monorepo] and build your project with them:
```sh
$ opam monorepo lock
$ opam monorepo pull
$ dune build
$ ls bin/xxd.com
```

Now, you have a portable program. Please note that your APE binary
**will assimilate** itself as a conventional resident of your platform after
**the first run**, so it can be fast and efficient for subsequent executions -
but it becomes **not** portable anymore! So if you intend to copy the binary to
Windows or Mac then please do that **before** you run it, not after.

## The toolchain

The `cosmopolitan` toolchain (see [`toolchain/`](./toolchain)) provides a
special compiler and a special `ld` script which integrates options needed
to well-build the _caml runtime_ with Cosmopolitan.

It puts into your OPAM 3 binaries:
- `arch-esperanto-none-static-cc` the compiler
- `arch-esperanto-none-static-ld` the linker
- `arch-esperanto-none-static-objinfo` a simple tool to mainly strip binaries

It installs few objects files:
- `cosmopolitan.a` the Cosmopolitan library
- `crt.o`, `ape.o`, `ape-no-modify-self.o` and [`ape.lds`][ape.lds]
- `startup.o` which is a well-builded `caml_startup` for your binaries which
  must be linked with `-z caml-startup` option
- `startup_unix.o`/`fake_unix.o` which initiates few contants needed by
  `libunix.a` if you depend on `unix.cmxa`

## The caml compiler

From the toolchain, we are able to compile the OCaml compiler and its runtime
with Cosmopolitan (with few fixes). `esperanto` provides a new OCaml toolchain
which can be used by `dune` to "cross"-compile a project.

Such design comes from [MirageOS][mirage] and [Solo5][solo5].

Currently, we only support OCaml 4.14 but we probably can support:
- older version
- OCaml multicore, `pthread` seems available

[ape]: https://justine.lol/ape.html
[cosmopolitan]: https://justine.lol/cosmopolitan/index.html
[ape.lds]: https://justine.lol/cosmopolitan/ape.lds
[mirage]: https://mirage.io/
[solo5]: https://github.com/Solo5/solo5
[opam-monorepo]: https://github.com/ocamllabs/opam-monorepo
