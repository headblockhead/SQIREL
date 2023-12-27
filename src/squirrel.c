#include "squirrel.h"
#include <stdlib.h>

void execute_key_rising(struct key *key) {
  for (uint_fast8_t i = 15; i >= default_layer;
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
  for (uint_fast8_t i = 15; i >= default_layer;
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
  if (key_is_pressed &&
      !key->pressed) {   // If the key is pressed, but wasn't pressed before:
    key->pressed = true; // Mark the key as pressed.
    execute_key_rising(key); // Execute the key's rising function.
  } else if (!key_is_pressed && key->pressed) { // If the key is not pressed,
                                                // but was pressed before:
    key->pressed = false;                       // Mark the key as not pressed.
    execute_key_falling(key);                   // Execute the key's falling
                                                // function.
  }
}
