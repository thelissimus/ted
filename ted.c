#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#define CTRL_KEY(k)	((k) & 0x1f)

typedef struct {
	int rows;
	int cols;
} Screen;

typedef struct {
	Screen screen;
	struct termios orig_termios;
} Config;

Config config;

char key_read(void);
void key_process(char);

int screen_get_size(int *, int *);
int screen_get_cursor_pos(int *, int *);
void screen_reset_cursor(void);
void screen_clear(void);
void screen_refresh(void);
void screen_draw_rows(void);

void raw_mode_on(void);
void raw_mode_off(void);

void die(const char *);

int main(void)
{
	if (screen_get_size(&config.screen.rows, &config.screen.cols) == -1) {
		die("screen_get_size");
	}
	raw_mode_on();

	for (;;) {
		screen_refresh();
		key_process(key_read());
	}

	return 0;
}

int screen_get_size(int *rows, int *cols)
{
	struct winsize ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
		if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) {
			return -1;
		}
		return screen_get_cursor_pos(rows, cols);
	}

	*rows = ws.ws_row;
	*cols = ws.ws_col;

	return 0;
}

int screen_get_cursor_pos(int *rows, int *cols)
{
	#define R_BUFSIZ 32
	char buf[R_BUFSIZ];
	unsigned int i = 0;

	if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) {
		return -1;
	}

	for (; i < R_BUFSIZ - 1; i++) {
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
	if (sscanf(&buf[2], "%d;%d", rows, cols) != 2) {
		return -1;
	}

	return 0;
	#undef R_BUFSIZ
}

char key_read(void)
{
	int n;
	char ch;
	while ((n = read(STDIN_FILENO, &ch, 1)) != 1) {
		if (n == -1 && errno != EAGAIN) {
			die("read");
		}
	}
	return ch;
}

void key_process(char ch)
{
	switch (ch) {
	case CTRL_KEY('q'):
		screen_clear();
		screen_reset_cursor();
		exit(0);
		break;
	}
}

void screen_clear(void)
{
	(void) write(STDOUT_FILENO, "\x1b[2J", 4);
}

void screen_reset_cursor(void)
{
	(void) write(STDOUT_FILENO, "\x1b[H", 3);
}

void screen_refresh(void)
{
	screen_clear();
	screen_draw_rows();
	screen_reset_cursor();
}

void screen_draw_rows(void)
{
	int y;
	for (y = 0; y < config.screen.rows; y++) {
		(void) write(STDOUT_FILENO, "~", 1);
		if (y < config.screen.rows - 1) {
			(void) write(STDOUT_FILENO, "\r\n", 2);
		}
	}
}

void raw_mode_on(void)
{
	if (tcgetattr(STDIN_FILENO, &config.orig_termios) == -1) {
		die("tcgetattr");
	}
	atexit(raw_mode_off);

	struct termios raw = config.orig_termios;
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cflag |= CS8;
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;

	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
		die("tcsetattr");
	}
}

void raw_mode_off(void)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &config.orig_termios) == -1) {
		die("tcsetattr");
	}
}

void die(const char *s)
{
	screen_clear();
	screen_reset_cursor();
	perror(s);
	exit(1);
}
