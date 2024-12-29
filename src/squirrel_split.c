#include "squirrel_split.h"
#include "squirrel.h"
#include "squirrel_consumer.h"
#include "squirrel_keyboard.h"
#include <stdint.h>
#include <string.h>

void get_packet(uint8_t (*packet)[9]) {
  memset(*packet, 0, 9);
  uint8_t local_keycodes[6] = {0};
  keyboard_get_keycodes(&local_keycodes);
  memcpy(*packet, local_keycodes, 6);      // 0th to 5th byte
  (*packet)[6] = keyboard_get_modifiers(); // 6th byte
  uint16_t consumer = consumer_get_consumer_code();
  (*packet)[7] = consumer & 0xFF; // 7th byte
  (*packet)[8] = consumer >> 8;   // 8th byte
}

bool remote_keycodes[256] = {false};
uint8_t remote_modifiers = 0;
uint16_t remote_consumer_code = 0;

void process_packet(uint8_t (*packet)[9]) {
  for (int i = 0; i < 256; i++) {
    remote_keycodes[i] = false;
  }
  for (int i = 0; i < 6; i++) {
    if ((*packet)[i] == 0) {
      break;
    }
    remote_keycodes[(*packet)[i]] = true;
  }
  remote_modifiers = (*packet)[6];                           // 6th byte
  remote_consumer_code = (*packet)[7] | ((*packet)[8] << 8); // 7th and 8th byte
}
