// SQUIRREL_KEYBOARD_H provides an interface for interacting as a USB Keyboard.
#ifndef SQUIRREL_KEYBOARD_H
#define SQUIRREL_KEYBOARD_H

#include <stdbool.h>
#include <stdint.h>

extern bool keycodes[256];
extern uint8_t modifiers;

// keyboard_activate_keycode marks the provided keycode as active.
void keyboard_activate_keycode(uint8_t keycode);
// keyboard_deactivate_keycode marks the provided keycode as inactive.
void keyboard_deactivate_keycode(uint8_t keycode);
// get_active_keycodes populates the provided array with the active keycodes,
// and returns the number of active keycodes.
void keyboard_get_keycodes(uint8_t *active_keycodes);

// keyboard_activate_modifier marks the provided modifier as active.
void keyboard_activate_modifier(uint8_t modifier);
// keyboard_deactivate_modifier marks the provided modifier as inactive.
void keyboard_deactivate_modifier(uint8_t modifier);
// get_active_modifiers returns the active modifiers.
uint8_t keyboard_get_modifiers();

#endif
