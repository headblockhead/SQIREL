#include "squirrel.h"
#include "squirrel_key.h"
#include "squirrel_keyboard.h"
#include "squirrel_quantum.h"

// test: keyboard_get_keycodes - in squirrel_keyboard.c
int main() {
  uint8_t active_keycodes[6] = {0, 0, 0, 0, 0, 0};
  keyboard_get_keycodes(&active_keycodes);
  for (uint8_t i = 0; i < 6; i++) {
    if (active_keycodes[i] != 0) {
      return 1;
    }
  }
  for (int i = 0; i < 6; i++) {
    keyboard_keycodes[i] = true;
  }
  keyboard_get_keycodes(&active_keycodes);
  for (uint8_t i = 0; i < 6; i++) {
    if (active_keycodes[i] != i) {
      return 2;
    }
  }
  keyboard_keycodes[7] = true;
  keyboard_get_keycodes(&active_keycodes);
  for (uint8_t i = 0; i < 6; i++) {
    if (active_keycodes[i] != i) {
      return 3;
    }
  }
  return 0;
};
