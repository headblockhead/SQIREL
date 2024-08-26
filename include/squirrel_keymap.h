#ifndef SQUIRREL_KEYMAP_H
#define SQUIRREL_KEYMAP_H
#include "squirrel_key.h"

struct key nop(void);
struct key keyboard(uint8_t keycode);
struct key keyboard_modifier(uint8_t modifier);
struct key consumer(uint16_t consumer);
struct key passthrough(void);
struct key layer_momentary(uint8_t layer);
struct key layer_toggle(uint8_t layer);
struct key layer_solo(uint8_t layer);
#endif
