#include "cursor.h"
#include "util.h"

void
Cursor_move(Cursor *cursor, CursorDirection dir, int n)
{
	switch (dir) {
	case CURSOR_LEFT:
		if (BETWEEN(cursor->x - n, cursor->x_min, cursor->x_max)) {
			cursor->x -= n;
		}
		break;
	case CURSOR_RIGHT:
		if (BETWEEN(cursor->x + n + 1, cursor->x_min, cursor->x_max)) {
			cursor->x += n;
		}
		break;
	case CURSOR_DOWN:
		if (BETWEEN(cursor->y + n + 1, cursor->y_min, cursor->y_max)) {
			cursor->y += n;
		}
		break;
	case CURSOR_UP:
		if (BETWEEN(cursor->y - n, cursor->y_min, cursor->y_max)) {
			cursor->y -= n;
		}
		break;
	}
}
