#include <stdio.h>
#include <stdlib.h>

#include "term_control.h"
#include "util.h"

bool
between(int x, int a, int b)
{
	return (a <= x && x <= b) || (b <= x && x <= a);
}

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
