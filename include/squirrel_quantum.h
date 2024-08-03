#ifndef SQUIRREL_QUANTUM_H
#define SQUIRREL_QUANTUM_H

#include "squirrel.h"
#include "squirrel_keyboard.h"
#include <stdarg.h>
#include <stdint.h>

// noop is a function that does nothing, can be used as a placeholder.
void noop(struct key *key, ...);

// keyboard_press is a function that activates a keycode on the keyboard.
void keyboard_press(struct key *key, uint8_t keycode);

// keyboard_release is a function that deactivates a keycode on the keyboard.
void keyboard_release(struct key *key, uint8_t keycode);

#endif
