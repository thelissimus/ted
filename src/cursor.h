#pragma once

#include <stddef.h>

enum cursor_direction { CURSOR_UP, CURSOR_DOWN, CURSOR_RIGHT, CURSOR_LEFT };

struct cursor {
	size_t x;
	size_t x_min;
	size_t x_max;
	size_t y;
	size_t y_min;
	size_t y_max;
};

void cursor_move(struct cursor *, enum cursor_direction, size_t);
