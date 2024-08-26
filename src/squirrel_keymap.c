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
  struct key key = {
      .pressed = keyboard_press,
      .released = keyboard_release,
      .pressed_argument_count = 1,
      .released_argument_count = 1,
  };
  key.pressed_arguments = malloc(1 * sizeof(void *));
  key.released_arguments = malloc(1 * sizeof(void *));
  key.pressed_arguments[0] = &keycode;
  key.released_arguments[0] = &keycode;
  return key;
}

struct key keyboard_modifier(uint8_t modifier) {
  struct key key = {
      .pressed = keyboard_modifier_press,
      .released = keyboard_modifier_release,
      .pressed_argument_count = 1,
      .released_argument_count = 1,
  };
  key.pressed_arguments = malloc(1 * sizeof(void *));
  key.released_arguments = malloc(1 * sizeof(void *));
  key.pressed_arguments[0] = &modifier;
  key.released_arguments[0] = &modifier;
  return key;
}

struct key consumer(uint16_t consumer) {
  struct key key = {
      .pressed = consumer_press,
      .released = consumer_release,
      .pressed_argument_count = 1,
      .released_argument_count = 1,
  };
  key.pressed_arguments = malloc(1 * sizeof(void *));
  key.released_arguments = malloc(1 * sizeof(void *));
  key.pressed_arguments[0] = &consumer;
  key.released_arguments[0] = &consumer;
  return key;
}

struct key passthrough(void) {
  return (struct key){
      .pressed = quantum_passthrough_press,
      .released = quantum_passthrough_release,
      .pressed_argument_count = 0,
      .released_argument_count = 0,
  };
}

struct key layer_momentary(uint8_t layer) {
  struct key key = {
      .pressed = layer_momentary_press,
      .released = layer_momentary_release,
      .pressed_argument_count = 1,
      .released_argument_count = 1,
  };
  key.pressed_arguments = malloc(1 * sizeof(void *));
  key.released_arguments = malloc(1 * sizeof(void *));
  key.pressed_arguments[0] = &layer;
  key.released_arguments[0] = &layer;
  return key;
}

struct key layer_toggle(uint8_t layer) {
  struct key key = {
      .pressed = layer_toggle_press,
      .released = layer_toggle_release,
      .pressed_argument_count = 1,
      .released_argument_count = 1,
  };
  key.pressed_arguments = malloc(1 * sizeof(void *));
  key.released_arguments = malloc(1 * sizeof(void *));
  key.pressed_arguments[0] = &layer;
  key.released_arguments[0] = &layer;
  return key;
}

struct key layer_solo(uint8_t layer) {
  struct key key = {
      .pressed = layer_solo_press,
      .released = layer_solo_release,
      .pressed_argument_count = 1,
      .released_argument_count = 1,
  };
  key.pressed_arguments = malloc(1 * sizeof(void *));
  key.released_arguments = malloc(1 * sizeof(void *));
  key.pressed_arguments[0] = &layer;
  key.released_arguments[0] = &layer;
  return key;
}
