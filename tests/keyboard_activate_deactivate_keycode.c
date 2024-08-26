#include "squirrel.h"
#include "squirrel_consumer.h"
#include "squirrel_key.h"
#include "squirrel_quantum.h"
#include <stdint.h>
#include <stdlib.h>

// test: keyboard_activate_keycode + keyboard_deactivate_keycode in
// squirrel_keyboard.c
int main() {
  for (uint8_t test_keycode = 0; test_keycode <= 254; test_keycode++) {
    // keyboard_activate_keycode
    keyboard_activate_keycode(test_keycode);
    if (keyboard_keycodes[test_keycode] != true) {
      return 1;
    }
    // keyboard_deactivate_keycode
    keyboard_deactivate_keycode(test_keycode);
    if (keyboard_keycodes[test_keycode] != false) {
      return 2;
    }
  }
};
