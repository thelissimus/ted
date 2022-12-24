#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>

#include "screen.h"
#include "term_control.h"

void screen_draw_welcome(const struct screen *, struct buffer *, const char *,
	int);

int
screen_get_size(struct screen *s)
{
	struct winsize ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != -1 || ws.ws_col != 0) {
		s->rows = ws.ws_row;
		s->cols = ws.ws_col;
		return 0;
	}

	// fallback method of getting cursor position
	if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) {
		return -1;
	}
	return term_get_cursor_pos(&s->rows, &s->cols);
}

void
screen_refresh(const struct screen *s, const struct cursor *c,
	const struct editor_rows *e)
{
	struct buffer b = buffer_init();

	// hide cursor and move it home
	buffer_append(&b, "\x1b[?25l", 6);
	buffer_append(&b, "\x1b[H", 3);
	// draw main content
	screen_draw_rows(s, &b, e);
	// move cursor
	char cpos[32];
	int cpos_l = term_set_cursor_pos(cpos, sizeof cpos, c->x, c->y);
	buffer_append(&b, cpos, cpos_l);
	// show cursor
	buffer_append(&b, "\x1b[?25h", 6);
	// write contents of the buffer
	(void) write(STDOUT_FILENO, b.buf, b.len);
	buffer_reset(&b);
}

void
screen_draw_rows(const struct screen *s, struct buffer *b,
	const struct editor_rows *e)
{
	int y;
	const char *msg = "TED - Text EDitor";

	for (y = 0; y < s->rows; y++) {
		if ((size_t) y < e->count) {
			size_t len = e->rows[y].length;
			if (len > (size_t) s->cols) {
				len = s->cols;
			}
			buffer_append(b, e->rows[y].content, len);
		} else {
			if (e->count == 0 && y == s->rows / 3) {
				screen_draw_welcome(s, b, msg,
					(int) strlen(msg));
			} else {
				buffer_append(b, "~", 1);
			}
		}

		buffer_append(b, "\x1b[K", 3);
		if (y < s->rows - 1) {
			buffer_append(b, "\r\n", 2);
		}
	}
}

void
screen_draw_welcome(const struct screen *s, struct buffer *b, const char *msg,
	int len)
{
	if (len > s->cols) {
		len = s->cols;
	}
	int pad = (s->cols - len) / 2;
	if (pad >= 1) {
		buffer_append(b, "~", 1);
		pad--;
	}
	while (pad-- >= 1) {
		buffer_append(b, " ", 1);
	}
	buffer_append(b, msg, len);
}
