#include "squirrel_keys.h"
#include <stdbool.h>
#include <stdint.h>

// active_keycodes is a list of all keycodes that are currently active.
bool active_keycodes[256] = {false};
// media_commands is a list of all media commands that are currently active.
// Limited to the first 256 media commands, as later commands are extremely
// uncommon, see: https://www.freebsddiary.org/APC/usb_hid_usages.php - Consumer
bool media_commands[256] = {false};
// modifiers is a bitfield of all active modifiers.
uint_fast8_t modifiers = 0;
