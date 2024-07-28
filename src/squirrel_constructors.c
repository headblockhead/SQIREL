#include "squirrel_constructors.h"
#include "squirrel_quantum.h"
#include "squirrel_types.h"

// Make a default key struct with the given keycode
struct key make_key(uint8_t keycode) {
  return (struct key){
      .rising = {key_down},
      .risingargs = {keycode},
      .falling = {key_up},
      .fallingargs = {keycode},
  };
}

struct key make_modifier(uint8_t modifier_code) {
  return (struct key){
      .rising = {mod_down},
      .risingargs = {modifier_code},
      .falling = {mod_up},
      .fallingargs = {modifier_code},
  };
}

struct key make_media(uint8_t media_code) {
  return (struct key){
      .rising = {media},
      .risingargs = {media_code},
  };
}
