#include <errno.h>
#include <unistd.h>

#include "config.h"
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
key_process(Config *config, int key)
{
	switch (key) {
	case CTRL_KEY('q'):
		return 1;
	case 'k':
	case ARROW_UP:
		Cursor_move(&config->cursor, CURSOR_UP, 1);
		break;
	case 'j':
	case ARROW_DOWN:
		Cursor_move(&config->cursor, CURSOR_DOWN, 1);
		break;
	case 'l':
	case ARROW_RIGHT:
		Cursor_move(&config->cursor, CURSOR_RIGHT, 1);
		break;
	case 'h':
	case ARROW_LEFT:
		Cursor_move(&config->cursor, CURSOR_LEFT, 1);
		break;
	case PAGE_UP:
		Cursor_move(&config->cursor, CURSOR_UP, config->cursor.y);
		break;
	case PAGE_DOWN:
		Cursor_move(&config->cursor, CURSOR_DOWN,
			config->screen.rows - 1 - config->cursor.y);
		break;
	case HOME_KEY:
		Cursor_move(&config->cursor, CURSOR_LEFT, config->cursor.x);
		break;
	case END_KEY:
		Cursor_move(&config->cursor, CURSOR_RIGHT,
			config->screen.cols - 1 - config->cursor.x);
		break;
	default:
		break;
	}
	return 0;
}
