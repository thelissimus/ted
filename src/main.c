#include "editor_state.h"
#include "key.h"
#include "term_control.h"
#include "util.h"

int
main(int argc, char *argv[])
{
	struct editor_state state;

	if (screen_get_size(&state.screen) == -1) {
		die("screen_get_size");
	}
	state.rows = editor_rows_init();
	state.cursor = (struct cursor) {
		.x = 0,
		.y = 0,
		.x_min = 0,
		.y_min = 0,
		.x_max = state.screen.cols,
		.y_max = state.screen.rows,
	};
	termios_get(&state.termios);
	raw_mode_on(&state.termios);
	if (argc >= 2) {
		if (editor_rows_readfile(&state.rows, argv[1]) != 0) {
			die("editor_rows_readfile");
		}
	}

	for (;;) {
		screen_refresh(&state.screen, &state.cursor, &state.rows);
		if (key_process(&state, key_read()) != 0) {
			break;
		}
	}

	termios_set(&state.termios);
	editor_rows_reset(&state.rows);
	cleanup();

	return 0;
}
