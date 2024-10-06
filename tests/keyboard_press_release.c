#include "squirrel.h"
#include "squirrel_key.h"
#include "squirrel_quantum.h"
#include <stdint.h>
#include <stdlib.h>

// test: keyboard_press + keyboard_release - in squirrel_quantum.c
int main() {
  struct key test_key; // values unused
  enum squirrel_error err;
  for (uint8_t keycode = 0; keycode != 255; keycode++) {
    // keyboard_press
    // Off becomes on
    keyboard_keycodes[keycode] = false;
    err = keyboard_press(&test_key, 0, 0, &keycode);
    if (err != ERR_NONE) {
      return 1;
    }
    if (keyboard_keycodes[keycode] != true) {
      return 2;
    }
    // On stays on
    err = keyboard_press(&test_key, 0, 0, &keycode);
    if (err != ERR_NONE) {
      return 3;
    }
    if (keyboard_keycodes[keycode] != true) {
      return 4;
    }

    // keyboard_release
    // On becomes off
    keyboard_keycodes[keycode] = true;
    err = keyboard_release(&test_key, 0, 0, &keycode);
    if (err != ERR_NONE) {
      return 5;
    }
    if (keyboard_keycodes[keycode] != false) {
      return 6;
    }
    // Off stays off
    err = keyboard_release(&test_key, 0, 0, &keycode);
    if (err != ERR_NONE) {
      return 7;
    }
    if (keyboard_keycodes[keycode] != false) {
      return 8;
    }
  }
  return 0;
};
