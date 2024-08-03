// SQUIRREL_CONSUMER_H provides an interface for interacting as a USB HID
// Consumer Control device.
#ifndef SQUIRREL_CONSUMER_H
#define SQUIRREL_CONSUMER_H

#include <stdint.h>

// The currently active consumer code. Only one consumer code can be active at a
// time.
extern uint16_t consumer_code;

// activate_consumer_code sets the provided consumer code as the active consumer
// code.
void activate_consumer_code(uint16_t consumer_code);

// deactivate_consumer_code sets the active consumer code to 0 if it is the
// provided consumer code.
void deactivate_consumer_code(uint16_t consumer_code);

// get_consumer_code returns the currently active consumer code.
uint16_t get_consumer_code();

#endif
