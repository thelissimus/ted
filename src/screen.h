#ifndef TED_SCREEN_H
#define TED_SCREEN_H

#include "buffer.h"
#include "cursor.h"

typedef struct {
	int rows;
	int cols;
} Screen;

int Screen_get_size(Screen *);
void Screen_refresh(Screen *, Cursor *);
void Screen_draw_rows(Screen *, Buffer *);
void Screen_draw_welcome(Screen *, Buffer *, const char *, int);

#endif // TED_SCREEN_H
