VERSION = 0.1

TARGET = bin/ted
PREFIX = /usr/local

CPPFLAGS = -D_DEFAULT_SOURCE
CFLAGS   = -std=c99 -Wall -Wextra -Wpedantic -O2 $(CPPFLAGS)
CC       = cc

SRC = $(addprefix src/, \
	buffer.c cursor.c key.c main.c row.c screen.c term_control.c util.c \
	)
OBJ = $(SRC:src/%.c=bin/%.o)

TEST_SRC     = $(wildcard src/*_test.c)
TEST_SRC_OBJ = $(TEST_SRC:src/%_test.c=bin/%.o)
TEST_OBJ     = $(TEST_SRC:src/%.c=bin/%.o)
TEST_BIN     = $(TEST_SRC:src/%.c=bin/%)
TEST_LIBS    = -lcriterion

all: $(TARGET)

options:
	@echo "VERSION      = $(VERSION)"
	@echo "TARGET       = $(TARGET)"
	@echo "PREFIX       = $(PREFIX)"
	@echo "CFLAGS       = $(CFLAGS)"
	@echo "CC           = $(CC)"
	@echo "SRC          = $(SRC)"
	@echo "OBJ          = $(OBJ)"
	@echo "TEST_SRC     = $(TEST_SRC)"
	@echo "TEST_SRC_OBJ = $(TEST_SRC_OBJ)"
	@echo "TEST_OBJ     = $(TEST_OBJ)"
	@echo "TEST_BIN     = $(TEST_BIN)"
	@echo "TEST_LIBS    = $(TEST_LIBS)"

bin/:
	mkdir bin/

bin/%.o: src/%.c | bin/
	$(CC) -o $@ $< -c $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

format:
	clang-format -i src/*.[ch]

lint:
	clang-tidy src/*.[ch]

$(TEST_BIN): $(TEST_OBJ) $(TEST_SRC_OBJ)
	$(CC) -o $@ $^ $(TEST_LIBS)

test: $(TEST_BIN)
	for test in $^; do ./$$test; done

clean:
	rm -f $(TARGET) $(OBJ) $(TEST_OBJ) $(TEST_BIN)

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f $(TARGET) $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/ted

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/ted

.PHONY: all options format lint test clean install uninstall
