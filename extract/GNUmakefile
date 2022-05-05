all:
	opam monorepo lock
	opam monorepo pull
	dune build ./extract.com

clean:
	dune clean
	$(RM) extract.com
	$(RM) *.locked
	$(RM) -r duniverse
