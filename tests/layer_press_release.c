#include "squirrel.h"
#include "squirrel_init.h"
#include "squirrel_key.h"
#include "squirrel_quantum.h"
#include <stdint.h>
#include <stdio.h>

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

  uint8_t target_layer = 1;

  // layer_momentary
  layer_momentary_press(0, 0, &target_layer);
  for (uint8_t i = 0; i < 16; i++) {
    if (layers[i].active &&
        i != target_layer) { // if any other layers are active, fail.
      printf("err while testing with target_layer %d,\n", target_layer);
      printf("layer unexpectedly active: %d\n", i);
      return 1;
    }
  }
  if (!layers[target_layer].active) { // if target_layer is not active, fail.
    return 8;
  }

  for (uint8_t i = 0; i < 16; i++) { // activate all layers
    layers[i].active = true;
  }
  layer_momentary_release(0, 0,
                          &target_layer); // should deactivate target_layer only
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
  layer_toggle_press(0, 0,
                     &target_layer); // should activate target_layer
  for (uint8_t i = 0; i < 16; i++) {
    if (layers[i].active &&
        i != target_layer) { // if any other layers are active, fail.
      return 11;
    }
  }
  if (!layers[target_layer].active) { // if target_layer is not active, fail.
    return 12;
  }
  layer_toggle_release(0, 0, &target_layer); // should not deactivate
  for (uint8_t i = 0; i < 16; i++) {
    if (layers[i].active &&
        i != target_layer) { // if any other layers are active, fail.
      return 13;
    }
  }
  if (!layers[target_layer].active) { // if target_layer is not active, fail.
    return 14;
  }
  layer_toggle_press(0, 0,
                     &target_layer); // should deactivate target_layer
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
  layer_solo_press(
      0, 0,
      &target_layer); // solo should turn off all layers except target_layer
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
      0, 0,
      &target_layer); // solo should not turn off target_layer if called again
  for (uint8_t i = 0; i < 16; i++) {
    if (layers[i].active &&
        i != target_layer) { // if any other layers are active, fail.
      return 19;
    }
  }
  if (!layers[target_layer].active) { // if target_layer is not active, fail.
    return 20;
  }
  layer_solo_release(0, 0,
                     &target_layer); // release should not do anything
  for (uint8_t i = 0; i < 16; i++) {
    if (layers[i].active &&
        i != target_layer) { // if any other layers are active, fail.
      return 21;
    }
  }
  if (!layers[target_layer].active) { // if target_layer is not active, fail.
    return 22;
  }

  return 0;
};
