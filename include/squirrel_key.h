#ifndef SQUIRREL_KEY_H
#define SQUIRREL_KEY_H
#include <stdbool.h>
#include <stdint.h>

#ifndef SQUIRREL_KEYCOUNT
#define SQUIRREL_KEYCOUNT 1
#endif

typedef enum squirrel_error (*keyfunc)(uint8_t, uint8_t, void *);

struct key {
  keyfunc pressed;         // called when the key is pressed
  keyfunc released;        // called when the key is released
  void *pressed_argument;  // argument to pass to pressed
  void *released_argument; // argument to pass to released
};

void copy_key(
    struct key *source,
    struct key *destination); // Copy the values from one key to another.
enum squirrel_error press_key(
    uint8_t key_index); // Press the key at the index in the appropriate layer.
enum squirrel_error
release_key(uint8_t key_index); // Release the key at the index in the
                                // appropriate layer.

// key_states is an array of booleans that represent the state of each key. Used
// by check_key to determine if a key is pressed or released.
extern bool key_states[SQUIRREL_KEYCOUNT];

// check_key compares the state of the key at the index to the key_states array
// to determine if the key is pressed or released, and calls the appropriate
// function.
enum squirrel_error check_key(uint8_t key_index,
                              bool is_pressed); // Check if the key at the
                                                // index is pressed or
                                                // released.
#endif
