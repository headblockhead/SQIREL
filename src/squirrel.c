#include "squirrel.h"
#include <stdlib.h>

void execute_key_rising(struct key *key) {
  for (uint8_t i = 15; i >= default_layer;
       i--) {         // Loop through all layers, top to bottom.
    if (!layers[i]) { // If the layer is not active, skip it.
      continue;
    }
    key->rising[i](key, key->risingargs[i],
                   i); // Execute the key's rising function.
    return;
  }
}

void execute_key_falling(struct key *key) {
  for (uint8_t i = 15; i >= default_layer;
       i--) {         // Loop through all layers, top to bottom.
    if (!layers[i]) { // If the layer is not active, skip it.
      continue;
    }
    key->falling[i](key, key->fallingargs[i],
                    i); // Execute the key's falling function.
    return;             // Stop looping through layers.
  }
}

void check_key(struct key *key, bool key_is_pressed) {
  if (key->pressed == key_is_pressed) {
    return; // If the key's state hasn't changed, do nothing.
  }
  if (key_is_pressed) {
    execute_key_rising(key); // Execute the key's rising function.
  } else {
    execute_key_falling(key); // Execute the key's falling function.
  }
  key->pressed = key_is_pressed; // Update the key's state.
}
