.PHONY: all %

all:
	$(MAKE) -C core

%:
	$(MAKE) -C core $@
