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
                            int arg_count, void **args);

// keyboard_press expects a single uint8 keycode
enum squirrel_error keyboard_press(struct key *key, uint8_t layer,
                                   uint8_t key_index, int arg_count,
                                   void **args);

// keyboard_release expects a single uint8 keycode
enum squirrel_error keyboard_release(struct key *key, uint8_t layer,
                                     uint8_t key_index, int arg_count,
                                     void **args);

// keyboard_modifier_press expects a single uint8 modifier
enum squirrel_error keyboard_modifier_press(struct key *key, uint8_t layer,
                                            uint8_t key_index, int arg_count,
                                            void **args);

// keyboard_modifier_release expects a single uint8 modifier
enum squirrel_error keyboard_modifier_release(struct key *key, uint8_t layer,
                                              uint8_t key_index, int arg_count,
                                              void **args);

// consumer_press expects a single uint16 consumer code. See
// https://www.freebsddiary.org/APC/usb_hid_usages for all defined codes.
enum squirrel_error consumer_press(struct key *key, uint8_t layer,
                                   uint8_t key_index, int arg_count,
                                   void **args);

// consumer_release expects a single uint16 consumer code. See
// https://www.freebsddiary.org/APC/usb_hid_usages for all defined codes.
enum squirrel_error consumer_release(struct key *key, uint8_t layer,
                                     uint8_t key_index, int arg_count,
                                     void **args);

// quantum_passthrough_press passes the press action to the highest active layer
// below the current one. It expectes no extra args. Equivalent to KC_TRNS in
// QMK.
enum squirrel_error quantum_passthrough_press(struct key *key, uint8_t layer,
                                              uint8_t key_index, int arg_count,
                                              void **args);

// quantum_passthrough_release passes the release action to the highest active
// layer below the current one. It expectes no extra args. Equivalent to KC_TRNS
// in QMK.
enum squirrel_error quantum_passthrough_release(struct key *key, uint8_t layer,
                                                uint8_t key_index,
                                                int arg_count, void **args);

// layer_momentary_press activates the layer with the given index. It expects
// the layer number as the first uint8 argument. Equivalent to MO() in QMK.
enum squirrel_error layer_momentary_press(struct key *key, uint8_t layer,
                                          uint8_t key_index, int arg_count,
                                          void **args);

// layer_momentary_release deactivates the layer with the given index. It
// expects the layer number as the first uint8 argument. Equivalent to MO() in
// QMK.
enum squirrel_error layer_momentary_release(struct key *key, uint8_t layer,
                                            uint8_t key_index, int arg_count,
                                            void **args);

// layer_toggle_press toggles the layer with the given index. It expects the
// layer number as the first uint8 argument. Equivalent to TG() in QMK.
enum squirrel_error layer_toggle_press(struct key *key, uint8_t layer,
                                       uint8_t key_index, int arg_count,
                                       void **args);

// layer_toggle_release does nothing at the moment. It expects the layer number
// as a uint8 anyway - this is a placeholder for future functionality.
// Equivalent to TG() in QMK.
enum squirrel_error layer_toggle_release(struct key *key, uint8_t layer,
                                         uint8_t key_index, int arg_count,
                                         void **args);

// layer_solo_press turns off all other layers than the layer with the given
// index. It expects the layer number as the first uint8 argument. Equivalent to
// TO() in QMK.
enum squirrel_error layer_solo_press(struct key *key, uint8_t layer,
                                     uint8_t key_index, int arg_count,
                                     void **args);

// layer_solo_release does nothing at the moment. It expects the layer number
// as a uint8 anyway - this is a placeholder for future functionality.
// Equivalent to TO() in QMK.
enum squirrel_error layer_solo_release(struct key *key, uint8_t layer,
                                       uint8_t key_index, int arg_count,
                                       void **args);
#endif
