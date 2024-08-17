#include "squirrel.h"
#include "squirrel_keyboard.h"
#include "squirrel_quantum.h"

// test: keyboard_press + keyboard_release end-to-end test in squirrel_quantum.c
int main() {
  // keyboard_press
  struct key test_key;
  for (uint8_t i = 0; i <= 255; i++) {
    // FALSE becomes TRUE
    for (uint8_t j = 0; j <= 255; j++) {
      keycodes[j] = false;
    }
    keyboard_press(&test_key, i);
    if (keycodes[i] == false) {
      return 1;
    }

    // TRUE stays TRUE
    for (uint8_t j = 0; j <= 255; j++) {
      keycodes[j] = true;
    }
    keyboard_press(&test_key, i);
    if (keycodes[i] == false) {
      return 2;
    }
  };

  // keyboard_release
  for (uint8_t i = 0; i <= 255; i++) {
    // TRUE becomes FALSE
    for (uint8_t j = 0; j <= 255; j++) {
      keycodes[j] = true;
    }
    keyboard_release(&test_key, i);
    if (keycodes[i] == true) {
      return 3;
    }
    // FALSE stays FALSE
    for (uint8_t j = 0; j <= 255; j++) {
      keycodes[j] = false;
    }
    keyboard_release(&test_key, i);
    if (keycodes[i] == true) {
      return 4;
    }
  };
  return 0;
};
