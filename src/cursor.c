#include "cursor.h"
#include "util.h"

void
Cursor_move(Cursor *cursor, CursorDirection dir)
{
	switch (dir) {
	case CURSOR_LEFT:
		if (between(cursor->x - 1, cursor->x_min, cursor->x_max)) {
			cursor->x--;
		}
		break;
	case CURSOR_RIGHT:
		if (between(cursor->x + 2, cursor->x_min, cursor->x_max)) {
			cursor->x++;
		}
		break;
	case CURSOR_DOWN:
		if (between(cursor->y + 2, cursor->y_min, cursor->y_max)) {
			cursor->y++;
		}
		break;
	case CURSOR_UP:
		if (between(cursor->y - 1, cursor->y_min, cursor->y_max)) {
			cursor->y--;
		}
		break;
	}
}
