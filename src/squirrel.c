#include <stdbool.h>
#include <stdint.h>

#include "squirrel.h"

// execute_key_rising executes the rising function of the key on the topmost
// active layer (above the default layer).
void execute_key_rising(struct key *key) {
  for (uint_fast8_t i = 15; i >= default_layer; i--) {
    if (!layers[i]) {
      continue;
    }
    key->rising[i](key, key->risingargs[i], i);
  }
}

// execute_key_falling executes the falling function of the key on the topmost
// active layer (above the default layer).
void execute_key_falling(struct key *key) {
  for (uint_fast8_t i = 15; i >= default_layer; i--) {
    if (!layers[i]) {
      continue;
    }
    key->falling[i](key, key->fallingargs[i], i);
  }
}
