#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>

#include "screen.h"
#include "term_control.h"

int
screen_get_size(Screen *screen)
{
	struct winsize ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != -1 || ws.ws_col != 0) {
		screen->rows = ws.ws_row;
		screen->cols = ws.ws_col;
		return 0;
	}

	// fallback method of getting cursor position
	if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) {
		return -1;
	}
	return term_get_cursor_pos(&screen->rows, &screen->cols);
}

void
screen_refresh(Screen *screen, Cursor *cursor)
{
	Buffer b = Buffer_init();

	// hide cursor and move it home
	Buffer_append(&b, "\x1b[?25l", 6);
	Buffer_append(&b, "\x1b[H", 3);

	// draw main content
	screen_draw_rows(screen, &b);

	// move cursor
	char buf[32];
	int written
		= term_set_cursor_pos(buf, sizeof buf, cursor->x, cursor->y);
	Buffer_append(&b, buf, written);

	// show cursor
	Buffer_append(&b, "\x1b[?25h", 6);

	// write contents of the buffer
	(void) write(STDOUT_FILENO, b.buf, b.len);
	Buffer_reset(&b);
}

void
screen_draw_rows(Screen *screen, Buffer *buffer)
{
	int y;
	const char *msg = "TED - Text EDitor";

	for (y = 0; y < screen->rows; y++) {
		if (y == screen->rows / 3) {
			screen_draw_welcome(screen, buffer, msg,
				(int) strlen(msg));
		} else {
			Buffer_append(buffer, "~", 1);
		}

		Buffer_append(buffer, "\x1b[K", 3);
		if (y < screen->rows - 1) {
			Buffer_append(buffer, "\r\n", 2);
		}
	}
}

void
screen_draw_welcome(Screen *screen, Buffer *buffer, const char *msg, int len)
{
	if (len > screen->cols) {
		len = screen->cols;
	}
	int pad = (screen->cols - len) / 2;
	if (pad >= 1) {
		Buffer_append(buffer, "~", 1);
		pad--;
	}
	while (pad-- >= 1) {
		Buffer_append(buffer, " ", 1);
	}
	Buffer_append(buffer, msg, len);
}
