#include <stdlib.h>
#include <string.h>

#include "buffer.h"

Buffer
Buffer_init(void)
{
	return (Buffer) { .buf = NULL, .len = 0 };
}

void
Buffer_append(Buffer *self, const char *s, int len)
{
	char *new = realloc(self->buf, self->len + len);
	if (new == NULL) {
		return;
	}
	memcpy(&new[self->len], s, len);
	self->buf = new;
	self->len += len;
}

void
Buffer_reset(Buffer *self)
{
	free(self->buf);
	self->len = 0;
}
