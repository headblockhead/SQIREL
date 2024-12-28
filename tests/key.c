#include "squirrel.h"
#include "squirrel_init.h"
#include "squirrel_key.h"
#include "squirrel_quantum.h"
#include <stdarg.h>
#include <stdlib.h>

uint8_t test_result = 1;

enum squirrel_error test_press(uint8_t layer, uint8_t key_index, void *arg) {
  (void)layer;
  (void)key_index;
  uint8_t code = *(uint8_t *)arg;
  if (code == 0xF0) {
    test_result = 0;
  }
  return ERR_NONE;
}

enum squirrel_error test_release(uint8_t layer, uint8_t key_index, void *arg) {
  (void)layer;
  (void)key_index;
  uint8_t code = *(uint8_t *)arg;
  if (code == 0xF0) {
    test_result = 0;
  }
  return ERR_NONE;
}

// test: press_key, release_key + check_key - in squirrel_key.c
int main() {
  squirrel_init(1);

  // press_key + release_key
  uint8_t code = 0xF0;

  struct key testkey;
  testkey.pressed = test_press;
  testkey.pressed_argument = &code;
  testkey.released = test_release;
  testkey.released_argument = &code;
  copy_key(&testkey, &layers[0].keys[0]);
  layers[0].active = true;

  // check that arguments are correct, and in the correct order.
  enum squirrel_error err = press_key(0);
  if (err != ERR_NONE) {
    return 2;
  }
  if (test_result != 0) {
    return 3;
  }
  // keys are copied to layer 17 (index 16) when pressed, to avoid layer issues.
  if (layers[16].keys[0].pressed_argument != &code) {
    return 4;
  }
  if (layers[16].keys[0].pressed_argument != &code) {
    return 5;
  }

  test_result = 1;
  err = release_key(0);
  if (err != ERR_NONE) {
    return 6;
  }
  if (test_result != 0) {
    return 7;
  }
  // Keys are replaced with passthrough on layer 17 when released.
  if (layers[16].keys[0].pressed_argument != NULL) {
    return 8;
  }
  if (layers[16].keys[0].released_argument != NULL) {
    return 9;
  }

  // check_key
  test_result = 1;
  key_states[0] = false;
  err = check_key(0, true); // should call press_key
  if (err != ERR_NONE) {
    return 10;
  }
  if (test_result != 0) {
    return 11;
  }
  if (key_states[0] != true) {
    return 12;
  }

  test_result = 1;
  key_states[0] = true;
  err = check_key(0, false); // should call release_key
  if (err != ERR_NONE) {
    return 13;
  }
  if (test_result != 0) {
    return 14;
  }
  if (key_states[0] != false) {
    return 15;
  }

  test_result = 1;
  key_states[0] = true;
  err = check_key(0, true); // should not call press_key
  if (err != ERR_NONE) {
    return 16;
  }
  if (test_result != 1) {
    return 17;
  }
  if (key_states[0] != true) {
    return 18;
  }

  test_result = 1;
  key_states[0] = false;
  err = check_key(0, false); // should not call release_key
  if (err != ERR_NONE) {
    return 19;
  }
  if (test_result != 1) {
    return 20;
  }
  if (key_states[0] != false) {
    return 21;
  }

  return 0;
}
