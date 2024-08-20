#include "squirrel.h"
#include "squirrel_init.h"
#include "squirrel_key.h"
#include "squirrel_quantum.h"
#include <stdlib.h>

uint8_t test_result = 1;

enum squirrel_error test_press(struct key *key, uint8_t layer,
                               uint8_t key_index, int arg_count, ...) {
  test_result = 0;
  return ERR_NONE;
}

enum squirrel_error test_release(struct key *key, uint8_t layer,
                                 uint8_t key_index, int arg_count, ...) {
  test_result = 0;
  return ERR_NONE;
}

// test: quantum_passthrough_press + quantum_passthrough_release test - in
// squirrel_quantum.c
int main() {
  init_keyboard(1);

  struct key testkey;
  testkey.pressed = test_press;
  testkey.pressed_argument_count = 0;
  testkey.released = test_release;
  testkey.released_argument_count = 0;
  layers[0].keys[0] = testkey;

  struct key passthroughkey;
  passthroughkey.pressed = quantum_passthrough_press;
  passthroughkey.pressed_argument_count = 0;
  passthroughkey.released = quantum_passthrough_release;
  passthroughkey.released_argument_count = 0;
  layers[1].keys[0] = passthroughkey;

  layers[0].active = true;
  layers[1].active = true;

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

  return test_result;
};
