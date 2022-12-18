#include <errno.h>
#include <unistd.h>

#include "config.h"
#include "key.h"
#include "util.h"

char
key_read(void)
{
	ssize_t n;
	char ch;
	while ((n = read(STDIN_FILENO, &ch, 1)) != 1) {
		if (n == -1 && errno != EAGAIN) {
			die("read");
		}
	}
	return ch;
}

int
key_process(Config *config, char ch)
{
	switch (ch) {
	case CTRL_KEY('q'):
		return 1;
	case 'h':
		Cursor_move(&config->cursor, CURSOR_LEFT);
		break;
	case 'j':
		Cursor_move(&config->cursor, CURSOR_DOWN);
		break;
	case 'k':
		Cursor_move(&config->cursor, CURSOR_UP);
		break;
	case 'l':
		Cursor_move(&config->cursor, CURSOR_RIGHT);
		break;
	default:
		break;
	}
	return 0;
}
