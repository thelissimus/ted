SRC = ted.c
OBJ = $(SRC:.c=.o)

VERSION = 0.1

PREFIX = /usr/local

CFLAGS = -std=c99 -Wall -Wextra -pedantic -O2

all: ted

%.o: %.c
	$(CC) -o $@ $< -c $(CFLAGS)

ted: $(OBJ)
	$(CC) -o $@ $(OBJ)

clean:
	rm -f ted $(OBJ) ted-$(VERSION).tar.gz

dist: clean
	mkdir -p ted-$(VERSION)
	cp -r Makefile $(SRC) ted-$(VERSION)
	tar -cf ted-$(VERSION).tar ted-$(VERSION)
	gzip ted-$(VERSION).tar
	rm -rf ted-$(VERSION)

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f ted $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/ted

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/ted

.PHONY: all clean dist install uninstall
