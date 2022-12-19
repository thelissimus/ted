#include <stdlib.h>
#include <string.h>

#include "buffer.h"

Buffer
Buffer_init(void)
{
	return (Buffer) { .buf = NULL, .len = 0 };
}

void
Buffer_append(Buffer *buffer, const char *s, int len)
{
	char *new = realloc(buffer->buf, buffer->len + len);
	if (new == NULL) {
		return;
	}
	memcpy(&new[buffer->len], s, len);
	buffer->buf = new;
	buffer->len += len;
}

void
Buffer_reset(Buffer *buffer)
{
	free(buffer->buf);
	buffer->len = 0;
}
