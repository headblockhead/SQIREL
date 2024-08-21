#ifndef SQUIRREL_INIT_H
#define SQUIRREL_INIT_H
enum squirrel_error init_keyboard(
    int total_keys); // Initialize the keyboard with the total number of keys.
enum squirrel_error
deinit_keyboard(); // Deinitialize the keyboard. Frees memory.
#endif
