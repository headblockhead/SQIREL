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
  return (struct key){
      .pressed = keyboard_press,
      .released = keyboard_release,
      .pressed_argument = &keycode,
      .released_argument = &keycode,
  };
}

struct key keyboard_modifier(uint8_t modifier) {
  return (struct key){
      .pressed = keyboard_modifier_press,
      .released = keyboard_modifier_release,
      .pressed_argument = &modifier,
      .released_argument = &modifier,
  };
}

struct key consumer(uint16_t consumer) {
  return (struct key){
      .pressed = consumer_press,
      .released = consumer_release,
      .pressed_argument = &consumer,
      .released_argument = &consumer,
  };
}

struct key passthrough(void) {
  return (struct key){
      .pressed = quantum_passthrough_press,
      .released = quantum_passthrough_release,
  };
}

struct key layer_momentary(uint8_t layer) {
  return (struct key){
      .pressed = layer_momentary_press,
      .released = layer_momentary_release,
      .pressed_argument = &layer,
      .released_argument = &layer,
  };
}

struct key layer_toggle(uint8_t layer) {
  return (struct key){
      .pressed = layer_toggle_press,
      .released = layer_toggle_release,
      .pressed_argument = &layer,
      .released_argument = &layer,
  };
}

struct key layer_solo(uint8_t layer) {
  return (struct key){
      .pressed = layer_solo_press,
      .released = layer_solo_release,
      .pressed_argument = &layer,
      .released_argument = &layer,
  };
}
