#include "squirrel_keyboard.h"
#include <stdbool.h>
#include <stdint.h>

bool keycodes[256] = {false};
uint8_t modifiers = 0;

void activate_keycode(uint8_t keycode) { keycodes[keycode] = true; }
void deactivate_keycode(uint8_t keycode) { keycodes[keycode] = false; }
int get_active_keycodes(uint8_t *active_keycodes) {
  uint8_t active_keycodes_index = 0;
  for (uint8_t i = 0; i != 255; i++) {
    if (!keycodes[i]) {
      continue;
    }
    active_keycodes[active_keycodes_index] = i;
    active_keycodes_index++;
  }
  return active_keycodes_index;
}

void activate_modifier(uint8_t modifier) { modifiers |= modifier; }
void deactivate_modifier(uint8_t modifier) { modifiers &= ~modifier; }
uint8_t get_active_modifiers() { return modifiers; }
