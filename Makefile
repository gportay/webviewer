#
# Copyright (C) 2017  Savoir-faire Linux Inc.
#	Vivien Didelot <vivien.didelot@savoirfairelinux.com>
#	Gaël Portay <gael.portay@savoirfairelinux.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#

ifneq (,$(DESTDIR))
INSTALL_ROOT = $(DESTDIR)
export INSTALL_ROOT
endif

.PHONY: all
all: src/Makefile
	$(MAKE) -C src $@

src/Makefile:
	cd $(@D) && qmake

.PHONY: doc
doc: qurlew.1.gz

.PHONY: install
install:
	$(MAKE) -C src $@

.PHONY: install-doc
install-doc: qurlew.1.gz
	install -d $(DESTDIR)/usr/share/man/man1/
	install -m 644 qurlew.1.gz $(DESTDIR)/usr/share/man/man1/

.PHONY: uninstall
uninstall:
	$(MAKE) -C src $@
	rm -f $(DESTDIR)/usr/share/man/man1/qurlew.1.gz

.PHONY: clean
clean:
	@$(MAKE) -C src $@
	rm -f qurlew.1.gz

.PHONY: distclean
distclean:
	@$(MAKE) -C src $@

%.1: %.1.adoc
	asciidoctor -b manpage -o $@ $<

%.gz: %
	gzip -c $^ >$@

