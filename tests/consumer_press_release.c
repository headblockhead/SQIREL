#include "squirrel.h"
#include "squirrel_consumer.h"
#include "squirrel_key.h"
#include "squirrel_quantum.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// test: consumer_press + consumer_release - in squirrel_quantum.c
int main() {
  struct key test_key; // values unused
  enum squirrel_error err;
  for (uint16_t test_consumer_code = 0; test_consumer_code != 0xFFFF;
       test_consumer_code++) {
    // consumer_press
    // no code becomes a code
    consumer_code = 0;
    err = consumer_press(&test_key, 0, 0, &test_consumer_code);
    if (err != ERR_NONE) {
      printf("err while testing with test_consumer_code %d,\n",
             test_consumer_code);
      printf("err from consumer_press in test 1: %d\n", err);
      return 1;
    }
    if (consumer_code != test_consumer_code) {
      printf("err while testing with test_consumer_code %d,\n",
             test_consumer_code);
      printf("consumer_code not equal to test_consumer_code in consumer_press "
             "test 1: "
             "%d\n",
             consumer_code);
      return 1;
    }
    // a code stays a code
    err = consumer_press(&test_key, 0, 0, &test_consumer_code);
    if (err != ERR_NONE) {
      printf("err while testing with test_consumer_code %d,\n",
             test_consumer_code);
      printf("err from consumer_press in test 2: %d\n", err);
      return 1;
    }
    if (consumer_code != test_consumer_code) {
      printf("err while testing with test_consumer_code %d,\n",
             test_consumer_code);
      printf("consumer_code not equal to test_consumer_code in consumer_press "
             "test 2: "
             "%d\n",
             consumer_code);
      return 1;
    }
    // another code becomes a code
    consumer_code = 0xFFFF;
    err = consumer_press(&test_key, 0, 0, &test_consumer_code);
    if (err != ERR_NONE) {
      printf("err while testing with test_consumer_code %d,\n",
             test_consumer_code);
      printf("err from consumer_press in test 3: %d\n", err);
      return 1;
    }
    if (consumer_code != test_consumer_code) {
      printf("err while testing with test_consumer_code %d,\n",
             test_consumer_code);
      printf("consumer_code not equal to test_consumer_code in consumer_press "
             "test 3: "
             "%d\n",
             consumer_code);
      return 1;
    }

    // consumer_release
    // a code becomes no code
    consumer_code = test_consumer_code;
    err = consumer_release(&test_key, 0, 0, &test_consumer_code);
    if (err != ERR_NONE) {
      printf("err while testing with test_consumer_code %d,\n",
             test_consumer_code);
      printf("err from consumer_release in test 1: %d\n", err);
      return 1;
    }
    if (consumer_code != 0) {
      printf("err while testing with test_consumer_code %d,\n",
             test_consumer_code);
      printf("consumer_code not equal to 0 in consumer_release test 1: %d\n",
             consumer_code);
      return 1;
    }
    // another code stays another code
    consumer_code = 0xFFFF;
    err = consumer_release(&test_key, 0, 0, &test_consumer_code);
    if (err != ERR_NONE) {
      printf("err while testing with test_consumer_code %d,\n",
             test_consumer_code);
      printf("err from consumer_release in test 2: %d\n", err);
      return 1;
    }
    if (consumer_code != 0xFFFF) {
      printf("err while testing with test_consumer_code %d,\n",
             test_consumer_code);
      printf("consumer_code not equal to 0xFFFF in consumer_release test 2: "
             "%d\n",
             consumer_code);
      return 1;
    }
  }
  return 0;
};
