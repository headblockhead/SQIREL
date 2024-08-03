#ifndef SQUIRREL_QUANTUM_H
#define SQUIRREL_QUANTUM_H

#include "squirrel.h"
#include "squirrel_keyboard.h"
#include <stdarg.h>
#include <stdint.h>

struct layer {
  struct key *keys; // array of keys in this layer
  bool active;      // true if this layer is currently active
};

// layers is a list of all the layers in the keyboard. 0-15 are to be used by
// the user. Don't modify layer 16 unless you know what you're doing :).
extern struct layer layers[17];

// noop is a function that does nothing, can be used as a placeholder.
void noop(struct key *key, ...);

// keyboard_press is a function that activates a keycode on the keyboard.
void keyboard_press(struct key *key, uint8_t keycode);

// keyboard_release is a function that deactivates a keycode on the keyboard.
void keyboard_release(struct key *key, uint8_t keycode);

// keyboard_modifier_press is a function that activates a modifier on the
// keyboard.
void keyboard_modifier_press(struct key *key, uint8_t modifier);

// keyboard_modifier_release is a function that deactivates a modifier on the
// keyboard.
void keyboard_modifier_release(struct key *key, uint8_t modifier);

// quantum_passthrough is a function that passes the keypress to the next layer
void quantum_passthrough_press(struct key *key, uint8_t layer,
                               uint8_t key_index);

// quantum_passthrough_release is a function that passes the keyrelease to the
// next layer
void quantum_passthrough_release(struct key *key, uint8_t layer,
                                 uint8_t key_index);

#endif
