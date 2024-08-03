#ifndef SQUIRREL_H
#define SQUIRREL_H

#include <stdbool.h>
#include <stdint.h>

struct key {
  void (*pressed)(struct key *, ...);  // called when the key is pressed
  void *pressed_arguments;             // arguments to pass to pressed
  void (*released)(struct key *, ...); // called when the key is released
  void *released_arguments;            // arguments to pass to released
  bool is_pressed;                     // true if the key is currently pressed
};

extern int key_count; // number of keys on the keyboard

void press_key(
    uint8_t key_index); // Press the key at the index in the appropriate layer.
void release_key(uint8_t key_index); // Release the key at the index in the
                                     // appropriate layer.
void check_key(uint8_t key_index, bool is_pressed); // Check if the key at the
                                                    // index is pressed or
                                                    // released.
void init_keyboard(
    int total_keys); // Initialize the keyboard with the total number of keys.

#endif
