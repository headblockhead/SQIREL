// SQUIRREL_CONSUMER_H provides an interface for interacting as a USB HID
// Consumer Control device.
#pragma once

#include <stdint.h>

// The currently active consumer code. Only one consumer code can be active at a
// time.
extern uint16_t consumer_code;

// consumer_activate_consumer_code sets the provided consumer code as the active
// consumer code.
void consumer_activate_consumer_code(uint16_t consumer_code);
// consumer_deactivate_consumer_code sets the active consumer code to 0 if it is
// the provided consumer code.
void consumer_deactivate_consumer_code(uint16_t consumer_code);
// consumer_get_consumer_code returns the currently active consumer code.
uint16_t consumer_get_consumer_code();
