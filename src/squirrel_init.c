#include "squirrel_init.h"
#include "squirrel.h"
#include "squirrel_key.h"
#include "squirrel_quantum.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

enum squirrel_error squirrel_init(int total_keys) {
  key_count = total_keys;
  struct key passthrough_key;
  passthrough_key.pressed = quantum_passthrough_press;
  passthrough_key.pressed_argument_count = 0;
  passthrough_key.pressed_arguments = NULL;
  passthrough_key.released = quantum_passthrough_release;
  passthrough_key.released_argument_count = 0;
  passthrough_key.released_arguments = NULL;
  for (uint8_t j = 16; j != 255; j--) {
    layers[j].keys = (struct key *)malloc(total_keys * sizeof(struct key));
    if (layers[j].keys == NULL) {
      return ERR_OUT_OF_MEMORY_KEYS;
    }
    for (int i = 0; i < total_keys; i++) {
      copy_key(&passthrough_key, &(layers[j].keys[i]));
    }
  }
  key_states = (bool *)malloc(total_keys * sizeof(bool));
  if (key_states == NULL) {
    return ERR_OUT_OF_MEMORY_KEY_STATES;
  }
  layers[16].active = true;
  return ERR_NONE;
};
