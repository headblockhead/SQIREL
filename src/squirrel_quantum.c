#include "squirrel_quantum.h"
#include "squirrel.h"
#include "squirrel_keyboard.h"
#include <stdarg.h>
#include <stdint.h>

enum squirrel_error key_nop(struct key *key, int arg_count, ...) {
  (void)key;
  (void)arg_count;
}

// keyboard_press expects a single uint8 keycode
enum squirrel_error keyboard_press(struct key *key, int arg_count, ...) {
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

// keyboard_release expects a single uint8 keycode
enum squirrel_error keyboard_release(struct key *key, int arg_count, ...) {
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

// keyboard_modifier_press expects a single uint8 modifier
enum squirrel_error keyboard_modifier_press(struct key *key, int arg_count,
                                            ...) {
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

enum squirrel_error keyboard_modifier_release(struct key *key, int arg_count,
                                              ...) {
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

// quantum_passthrough_press expects a uint8 with the layer of the key it was
// activated from, and a uint8 of the key's index in the layer.
enum squirrel_error quantum_passthrough_press(struct key *key, int arg_count,
                                              ...) {
  va_list args;
  va_start(args, arg_count);
  if (arg_count != 1) {
    return ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT;
  };
  uint8_t modifier = va_arg(args, int);
  deactivate_modifier(modifier); // squirrel_keyboard
  va_end(args);
  return ERR_NONE;

  for (int i = layer; i >= 0; i--) {
    if (!layers[i].active) {
      break;
    }
    struct key next_key = layers[i].keys[key_index];
    next_key.pressed(&next_key, next_key.pressed_arguments);
  }
}

enum squirrel_error quantum_passthrough_release(struct key *key, int arg_count,
                                                ...) {
  for (int i = layer; i >= 0; i--) {
    if (!layers[i].active) {
      break;
    }
    struct key next_key = layers[i].keys[key_index];
    next_key.released(&next_key, next_key.released_arguments);
  }
}
