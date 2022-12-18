#include "config.h"
#include "key.h"
#include "term_control.h"
#include "util.h"

int
main(void)
{
	Config config;
	if (screen_get_size(&config.screen) == -1) {
		die("screen_get_size");
	}
	config.cursor = (Cursor) {
		.x = 0,
		.y = 0,
		.x_min = 0,
		.y_min = 0,
		.x_max = config.screen.cols,
		.y_max = config.screen.rows,
	};
	termios_get(&config.initial_termios);
	raw_mode_on(&config.initial_termios);

	for (;;) {
		screen_refresh(&config.screen, &config.cursor);
		if (key_process(&config, key_read()) != 0) {
			break;
		}
	}

	cleanup();
	termios_set(&config.initial_termios);

	return 0;
}
