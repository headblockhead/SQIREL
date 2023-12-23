#include "hardware/gpio.h"
#include "pico/multicore.h"
#include "pico/stdlib.h"
#include "pico/time.h"
#include <stdio.h>
#include <string.h>

#include "bsp/board.h"
#include "tusb.h"

#include "usb_descriptors.h"

// A key represents a physical key on the keyboard.
struct key {
  uint_fast8_t row; // The row it is wired to
  uint_fast8_t col; // The column it is wired to
  void (*rising[16])(
      uint_fast8_t);           // A list of functions to call when the
                               // key is pressed down, for each layer (0-15)
  uint_fast8_t risingargs[16]; // The arguments to pass to each function in the
                               // rising list.
  void (*falling[16])(uint_fast8_t); // A list of functions to call when the
                                     // key is released, for each layer (0-15)
  uint_fast8_t fallingargs[16]; // The arguments to pass to each function in the
                                // falling list.
  bool pressed;                 // Whether the key is currently pressed down.
};

// active_keycodes is a list of all the keycodes that are currently pressed,
// theese are sent to the host with every keyboard HID report.
bool active_keycodes[256] = {};

// modifiers is a bitfield of all the modifier keys that are currently pressed.
uint_fast8_t modifiers = 0;

// USB Callbacks:

// Invoked when device is mounted
void tud_mount_cb(void){};
// Invoked when device is unmounted
void tud_umount_cb(void){};

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from
// bus
void tud_suspend_cb(bool remote_wakeup_en) { (void)remote_wakeup_en; }

// Invoked when usb bus is resumed
void tud_resume_cb(void) {}

// Send HID reports to the host

// Send a HID report with the given keycodes to the host.
static void send_hid_kbd_codes(uint8_t keycode_assembly[6]) {
  // skip if hid is not ready yet
  if (!tud_hid_ready()) {
    return;
  };
  tud_hid_keyboard_report(REPORT_ID_KEYBOARD, modifiers, keycode_assembly);
}

// Send a HID report with no keycodes to the host.
static void send_hid_kbd_null() {
  // skip if hid is not ready yet
  if (!tud_hid_ready()) {
    return;
  };
  tud_hid_keyboard_report(REPORT_ID_KEYBOARD, modifiers, NULL);
}

// Every 10ms, we will sent 1 report for each HID profile (keyboard, mouse etc
// ..) tud_hid_report_complete_cb() is used to send the next report after
// previous one is complete
void hid_task(void) {
  // Poll every 10ms
  const uint32_t interval_ms = 10;    // Time between each report
  static uint32_t next_report_ms = 0; // Time of next report

  if (board_millis() - next_report_ms < interval_ms) {
    return; // Running too fast, try again later.
  };
  next_report_ms += interval_ms; // Schedule next report

  // Reports are sent in a chain, with one report for each HID device.

  // First, send the keyboard report. 6 keycodes can be sent in each report as
  // being pressed.
  uint8_t keycode_assembly[6] = {0}; // The keycodes to send in the report.
  uint_fast8_t index = 0;            // The index of the keycode_assembly array.

  for (int i = 0; i <= 0xFF; i++) { // Loop through all keycodes
    if (active_keycodes[i]) {       // If the keycode is active (pressed down)
      keycode_assembly[index] = i;  // Add the keycode to the assembly array.
      index++;          // Increment the index of the assembly array.
      if (index >= 6) { // If the report is full, stop adding keycodes.
        break;
      }
    }
  }
  if (index > 0) { // If there are any keycodes to send, send them.
    send_hid_kbd_codes(keycode_assembly);
  } else {
    send_hid_kbd_null();
  }
}

// Invoked when sent REPORT successfully to host
// Application can use this to send the next report
// Note: For composite reports, report[0] is report ID
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const *report,
                                uint16_t len) {
  (void)instance;
  (void)report;
  (void)len;
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id,
                               hid_report_type_t report_type, uint8_t *buffer,
                               uint16_t reqlen) {
  // TODO not Implemented
  (void)instance;
  (void)report_id;
  (void)report_type;
  (void)buffer;
  (void)reqlen;

  return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id,
                           hid_report_type_t report_type, uint8_t const *buffer,
                           uint16_t bufsize) {
  (void)instance;
  (void)report_id;
  (void)report_type;
  (void)buffer;
  (void)bufsize;
}

void keydown(uint_fast8_t keycode) { active_keycodes[keycode] = true; }
void keyup(uint_fast8_t keycode) { active_keycodes[keycode] = false; }

void moddown(uint_fast8_t modcode) { modifiers |= modcode; }
void modup(uint_fast8_t modcode) { modifiers &= ~modcode; }

struct key key1 = {
    .row = 0,
    .col = 0,
    .rising = {moddown},
    .risingargs = {KEYBOARD_MODIFIER_LEFTCTRL},
    .falling = {modup},
    .fallingargs = {KEYBOARD_MODIFIER_LEFTCTRL},
};

struct key key2 = {
    .row = 0,
    .col = 1,
    .rising = {moddown},
    .risingargs = {KEYBOARD_MODIFIER_LEFTALT},
    .falling = {modup},
    .fallingargs = {KEYBOARD_MODIFIER_LEFTALT},
};

struct key key3 = {
    .row = 0,
    .col = 2,
    .rising = {keydown},
    .risingargs = {HID_KEY_C},
    .falling = {keyup},
    .fallingargs = {HID_KEY_C},
};

struct key key4 = {
    .row = 0,
    .col = 3,
    .rising = {keydown},
    .risingargs = {HID_KEY_D},
    .falling = {keyup},
    .fallingargs = {HID_KEY_D},
};

struct key key5 = {
    .row = 0,
    .col = 4,
    .rising = {keydown},
    .risingargs = {HID_KEY_E},
    .falling = {keyup},
    .fallingargs = {HID_KEY_E},
};

struct key *keys[5] = {&key1, &key2, &key3, &key4, &key5};

// core1_entry is the entry point for the second core, and runs the input
// checking cycle, and runs the pressed functions for each key.
void core1_entry() {
  for (int i = 0; i <= 4; i++) {
    gpio_init(i);
    gpio_set_dir(i, GPIO_IN);
    gpio_pull_down(i);
  }
  while (true) {
    for (int i = 0; i <= 4; i++) {
      if (gpio_get(i)) {
        if (!keys[i]->pressed) {
          keys[i]->pressed = true;
          if (keys[i]->rising[0] != NULL) {
            keys[i]->rising[0](keys[i]->risingargs[0]);
          }
        }
      } else {
        if (keys[i]->pressed) {
          keys[i]->pressed = false;
          if (keys[i]->falling[0] != NULL) {
            keys[i]->falling[0](keys[i]->fallingargs[0]);
          }
        }
      }
    }
  }
}

// the main function, runs the usb communication, the display, the rgb leds
// and communication with the second microcontroller.
int main(void) {
  board_init();
  tusb_init();

  // Start the second core
  multicore_launch_core1(core1_entry);

  while (1) {
    tud_task(); // tinyusb device task
    hid_task();
  }
}
