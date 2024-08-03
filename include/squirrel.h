#ifndef SQUIRREL_H
#define SQUIRREL_H

#include <stdint.h>

struct key {
  void *pressed(struct key *, ...);  // called when the key is pressed
  void *pressed_arguments;           // arguments to pass to pressed
  void *released(struct key *, ...); // called when the key is released
  void *released_arguments;          // arguments to pass to released
  bool is_pressed;                   // true if the key is currently pressed
};

struct layer {
  struct key *keys; // array of keys in this layer
  uint8_t num_keys; // number of keys in this layer
  bool active;      // true if this layer is currently active
};

struct keyboard {
  struct layer *layers; // array of layers in this keyboard
  uint8_t num_layers;   // number of layers in this keyboard
};

extern struct key *keys; // array of all keys on the keyboard
extern uint8_t num_keys; // number of keys on the keyboard

extern struct layer layers[16]; // array of all layers on the keyboard
extern struct layer
    floating_layer; // a layer that is not part of the keyboard, used for when
                    // keys are held, to help with cross-layer transitions

#endif
