#!/bin/sh

ocamlfind opt -linkpkg -package digestif.c,digestif,fmt,camlzip \
	extract.ml -o extract.com
rm extract.cmi
rm extract.cmx
rm extract.o
