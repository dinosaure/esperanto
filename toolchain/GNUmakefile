EXTRACT=opam exec -- dune exec --display=verbose ./extract.exe --
INSTALL=opam exec -- dune exec --display=verbose ./install.exe --
DISTRIBUTION=cosmocc.zip
DIGEST=cosmocc.digest
DST=cosmo
PREFIX=/usr/local

SRCS=
OBJS=$(patsubst %.c,${DST}/esperanto/%.o,${SRCS})
DIRECTORY_GUARD=@mkdir -p $(@D)

COSMOCC=$(shell ${EXTRACT} list -d ${DST} --digest ${DIGEST} ${DISTRIBUTION})

all: ${COSMOCC}

extract: ${DIGEST} ${DISTRIBUTION}
	@echo " UNZIP ${DISTRIBUTION}"
	@${EXTRACT} -d ${DST} --digest ${DIGEST} ${DISTRIBUTION}

${DST}/esperanto/%.o: %.c ${COSMOCC}
	$(DIRECTORY_GUARD)
	@echo " COSMOCC $< $@"
	@${DST}/bin/cosmocc -c $< -o $@

install: ${COSMOCC} ${OBJS}
	@echo " INSTALL ${PREFIX}"
	@${INSTALL} -d ${DST} --digest ${DIGEST} --prefix "${PREFIX}"

clean:
	opam exec -- dune clean
	rm -rf ${DST}
	rm -rf ${OBJS}

.PHONY: clean install
