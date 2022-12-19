#pragma once

#include <stdbool.h>

#define BETWEEN(x, low, high) (low <= x && x <= high)

void cleanup(void);
void die(const char *);
