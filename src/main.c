#include "editor_state.h"
#include "key.h"
#include "term_control.h"
#include "util.h"

int
main(void)
{
	struct editor_state state;
	if (screen_get_size(&state.screen) == -1) {
		die("screen_get_size");
	}
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

	for (;;) {
		screen_refresh(&state.screen, &state.cursor);
		if (key_process(&state, key_read()) != 0) {
			break;
		}
	}

	cleanup();
	termios_set(&state.termios);

	return 0;
}
