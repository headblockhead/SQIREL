#include "squirrel_constructors.h"
#include "squirrel_quantum.h"
#include "squirrel_types.h"

struct key make_key(void) {
  return (struct key){};
}

void key_add_keycode(struct key *key, uint8_t layer, uint8_t keycode) {
  key->rising[layer] = key_down;
  key->risingargs[layer] = keycode;
  key->falling[layer] = key_up;
  key->fallingargs[layer] = keycode;
}

void key_add_mod(struct key *key, uint8_t layer, uint8_t modifier_code) {
  key->rising[layer] = mod_down;
  key->risingargs[layer] = modifier_code;
  key->falling[layer] = mod_up;
  key->fallingargs[layer] = modifier_code;
}

void key_add_media(struct key *key, uint8_t layer, uint16_t media_code) {
  key->rising[layer] = media_down;
  key->risingargs[layer] = media_code;
  key->falling[layer] = media_up;
  key->fallingargs[layer] = media_code;
}

void key_add_momentary(struct key *key, uint8_t layer, uint8_t target_layer) {
  key->rising[layer] = momentary_rising;
  key->risingargs[layer] = target_layer;
  key->falling[layer] = momentary_falling;
  key->fallingargs[layer] = target_layer;
}

void key_add_pass_through(struct key *key, uint8_t layer) {
  key->rising[layer] = pass_through_rising;
  key->risingargs[layer] = 0;
  key->falling[layer] = pass_through_falling;
  key->fallingargs[layer] = 0;
}

void key_add_custom_code(struct key *key, uint8_t layer) {
  key->rising[layer] = custom_code_down;
  key->risingargs[layer] = 0;
  key->falling[layer] = custom_code_up;
  key->fallingargs[layer] = 0;
}
