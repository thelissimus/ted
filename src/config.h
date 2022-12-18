#ifndef TED_CONFIG_H
#define TED_CONFIG_H

#include <termios.h>

#include "screen.h"

typedef struct {
	Screen screen;
	Cursor cursor;
	struct termios initial_termios;
} Config;

#endif // TED_CONFIG_H
