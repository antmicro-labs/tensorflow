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

#include "assistant_services.h"
#include "string.h"

// Globals
static AssistantServices assistantServices;
namespace {
  volatile unsigned int* const led_r_address = (unsigned int*)0x82005800;
  volatile unsigned int* const led_g_address = (unsigned int*)0x82006000;
  volatile unsigned int* const led_b_address = (unsigned int*)0x82006800;
}  // namespace

static void setLeds(unsigned int led_r, unsigned int led_g, unsigned int led_b) {
  *led_r_address = led_r;
  *led_g_address = led_g;
  *led_b_address = led_b;
}

void RespondToCommand(tflite::ErrorReporter* error_reporter,
                      int32_t current_time, const char* found_command,
                      uint8_t score, bool is_new_command) {
  if (is_new_command) {
    error_reporter->Report("Heard %s (%d) @%dms", found_command, score,
                           current_time);
    VoiceCommand command;
    if (strcmp("yes", found_command) == 0) {
      setLeds(0, 0, 1);
      command = VoiceCommand::Yes;
    } else if (strcmp("no", found_command) == 0) {
      setLeds(0, 1, 0);
      command = VoiceCommand::No;
    } else if (strcmp("up", found_command) == 0) {
      setLeds(0, 0, 0);
      command = VoiceCommand::Up;
    } else if (strcmp("down", found_command) == 0) {
      setLeds(0, 0, 0);
      command = VoiceCommand::Down;
    } else if (strcmp("left", found_command) == 0) {
      setLeds(0, 1, 1);
      command = VoiceCommand::Left;
    } else if (strcmp("right", found_command) == 0) {
      setLeds(1, 0, 0);
      command = VoiceCommand::Right;
    } else if (strcmp("on", found_command) == 0) {
      setLeds(1, 0, 1);
      command = VoiceCommand::On;
    } else if (strcmp("off", found_command) == 0) {
      setLeds(1, 1, 0);
      command = VoiceCommand::Off;
    } else if (strcmp("stop", found_command) == 0) {
      setLeds(0, 0, 0);
      command = VoiceCommand::Stop;
    } else if (strcmp("go", found_command) == 0) {
      setLeds(1, 1, 1);
      command = VoiceCommand::Go;
    } else if (strcmp("unknown", found_command) == 0) {
      setLeds(0, 0, 0);
      command = VoiceCommand::Unknown;
    } else {
      setLeds(0, 0, 0);
      command = VoiceCommand::Silence;
    }
    assistantServices.interpretVoiceCommand(command);
  }
}
