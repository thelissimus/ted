#pragma once

#include <termios.h>

#include "screen.h"

typedef struct {
	Screen screen;
	Cursor cursor;
	struct termios initial_termios;
} Config;
