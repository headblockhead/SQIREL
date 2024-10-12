#include "squirrel_key.h"
#include "squirrel_quantum.h"
#include <stdlib.h>

struct key nop(void) {
  return (struct key){
      .pressed = key_nop,
      .released = key_nop,
  };
}

struct key keyboard(uint8_t keycode) {
  uint8_t *new_keycode = malloc(sizeof(uint8_t));
  *new_keycode = keycode;
  return (struct key){
      .pressed = keyboard_press,
      .released = keyboard_release,
      .pressed_argument = new_keycode,
      .released_argument = new_keycode,
  };
}

struct key keyboard_modifier(uint8_t modifier) {
  uint8_t *new_modifier = malloc(sizeof(uint8_t));
  *new_modifier = modifier;
  return (struct key){
      .pressed = keyboard_modifier_press,
      .released = keyboard_modifier_release,
      .pressed_argument = new_modifier,
      .released_argument = new_modifier,
  };
}

struct key consumer(uint16_t consumer) {
  uint16_t *new_consumer = malloc(sizeof(uint16_t));
  *new_consumer = consumer;
  return (struct key){
      .pressed = consumer_press,
      .released = consumer_release,
      .pressed_argument = new_consumer,
      .released_argument = new_consumer,
  };
}

struct key passthrough(void) {
  return (struct key){
      .pressed = quantum_passthrough_press,
      .released = quantum_passthrough_release,
  };
}

struct key layer_momentary(uint8_t layer) {
  uint8_t *new_layer = malloc(sizeof(uint8_t));
  *new_layer = layer;
  return (struct key){
      .pressed = layer_momentary_press,
      .released = layer_momentary_release,
      .pressed_argument = new_layer,
      .released_argument = new_layer,
  };
}

struct key layer_toggle(uint8_t layer) {
  uint8_t *new_layer = malloc(sizeof(uint8_t));
  *new_layer = layer;
  return (struct key){
      .pressed = layer_toggle_press,
      .released = layer_toggle_release,
      .pressed_argument = new_layer,
      .released_argument = new_layer,
  };
}

struct key layer_solo(uint8_t layer) {
  uint8_t *new_layer = malloc(sizeof(uint8_t));
  *new_layer = layer;
  return (struct key){
      .pressed = layer_solo_press,
      .released = layer_solo_release,
      .pressed_argument = new_layer,
      .released_argument = new_layer,
  };
}
