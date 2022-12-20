#pragma once

enum cursor_direction { CURSOR_UP, CURSOR_DOWN, CURSOR_RIGHT, CURSOR_LEFT };

struct cursor {
	int x;
	int x_min;
	int x_max;
	int y;
	int y_min;
	int y_max;
};

void cursor_move(struct cursor *, enum cursor_direction, int);
