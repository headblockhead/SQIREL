#include "squirrel.h"
#include "squirrel_quantum.h"

// test: keyboard_press + keyboard_release test - in squirrel_quantum.c
int main() {
  // keyboard_press
  struct key test_key; // values unused
  for (uint8_t keycode; keycode <= 127; keycode++) {
    // Off becomes on
    keycodes[keycode] = false;
    keyboard_press(&test_key, 0, 0, 1, keycode);
    if (keycodes[keycode] != true) {
      return 1;
    }
    // On stays on
    keyboard_press(&test_key, 0, 0, 1, keycode);
    if (keycodes[keycode] != true) {
      return 2;
    }

    // On becomes off
    keycodes[keycode] = true;
    keyboard_release(&test_key, 0, 0, 1, keycode);
    if (keycodes[keycode] != false) {
      return 3;
    }
    // Off stays off
    keyboard_release(&test_key, 0, 0, 1, keycode);
    if (keycodes[keycode] != false) {
      return 4;
    }
  }
  return 0;
};
