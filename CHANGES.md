## v0.0.6 (2024-08-10) Paris - France

- Upgrade to Cosmopolitan 3.6.2

## v0.0.5 (2023-12-21) Paris - France

- Support Cosmopolitan 3.1 (#43, @dinosaure)
- Fix the compilation of esperanto with setup-ocaml and GitHub CI (#44, @dinosaure)
- Extend the support of Esperanto to 4.13 (#45, @dinosaure)

## v0.0.4 (2023-05-25) Paris - France

- Fix the compilation of `threads.cmxa` (@dinosaure, #38)
- Update to the last version of Cosmopolitan (@dinosaure, #40)

## v0.0.3 (2023-03-08) Paris - France

- Delete the `pth` relicat and directly use `pthread` from Cosmopolitan (#33, @dinosaure)
- Delete the `-mnop-mcount` and fix the issue with `dune.3.7.0` (#34, @dinosaure)
  The `-mnop-mcount` is important only if we use `-pg` which is not the case. The initial
  issue is a conflict with this option and `-fPIC` introduced by `dune.3.7.0`.
- Upgrade Esperanto with Cosmopolitan 2.2-96-gae365928c (#36, @dinosaure)
  This specific version of Cosmopolitan fixes an issue about Esperanto and the
  LWT support. However, this specific version of Cosmopolitan loses the support of
  `speed_t` (all values of this type disappeared).

## v0.0.2 (2023-01-17) Paris - France

- Delete `conf-gcc` (we currently are able to use `clang`)
- The current toolchain does not work on MacOS
- Add conf-cosmopolitan package
- Upgrade to Cosmopolitan v2.2 (#28)
- Update the provided `extract.com` (#30)
- Fix the support of OCaml 4.14.1
- Delete `pth` (Cosmopolitan provides `pthread`)

## v0.0.1 (2022-09-22) Paris - France

- First release of `esperanto`
