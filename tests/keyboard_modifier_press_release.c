#include "squirrel.h"
#include "squirrel_key.h"
#include "squirrel_quantum.h"
#include <stdint.h>
#include <stdlib.h>

// test: keyboard_modifier_press + keyboard_modifier_release test - in
// squirrel_quantum.c
int main() {
  struct key test_key; // values unused
  // keyboard_modifier_press

  // no modifiers adding no modifiers is no modifiers
  uint8_t current_modifier = 0b00000000;
  keyboard_modifiers = 0;
  enum squirrel_error err = keyboard_modifier_press(0, 0, &current_modifier);
  if (err != ERR_NONE) {
    return 255;
  }
  if (keyboard_modifiers != 0b00000000) {
    return 1;
  }

  // no modifiers adding a modifier is a modifier
  current_modifier = 0b00000001;
  for (uint8_t i = 0; i < 8; i++) {
    keyboard_modifiers = 0;
    enum squirrel_error err = keyboard_modifier_press(0, 0, &current_modifier);
    if (err != ERR_NONE) {
      return 255;
    }
    if (keyboard_modifiers != current_modifier) {
      return 2;
    }
    current_modifier = current_modifier << 1;
  }

  // a modifier adding a modifier is more than one modifier
  current_modifier = 0b00000001;
  for (uint8_t i = 0; i < 8; i++) {
    // modifiers stack, ORd to become the same number
    uint8_t old_modifiers = keyboard_modifiers;
    enum squirrel_error err = keyboard_modifier_press(0, 0, &current_modifier);
    if (err != ERR_NONE) {
      return 255;
    }
    if (keyboard_modifiers != (old_modifiers | current_modifier)) {
      return 3;
    }
    current_modifier = current_modifier << 1;
  }

  // keyboard_modifier_release

  // no modifiers removing no modifiers is no modifiers
  current_modifier = 0b00000000;
  keyboard_modifiers = 0;
  err = keyboard_modifier_release(0, 0, &current_modifier);
  if (err != ERR_NONE) {
    return 255;
  }
  if (keyboard_modifiers != 0b00000000) {
    return 4;
  }

  // a modifier removing a modifier is no modifiers
  current_modifier = 0b00000001;
  for (uint8_t i = 0; i < 8; i++) {
    keyboard_modifiers = current_modifier;
    enum squirrel_error err =
        keyboard_modifier_release(0, 0, &current_modifier);
    if (err != ERR_NONE) {
      return 255;
    }
    if (keyboard_modifiers != 0b000000000) {
      return 5;
    }
    current_modifier = current_modifier << 1;
  }

  // more than one modifier removing a modifier is less modifiers.
  current_modifier = 0b00000001;
  keyboard_modifiers = 0b11111111;
  for (uint8_t i = 0; i < 8; i++) {
    // modifiers stack, ORd to become the same number
    uint8_t old_modifiers = keyboard_modifiers;
    enum squirrel_error err =
        keyboard_modifier_release(0, 0, &current_modifier);
    if (err != ERR_NONE) {
      return 255;
    }
    if (keyboard_modifiers != (old_modifiers & ~current_modifier)) {
      return 6;
    }
    current_modifier = current_modifier << 1;
  }

  return 0;
};
