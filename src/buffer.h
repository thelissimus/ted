#pragma once

#include <stddef.h>

struct buffer {
	char *buf;
	size_t len;
};

struct buffer buffer_init(void);
void buffer_append(struct buffer *, const char *, size_t);
void buffer_reset(struct buffer *);
