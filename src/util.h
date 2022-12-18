#ifndef TED_UTIL_H
#define TED_UTIL_H

#include <stdbool.h>

#define BETWEEN(x, low, high) (low <= x && x <= high)

void cleanup(void);
void die(const char *);

#endif // TED_UTIL_H
