#include "squirrel.h"
#include "squirrel_consumer.h"
#include "squirrel_key.h"
#include "squirrel_quantum.h"

// test: consumer_press + consumer_release - in squirrel_quantum.c
int main() {
  struct key test_key; // values unused
  enum squirrel_error err;
  for (uint16_t test_consumer_code = 0; test_consumer_code <= 65534;
       test_consumer_code++) {
    // consumer_press
    // no code becomes a code
    consumer_code = 0;
    err = consumer_press(&test_key, 0, 0, 1, test_consumer_code);
    if (err != ERR_NONE) {
      return 1;
    }
    if (consumer_code != test_consumer_code) {
      return 2;
    }
    // a code stays a code
    err = consumer_press(&test_key, 0, 0, 1, test_consumer_code);
    if (err != ERR_NONE) {
      return 3;
    }
    if (consumer_code != test_consumer_code) {
      return 4;
    }
    // another code becomes a code
    consumer_code = 0xFFFF;
    err = consumer_press(&test_key, 0, 0, 1, test_consumer_code);
    if (err != ERR_NONE) {
      return 5;
    }
    if (consumer_code != test_consumer_code) {
      return 6;
    }

    // consumer_release
    // a code becomes no code
    consumer_code = test_consumer_code;
    err = consumer_release(&test_key, 0, 0, 1, test_consumer_code);
    if (err != ERR_NONE) {
      return 7;
    }
    if (consumer_code != 0) {
      return 8;
    }
    // another code stays another code
    consumer_code = 0xFFFF;
    err = consumer_release(&test_key, 0, 0, 1, test_consumer_code);
    if (err != ERR_NONE) {
      return 9;
    }
    if (consumer_code != 0xFFFF) {
      return 10;
    }
  }

  // Test expected errors
  err = consumer_press(&test_key, 0, 0, 0, 0);
  if (err != ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT) {
    return 11;
  }
  err = consumer_release(&test_key, 0, 0, 0, 0);
  if (err != ERR_KEY_FUNC_WRONG_ARGUMENT_COUNT) {
    return 12;
  }

  return 0;
};
