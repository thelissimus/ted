#pragma once

#include <stddef.h>

struct buffer {
	void *buf;
	size_t len;
};

struct buffer buffer_init(void);
void buffer_reset(struct buffer *);
void buffer_append(struct buffer *, const void *, size_t);
