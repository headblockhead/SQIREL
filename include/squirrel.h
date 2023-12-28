#ifndef SQUIRREL_H
#define SQUIRREL_H
#include "squirrel_keys.h"
#include "squirrel_quantum.h"
#include "squirrel_types.h"

// Execute the rising function of the key on the highest active layer.
void execute_key_rising(struct key *key, bool *layers[16],
                        uint_fast8_t *default_layer);

// Execute the falling function of the key on the highest active layer.
void execute_key_falling(struct key *key, bool *layers[16],
                         uint_fast8_t *default_layer);

// Check if a key is pressed or not, and compare it to its previous state. Then
// execute the key's rising or falling function if necessary.
void check_key(struct key *key, bool key_is_pressed, bool *layers[16],
               uint_fast8_t *default_layer);
#endif
