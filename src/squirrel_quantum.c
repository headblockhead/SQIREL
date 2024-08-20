#include "squirrel_quantum.h"
#include "squirrel.h"
#include "squirrel_consumer.h"
#include "squirrel_key.h"
#include "squirrel_keyboard.h"
#include <stdarg.h>
#include <stdint.h>

struct layer layers[17];

enum squirrel_error key_nop(struct key *key, uint8_t layer, uint8_t key_index,
                            int arg_count, ...) {
  (void)key;
  (void)arg_count;
  return ERR_NONE;
}

enum squirrel_error keyboard_press(struct key *key, uint8_t layer,
                                   uint8_t key_index, int arg_count, ...) {
  (void)layer;
  (void)key_index;

  va_list args;
  va_start(args, arg_count);
  if (arg_count != 1) {
    return ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT;
  };
  uint8_t keycode = va_arg(args, int);
  keyboard_activate_keycode(keycode); // squirrel_keyboard
  va_end(args);
  return ERR_NONE;
};

enum squirrel_error keyboard_release(struct key *key, uint8_t layer,
                                     uint8_t key_index, int arg_count, ...) {
  (void)layer;
  (void)key_index;

  va_list args;
  va_start(args, arg_count);
  if (arg_count != 1) {
    return ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT;
  };
  uint8_t keycode = va_arg(args, int);
  keyboard_deactivate_keycode(keycode); // squirrel_keyboard
  va_end(args);
  return ERR_NONE;
}

enum squirrel_error keyboard_modifier_press(struct key *key, uint8_t layer,
                                            uint8_t key_index, int arg_count,
                                            ...) {
  (void)layer;
  (void)key_index;

  va_list args;
  va_start(args, arg_count);
  if (arg_count != 1) {
    return ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT;
  };
  uint8_t modifier = va_arg(args, int);
  keyboard_activate_modifier(modifier); // squirrel_keyboard
  va_end(args);
  return ERR_NONE;
}

enum squirrel_error keyboard_modifier_release(struct key *key, uint8_t layer,
                                              uint8_t key_index, int arg_count,
                                              ...) {
  (void)layer;
  (void)key_index;

  va_list args;
  va_start(args, arg_count);
  if (arg_count != 1) {
    return ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT;
  };
  uint8_t modifier = va_arg(args, int);
  keyboard_deactivate_modifier(modifier); // squirrel_keyboard
  va_end(args);
  return ERR_NONE;
}

enum squirrel_error consumer_press(struct key *key, uint8_t layer,
                                   uint8_t key_index, int arg_count, ...) {
  (void)layer;
  (void)key_index;

  va_list args;
  va_start(args, arg_count);
  if (arg_count != 1) {
    return ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT;
  };
  uint16_t consumer_code = va_arg(args, int);
  consumer_activate_consumer_code(consumer_code); // squirrel_consumer
  va_end(args);
  return ERR_NONE;
}

enum squirrel_error consumer_release(struct key *key, uint8_t layer,
                                     uint8_t key_index, int arg_count, ...) {
  (void)layer;
  (void)key_index;

  va_list args;
  va_start(args, arg_count);
  if (arg_count != 1) {
    return ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT;
  };
  uint16_t consumer_code = va_arg(args, int);
  consumer_deactivate_consumer_code(consumer_code); // squirrel_consumer
  va_end(args);
  return ERR_NONE;
}

// quantum_passthrough_press does not take extra arguments.
enum squirrel_error quantum_passthrough_press(struct key *key, uint8_t layer,
                                              uint8_t key_index, int arg_count,
                                              ...) {
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
                                                int arg_count, ...) {
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
