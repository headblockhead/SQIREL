#include "squirrel_keys.h"
#include <stdbool.h>
#include <stdint.h>

// active_keycodes is a list of all keycodes that are currently active.
bool active_keycodes[256] = {false};
// the current active media code, or 0 if none.
// see: https://www.freebsddiary.org/APC/usb_hid_usages.php - Consumer
uint16_t active_media_code = 0;
// modifiers is a bitfield of all active modifiers.
uint8_t modifiers = 0;
