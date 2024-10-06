#include "squirrel_key.h"
#include "squirrel.h"
#include "squirrel_quantum.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int key_count = 0; // This should be overwritten by squirrel_init

void copy_key(struct key *source, struct key *destination) {
  *destination = *source;
}

enum squirrel_error press_key(uint8_t key_index) {
  for (int i = 16; i >= 0; i--) {
    if (!layers[i].active) {
      continue;
    }
    struct key selected_key = layers[i].keys[key_index];
    enum squirrel_error err = selected_key.pressed(
        &selected_key, i, key_index, selected_key.pressed_argument);
    if (err != ERR_NONE) {
      return err;
    }
    if (i == 16) {
      continue;
    }
    copy_key(&selected_key, &layers[16].keys[key_index]);
  }
  return ERR_NONE;
}

enum squirrel_error release_key(uint8_t key_index) {
  for (int i = 16; i >= 0; i--) {
    if (!layers[i].active) {
      continue;
    }
    struct key selected_key = layers[i].keys[key_index];
    enum squirrel_error err = selected_key.released(
        &selected_key, i, key_index, selected_key.released_argument);
    if (err != ERR_NONE) {
      return err;
    }
    if (i != 16) {
      continue;
    }
    struct key passthrough_key;
    passthrough_key.pressed = quantum_passthrough_press;
    passthrough_key.released = quantum_passthrough_release;
    copy_key(&passthrough_key, &layers[16].keys[key_index]);
  }
  return ERR_NONE;
}

bool *key_states;

enum squirrel_error check_key(uint8_t key_index, bool is_pressed) {
  enum squirrel_error err;
  if (key_states[key_index] == is_pressed) {
    return ERR_NONE;
  }
  if (is_pressed) {
    key_states[key_index] = true;
    return press_key(key_index);
  }
  key_states[key_index] = false;
  return release_key(key_index);
  return ERR_NONE;
}
