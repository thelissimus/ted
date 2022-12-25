#include <sys/types.h>

#include "cursor.h"
#include "util.h"

void
cursor_move(struct cursor *csr, enum cursor_direction dir, size_t n)
{
	switch (dir) {
	case CURSOR_LEFT:
		if (BETWEEN(csr->x - n, csr->x_min, csr->x_max)) {
			csr->x -= n;
		} else if ((ssize_t) (csr->x - n) < (ssize_t) csr->x_min) {
			csr->x = csr->x_min;
		}
		break;
	case CURSOR_RIGHT:
		if (BETWEEN(csr->x + n + 1, csr->x_min, csr->x_max)) {
			csr->x += n;
		} else if (csr->x + n + 1 > csr->x_max) {
			csr->x = csr->x_max;
		}
		break;
	case CURSOR_DOWN:
		if (BETWEEN(csr->y + n + 1, csr->y_min, csr->y_max)) {
			csr->y += n;
		} else if (csr->y + n + 1 > csr->y_max) {
			csr->y = csr->y_max;
		}
		break;
	case CURSOR_UP:
		if (BETWEEN(csr->y - n, csr->y_min, csr->y_max)) {
			csr->y -= n;
		} else if ((ssize_t) (csr->y - n) < (ssize_t) csr->y_min) {
			csr->y = csr->y_min;
		}
		break;
	}
}
