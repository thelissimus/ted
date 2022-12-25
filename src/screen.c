#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>

#include "screen.h"
#include "term_control.h"

static void screen_draw_welcome(const struct screen *, struct buffer *,
	const char *, int);
static void screen_scroll(const struct screen *, const struct cursor *,
	struct editor_rows *);

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
screen_refresh(const struct screen *scr, const struct cursor *csr,
	struct editor_rows *rws)
{
	struct buffer b = buffer_init();

	screen_scroll(scr, csr, rws);
	// hide cursor and move it home
	buffer_append(&b, "\x1b[?25l", 6);
	buffer_append(&b, "\x1b[H", 3);
	// draw main content
	screen_draw_rows(scr, &b, rws);
	// move cursor
	char cpos[32];
	int cpos_l = term_set_cursor_pos(cpos, sizeof cpos,
		(int) (csr->x - rws->col_offset),
		(int) (csr->y - rws->row_offset));
	buffer_append(&b, cpos, cpos_l);
	// show cursor
	buffer_append(&b, "\x1b[?25h", 6);
	// write contents of the buffer
	(void) write(STDOUT_FILENO, b.buf, b.len);
	buffer_reset(&b);
}

void
screen_draw_rows(const struct screen *scr, struct buffer *buf,
	const struct editor_rows *rws)
{
	int y;
	size_t cur_row;
	ssize_t col_len;
	const char *msg = "TED - Text EDitor";

	for (y = 0; y < scr->rows; y++) {
		cur_row = y + rws->row_offset;

		if ((size_t) y < rws->count) {
			col_len = (ssize_t) (rws->rows[cur_row].length
				- rws->col_offset);
			if (col_len < 0) {
				col_len = 0;
			}
			if (col_len > scr->cols) {
				col_len = scr->cols;
			}
			buffer_append(buf,
				&rws->rows[cur_row].content[rws->col_offset],
				col_len);
		} else {
			if (rws->count == 0 && y == scr->rows / 3) {
				screen_draw_welcome(scr, buf, msg,
					(int) strlen(msg));
			} else {
				buffer_append(buf, "~", 1);
			}
		}

		buffer_append(buf, "\x1b[K", 3);
		if (y < scr->rows - 1) {
			buffer_append(buf, "\r\n", 2);
		}
	}
}

void
screen_draw_welcome(const struct screen *scr, struct buffer *buf,
	const char *msg, int len)
{
	if (len > scr->cols) {
		len = scr->cols;
	}
	int pad = (scr->cols - len) / 2;
	if (pad >= 1) {
		buffer_append(buf, "~", 1);
		pad--;
	}
	while (pad-- >= 1) {
		buffer_append(buf, " ", 1);
	}
	buffer_append(buf, msg, len);
}

void
screen_scroll(const struct screen *scr, const struct cursor *csr,
	struct editor_rows *rws)
{
	// horizontal
	if (csr->x < rws->col_offset) {
		rws->col_offset = csr->x;
	} else if (csr->x >= rws->col_offset + scr->cols - 1) {
		rws->col_offset = csr->x - scr->cols + 1;
	}

	// vertical
	if (csr->y < rws->row_offset) {
		rws->row_offset = csr->y;
	} else if (csr->y >= rws->row_offset + scr->rows - 1) {
		rws->row_offset = csr->y - scr->rows + 1;
	}
}
