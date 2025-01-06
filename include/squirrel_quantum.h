#pragma once

#include "squirrel.h"
#include "squirrel_key.h"
#include "squirrel_keyboard.h"
#include <stdarg.h>
#include <stdint.h>

struct layer {
  bool active; // true if this layer is currently active
  struct key *keys;
};

// layers is a list of all the layers in the keyboard. 0-15 are configured,
// layer 16 is used for held keys and should only be modified by SQUIRREL.
extern struct layer layers[17];

// key_nop does nothing (no operation)
enum squirrel_error key_nop(uint8_t layer, uint8_t key_index, void *arg);

// keyboard_press expects a single uint8 keycode
enum squirrel_error keyboard_press(uint8_t layer, uint8_t key_index, void *arg);

// keyboard_release expects a single uint8 keycode
enum squirrel_error keyboard_release(uint8_t layer, uint8_t key_index,
                                     void *arg);

// keyboard_modifier_press expects a single uint8 modifier
enum squirrel_error keyboard_modifier_press(uint8_t layer, uint8_t key_index,
                                            void *arg);

// keyboard_modifier_release expects a single uint8 modifier
enum squirrel_error keyboard_modifier_release(uint8_t layer, uint8_t key_index,
                                              void *arg);

// consumer_press expects a single uint16 consumer code. See
// https://www.freebsddiary.org/APC/usb_hid_usages for all defined codes.
enum squirrel_error consumer_press(uint8_t layer, uint8_t key_index, void *arg);

// consumer_release expects a single uint16 consumer code. See
// https://www.freebsddiary.org/APC/usb_hid_usages for all defined codes.
enum squirrel_error consumer_release(uint8_t layer, uint8_t key_index,
                                     void *arg);

// quantum_passthrough_press passes the press action to the highest active layer
// below the current one. It expectes no extra args. Equivalent to KC_TRNS in
// QMK.
enum squirrel_error quantum_passthrough_press(uint8_t layer, uint8_t key_index,
                                              void *arg);

// quantum_passthrough_release passes the release action to the highest active
// layer below the current one. It expectes no extra args. Equivalent to KC_TRNS
// in QMK.
enum squirrel_error quantum_passthrough_release(uint8_t layer,
                                                uint8_t key_index, void *arg);

// layer_momentary_press activates the layer with the given index. It expects
// the layer number as the first uint8 argument. Equivalent to MO() in QMK.
enum squirrel_error layer_momentary_press(uint8_t layer, uint8_t key_index,
                                          void *arg);

// layer_momentary_release deactivates the layer with the given index. It
// expects the layer number as the first uint8 argument. Equivalent to MO() in
// QMK.
enum squirrel_error layer_momentary_release(uint8_t layer, uint8_t key_index,
                                            void *arg);

// layer_toggle_press toggles the layer with the given index. It expects the
// layer number as the first uint8 argument. Equivalent to TG() in QMK.
enum squirrel_error layer_toggle_press(uint8_t layer, uint8_t key_index,
                                       void *arg);

// layer_toggle_release does nothing at the moment. It expects the layer number
// as a uint8 anyway - this is a placeholder for future functionality.
// Equivalent to TG() in QMK.
enum squirrel_error layer_toggle_release(uint8_t layer, uint8_t key_index,
                                         void *arg);
