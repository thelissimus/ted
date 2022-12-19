#pragma once

#include <stddef.h>
#include <termios.h>

int raw_mode_on(struct termios *);
int termios_get(struct termios *);
int termios_set(struct termios *);

int term_get_cursor_pos(int *, int *);
int term_set_cursor_pos(char *, size_t, int, int);
void term_reset_cursor(void);
void term_clear(void);
