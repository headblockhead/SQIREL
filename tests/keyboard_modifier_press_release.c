#include "squirrel.h"
#include "squirrel_quantum.h"

// test: keyboard_modifier_press + keyboard_modifier_release test - in
// squirrel_quantum.c
int main() {
  struct key test_key; // values unused

  // keyboard_modifier_press

  // no modifiers adding no modifiers is no modifiers
  uint8_t current_modifier = 0b00000000;
  modifiers = 0;
  keyboard_modifier_press(&test_key, 0, 0, 1, current_modifier);
  if (modifiers != 0b00000000) {
    return 1;
  }

  // no modifiers adding a modifier is a modifier
  current_modifier = 0b00000001;
  for (uint8_t i = 0; i < 8; i++) {
    modifiers = 0;
    keyboard_modifier_press(&test_key, 0, 0, 1, current_modifier);
    if (modifiers != current_modifier) {
      return 2;
    }
    current_modifier = current_modifier << 1;
  }

  // a modifier adding a modifier is more than one modifier
  current_modifier = 0b00000001;
  for (uint8_t i = 0; i < 8; i++) {
    // modifiers stack, ORd to become the same number
    uint8_t old_modifiers = modifiers;
    keyboard_modifier_press(&test_key, 0, 0, 1, current_modifier);
    if (modifiers != (old_modifiers | current_modifier)) {
      return 3;
    }
    current_modifier = current_modifier << 1;
  }

  // keyboard_modifier_release

  // no modifiers removing no modifiers is no modifiers
  current_modifier = 0b00000000;
  modifiers = 0;
  keyboard_modifier_release(&test_key, 0, 0, 1, current_modifier);
  if (modifiers != 0b00000000) {
    return 4;
  }

  // a modifier removing a modifier is no modifiers
  current_modifier = 0b00000001;
  for (uint8_t i = 0; i < 8; i++) {
    modifiers = current_modifier;
    keyboard_modifier_release(&test_key, 0, 0, 1, current_modifier);
    if (modifiers != 0b000000000) {
      return 5;
    }
    current_modifier = current_modifier << 1;
  }

  // more than one modifier removing a modifier is less modifiers.
  current_modifier = 0b00000001;
  modifiers = 0b11111111;
  for (uint8_t i = 0; i < 8; i++) {
    // modifiers stack, ORd to become the same number
    uint8_t old_modifiers = modifiers;
    keyboard_modifier_release(&test_key, 0, 0, 1, current_modifier);
    if (modifiers != (old_modifiers & ~current_modifier)) {
      return 6;
    }
    current_modifier = current_modifier << 1;
  }

  return 0;
};
