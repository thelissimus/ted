#pragma once

#include "buffer.h"
#include "cursor.h"
#include "row.h"

struct screen {
	int rows;
	int cols;
};

int screen_get_size(struct screen *);
void screen_refresh(const struct screen *, const struct cursor *,
	struct editor_rows *);
void screen_draw_rows(const struct screen *, struct buffer *,
	const struct editor_rows *);
