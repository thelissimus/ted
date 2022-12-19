#pragma once

#include "config.h"

#define CTRL_KEY(k) ((k) &0x1f)

char key_read(void);
int key_process(Config *, char);
