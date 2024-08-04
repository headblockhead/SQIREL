#include "squirrel.h"
#include "squirrel_quantum.h"
#include <stdint.h>
#include <string.h>

struct layer layers[17];
int key_count;

// struct key noopkey = {noop, NULL, noop, NULL, false};

void press_key(uint8_t key_index) {
  for (uint8_t i = 16; i >= 0; i--) {
    if (!layers[i].active) {
      return;
    }
    struct key selected_key = layers[i].keys[key_index];
    selected_key.pressed(&selected_key, selected_key.pressed_arguments);
    if (i == 16) {
      continue;
    }
    memcpy(&layers[16].keys[key_index], &selected_key,
           sizeof(struct key)); // Copy to the held keys layer
  }
}

void release_key(uint8_t key_index) {
  for (uint8_t i = 16; i >= 0; i--) {
    if (!layers[i].active) {
      return;
    }
    struct key selected_key = layers[i].keys[key_index];
    selected_key.released(&selected_key, selected_key.released_arguments);
    if (i != 16) {
      continue;
    }
  }
}

void check_key(uint8_t key_index, bool is_pressed) {
  for (uint8_t i = 0; i < 17; i++) {
    bool was_pressed = layers[i].keys[key_index].is_pressed;
    if (was_pressed == is_pressed) {
      continue;
    }
    if (is_pressed) {
      press_key(key_index);
      layers[i].keys[key_index].is_pressed = true;
    } else {
      release_key(key_index);
      layers[i].keys[key_index].is_pressed = false;
    }
  }
}

void init_keyboard(int total_keys) {
  layers[16].active = true;
  key_count = key_count;
}
