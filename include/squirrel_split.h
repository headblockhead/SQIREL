#pragma once

#include <stdint.h>

// get_packet takes a pointer to a 9-byte array and fills it with the data for
// the packet to be sent.
void get_packet(uint8_t (*packet)[9]);

extern uint8_t remote_keycodes[6];
extern uint8_t remote_modifiers;
extern uint16_t remote_consumer_code;
