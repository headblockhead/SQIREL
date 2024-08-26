#ifndef SQUIRREL_INIT_H
#define SQUIRREL_INIT_H
enum squirrel_error squirrel_init(
    int total_keys); // Initialize the keyboard with the total number of keys.
enum squirrel_error
squirrel_deinit(); // Deinitialize the keyboard. Frees memory.
#endif
