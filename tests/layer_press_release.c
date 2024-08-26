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
// layer_solo_press
// layer_solo_release
// in squirrel_quantum.c
int main() {
  squirrel_init(1);
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
  err = layer_solo_press(&test_key, 0, 0, 0, 0); // too few
  if (err != ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT) {
    return 5;
  }
  err = layer_solo_release(&test_key, 0, 0, 2, 0); // too many
  if (err != ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT) {
    return 6;
  }

  void **args = malloc(sizeof(void *));
  uint8_t target_layer = 1;
  args[0] = &target_layer;

  // layer_momentary
  layer_momentary_press(&test_key, 0, 0, 1,
                        args); // should activate target_layer only
  for (uint8_t i = 0; i < 16; i++) {
    if (layers[i].active &&
        i != target_layer) { // if any other layers are active, fail.
      return 7;
    }
  }
  if (!layers[target_layer].active) { // if target_layer is not active, fail.
    return 8;
  }
  for (uint8_t i = 0; i < 16; i++) { // activate all layers
    layers[i].active = true;
  }
  layer_momentary_release(&test_key, 0, 0, 1,
                          args); // should deactivate target_layer only
  for (uint8_t i = 0; i < 16; i++) {
    if (!layers[i].active &&
        i != target_layer) { // if any other layers are not active, fail.
      return 9;
    }
  }
  if (layers[target_layer].active) { // if target_layer is active, fail.
    return 10;
  }
  for (uint8_t i = 0; i < 16; i++) { // deactivate all layers for next test
    layers[i].active = false;
  }

  // layer_toggle
  layer_toggle_press(&test_key, 0, 0, 1, args); // should activate target_layer
  for (uint8_t i = 0; i < 16; i++) {
    if (layers[i].active &&
        i != target_layer) { // if any other layers are active, fail.
      return 11;
    }
  }
  if (!layers[target_layer].active) { // if target_layer is not active, fail.
    return 12;
  }
  layer_toggle_release(&test_key, 0, 0, 1, args); // should not deactivate
  for (uint8_t i = 0; i < 16; i++) {
    if (layers[i].active &&
        i != target_layer) { // if any other layers are active, fail.
      return 13;
    }
  }
  if (!layers[target_layer].active) { // if target_layer is not active, fail.
    return 14;
  }
  layer_toggle_press(&test_key, 0, 0, 1,
                     args);          // should deactivate target_layer
  for (uint8_t i = 0; i < 16; i++) { // if any other layers are active, fail.
    if (layers[i].active && i != target_layer) {
      return 15;
    }
  }
  if (layers[target_layer].active) { // if target_layer is active, fail.
    return 16;
  }

  // layer_solo
  for (uint8_t i = 0; i < 16; i++) { // turn on all layers
    layers[i].active = true;
  }
  layer_solo_press(&test_key, 0, 0, 1,
                   args); // solo should turn off all layers except target_layer
  for (uint8_t i = 0; i < 16; i++) {
    if (layers[i].active &&
        i != target_layer) { // if any other layers are active, fail.
      return 17;
    }
  }
  if (!layers[target_layer].active) { // if target_layer is not active, fail.
    return 18;
  }
  layer_solo_press(
      &test_key, 0, 0, 1,
      args); // solo should not turn off target_layer if called again
  for (uint8_t i = 0; i < 16; i++) {
    if (layers[i].active &&
        i != target_layer) { // if any other layers are active, fail.
      return 19;
    }
  }
  if (!layers[target_layer].active) { // if target_layer is not active, fail.
    return 20;
  }
  layer_solo_release(&test_key, 0, 0, 1,
                     args); // release should not do anything
  for (uint8_t i = 0; i < 16; i++) {
    if (layers[i].active &&
        i != target_layer) { // if any other layers are active, fail.
      return 21;
    }
  }
  if (!layers[target_layer].active) { // if target_layer is not active, fail.
    return 22;
  }
  free(args);

  return 0;
};
