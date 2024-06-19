#ifndef SQUIRREL_CONSTRUCTORS_H
#define SQUIRREL_CONSTRUCTORS_H

#include "squirrel_quantum.h"
#include "squirrel_types.h"

struct key make_key(uint_fast8_t keycode);
struct key make_modifier(uint_fast8_t modifier_code);

#endif
