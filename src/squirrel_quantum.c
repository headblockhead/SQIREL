#include "squirrel_quantum.h"
#include "squirrel.h"
#include "squirrel_keyboard.h"
#include <stdarg.h>
#include <stdint.h>

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
  activate_keycode(keycode); // squirrel_keyboard
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
  deactivate_keycode(keycode); // squirrel_keyboard
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
  activate_modifier(modifier); // squirrel_keyboard
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
  deactivate_modifier(modifier); // squirrel_keyboard
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
  for (int i = layer; i >= 0; i--) {
    if (!layers[i].active) {
      break;
    }
    struct key next_key = layers[i].keys[key_index];
    next_key.pressed(&next_key, next_key.pressed_arguments);
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
  for (int i = layer; i >= 0; i--) {
    if (!layers[i].active) {
      break;
    }
    struct key next_key = layers[i].keys[key_index];
    next_key.released(&next_key, next_key.released_arguments);
  }
  return ERR_NONE;
}
