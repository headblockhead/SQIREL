#include "squirrel_consumer.h"
#include <stdint.h>

uint16_t consumer_code = 0;

void activate_consumer_code(uint16_t code) { consumer_code = code; }

void deactivate_consumer_code(uint16_t code) {
  if (consumer_code == code) {
    consumer_code = 0;
  }
}

uint16_t get_consumer_code() { return consumer_code; }
