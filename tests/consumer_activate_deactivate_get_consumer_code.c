#include "squirrel.h"
#include "squirrel_consumer.h"
#include "squirrel_key.h"
#include "squirrel_quantum.h"
#include <stdint.h>
#include <stdlib.h>

// test: consumer_activate_consumer_code + consumer_deactivate_consumer_code +
// consumer_get_consumer_code - in squirrel_consumer.c
int main() {
  for (uint16_t test_consumer_code = 0; test_consumer_code <= 65534;
       test_consumer_code++) {
    // consumer_activate_consumer_code
    consumer_activate_consumer_code(test_consumer_code);
    if (consumer_get_consumer_code() != test_consumer_code) {
      return 1;
    }
    // consumer_deactivate_consumer_code
    consumer_deactivate_consumer_code(test_consumer_code);
    if (consumer_get_consumer_code() != 0) {
      return 2;
    }
  }
};
