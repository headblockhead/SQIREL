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
  uint_fast8_t row;             // The row it is wired to
  uint_fast8_t col;             // The column it is wired to
  void (*rising[16])(uint8_t);  // A list of functions to call when the
                                // key is pressed down, for each layer (0-15)
  uint8_t risingargs[16];       // The arguments to pass to each function in the
                                // rising list.
  void (*falling[16])(uint8_t); // A list of functions to call when the
                                // key is released, for each layer (0-15)
  uint8_t fallingargs[16];      // The arguments to pass to each function in the
                                // falling list.
  bool pressed;                 // Whether the key is currently pressed down.
};

bool active_keycodes[256] = {};

// USB Callbacks:

bool device_connected = false;

// Invoked when device is mounted
void tud_mount_cb(void) { device_connected = true; };
// Invoked when device is unmounted
void tud_umount_cb(void) { device_connected = false; };

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from
// bus
void tud_suspend_cb(bool remote_wakeup_en) { (void)remote_wakeup_en; }

// Invoked when usb bus is resumed
void tud_resume_cb(void) {}

// Send HID report to host
static void send_hid_keycode(uint8_t keycode_assembly[6]) {
  // skip if hid is not ready yet
  if (!tud_hid_ready())
    return;
  tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode_assembly);
}

static void send_null_hid_report() {
  // skip if hid is not ready yet
  if (!tud_hid_ready())
    return;
  tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
}

// Every 10ms, we will sent 1 report for each HID profile (keyboard, mouse etc
// ..) tud_hid_report_complete_cb() is used to send the next report after
// previous one is complete
void hid_task(void) {
  // Poll every 10ms
  const uint32_t interval_ms = 10;
  static uint32_t start_ms = 0;

  if (board_millis() - start_ms < interval_ms)
    return; // not enough time
  start_ms += interval_ms;

  // Send the 1st of report chain, the rest will be sent by
  // tud_hid_report_complete_cb()

  uint8_t keycode_assembly[6] = {0};
  uint_fast8_t index = 0;
  for (int i = 0; i < 256; i++) {
    if (active_keycodes[i]) {
      if (index >= 6) {
        send_hid_keycode(keycode_assembly);
        break;
      }
      keycode_assembly[index] = i;
      index++;
    }
  }
  if (index < 6) {
    send_hid_keycode(keycode_assembly);
  } else if (index == 0) {
    send_null_hid_report();
  }
}

// Invoked when sent REPORT successfully to host
// Application can use this to send the next report
// Note: For composite reports, report[0] is report ID
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const *report,
                                uint16_t len) {
  (void)instance;
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
}

void keydown(uint8_t keycode) { active_keycodes[keycode] = true; }
void keyup(uint8_t keycode) { active_keycodes[keycode] = false; }

struct key key1 = {
    .row = 0,
    .col = 0,
    .rising = {keydown},
    .risingargs = {HID_KEY_A},
    .falling = {keyup},
    .fallingargs = {HID_KEY_A},
};

struct key key2 = {
    .row = 0,
    .col = 1,
    .rising = {keydown},
    .risingargs = {HID_KEY_B},
    .falling = {keyup},
    .fallingargs = {HID_KEY_B},
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
            sleep_ms(10);
          }
        }
      } else {
        if (keys[i]->pressed) {
          keys[i]->pressed = false;
          if (keys[i]->falling[0] != NULL) {
            keys[i]->falling[0](keys[i]->fallingargs[0]);
            sleep_ms(10);
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
