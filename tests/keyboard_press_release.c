#include "squirrel.h"
#include "squirrel_key.h"
#include "squirrel_quantum.h"
#include <stdint.h>
#include <stdlib.h>

// test: keyboard_press + keyboard_release - in squirrel_quantum.c
int main() {
  struct key test_key; // values unused
  enum squirrel_error err;
  void **args = malloc(sizeof(void *));
  for (uint8_t keycode = 0; keycode != 255; keycode++) {
    args[0] = &keycode;
    // keyboard_press
    // Off becomes on
    keyboard_keycodes[keycode] = false;
    err = keyboard_press(&test_key, 0, 0, 1, args);
    if (err != ERR_NONE) {
      return 1;
    }
    if (keyboard_keycodes[keycode] != true) {
      return 2;
    }
    // On stays on
    err = keyboard_press(&test_key, 0, 0, 1, args);
    if (err != ERR_NONE) {
      return 3;
    }
    if (keyboard_keycodes[keycode] != true) {
      return 4;
    }

    // keyboard_release
    // On becomes off
    keyboard_keycodes[keycode] = true;
    err = keyboard_release(&test_key, 0, 0, 1, args);
    if (err != ERR_NONE) {
      return 5;
    }
    if (keyboard_keycodes[keycode] != false) {
      return 6;
    }
    // Off stays off
    err = keyboard_release(&test_key, 0, 0, 1, args);
    if (err != ERR_NONE) {
      return 7;
    }
    if (keyboard_keycodes[keycode] != false) {
      return 8;
    }
  }
  free(args);

  // Test expected errors
  err = consumer_press(&test_key, 0, 0, 0, 0); // too few
  if (err != ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT) {
    return 9;
  }
  err = consumer_press(&test_key, 0, 0, 2, 0); // too many
  if (err != ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT) {
    return 10;
  }
  err = consumer_release(&test_key, 0, 0, 0, 0); // too few
  if (err != ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT) {
    return 10;
  }
  err = consumer_release(&test_key, 0, 0, 2, 0); // too many
  if (err != ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT) {
    return 10;
  }
  return 0;
};
