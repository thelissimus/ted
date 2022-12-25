#pragma once

#include <stddef.h>

struct row {
	size_t length;
	char *content;
};

struct editor_rows {
	size_t row_offset;
	size_t col_offset;
	size_t col_max;
	size_t count;
	struct row *rows;
};

struct editor_rows editor_rows_init(void);
void editor_rows_append(struct editor_rows *, const char *, size_t);
void editor_rows_reset(struct editor_rows *);
int editor_rows_readfile(struct editor_rows *, const char *);
