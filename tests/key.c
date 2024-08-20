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

  free(testkey.pressed_arguments);
  free(testkey.released_arguments);

  // TODO: check_key

  return test_result;
}
