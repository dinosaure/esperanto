.PHONY: distrib
distrib: GIT_VERSION = $(shell git -C . describe --dirty --tags --always)
distrib: GIT_OLDBRANCH = $(shell git rev-parse --abbrev-ref HEAD)
distrib:
	git checkout -b distrib/$(GIT_VERSION)
	git commit -m "Release tarball for $(GIT_VERSION)" --allow-empty
	@echo DISTRIB esperanto-$(GIT_VERSION).tar.gz
	git archive --format=tar.gz --prefix=esperanto-$(GIT_VERSION)/ \
		distrib/$(GIT_VERSION) > esperanto-$(GIT_VERSION).tar.gz
	-git checkout $(GIT_OLDBRANCH)
	-git branch -D distrib/$(GIT_VERSION)
