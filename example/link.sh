#!/bin/sh

apelink -o cat.com \
  -l $(opam var bin)/ape-x86_64.elf \
  -l $(opam var bin)/ape-aarch64.elf \
  -M $(opam var bin)/ape-m1.c \
  _build/aarch64-esperanto/cat.exe.dbg \
  _build/x86_64-esperanto/cat.exe.dbg
