#ifndef SQUIRREL_H
#define SQUIRREL_H

#include <stdint.h>

enum squirrel_error {
  ERR_NONE = 0,
  ERR_PASSTHROUGH_ON_BOTTOM_LAYER,
  ERR_OUT_OF_MEMORY_KEYS,
  ERR_OUT_OF_MEMORY_KEY_STATES,
};

#endif
