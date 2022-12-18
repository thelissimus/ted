#include <stdio.h>
#include <stdlib.h>

#include "term_control.h"
#include "util.h"

void
cleanup(void)
{
	term_clear();
	term_reset_cursor();
}

void
die(const char *s)
{
	cleanup();
	perror(s);
	exit(1);
}
