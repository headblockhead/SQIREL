#include "squirrel.h"
#include "squirrel_init.h"
#include "squirrel_key.h"
#include "squirrel_quantum.h"
#include <stdint.h>
#include <stdlib.h>

// test:
// layer_momentary_press
// layer_momentary_release
// layer_toggle_press
// layer_toggle_release
// layer_turn_on_press
// layer_turn_on_release
// in squirrel_quantum.c
int main() {
  init_keyboard(1);
  enum squirrel_error err;
  struct key test_key;

  // Test expected errors
  err = layer_momentary_press(&test_key, 0, 0, 0, 0); // too few
  if (err != ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT) {
    return 1;
  }
  err = layer_momentary_release(&test_key, 0, 0, 2, 0); // too many
  if (err != ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT) {
    return 2;
  }
  err = layer_toggle_press(&test_key, 0, 0, 0, 0); // too few
  if (err != ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT) {
    return 3;
  }
  err = layer_toggle_release(&test_key, 0, 0, 2, 0); // too many
  if (err != ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT) {
    return 4;
  }
  err = layer_turn_on_press(&test_key, 0, 0, 0, 0); // too few
  if (err != ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT) {
    return 5;
  }
  err = layer_turn_on_release(&test_key, 0, 0, 2, 0); // too many
  if (err != ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT) {
    return 6;
  }

  void **args = malloc(sizeof(void *));
  uint8_t target_layer = 1;
  args[0] = &target_layer;
  layer_momentary_press(&test_key, 0, 0, 1, args);
  free(args);

  return 0;
};
