#include "squirrel_keyboard.h"
#include "squirrel_split.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

bool keyboard_keycodes[256] = {false};
uint8_t keyboard_modifiers = 0;

void keyboard_activate_keycode(uint8_t keycode) {
  keyboard_keycodes[keycode] = true;
}
void keyboard_deactivate_keycode(uint8_t keycode) {
  keyboard_keycodes[keycode] = false;
}

bool keyboard_get_local_keycodes(uint8_t (*active_keycodes)[6]) {
  memset(*active_keycodes, 0, 6);
  uint8_t active_keycodes_index = 0;
  for (int i = 0; (i <= 0xFF) && active_keycodes_index < 6; i++) {
    if (!keyboard_keycodes[i]) {
      continue;
    }
    (*active_keycodes)[active_keycodes_index] = i;
    active_keycodes_index++;
  }
  return active_keycodes_index != 0;
}

bool keyboard_get_keycodes(uint8_t (*active_keycodes)[6]) {
  memset(*active_keycodes, 0, 6);
  uint8_t active_keycodes_index = 0;
  for (int i = 0; (i <= 0xFF) && active_keycodes_index < 6; i++) {
    if (!keyboard_keycodes[i] && !remote_keycodes[i]) {
      continue;
    }
    (*active_keycodes)[active_keycodes_index] = i;
    active_keycodes_index++;
  }
  return active_keycodes_index != 0;
}

void keyboard_activate_modifier(uint8_t modifier) {
  keyboard_modifiers |= modifier;
}
void keyboard_deactivate_modifier(uint8_t modifier) {
  keyboard_modifiers &= ~modifier;
}
uint8_t keyboard_get_modifiers() {
  return keyboard_modifiers | remote_modifiers;
}
uint8_t keyboard_get_local_modifiers() { return keyboard_modifiers; }
