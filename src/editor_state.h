#pragma once

#include <termios.h>

#include "row.h"
#include "screen.h"

struct editor_state {
	struct screen screen;
	struct cursor cursor;
	struct termios termios;
	struct editor_rows rows;
};
