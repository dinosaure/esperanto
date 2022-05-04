# Esperanto - when [Cosmopolitan][cosmopolitan] meets OCaml

**The status of this repository is experimental**

[Cosmopolitan][cosmopolitan] is a C library with a link trick which permits us
craft an artifact `*.com` which can run everywhere: build-once run-anywhere.

The goal of `esperanto` is to provide a new OCaml _toolchain_ which uses this
specific library with the special link script [`ape.lds`][ape.lds] to let a
user to craft a binary with OCaml which should run anywhere.

The current status of this repository permits to compile a simple program such
as a `sha256sum` which uses [`digestif`][digestif][^1] and craft a binary which
works on Windows, Linux and Mac.

## The toolchain

The `cosmopolitan` toolchain (see [`toolchain/`][./toolchain] provides a
special compiler and a special `ld` script which integrates options needed
to well-build the _caml runtime_ with Cosmopolitan.

It puts into your OPAM 3 binaries:
- `[arch]-esperanto-none-static-cc` the compiler
- `[arch]-esperanto-none-static-ld` the linker
- `[arch]-esperanto-none-static-objinfo` a simple tool to mainly strip binaries

It installs few objects files:
- `cosmopolitan.a` the Cosmopolitan library
- `crt.o`, `ape.o`, `ape-no-modify-self.o` and [`ape.lds`][ape.lds]
- `startup.o` which is a well-builder `caml_startup` for your binaries which
  must be linked with `-z caml-startup` option

Finally, it provides mainly `cosmopolitan.h` and some files that are only
redirects to the first one.

From all of these files, the user is able to use a C compiler which is able to
compile C files with Cosmopolitan's options. Then, it is able to properly link
objects file to a Cosmopolitan artificact.

## The caml compiler

From the toolchain, we are able to compile the OCaml compiler and its runtime
with Cosmopolitan (with few fixes). `esperanto` provides a new OCaml toolchain
which is able to be used by `dune` to "cross"-compile a project with this
tweaked compiler and Cosmopolitan.

Such design comes from [MirageOS][mirage] and [Solo5][solo5].

Currently, we only support OCaml 4.14 but we probably can support:
- older version
- OCaml multicore, `phtread` seems available

## How to use it?

We will take a example with [`digestif`][digestif] and do a little program
which digest `stdin`:
```sh
$ git clone https://github.com/mirage/digestif.git
$ cd digestif
$ git checkout esperanto
$ opam pin add https://github.com/dinosaure/esperanto.git
$ opam install cosmopolitan esperanto opam-monorepo
$ opam monorepo lock
$ opam monorepo pull
$ dune build bin/sha256sum.com
$ cp _build/esperanto/bin/sha256sum.com .
$ chmod +w sha256sum.com
```

You can introspect what we did on `digestif` to be able to craft our
`sha256sum` program but it's mainly a new `dune-workspace` file which describes
the `esperanto` toolchain. A link flags is needed to integrate into your binary
the `caml_startup` function with `-z caml-startup`. On the default context,
your linker will probably ignore this option.

The usage of [`opam monorepo`][opam-monorepo] helps us to make a fully-static
binary. You can denote the size of the binary: 900K which is good for something
which integrate the _caml runtime_. For comparison, the same program with the
default context is: 1.2M.

**Warning**: About the usage of `sha256sum.com`, if you want to use it into
another system (such as Windows), you should **NOT** run it into your host
system and you directly copy the artifact as is into your another system.
Indeed, with the [`ape.lds`] trick, the program modifies **itself** according
to the system - it's why we need to do a `chmod +w sha256sum.com`.

Then, you can write (whatever the system) you `sha256sum.com` as a simple
program:
```sh
$ bash -c 'echo "Hello World" | ./sha256sum.com'
d2a84f4b8b650937ec8f73cd8be2c74add5a911ba64df27458ed8229da804a26
```

### A small example

The distribution comes with a small example into [./example][./example] which
is a simple program which repeats what you want to say. I hope it will speak
the same language as you...

Again, you can build it like:
```sh
$ opam install cosmopolitan esperanto
$ cd example
$ dune build ./cat.com
$ bash -c './cat.com'
Hello World!
^DHello World!
```

## Experimental status

Currently, this repository is a _working-in-progress_ repository. Some issues
exists and it will nice to include `unix.cmxa` and be able to compile mostly
anything from the OCaml ecosystem with Cosmopolitan.

### TODO-list

- [ ] Fix issues about some constants like `O_TRUNC`
- [ ] Support of `unix.cmxa`
- [ ] Support of `pthreads`

[^1]: For such case, [`opam monorepo`] and `dune` is required to fetch
dependencies needed to build **statically** the requested binary.

[Cosmopolitan]: https://justine.lol/cosmopolitan/index.html
[ape.lds]: https://justine.lol/cosmopolitan/ape.lds
[digestif]: https://github.com/mirage/digestif
[mirage]: https://mirage.io/
[solo5]: https://github.com/Solo5/solo5
[opam-monorepo]: https://github.com/ocamllabs/opam-monorepo
