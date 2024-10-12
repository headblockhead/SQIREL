#include "squirrel.h"
#include "squirrel_init.h"
#include "squirrel_key.h"
#include "squirrel_keymap.h"
#include "squirrel_quantum.h"
#include <stdarg.h>
#include <stdlib.h>

int main() {
  squirrel_init();

  layers[0].keys[0] = keyboard(0x00);
  layers[0].keys[1] = keyboard(0x01);

  if (*(uint8_t *)(layers[0].keys[0].pressed_argument) != 0x00) {
    return 1;
  }
  if (*(uint8_t *)(layers[0].keys[1].pressed_argument) != 0x01) {
    return 2;
  }
}
