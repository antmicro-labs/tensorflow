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

// Globals
static AssistantServices assistantServices;


void RespondToCommand(tflite::ErrorReporter* error_reporter,
                      int32_t current_time, const char* found_command,
                      uint8_t score, bool is_new_command) {
  

  volatile unsigned int* ledr = (unsigned int*)0x82005800;
  volatile unsigned int* ledg = (unsigned int*)0x82006000;
  volatile unsigned int* ledb = (unsigned int*)0x82006800;

  if (is_new_command) {
    error_reporter->Report("Heard %s (%d) @%dms", found_command, score,
                           current_time);
    VoiceCommand command;
    if (found_command[0] == 'y') {
      *ledr = 1;
      *ledg = 0;
      *ledb = 0;
      command = VoiceCommand::Yes;
    }
    if (found_command[0] == 'n') {
      *ledr = 0;
      *ledg = 1;
      *ledb = 0;
      command = VoiceCommand::No;
    }
    if (found_command[0] == 'u') {
      *ledr = 0;
      *ledg = 0;
      *ledb = 1;
    }
    assistantServices.interpretVoiceCommand(command);
  }
}
