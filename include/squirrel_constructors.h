#ifndef SQUIRREL_CONSTRUCTORS_H
#define SQUIRREL_CONSTRUCTORS_H

#include "squirrel_types.h"

// Create a key struct with empty values
struct key make_key(void);

// Add a standard keycode function to the key struct for the given layer
void key_add_KC(struct key *key, uint8_t layer, uint8_t keycode);
// Add a modifier function to the key struct for the given layer
void key_add_mod(struct key *key, uint8_t layer, uint8_t modifier_code);
// Add a media function to the key struct for the given layer
void key_add_media(struct key *key, uint8_t layer, uint16_t media_code);
// Add a momentary layer switch function to the key struct for the given layer
void key_add_momentary(struct key *key, uint8_t layer, uint8_t target_layer);
// Add a pass-through function to the key struct for the given layer
void key_add_pass_through(struct key *key, uint8_t layer);
#endif
