#include <stdlib.h>
#include <string.h>

#include "buffer.h"

struct buffer
buffer_init(void)
{
	return (struct buffer) { .buf = NULL, .len = 0 };
}

void
buffer_reset(struct buffer *b)
{
	if (b->len == 0) {
		return;
	}
	free(b->buf);
	b->buf = NULL;
	b->len = 0;
}

void
buffer_append(struct buffer *b, const void *src, size_t len)
{
	char *new = realloc(b->buf, b->len + len);
	if (new == NULL) {
		return;
	}
	memcpy(&new[b->len], src, len);
	b->buf = new;
	b->len += len;
}
