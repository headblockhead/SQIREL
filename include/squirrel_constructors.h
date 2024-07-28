#ifndef SQUIRREL_CONSTRUCTORS_H
#define SQUIRREL_CONSTRUCTORS_H

#include "squirrel_quantum.h"
#include "squirrel_types.h"

struct key make_key(uint8_t keycode);
struct key make_modifier(uint8_t modifier_code);
struct key make_media(uint8_t media_code);

#endif
