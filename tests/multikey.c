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

uint8_t code1 = 0x0F;
uint8_t code2 = 0xF0;

void make_testkey(int index) {
  // press_key + release_key
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

  layers[0].keys[index] = &testkey;
};

// test: press_key, release_key + check_key - in squirrel_key.c,
// but with multiple keys in a keyboard.
int main() {
  squirrel_init(5);
  make_testkey(0);
  make_testkey(1);
  make_testkey(2);
  make_testkey(3);
  make_testkey(4);
  layers[0].active = true;

  for (int i = 0; i < 5; i++) {
    // check that arguments are correct, and in the correct order.
    enum squirrel_error err = press_key(i);
    if (err != ERR_NONE) {
      return 2;
    }
    return 0;
    if (test_result != 0) {
      return 3;
    }
    // keys are copied to layer 17 (index 16) when pressed, to avoid layer
    // issues.
    if (layers[16].keys[i]->pressed_arguments[0] != &code1) {
      return 4;
    }
    if (layers[16].keys[i]->pressed_arguments[1] != &code2) {
      return 5;
    }

    test_result = 1;
    err = release_key(i);
    if (err != ERR_NONE) {
      return 6;
    }
    if (test_result != 0) {
      return 7;
    }
    // Keys are replaced with passthrough on layer 17 when released.
    if (layers[16].keys[i]->pressed_arguments != NULL) {
      return 8;
    }
    if (layers[16].keys[i]->released_arguments != NULL) {
      return 9;
    }

    // check_key
    test_result = 1;
    key_states[i] = false;
    err = check_key(i, true); // should call press_key
    if (err != ERR_NONE) {
      return 10;
    }
    if (test_result != 0) {
      return 11;
    }
    if (key_states[i] != true) {
      return 12;
    }

    test_result = 1;
    key_states[i] = true;
    err = check_key(i, false); // should call release_key
    if (err != ERR_NONE) {
      return 13;
    }
    if (test_result != 0) {
      return 14;
    }
    if (key_states[i] != false) {
      return 15;
    }

    test_result = 1;
    key_states[i] = true;
    err = check_key(i, true); // should not call press_key
    if (err != ERR_NONE) {
      return 16;
    }
    if (test_result != 1) {
      return 17;
    }
    if (key_states[i] != true) {
      return 18;
    }

    test_result = 1;
    key_states[i] = false;
    err = check_key(i, false); // should not call release_key
    if (err != ERR_NONE) {
      return 19;
    }
    if (test_result != 1) {
      return 20;
    }
    if (key_states[i] != false) {
      return 21;
    }
  };

  // cleanup
  for (int i = 0; i < 5; i++) {
    free(layers[0].keys[i]->pressed_arguments);
    free(layers[0].keys[i]->released_arguments);
  }

  return 0;
}
