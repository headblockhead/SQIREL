#include "squirrel_quantum.h"
#include "squirrel.h"
#include "squirrel_consumer.h"
#include "squirrel_key.h"
#include "squirrel_keyboard.h"
#include <stdint.h>
#include <stdlib.h>

struct layer layers[17];

enum squirrel_error key_nop(struct key *key, uint8_t layer, uint8_t key_index,
                            int arg_count, void **args) {
  (void)key;
  (void)arg_count;
  (void)args;
  return ERR_NONE;
}

enum squirrel_error keyboard_press(struct key *key, uint8_t layer,
                                   uint8_t key_index, int arg_count,
                                   void **args) {
  (void)layer;
  (void)key_index;
  if (arg_count != 1) {
    return ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT;
  };

  keyboard_activate_keycode(*(uint8_t *)args[0]); // squirrel_keyboard
  return ERR_NONE;
};

enum squirrel_error keyboard_release(struct key *key, uint8_t layer,
                                     uint8_t key_index, int arg_count,
                                     void **args) {
  (void)layer;
  (void)key_index;
  if (arg_count != 1) {
    return ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT;
  };
  keyboard_deactivate_keycode(*(uint8_t *)args[0]); // squirrel_keyboard
  return ERR_NONE;
}

enum squirrel_error keyboard_modifier_press(struct key *key, uint8_t layer,
                                            uint8_t key_index, int arg_count,
                                            void **args) {
  (void)layer;
  (void)key_index;
  if (arg_count != 1) {
    return ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT;
  };
  keyboard_activate_modifier(*(uint8_t *)args[0]); // squirrel_keyboard
  return ERR_NONE;
}

enum squirrel_error keyboard_modifier_release(struct key *key, uint8_t layer,
                                              uint8_t key_index, int arg_count,
                                              void **args) {
  (void)layer;
  (void)key_index;
  if (arg_count != 1) {
    return ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT;
  };
  keyboard_deactivate_modifier(*(uint8_t *)args[0]); // squirrel_keyboard
  return ERR_NONE;
}

enum squirrel_error consumer_press(struct key *key, uint8_t layer,
                                   uint8_t key_index, int arg_count,
                                   void **args) {
  (void)layer;
  (void)key_index;
  if (arg_count != 1) {
    return ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT;
  };
  consumer_activate_consumer_code(*(uint16_t *)args[0]); // squirrel_consumer
  return ERR_NONE;
}

enum squirrel_error consumer_release(struct key *key, uint8_t layer,
                                     uint8_t key_index, int arg_count,
                                     void **args) {
  (void)layer;
  (void)key_index;
  if (arg_count != 1) {
    return ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT;
  };
  consumer_deactivate_consumer_code(*(uint16_t *)args[0]); // squirrel_consumer
  return ERR_NONE;
}

// quantum_passthrough_press does not take extra arguments.
enum squirrel_error quantum_passthrough_press(struct key *key, uint8_t layer,
                                              uint8_t key_index, int arg_count,
                                              void **args) {
  if (arg_count != 0) {
    return ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT;
  };
  if (layer == 0) {
    return ERR_PASSTHROUGH_ON_BOTTOM_LAYER;
  };
  for (uint8_t i = layer - 1; i != 255; i--) {
    if (!layers[i].active) {
      continue;
    }
    struct key *selected_key = &(layers[i].keys[key_index]);
    enum squirrel_error err = selected_key->pressed(
        selected_key, i, key_index, selected_key->pressed_argument_count,
        selected_key->pressed_arguments);
    if (err != ERR_NONE) {
      return err;
    }
    if (i == 16) {
      continue;
    }
    copy_key(selected_key, &layers[16].keys[key_index]);
  }
  return ERR_NONE;
}

// quantum_passthrough_release does not take extra arguments.
enum squirrel_error quantum_passthrough_release(struct key *key, uint8_t layer,
                                                uint8_t key_index,
                                                int arg_count, void **args) {
  if (arg_count != 0) {
    return ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT;
  };
  if (layer == 0) {
    return ERR_PASSTHROUGH_ON_BOTTOM_LAYER;
  };
  for (uint8_t i = layer - 1; i != 255; i--) {
    if (!layers[i].active) {
      continue;
    }
    struct key *selected_key = &(layers[i].keys[key_index]);
    enum squirrel_error err = selected_key->released(
        selected_key, i, key_index, selected_key->released_argument_count,
        selected_key->released_arguments);
    if (err != ERR_NONE) {
      return err;
    }
    if (i != 16) {
      continue;
    }
    struct key passthrough_key;
    passthrough_key.pressed = quantum_passthrough_press;
    passthrough_key.pressed_argument_count = 0;
    passthrough_key.released = quantum_passthrough_release;
    passthrough_key.released_argument_count = 0;
    copy_key(&passthrough_key, &layers[16].keys[key_index]);
  }
  return ERR_NONE;
}

enum squirrel_error layer_momentary_press(struct key *key, uint8_t layer,
                                          uint8_t key_index, int arg_count,
                                          void **args) {
  if (arg_count != 1) {
    return ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT;
  };
  uint8_t target_layer = *(uint8_t *)args[0];
  layers[target_layer].active = true;
  return ERR_NONE;
}

enum squirrel_error layer_momentary_release(struct key *key, uint8_t layer,
                                            uint8_t key_index, int arg_count,
                                            void **args) {
  if (arg_count != 1) {
    return ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT;
  };
  uint8_t target_layer = *(uint8_t *)args[0];
  layers[target_layer].active = false;
  return ERR_NONE;
}

enum squirrel_error layer_toggle_press(struct key *key, uint8_t layer,
                                       uint8_t key_index, int arg_count,
                                       void **args) {
  if (arg_count != 1) {
    return ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT;
  };
  uint8_t target_layer = *(uint8_t *)args[0];
  layers[target_layer].active = !layers[target_layer].active;
  return ERR_NONE;
}

enum squirrel_error layer_toggle_release(struct key *key, uint8_t layer,
                                         uint8_t key_index, int arg_count,
                                         void **args) {
  if (arg_count != 1) {
    return ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT;
  };
  return ERR_NONE;
}

enum squirrel_error layer_solo_press(struct key *key, uint8_t layer,
                                     uint8_t key_index, int arg_count,
                                     void **args) {
  if (arg_count != 1) {
    return ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT;
  };
  uint8_t target_layer = *(uint8_t *)args[0];
  for (uint8_t i = 0; i < 16; i++) {
    layers[i].active = false;
  }
  layers[target_layer].active = true;
  return ERR_NONE;
}

enum squirrel_error layer_solo_release(struct key *key, uint8_t layer,
                                       uint8_t key_index, int arg_count,
                                       void **args) {
  if (arg_count != 1) {
    return ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT;
  };
  return ERR_NONE;
}
