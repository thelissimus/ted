#include <errno.h>
#include <unistd.h>

#include "editor_state.h"
#include "key.h"
#include "util.h"

int
key_read(void)
{
	ssize_t n;
	char ch;
	while ((n = read(STDIN_FILENO, &ch, 1)) != 1) {
		if (n == -1 && errno != EAGAIN) {
			die("read");
		}
	}
	if (ch != VT_ESC) {
		return ch;
	}

	char seq[3];
	if (read(STDIN_FILENO, seq, 2) != 2) {
		return VT_ESC;
	}

	if (seq[0] != '[') {
		return VT_ESC;
	} else if (seq[0] == 'O') {
		switch (seq[1]) {
		case 'H':
			return HOME_KEY;
		case 'F':
			return END_KEY;
		}
	}

	if (BETWEEN(seq[1], '0', '9')) {
		if (read(STDIN_FILENO, &seq[2], 1) != 1) {
			return VT_ESC;
		}
		if (seq[2] != '~') {
			return VT_ESC;
		}
		switch (seq[1]) {
		case '5':
			return PAGE_UP;
		case '6':
			return PAGE_DOWN;
		case '1':
		case '7':
			return HOME_KEY;
		case '4':
		case '8':
			return END_KEY;
		case '3':
			return DEL_KEY;
		}
		return VT_ESC;
	}

	switch (seq[1]) {
	case 'A':
		return ARROW_UP;
	case 'B':
		return ARROW_DOWN;
	case 'C':
		return ARROW_RIGHT;
	case 'D':
		return ARROW_LEFT;
	case 'H':
		return HOME_KEY;
	case 'F':
		return END_KEY;
	}

	return VT_ESC;
}

int
key_process(struct editor_state *st, int key)
{
	switch (key) {
	case CTRL_KEY('q'):
		return 1;

	case 'k':
	case ARROW_UP:
		cursor_move(&st->cursor, CURSOR_UP, 1);
		break;
	case 'j':
	case ARROW_DOWN:
		cursor_move(&st->cursor, CURSOR_DOWN, 1);
		break;

	case 'l':
	case ARROW_RIGHT:
		cursor_move(&st->cursor, CURSOR_RIGHT, 1);
		break;

	case 'h':
	case ARROW_LEFT:
		cursor_move(&st->cursor, CURSOR_LEFT, 1);
		break;

	case PAGE_UP:
		cursor_move(&st->cursor, CURSOR_UP, st->cursor.y);
		break;

	case PAGE_DOWN:
		cursor_move(&st->cursor, CURSOR_DOWN,
			st->screen.rows - 1 - st->cursor.y);
		break;

	case HOME_KEY:
		cursor_move(&st->cursor, CURSOR_LEFT, st->cursor.x);
		break;

	case END_KEY:
		cursor_move(&st->cursor, CURSOR_RIGHT,
			st->screen.cols - 1 - st->cursor.x);
		break;

	default:
		break;
	}
	return 0;
}
