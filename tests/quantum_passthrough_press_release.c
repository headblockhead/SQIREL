#include "squirrel.h"
#include "squirrel_init.h"
#include "squirrel_key.h"
#include "squirrel_quantum.h"
#include <stdlib.h>

uint8_t test_result = 1; // 0 = pass, 1 = fail
bool bad_test = false;   // true = fail

enum squirrel_error test_press(struct key *key, uint8_t layer,
                               uint8_t key_index, int arg_count, void **args) {
  test_result = 0;
  return ERR_NONE;
}

enum squirrel_error test_release(struct key *key, uint8_t layer,
                                 uint8_t key_index, int arg_count,
                                 void **args) {
  test_result = 0;
  return ERR_NONE;
}

enum squirrel_error bad_test_press(struct key *key, uint8_t layer,
                                   uint8_t key_index, int arg_count,
                                   void **args) {
  bad_test = true;
  return ERR_NONE;
}

enum squirrel_error bad_test_release(struct key *key, uint8_t layer,
                                     uint8_t key_index, int arg_count,
                                     void **args) {
  bad_test = true;
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
  layers[0].keys[0] = testkey; // When testkey is pressed, the test is passing.

  struct key passthroughkey;
  passthroughkey.pressed = quantum_passthrough_press;
  passthroughkey.pressed_argument_count = 0;
  passthroughkey.released = quantum_passthrough_release;
  passthroughkey.released_argument_count = 0;
  layers[1].keys[0] = passthroughkey; // This is the key being tested.

  layers[0].active = true;
  layers[1].active = true;

  // Passthrough should press the key below it.
  enum squirrel_error err = press_key(0); // Press the key.
  if (err != ERR_NONE) { // If there is an error, the test fails.
    return 2;
  }
  if (test_result != 0) { // If the testkey is not pressed, the test fails.
    return 3;
  }

  test_result = 1;       // Reset the test result to failing again.
  err = release_key(0);  // Release the key.
  if (err != ERR_NONE) { // If there is an error, the test fails.
    return 4;
  }
  if (test_result != 0) { // If the testkey is not released, the test fails.
    return 5;
  }

  // Passthrough should fall through inactive layers
  layers[0].active = true; // this layer contains the testkey.
  layers[1].active =
      false; // this layer contains the badtestkey and should be ignored.
  layers[2].active = true; // this layer contains the passthrough key.

  layers[2].keys[0] = passthroughkey;

  struct key badtestkey;
  badtestkey.pressed = bad_test_press;
  badtestkey.pressed_argument_count = 0;
  badtestkey.released = bad_test_release;
  badtestkey.released_argument_count = 0;
  layers[1].keys[0] = badtestkey; // When badtestkey is pressed, the test is
                                  // failing.

  test_result = 1;       // Reset the test result to failing again.
  err = press_key(0);    // Press the key.
  if (err != ERR_NONE) { // If there is an error, the test fails.
    return 6;
  }
  if (bad_test) { // If the badtestkey is pressed, the test fails.
    return 7;
  }
  if (test_result != 0) { // If the testkey is not pressed, the test fails.
    return 7;
  }

  test_result = 1;       // Reset the test result to failing again.
  err = release_key(0);  // Release the key.
  if (err != ERR_NONE) { // If there is an error, the test fails.
    return 8;
  }
  if (bad_test) { // If the badtestkey is released, the test fails.
    return 9;
  }
  if (test_result != 0) { // If the testkey is not released, the test fails.
    return 10;
  }
  return 0;
};
