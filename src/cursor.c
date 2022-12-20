#include "cursor.h"
#include "util.h"

void
cursor_move(struct cursor *csr, enum cursor_direction dir, int n)
{
	switch (dir) {
	case CURSOR_LEFT:
		if (BETWEEN(csr->x - n, csr->x_min, csr->x_max)) {
			csr->x -= n;
		}
		break;
	case CURSOR_RIGHT:
		if (BETWEEN(csr->x + n + 1, csr->x_min, csr->x_max)) {
			csr->x += n;
		}
		break;
	case CURSOR_DOWN:
		if (BETWEEN(csr->y + n + 1, csr->y_min, csr->y_max)) {
			csr->y += n;
		}
		break;
	case CURSOR_UP:
		if (BETWEEN(csr->y - n, csr->y_min, csr->y_max)) {
			csr->y -= n;
		}
		break;
	}
}
