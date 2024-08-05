#include "squirrel.h"
#include "squirrel_quantum.h"

int main() {
  init_keyboard(75);
  struct key test_key;
  test_key.pressed = &keyboard_press;
  test_key.released = &keyboard_press;
  return 0;
};
