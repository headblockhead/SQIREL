#include "squirrel_quantum.h"
#include "squirrel.h"
#include "squirrel_keyboard.h"
#include <stdarg.h>
#include <stdint.h>

void noop(struct key *key, ...) { (void)key; }

void keyboard_press(struct key *key, uint8_t keycode) {
  activate_keycode(keycode);
}

void keyboard_release(struct key *key, uint8_t keycode) {
  deactivate_keycode(keycode);
}

void keyboard_modifier_press(struct key *key, uint8_t modifier) {
  activate_modifier(modifier);
}

void keyboard_modifier_release(struct key *key, uint8_t modifier) {
  deactivate_modifier(modifier);
}
