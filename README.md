<h1 align="center">Esperanto</h1>
<h4 align="center">Build-once Run-anywhere OCaml programs</h4>
<br>

Esperanto makes OCaml a build-once run-anywhere language, like itself, except
it doesn't need an interpreter or virtual machine. Indeed, OCaml is able to
produce a **native** executable which requires few libraries:
- a standard C library
- `libasmrun.a` (the _caml-runtime_)
- probably `libunix.a` if you depend on `unix.cmxa`
- probably `libpthread.a` if you depend on `threads.cmxa`

Esperanto replaces the host's C library by [Cosmopolitan][cosmopolitan]. Then,
it outputs a POSIX-approved polyglot format that runs on many platforms. For
more details, please read the [αcτµαlly pδrταblε εxεcµταblε][ape].

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
$ cat >>bin/dune <<EOF

; A rule to properly strip everythings
(rule
 (target xxd.com)
 (enabled_if
  (= %{context_name} esperanto))
 (mode promote)
 (deps xxd.exe)
 (action (run objcopy -S -O binary %{deps} %{target})))
EOF
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
$ dune build bin/xxd.com
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
- `startup_unix.o`/`fake_unix.o` which initiates few constants needed by
  `libunix.a` if you depend on `unix.cmxa`
- `startup_threads.o`/`fake_threads.o` which initiates few constants needed by
  `libthreads.a` if you depend on `threads.cmxa`

## The caml compiler

From the toolchain, we are able to compile the OCaml compiler and its runtime
with Cosmopolitan (with few fixes). `esperanto` provides a new OCaml toolchain
which can be used by `dune` to "cross"-compile a project.

Such design comes from [MirageOS][mirage] and [Solo5][solo5].

Currently, we support OCaml 4.12, 4.13 & 4.14.

## Issues and bugs

### `pthread` and platforms

Currently, we use [`pth`][pth] to provide from few POSIX-available _syscalls_
the `pthread` library required by `threads.cmxa`. However, the support of `pth`
is only about POSIX systems. The Windows support is not done yet so. An issue
exists to track such support. For other systems like \*BSD, the support should
works.

### Warnings and C stubs

The hard part of esperanto is when we need to compile C stubs with the
Cosmopolitan C library. Indeed, the context is a bit different and your C code
probably does not compile with Cosmopolitan. The usual mistake is about
constants:
```c
static int wait_flag_table[] = { WNOHANG, WUNTRACED };

value wait4(value flags, ...) {
  int flags = caml_convert_flag_list(flags, wait_flag_table);
  ...
}
```

```ocaml
type wait_flag = WNOHANG | WUNTRACED
external wait4 : wait_flag list -> ... = "wait4"
```

Such code **can not** compile with Cosmopolitan due to the fact that `WNOHANG`
& `WUNTRACED` are not constants but values which are set at the beginning of
your program according to your platform.

Some others issues can remain but they are probably specific to you code. But
Esperanto can not fit for every projects, so third-party libraries maintainers
should be aware about "these details" if they want to support Esperanto.

[ape]: https://justine.lol/ape.html
[cosmopolitan]: https://justine.lol/cosmopolitan/index.html
[ape.lds]: https://justine.lol/cosmopolitan/ape.lds
[mirage]: https://mirage.io/
[solo5]: https://github.com/Solo5/solo5
[opam-monorepo]: https://github.com/ocamllabs/opam-monorepo
[pth]: https://www.gnu.org/software/pth/
