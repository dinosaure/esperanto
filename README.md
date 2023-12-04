<h1 align="center">Esperanto</h1>
<h4 align="center">Build-once Run-anywhere OCaml programs</h4>
<br>

Esperanto makes OCaml a build-once run-anywhere language, like itself, except
it doesn't need an interpreter or virtual machine. Indeed, OCaml is able to
produce a **native** executable which requires few libraries:
- a standard C library
- `libasmrun.a` (the _caml-runtime_)
- `unix.cmxa` and `threads.cmxa`

Esperanto replaces the host's C library by [Cosmopolitan][cosmopolitan]. Then,
it outputs a POSIX-approved polyglot format that runs on many platforms. For
more details, please read the [αcτµαlly pδrταblε εxεcµταblε][ape].

The goal of esperanto is to provide a _toolchain_ which is able to compile an
OCaml project to `aarch64` and `x86_64` and link these artifacts together to
produce an actually portable executable. Esperanto is primarily a distribution
tool rather than a development tool. We advise the user to have a finalized
project and then use Esperanto to produce a distribution.

The pipeline used to produce such a portable executable must respect certain
constraints:
- not depend on dynamic objects (`*.so`)
- the C files required for compilation can also be compiled with the
  Cosmopolitan C library

## Getting Started

Let's take the example of a simple program to understand the basic "pipeline"
required to produce a `.com` (for COsMpolitan) executable. We recommend using
Esperanto in a [Docker][docker] or "clean" system (like a special
[`opam` switch][switch]). Once again, the aim is to produce an artifact from a
finalized project, not to develop an application. So you need opam. Let's take
Docker as an example:

```sh
$ docker run -it --platform amd64 ocaml/opam:ubuntu-23-04-ocaml-4.14
$ opam pin add -y https://github.com/dinosaure/esperanto.git
```

Esperanto installs 4 packages:
- `conf-cosmopolitan`, this package verifies that your system can, indeed, run
  [ape][ape] programs.
- `esperanto-cosmopolitan`, this package is the Cosmopolitan toolchain as
  available from [cosmocc.zip][cosmo.zip] (v3.1.3) packaged for `opam`. It
  verifies the integrity of distribution files according to these
  [fingerprints][./toolchain/cosmocc.digest]

Finally, 2 versions of the OCaml compiler are available:
- To produce an `x86_64` program (`x86_64-esperanto`)
- To produce an `aarch64` program (`aarch64-esperanto`)

### A simple program

Let's start to make a simple _Hello World!_ example:
```sh
$ cat >main.ml <<EOF
let () = print_endline "Hello World!"
EOF
$ ocamlfind -toolchain x86_64_esperanto opt -o main.x86_64.elf main.ml
$ ocamlfind -toolchain aarch64_esperanto opt -o main.aarch64.elf main.ml
$ apelink -o main.com \
     -l $(opam var bin)/ape-x86_64.elf \
     -l $(opam var bin)/ape-aarch64.elf \
     -M $(opam var bin)/ape-m1.c \
     main.x86_64.elf main.aarch64.elf
$ sh -c "./main.com"
Hello World!
```

### Cross compilation and static linking

Producing an executable from your OCaml project that is portable on all systems
requires 2 precise points:
1) project dependencies must be available to compile in a consistent context.
   Such consistency can be achieved by `dune` and a _"monorepo"_ format for your
   project.
2) C dependencies must be able to compile with Cosmopolitan.
   [cosmocc.zip][cosmocc.zip] offers a patched version of GCC and Cosmopolitan
   exposes many functions. However, you may need to patch your C code (in
   particular, you can use `__COSMOPOLITAN__`).

If these 2 points are met (getting the dependency sources and having
Cosmopolitan-compatible C code), we're ready to produce the final artifact using
the Esperanto toolchain. So, 3 steps are necessary:
1) compile project for x86_64 architecture
2) compile project for aarch64 architecture
3) link the 2 `ELF` files into a portable binary

### Esperanto and _real_ project (with `dune` and `opam monorepo`)

To achieve our 2 objectives, we're going to use `dune` to provide us with the
famous contexts linked to our 2 toolchains (`x86_64` and `aarch64`) and
`opam monorepo` to download locally the dependencies needed for our project (the
constraint implies that all dependencies use dune). Let's play with [hxd][hxd],
a small project.

You can take your favorite project and compile executables with the
Esperanto toolchain. You need to specify two new contexts:
```sh
$ git clone https://github.com/dinosaure/hxd.git
$ cd hxd
$ opam repo add opam-overlays https://github.com/dune-universe/opam-overlays.git
$ sudo apt install pkg-config
$ cat >dune-workspace<<EOF
(lang dune 2.0)

(context (default))

(context
 (default
  (name x86_64-esperanto)
  (toolchain x86_64_esperanto)
  (host default)))

(context
 (default
  (name aarch64-esperanto)
  (toolchain aarch64_esperanto)
  (host default)))
EOF
```

Finally, as a static program, you must fetch dependencies with
[opam monorepo][opam-monorepo] and build your project with them:
```sh
$ opam monorepo lock --ocaml-version=4.14.1
$ opam monorepo pull
$ dune build bin/xxd.exe
$ apelink -o xxd.com \
     -l $(opam var bin)/ape-x86_64.elf \
     -l $(opam var bin)/ape-aarch64.elf \
     -M $(opam var bin)/ape-m1.c \
     _build/bin/x86_64-esperanto/xxd.exe.dbg \
     _build/bin/aarch64-esperanto/xxd.exe.dbg
```

Now, you have a portable/polyglot program! The user can _assimilate_ the
program with the `--assimilate` option. Assimilation consists in "specializing"
the executable for the host system.
```sh
$ sh -c "./bin/xxd.com --assimilate"
$ uname -p
x86_64
$ file bin/xxd.com
bin/xxd.com: ELF 64-bit LSB executable, x86-64
```

The `--assimilate` option modify the executable itself to become _really_
native to your platform - in other words, the executable no longer becomes
polyglot!

## Credits

Such design comes from [MirageOS][mirage] and [Solo5][solo5]. For C stubs, the
`cosmocc` toolchain provides  the `__COSMOPOLITAN__` definition which permits to
orchestrate your compilation of C files according to the OCaml toolchain.

Currently, we support OCaml 4.14.

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

If the issue persist with Python `subprocess` or old versions of fish, we also
advise an "assimilation" in these cases. However, as explained above, the binary
no longer becomes _polyglot_!

An other issue on Linux is about `binfmt_misc` which wants to interpret the
binary as a Windows executable (due to the header of the APE binary). A good
explanation is available here: jart/cosmopolitan#2

[ape]: https://justine.lol/ape.html
[cosmopolitan]: https://justine.lol/cosmopolitan/index.html
[ape.lds]: https://justine.lol/cosmopolitan/ape.lds
[mirage]: https://mirage.io/
[solo5]: https://github.com/Solo5/solo5
[opam-monorepo]: https://github.com/ocamllabs/opam-monorepo
[pth]: https://www.gnu.org/software/pth/
