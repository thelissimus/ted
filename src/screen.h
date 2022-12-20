#pragma once

#include "buffer.h"
#include "cursor.h"

struct screen {
	int rows;
	int cols;
};

int screen_get_size(struct screen *);
void screen_refresh(const struct screen *, const struct cursor *);
void screen_draw_rows(const struct screen *, struct buffer *);
