#ifndef SQUIRREL_QUANTUM_H
#define SQUIRREL_QUANTUM_H
#include <stdbool.h>
#include <stdint.h>

#include "squirrel_keys.h"
#include "squirrel_types.h"

// if custom_code_active is true, the keyboard is in custom code mode and will
// ignore keycodes from the key_down/up functions - instead redirecting them to
// the custom code buffer.
extern bool custom_code_active;

// custom_code_buffer holds the custom code entered by the user. The buffer's
// contents are read and the keycode entered is set to active when the ENTER key
// is pressed.
extern uint16_t custom_code_buffer; // entered in binary - 8 bits for keycode,
                                    // 16 bits for media code.
extern uint8_t custom_code_buffer_index; // index of the buffer

// layers is a list of all quantum layers in the keyboard, when a key is pressed
// the layers are read top (15) to bottom (default_layer), with only active
// layers (layers that are 'true' in this array) being read.
extern bool layers[16];

// The defualt layer is always active, it is the bottom layer of the
// layer stack and no layers below it will be read.
extern uint8_t default_layer;

// key_down marks the keycode as active in the active_keycodes array.
void key_down(struct key *key, uint16_t keycode, uint8_t layer);
// key_up marks the keycode as inactive in the active_keycodes array.
void key_up(struct key *key, uint16_t keycode, uint8_t layer);

// mod_down adds the modifier code to the modifiers variable.
void mod_down(struct key *key, uint16_t modifier_code, uint8_t layer);
// mod_up removes the modifier code from the modifiers variable.
void mod_up(struct key *key, uint16_t modifier_code, uint8_t layer);

// media_down sets the media code to the media_code.
void media_down(struct key *key, uint16_t media_code, uint8_t layer);

// media_up sets the media code back to 0.
void media_up(struct key *key, uint16_t media_code, uint8_t layer);

// custom_code_down sets the keyboard to custom code mode.
void custom_code_down(struct key *key, uint16_t arg, uint8_t layer);

// custom_code_up sets the keyboard to normal mode and lifts up the custom code
// key.
void custom_code_up(struct key *key, uint16_t arg, uint8_t layer);

// pass_through_rising passes down the rising function of the key to the first
// active layer below it (but no layers below the default layer). Equivalent to
// KC_TRNS when paired with pass_through_falling.
void pass_through_rising(struct key *key, uint16_t arg, uint8_t layer);

// pass_through_falling passes down the falling function of the key to the first
// active layer below it (but no layers below the default layer). Equivalent to
// KC_TRNS when paired with pass_through_rising.
void pass_through_falling(struct key *key, uint16_t arg, uint8_t layer);

// momentary_rising sets the target layer to active when run. Equivalent to
// MO(layer) when paired with momentary_falling.
void momentary_rising(struct key *key, uint16_t target_layer, uint8_t layer);

// momentary_falling sets the target layer to inactive when run. Equivalent to
// MO(layer) when paired with momentary_rising.
void momentary_falling(struct key *key, uint16_t target_layer, uint8_t layer);

// toggle toggles the target layer when the key is pressed. Can be
// assigned to rising or falling functions. Equivalent to TG(layer).
void toggle(struct key *key, uint16_t target_layer, uint8_t layer);

// turn_on turns on the target layer, while disabling all other layers (apart
// from the default layer). Can be assigned to rising or falling functions.
// Equivalent to TO(layer).
void turn_on(struct key *key, uint16_t target_layer, uint8_t layer);

// default_set changes the default layer to the target layer. Can be assigned to
// rising or falling functions. Equivalent to DF(layer).
void default_set(struct key *key, uint16_t target_layer, uint8_t layer);
#endif
