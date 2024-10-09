#include "squirrel_quantum.h"
#include "squirrel.h"
#include "squirrel_consumer.h"
#include "squirrel_key.h"
#include "squirrel_keyboard.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct layer layers[17] = {};

enum squirrel_error key_nop(uint8_t layer, uint8_t key_index, void *arg) {
  (void)arg;
  return ERR_NONE;
}

enum squirrel_error keyboard_press(uint8_t layer, uint8_t key_index,
                                   void *arg) {
  (void)layer;
  (void)key_index;
  keyboard_activate_keycode(*(uint8_t *)arg); // squirrel_keyboard
  return ERR_NONE;
};

enum squirrel_error keyboard_release(uint8_t layer, uint8_t key_index,
                                     void *arg) {
  (void)layer;
  (void)key_index;
  keyboard_deactivate_keycode(*(uint8_t *)arg); // squirrel_keyboard
  return ERR_NONE;
}

enum squirrel_error keyboard_modifier_press(uint8_t layer, uint8_t key_index,
                                            void *arg) {
  (void)layer;
  (void)key_index;
  keyboard_activate_modifier(*(uint8_t *)arg); // squirrel_keyboard
  return ERR_NONE;
}

enum squirrel_error keyboard_modifier_release(uint8_t layer, uint8_t key_index,
                                              void *arg) {
  (void)layer;
  (void)key_index;
  keyboard_deactivate_modifier(*(uint8_t *)arg); // squirrel_keyboard
  return ERR_NONE;
}

enum squirrel_error consumer_press(uint8_t layer, uint8_t key_index,
                                   void *arg) {
  (void)layer;
  (void)key_index;
  consumer_activate_consumer_code(*(uint16_t *)arg); // squirrel_consumer
  return ERR_NONE;
}

enum squirrel_error consumer_release(uint8_t layer, uint8_t key_index,
                                     void *arg) {
  (void)layer;
  (void)key_index;
  consumer_deactivate_consumer_code(*(uint16_t *)arg); // squirrel_consumer
  return ERR_NONE;
}

// quantum_passthrough_press does not take extra arguments.
enum squirrel_error quantum_passthrough_press(uint8_t layer, uint8_t key_index,
                                              void *arg) {
  if (layer == 0) {
    return ERR_PASSTHROUGH_ON_BOTTOM_LAYER;
  };
  for (int i = layer - 1; i >= 0; i--) {
    if (!layers[i].active) {
      continue;
    }
    struct key selected_key = layers[i].keys[key_index];
    enum squirrel_error err =
        selected_key.pressed(i, key_index, selected_key.pressed_argument);
    if (err != ERR_NONE) {
      return err;
    }
    if (i == 16) {
      break;
    }
    copy_key(&selected_key, &layers[16].keys[key_index]);
    break;
  }
  return ERR_NONE;
}

// quantum_passthrough_release does not take extra arguments.
enum squirrel_error quantum_passthrough_release(uint8_t layer,
                                                uint8_t key_index, void *arg) {
  if (layer == 0) {
    return ERR_PASSTHROUGH_ON_BOTTOM_LAYER;
  };
  for (int i = layer - 1; i >= 0; i--) {
    if (!layers[i].active) {
      continue;
    }
    struct key selected_key = layers[i].keys[key_index];
    enum squirrel_error err =
        selected_key.released(i, key_index, selected_key.released_argument);
    if (err != ERR_NONE) {
      return err;
    }
    if (i != 16) {
      break;
    }
    struct key passthrough_key;
    passthrough_key.pressed = quantum_passthrough_press;
    passthrough_key.released = quantum_passthrough_release;
    copy_key(&passthrough_key, &layers[16].keys[key_index]);
    break;
  }
  return ERR_NONE;
}

enum squirrel_error layer_momentary_press(uint8_t layer, uint8_t key_index,
                                          void *arg) {
  uint8_t target_layer = *(uint8_t *)arg;
  layers[target_layer].active = true;
  return ERR_NONE;
}

enum squirrel_error layer_momentary_release(uint8_t layer, uint8_t key_index,
                                            void *arg) {
  uint8_t target_layer = *(uint8_t *)arg;
  layers[target_layer].active = false;
  return ERR_NONE;
}

enum squirrel_error layer_toggle_press(uint8_t layer, uint8_t key_index,
                                       void *arg) {
  uint8_t target_layer = *(uint8_t *)arg;
  layers[target_layer].active = !layers[target_layer].active;
  return ERR_NONE;
}

enum squirrel_error layer_toggle_release(uint8_t layer, uint8_t key_index,
                                         void *arg) {
  return ERR_NONE;
}

enum squirrel_error layer_solo_press(uint8_t layer, uint8_t key_index,
                                     void *arg) {
  uint8_t target_layer = *(uint8_t *)arg;
  for (uint8_t i = 0; i < 16; i++) {
    layers[i].active = false;
  }
  layers[target_layer].active = true;
  return ERR_NONE;
}

enum squirrel_error layer_solo_release(uint8_t layer, uint8_t key_index,
                                       void *arg) {
  return ERR_NONE;
}
