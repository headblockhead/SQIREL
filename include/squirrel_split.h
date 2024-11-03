#pragma once

#include <stdbool.h>
#include <stdint.h>

// get_packet takes a pointer to a 9-byte array and fills it with the data for
// the packet to be sent.
void get_packet(uint8_t (*packet)[9]);

// process_packet takes a pointer to a 9-byte array and extracts the data from
// it into the remote_keycodes, remote_modifiers, and remote_consumer_code.
void process_packet(uint8_t (*packet)[9]);

extern bool remote_keycodes[256];
extern uint8_t remote_modifiers;
extern uint16_t remote_consumer_code;
