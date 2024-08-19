#ifndef SQUIRREL_H
#define SQUIRREL_H

#include <stdint.h>

enum squirrel_error {
  ERR_NONE = 0,
  ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT,
  ERR_PASSTHROUGH_ON_BOTTOM_LAYER
};

#endif
