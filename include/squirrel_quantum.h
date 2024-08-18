#ifndef SQUIRREL_QUANTUM_H
#define SQUIRREL_QUANTUM_H

#include "squirrel.h"
#include "squirrel_keyboard.h"
#include <stdarg.h>
#include <stdint.h>

struct layer {
  struct key *keys; // array of keys in this layer
  bool active;      // true if this layer is currently active
};

// layers is a list of all the layers in the keyboard. 0-15 are configured,
// layer 16 is used for held keys and should only be modified by SQUIRREL.
extern struct layer layers[17];

// key_nop does nothing (no operation)
enum squirrel_error key_nop(struct key *key, uint8_t layer, uint8_t key_index,
                            int arg_count, ...);

// keyboard_press expects a single uint8 keycode
enum squirrel_error keyboard_press(struct key *key, uint8_t layer,
                                   uint8_t key_index, int arg_count, ...);

// keyboard_release expects a single uint8 keycode
enum squirrel_error keyboard_release(struct key *key, uint8_t layer,
                                     uint8_t key_index, int arg_count, ...);

// keyboard_modifier_press expects a single uint8 modifier
enum squirrel_error keyboard_modifier_press(struct key *key, uint8_t layer,
                                            uint8_t key_index, int arg_count,
                                            ...);

// keyboard_modifier_release expects a single uint8 modifier
enum squirrel_error keyboard_modifier_release(struct key *key, uint8_t layer,
                                              uint8_t key_index, int arg_count,
                                              ...);

// quantum_passthrough passes the press action to the highest active layer below
// the current one. It expectes no extra args.
enum squirrel_error quantum_passthrough_press(struct key *key, uint8_t layer,
                                              uint8_t key_index, int arg_count,
                                              ...);

// quantum_passthrough_release passes the release action to the highest active
// layer below the current one. It expectes no extra args.
enum squirrel_error quantum_passthrough_release(struct key *key, uint8_t layer,
                                                uint8_t key_index,
                                                int arg_count, ...);

#endif
