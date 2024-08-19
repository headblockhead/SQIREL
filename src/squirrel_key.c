#include "squirrel_key.h"
#include "squirrel.h"
#include "squirrel_quantum.h"
#include <stdint.h>

void copy_key(struct key *source, struct key *destination) {
  destination->is_pressed = source->is_pressed;
  destination->pressed = source->pressed;
  destination->pressed_arguments = source->pressed_arguments;
  destination->pressed_argument_count = source->pressed_argument_count;
  destination->released = source->released;
  destination->released_arguments = source->released_arguments;
  destination->released_argument_count = source->released_argument_count;
}

enum squirrel_error press_key(uint8_t key_index) {
  enum squirrel_error err;
  for (uint8_t i = 16; i >= 0; i--) {
    if (!layers[i].active) {
      continue;
    }
    struct key *selected_key = &(layers[i].keys[key_index]);
    err = selected_key->pressed(selected_key, i, key_index,
                                selected_key->pressed_argument_count,
                                selected_key->pressed_arguments);
    if (i == 16) {
      continue;
    }
    copy_key(selected_key, &layers[16].keys[key_index]);
  }
  return err;
}

enum squirrel_error release_key(uint8_t key_index) {
  enum squirrel_error err;
  for (uint8_t i = 16; i >= 0; i--) {
    if (!layers[i].active) {
      continue;
    }
    struct key *selected_key = &(layers[i].keys[key_index]);
    err = selected_key->released(selected_key, i, key_index,
                                 selected_key->released_argument_count,
                                 selected_key->released_arguments);
    if (i != 16) {
      continue;
    }
    struct key passthrough_key;
    passthrough_key.pressed = quantum_passthrough_press;
    passthrough_key.released = quantum_passthrough_release;
    copy_key(&passthrough_key, &layers[16].keys[key_index]);
  }
  return err;
}

enum squirrel_error check_key(uint8_t key_index, bool is_pressed) {
  enum squirrel_error err;
  for (uint8_t i = 0; i < 17; i++) {
    bool was_pressed = layers[i].keys[key_index].is_pressed;
    if (was_pressed == is_pressed) {
      continue;
    }
    if (is_pressed) {
      err = press_key(key_index);
      layers[i].keys[key_index].is_pressed = true;
    } else {
      err = release_key(key_index);
      layers[i].keys[key_index].is_pressed = false;
    }
  }
  return err;
}
