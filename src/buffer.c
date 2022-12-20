#include <stdlib.h>
#include <string.h>

#include "buffer.h"

struct buffer
buffer_init(void)
{
	return (struct buffer) { .buf = NULL, .len = 0 };
}

void
buffer_append(struct buffer *b, const char *s, size_t len)
{
	char *new = realloc(b->buf, b->len + len);
	if (new == NULL) {
		return;
	}
	memcpy(&new[b->len], s, len);
	b->buf = new;
	b->len += len;
}

void
buffer_reset(struct buffer *b)
{
	free(b->buf);
	b->len = 0;
}
