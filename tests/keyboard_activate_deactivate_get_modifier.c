#include "squirrel.h"
#include "squirrel_consumer.h"
#include "squirrel_key.h"
#include "squirrel_quantum.h"
#include <stdint.h>
#include <stdlib.h>

// test: keyboard_activate_modifier + keyboard_deactivate_modifier +
// keyboard_get_modifiers - in squirrel_keyboard.c
int main() {
  for (uint8_t test_modifier = 0b00000001; test_modifier != 0b00000000;
       test_modifier = test_modifier << 1) {
    for (uint8_t test_modifier_2 = 0b10000000; test_modifier_2 != 0b00000000;
         test_modifier_2 = test_modifier_2 >> 1) {
      if (test_modifier == test_modifier_2) { // Skip if the same modifier
        continue;
      }
      keyboard_activate_modifier(test_modifier);
      if (keyboard_get_modifiers() != test_modifier) {
        return 1;
      }
      keyboard_activate_modifier(test_modifier_2);
      if (keyboard_get_modifiers() != (test_modifier | test_modifier_2)) {
        return 2;
      }
      // keyboard_deactivate_modifier
      keyboard_deactivate_modifier(test_modifier);
      if (keyboard_get_modifiers() != test_modifier_2) {
        return 3;
      }
      keyboard_deactivate_modifier(test_modifier_2);
      if (keyboard_get_modifiers() != 0) {
        return 4;
      }
    }
  }
};
