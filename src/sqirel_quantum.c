#include <stdbool.h>
#include <stdint.h>

#include "sqirel_keys.h"
#include "sqirel_quantum.h"
#include "sqirel_types.h"

// key_down marks the keycode as active in the active_keycodes array.
void key_down(struct key *key, uint_fast8_t keycode, uint_fast8_t layer) {
  (void)key;
  (void)layer;
  active_keycodes[keycode] = true; // Mark the keycode as active.
}
// key_up marks the keycode as inactive in the active_keycodes array.
void key_up(struct key *key, uint_fast8_t keycode, uint_fast8_t layer) {
  (void)key;
  (void)layer;
  active_keycodes[keycode] = false; // Mark the keycode as inactive.
}

// mod_down adds the modifier code to the modifiers variable.
void mod_down(struct key *key, uint_fast8_t modifier_code, uint_fast8_t layer) {
  (void)key;
  (void)layer;
  modifiers |=
      modifier_code; // OR the modifier code into the modifiers variable.
}
// mod_up removes the modifier code from the modifiers variable.
void mod_up(struct key *key, uint_fast8_t modifier_code, uint_fast8_t layer) {
  (void)key;

  (void)layer;
  modifiers &= ~modifier_code; // AND the inverse of the modifier code into the
                               // modifiers variable.
}

// pass_through_rising passes down the rising function of the key to the first
// active layer below it (but no layers below the default layer). Equivalent to
// KC_TRNS when paired with pass_through_falling.
void pass_through_rising(struct key *key, uint_fast8_t arg,
                         uint_fast8_t layer) {
  (void)arg;
  for (uint_fast8_t i = layer - 1; i >= default_layer;
       i--) { // Start at the layer below the current layer, go down until the
              // default layer.
    if (!layers[i]) { // If the layer is not active, skip it.
      continue;
    }
    key->rising[i](key, key->risingargs[i], i); // Call the rising function for
                                                // the layer.
  }
}

// pass_through_falling passes down the falling function of the key to the first
// active layer below it (but no layers below the default layer). Equivalent to
// KC_TRNS when paired with pass_through_rising.
void pass_through_falling(struct key *key, uint_fast8_t arg,
                          uint_fast8_t layer) {
  (void)arg;
  for (uint_fast8_t i = layer - 1; i >= default_layer;
       i--) { // Start at the layer below the current layer, go down until the
              // default layer.
    if (!layers[i]) { // If the layer is not active, skip it.
      continue;
    }
    key->falling[i](key, key->fallingargs[i], i); // Call the falling function
                                                  // for the layer.
  }
}

// momentary_rising sets the target layer to active when run. Equivalent to
// MO(layer) when paired with momentary_falling.
void momentary_rising(struct key *key, uint_fast8_t target_layer,
                      uint_fast8_t layer) {
  (void)key;
  (void)layer;
  layers[target_layer] = true;
}

// momentary_falling sets the target layer to inactive when run. Equivalent to
// MO(layer) when paired with momentary_rising.
void momentary_falling(struct key *key, uint_fast8_t target_layer,
                       uint_fast8_t layer) {
  (void)key;
  (void)layer;
  layers[target_layer] = false;
}

// toggle toggles the target layer when the key is pressed. Can be
// assigned to rising or falling functions. Equivalent to TG(layer).
void toggle(struct key *key, uint_fast8_t target_layer, uint_fast8_t layer) {
  (void)key;
  if (layer == target_layer) {
    layer = default_layer;
  } else {
    layer = target_layer;
  }
}

// turn_on turns on the target layer, while disabling all other layers (apart
// from the default layer). Can be assigned to rising or falling functions.
// Equivalent to TO(layer).
void turn_on(struct key *key, uint_fast8_t target_layer, uint_fast8_t layer) {
  (void)key;
  (void)layer;
  for (int i = 0; i <= 15; i++) {
    layers[i] = false;
  }
  layers[default_layer] = true;
  layers[target_layer] = true;
}

// default_set changes the default layer to the target layer. Can be assigned to
// rising or falling functions. Equivalent to DF(layer).
void default_set(struct key *key, uint_fast8_t target_layer,
                 uint_fast8_t layer) {
  (void)key;
  (void)layer;
  default_layer = target_layer;
}
