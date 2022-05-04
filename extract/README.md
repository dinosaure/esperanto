# The tool which is able to extract cosmopolitan distribution

This tool is simple. It wants to _unzip_ `cosmopolitan.zip` and it is used by
our Cosmopolitan toolchain. If you install `esperanto`, you should able to
compile, at least, this project with:
```sh
$ opam monorepo lock
$ opam monorepo pull
$ dune build
$ cp _build/esperanto/extract.com .
$ chmod +w extract.com
```

The given artifact should work anywhere. However, the current state of
`esperanto` does not pass the `O_TRUNC` option when we use `openat`. By this
fact - which is more related to `cosmopolitan`/`esperanto` - the tool fails.
