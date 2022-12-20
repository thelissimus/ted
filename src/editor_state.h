#pragma once

#include <termios.h>

#include "screen.h"

struct editor_state {
	struct screen screen;
	struct cursor cursor;
	struct termios termios;
};
