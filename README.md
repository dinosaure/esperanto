<h1 align="center">Esperanto</h1>
<h4 align="center">Build-once Run-anywhere OCaml programs</h4>
<br>

Esperanto makes OCaml a build-once run-anywhere language, like itself, except
it doesn't need an interpreter or virtual machine. Indeed, OCaml is able to
produce a **native** executable which requires few libraries:
- a standard C library
- `libasmrun.a` (the _caml-runtime_)
- probably `libunix.a` if you depend on `unix.cmxa`

Esperanto replaces the host's C library by [Cosmopolitan][cosmopolitan]. Then,
it outputs a POSIX-approved polyglot format that runs on many platforms. For
more details, please read the [αcτµαlly pδrταblε εxεcµταblε][ape].

## Getting Started

You can install the project with OPAM:
```sh
$ opam pin add -y https://github.com/dinosaure/esperanto.git
```

### A simple program

Let's start to make a simple _Hello World!_ example:
```sh
$ cat >main.ml <<EOF
let () = print_endline "Hello World!"
EOF
$ ocamlfind -toolchain esperanto opt main.ml
$ objcopy -S -O binary a.out
$ file a.out
a.out: DOS/MBR boot sector
$ sh -c "./a.out"
Hello World!
```

### With `dune` and dependencies

You can take your favorite project and compile executables with the
Esperanto toolchain. You need to specify a new `dune-workspace`:
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

Now, you have a portable/polyglot program. The user can _assimilate_ the
program with the `--assimilate` option:
```sh
$ file bin/xxd.com
bin/xxd.com: DOS/MBR boot sector
$ sh -c "./bin/xxd.com --assimilate"
$ file bin/xxd.com
bin/xxd.com: ELF 64-bit LSB executable
```

The `--assimilate` option modify the executable itself to become _really_
native to your platform - in other words, the executable no longer becomes
polyglot!

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

## The caml compiler

From the toolchain, we are able to compile the OCaml compiler and its runtime
with Cosmopolitan (with few fixes). `esperanto` provides a new OCaml toolchain
which can be used by `dune` to "cross"-compile a project.

Such design comes from [MirageOS][mirage] and [Solo5][solo5]. For C stubs, we
provide the `__ESPERANTO__` definition which permits to orchestrate your
compilation of C files according to the OCaml toolchain.

Currently, we support OCaml 4.13 & 4.14.

## Issues and bugs

### `zsh` and `binfmt_misc`

Currently, `zsh < 5.9.0` does not support well Cosmopolitan/APE binaries.
However, the recent version fix the initial issue. In the case of you have
`zsh < 5.9.0`, you can use the `--assimilate` option to modify the executable
to a _real_ native application:
```sh
$ zsh --version
zsh 5.8.1
$ zsh
$ ./a.out
zsh: exec format error: ./a.out
$ sh -c "./a.out --assimilate"
$ ./a.out
Hello World!
```

However, as explained above, the binary no longer becomes _polyglot_!

An other issue on Linux is about `binfmt_misc` which wants to interpret the
binary as a Windows executable (due to the header of the Cosmopolitan binary).
A good explanation is available here: jart/cosmopolitan#2

The Cosmopolitan distribution (and specially the APE distribution) gives an
installer: https://justine.lol/apeloader/#binfmt_misc
This installer learns to `binfmt_misc` how to recognize and execute a
Cosmopolitan binary.

### `pthread` and platforms

Cosmopolitan provides partially `pthread` (only mutex) and few functions which
can simulate threads (see `spawn` and `join`). Due to the partial
implementation of the `pthread`, we are not able to provide `threads.cmxa` from
the OCaml project. However, _upstream_ wants to improve this situation and, in
the near future, Cosmopolitan will probably provide a full implementation of
`pthread`. In this future, we will be able to provide `threads.cmxa` and start
the support of OCaml 5.0.

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
