#ifndef SQUIRREL_TYPES_H
#define SQUIRREL_TYPES_H
#include <stdbool.h>
#include <stdint.h>

// key represents a physical key on the keyboard.
struct key {
  void (*rising[16])(
      struct key *, uint_fast8_t, uint_fast8_t, bool (*)[16],
      uint_fast8_t *);         // A list of functions to call when the
                               // key is pressed down, for each layer (0-15).
  uint_fast8_t risingargs[16]; // The argument to pass to the function in
                               // the rising list, for each layer (0-15).
  void (*falling[16])(
      struct key *, uint_fast8_t, uint_fast8_t, bool (*)[16],
      uint_fast8_t *);          // A list of functions to call when the
                                // key is released, for each layer (0-15).
  uint_fast8_t fallingargs[16]; // The argument to pass to the function in
                                // the falling list, for each layer (0-15).
  bool pressed; // Whether the key is currently pressed down, used to detect
                // rising and falling edges.
};
#endif
