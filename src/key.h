#pragma once

#include "editor_state.h"

#define CTRL_KEY(k) ((k) &0x1f)
#define VT_ESC      '\x1b'

enum keycode {
	ARROW_UP = 1000,
	ARROW_DOWN,
	ARROW_RIGHT,
	ARROW_LEFT,
	PAGE_UP,
	PAGE_DOWN,
	HOME_KEY,
	END_KEY,
	DEL_KEY,
};

int key_read(void);
int key_process(struct editor_state *, int);
