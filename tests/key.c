#include "squirrel.h"
#include "squirrel_init.h"
#include "squirrel_key.h"
#include "squirrel_quantum.h"
#include <stdarg.h>
#include <stdlib.h>

uint8_t test_result = 1;

enum squirrel_error test_press(struct key *key, uint8_t layer,
                               uint8_t key_index, int arg_count, void **args) {
  (void)layer;
  (void)key_index;

  if (arg_count != 2) {
    return ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT;
  };
  uint8_t code1 = *(uint8_t *)args[0];
  uint8_t code2 = *(uint8_t *)args[1];
  if (code1 == 0x0F && code2 == 0xF0) {
    test_result = 0;
  }
  return ERR_NONE;
}

enum squirrel_error test_release(struct key *key, uint8_t layer,
                                 uint8_t key_index, int arg_count,
                                 void **args) {
  (void)layer;
  (void)key_index;

  if (arg_count != 2) {
    return ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT;
  };
  uint8_t code1 = *(uint8_t *)args[0];
  uint8_t code2 = *(uint8_t *)args[1];
  if (code1 == 0xF0 && code2 == 0x0F) {
    test_result = 0;
  }
  return ERR_NONE;
}

// test: press_key, release_key + check_key - in squirrel_key.c
int main() {
  init_keyboard(1);

  // press_key + release_key
  uint8_t code1 = 0x0F;
  uint8_t code2 = 0xF0;

  struct key testkey;
  testkey.pressed = test_press;
  testkey.pressed_argument_count = 2;
  testkey.pressed_arguments = malloc(2 * sizeof(void *));
  testkey.pressed_arguments[0] = &code1;
  testkey.pressed_arguments[1] = &code2;

  testkey.released = test_release;
  testkey.released_argument_count = 2;
  testkey.released_arguments = malloc(2 * sizeof(void *));
  testkey.released_arguments[0] = &code2;
  testkey.released_arguments[1] = &code1;

  layers[0].keys[0] = testkey;
  layers[0].active = true;

  // check that arguments are correct, and in the correct order.
  enum squirrel_error err = press_key(0);
  if (err != ERR_NONE) {
    return 2;
  }
  if (test_result != 0) {
    return 3;
  }

  test_result = 1;
  err = release_key(0);
  if (err != ERR_NONE) {
    return 4;
  }
  if (test_result != 0) {
    return 5;
  }

  // check_key
  test_result = 1;
  key_states[0] = false;
  err = check_key(0, true); // should call press_key
  if (err != ERR_NONE) {
    return 6;
  }
  if (test_result != 0) {
    return 7;
  }
  if (key_states[0] != true) {
    return 8;
  }

  test_result = 1;
  key_states[0] = true;
  err = check_key(0, false); // should call release_key
  if (err != ERR_NONE) {
    return 9;
  }
  if (test_result != 0) {
    return 10;
  }
  if (key_states[0] != false) {
    return 11;
  }

  test_result = 1;
  key_states[0] = true;
  err = check_key(0, true); // should not call press_key
  if (err != ERR_NONE) {
    return 12;
  }
  if (test_result != 1) {
    return 13;
  }
  if (key_states[0] != true) {
    return 14;
  }

  test_result = 1;
  key_states[0] = false;
  err = check_key(0, false); // should not call release_key
  if (err != ERR_NONE) {
    return 15;
  }
  if (test_result != 1) {
    return 16;
  }
  if (key_states[0] != false) {
    return 17;
  }

  free(testkey.pressed_arguments);
  free(testkey.released_arguments);

  return 0;
}
