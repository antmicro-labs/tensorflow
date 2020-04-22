/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "tensorflow/lite/micro/examples/micro_speech/command_responder.h"
#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>

#define LED_PORT0	DT_ALIAS_LED0_GPIOS_CONTROLLER
#define LED_PORT1	DT_ALIAS_LED1_GPIOS_CONTROLLER
#define LED_PORT2	DT_ALIAS_LED2_GPIOS_CONTROLLER
#define LED0		DT_ALIAS_LED0_GPIOS_PIN
#define LED1		DT_ALIAS_LED1_GPIOS_PIN
#define LED2		DT_ALIAS_LED2_GPIOS_PIN

// The default implementation writes out the name of the recognized command
// to the error console. The extended implementation turns on LEDs coresponding to commands
void RespondToCommand(tflite::ErrorReporter* error_reporter,
                      int32_t current_time, const char* found_command,
                      uint8_t score, bool is_new_command) {

  struct device *dev0, *dev1, *dev2;

  dev0 = device_get_binding(LED_PORT0);
  dev1 = device_get_binding(LED_PORT1);
  dev2 = device_get_binding(LED_PORT2);
  /* Set LED pins as output */
  gpio_pin_configure(dev0, LED0, GPIO_DIR_OUT);
  gpio_pin_configure(dev1, LED1, GPIO_DIR_OUT);
  gpio_pin_configure(dev2, LED2, GPIO_DIR_OUT);

  if (is_new_command) {
    error_reporter->Report("Heard %s (%d) @%dms", found_command, score,
                           current_time);

    if (found_command[0] == 'y') {
      gpio_pin_write(dev0, LED0, 1);
    }
    if (found_command[0] == 'n') {
      gpio_pin_write(dev1, LED1, 1);
    }
    if (found_command[0] == 'u') {
      gpio_pin_write(dev2, LED2, 1);
    }
  }
}
