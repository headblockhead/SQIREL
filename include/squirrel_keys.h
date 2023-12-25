#ifndef SQUIREL_KEYS_H
#define SQUIREL_KEYS_H
#include <stdbool.h>
#include <stdint.h>

// active_keycodes is a list of all the keycodes that are currently pressed,
// these should be sent to the host with every keyboard HID report.
extern bool active_keycodes[256];

// modifiers is a bitfield of all the modifier keys that are currently pressed.
// This should also be sent to the host with all keyboard HID reports.
extern uint_fast8_t modifiers;
#endif
