#ifndef TED_SCREEN_H
#define TED_SCREEN_H

#include "buffer.h"
#include "cursor.h"

typedef struct {
	int rows;
	int cols;
} Screen;

int screen_get_size(Screen *);
void screen_refresh(Screen *, Cursor *);
void screen_draw_rows(Screen *, Buffer *);
void screen_draw_welcome(Screen *, Buffer *, const char *, int);

#endif // TED_SCREEN_H
