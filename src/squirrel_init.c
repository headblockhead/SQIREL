#include "squirrel_init.h"
#include "squirrel.h"
#include "squirrel_key.h"
#include "squirrel_quantum.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum squirrel_error squirrel_init(void) {
  struct key passthrough_key = (struct key){
      .pressed = quantum_passthrough_press,
      .released = quantum_passthrough_release,
  };
  for (int j = 16; j >= 0; j--) {
    layers[j].active = false;
    for (int i = 0; i < SQUIRREL_KEYCOUNT; i++) {
      copy_key(&passthrough_key, &layers[j].keys[i]);
    }
  }
  layers[16].active = true;
  return ERR_NONE;
};
