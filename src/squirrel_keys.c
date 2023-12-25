#include "squirrel_keys.h"
#include <stdbool.h>
#include <stdint.h>

bool active_keycodes[256] = {false};
uint_fast8_t modifiers = 0;
