// SQUIRREL_KEYBOARD_H provides an interface for interacting as a USB Keyboard.
#ifndef SQUIRREL_KEYBOARD_H
#define SQUIRREL_KEYBOARD_H

#include <stdbool.h>
#include <stdint.h>

extern bool keyboard_keycodes[256];
extern uint8_t keyboard_modifiers;

// keyboard_activate_keycode marks the provided keycode as active.
void keyboard_activate_keycode(uint8_t keycode);
// keyboard_deactivate_keycode marks the provided keycode as inactive.
void keyboard_deactivate_keycode(uint8_t keycode);
// keyboard_get_keycodes populates the provided array with the first 6 active
// keycodes. 6 is the maximum number of keycodes that
// can be sent over USB HID. It also returns true if there are any active
// keycodes.
bool keyboard_get_keycodes(uint8_t (*active_keycodes)[6]);

// keyboard_activate_modifier marks the provided modifier as active.
void keyboard_activate_modifier(uint8_t modifier);
// keyboard_deactivate_modifier marks the provided modifier as inactive.
void keyboard_deactivate_modifier(uint8_t modifier);
// keyboard_get_modifiers returns a bitfield of active modifiers.
uint8_t keyboard_get_modifiers();

#endif
