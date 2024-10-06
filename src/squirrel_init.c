#include "squirrel_init.h"
#include "squirrel.h"
#include "squirrel_key.h"
#include "squirrel_quantum.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum squirrel_error squirrel_init(int total_keys) {
  key_count = total_keys;
  struct key passthrough_key = (struct key){
      .pressed = quantum_passthrough_press,
      .released = quantum_passthrough_release,
  };
  for (int j = 16; j >= 0; j--) {
    layers[j].active = false;
    layers[j].keys = (struct key *)malloc(total_keys * sizeof(struct key) +
                                          2 * sizeof(void *));
    for (int i = 0; i < total_keys; i++) {
      layers[j].keys[i] = passthrough_key;
    }
  }
  key_states = (bool *)malloc(total_keys * sizeof(bool));
  if (key_states == NULL) {
    return ERR_OUT_OF_MEMORY_KEY_STATES;
  }
  layers[16].active = true;
  return ERR_NONE;
};
