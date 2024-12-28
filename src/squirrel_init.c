#include "squirrel_init.h"
#include "squirrel.h"
#include "squirrel_key.h"
#include "squirrel_quantum.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum squirrel_error squirrel_init(int keys) {
  struct key passthrough_key = (struct key){
      .pressed = quantum_passthrough_press,
      .released = quantum_passthrough_release,
  };
  for (int j = 16; j >= 0; j--) {
    layers[j].active = false;
    layers[j].keys = malloc(sizeof(struct key) * keys);
    if (layers[j].keys == NULL) {
      return ERR_OOM;
    }
    for (int i = 0; i < keys; i++) {
      copy_key(&passthrough_key, &layers[j].keys[i]);
    }
  }
  layers[16].active = true;
  key_states = malloc(sizeof(bool) * keys);

  if (key_states == NULL) {
    return ERR_OOM;
  }

  return ERR_NONE;
};
