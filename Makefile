SRC = $(addprefix src/, \
	buffer.c cursor.c key.c main.c row.c screen.c term_control.c util.c \
	)
OBJ = $(SRC:.c=.o)

VERSION = 0.1

PREFIX = /usr/local

CFLAGS = -std=c99 -Wall -Wextra -Wpedantic -O2

all: ted

%.o: %.c
	$(CC) $< -o $@ -c $(CFLAGS)

ted: $(OBJ)
	$(CC) -o $@ $(OBJ)

format:
	clang-format -i src/*.[ch]

lint:
	clang-tidy src/*.[ch]

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

.PHONY: all format lint clean dist install uninstall
