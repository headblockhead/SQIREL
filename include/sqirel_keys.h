#ifndef SQUIREL_CORE_H
#define SQUIREL_CORE_H
#include <stdbool.h>
#include <stdint.h>

// active_keycodes is a list of all the keycodes that are currently pressed,
// these should be sent to the host with every keyboard HID report.
bool active_keycodes[256] = {};

// modifiers is a bitfield of all the modifier keys that are currently pressed.
// This should also be sent to the host with all keyboard HID reports.
uint_fast8_t modifiers = 0;
#endif
