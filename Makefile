PREFIX = /usr/local

.PHONY: all
all:
	cd quicknanobrowser && qmake && $(MAKE)

.PHONY: install
install:
	install -d $(DESTDIR)$(PREFIX)/bin/
	install -m 755 quicknanobrowser/quicknanobrowser $(DESTDIR)$(PREFIX)/bin/webviewer

.PHONY: clean
clean:
	$(MAKE) -C quicknanobrowser clean

.PHONY: mrproper
mrproper:
	$(MAKE) -C quicknanobrowser distclean
