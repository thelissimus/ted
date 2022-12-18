#include <stdio.h>
#include <unistd.h>

#include "term_control.h"

int
raw_mode_on(struct termios *initial)
{
	struct termios raw = *initial;

	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cflag |= CS8;
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;

	return termios_set(&raw);
}

int
termios_get(struct termios *dest)
{
	return tcgetattr(STDIN_FILENO, dest);
}

int
termios_set(struct termios *src)
{
	return tcsetattr(STDIN_FILENO, TCSAFLUSH, src);
}

int
term_get_cursor_pos(int *rows, int *cols)
{
	char buf[32];
	unsigned int i = 0;

	if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) {
		return -1;
	}

	for (; i < sizeof buf - 1; i++) {
		if (read(STDIN_FILENO, &buf[i], 1) != 1) {
			break;
		}
		if (buf[i] == 'R') {
			break;
		}
	}
	buf[i] = '\0';

	if (buf[0] != '\x1b' || buf[1] != '[') {
		return -1;
	}
	// todo: safer way of parsing
	if (sscanf(&buf[2], "%d;%d", rows, cols) != 2) {
		return -1;
	}

	return 0;
}

int
term_set_cursor_pos(char *buf, size_t len, int x, int y)
{
	return snprintf(buf, len, "\x1b[%d;%dH", y + 1, x + 1);
}

void
term_clear(void)
{
	(void) write(STDOUT_FILENO, "\x1b[2J", 4);
}

void
term_reset_cursor(void)
{
	(void) write(STDOUT_FILENO, "\x1b[H", 3);
}
