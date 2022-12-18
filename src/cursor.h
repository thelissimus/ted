#ifndef TED_CURSOR_H
#define TED_CURSOR_H

typedef enum {
	CURSOR_UP,
	CURSOR_DOWN,
	CURSOR_RIGHT,
	CURSOR_LEFT
} CursorDirection;

typedef struct {
	int x;
	int x_min;
	int x_max;
	int y;
	int y_min;
	int y_max;
} Cursor;

void Cursor_move(Cursor *, CursorDirection);

#endif // TED_CURSOR_H
