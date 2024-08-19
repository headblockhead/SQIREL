#include "squirrel.h"
#include "squirrel_key.h"
#include "squirrel_quantum.h"
#include <stdint.h>
#include <string.h>

enum squirrel_error init_keyboard(int total_keys) {
  key_count = total_keys;
  struct layer empty_layer;
  empty_layer.active = false;
  struct key passthrough_key;
  passthrough_key.pressed = quantum_passthrough_press;
  passthrough_key.released = quantum_passthrough_release;
  for (int i = 0; i < total_keys; i++) {
    copy_key(&passthrough_key, &(empty_layer.keys[i]));
  }
  return ERR_NONE;
};
