#define _GNU_SOURCE

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "row.h"

struct editor_rows
editor_rows_init(void)
{
	return (struct editor_rows) { .rows = NULL, .count = 0 };
}

void
editor_rows_append(struct editor_rows *rs, const char *str, size_t len)
{
	rs->rows = realloc(rs->rows, sizeof(struct row) * (rs->count + 1));
	rs->rows[rs->count].length = len;
	rs->rows[rs->count].content = malloc(len * sizeof(char) + 1);
	memcpy(rs->rows[rs->count].content, str, len);
	rs->rows[rs->count].content[len] = '\0';
	rs->count++;
}

void
editor_rows_reset(struct editor_rows *rs)
{
	if (rs->count == 0) {
		return;
	}

	while (rs->count > 0) {
		free(rs->rows[rs->count - 1].content);
		rs->count--;
	}

	free(rs->rows);
	rs->count = 0;
}

int
editor_rows_readfile(struct editor_rows *rs, const char *filename)
{
	char *line = NULL;
	size_t cap = 0;
	ssize_t len;
	FILE *file;

	file = fopen(filename, "r");
	if (file == NULL) {
		return -1;
	}

	while ((len = getline(&line, &cap, file)) != -1) {
		if (len > 0) {
			len = (ssize_t) strcspn(line, "\r\n");
			line[len] = '\0';
		}
		editor_rows_append(rs, line, len);
	}

	free(line);
	fclose(file);
	return 0;
}
