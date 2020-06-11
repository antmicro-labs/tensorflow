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

// TensorFlow Headers
#include "tensorflow/lite/micro/examples/micro_speech/audio_provider.h"

#include "tensorflow/lite/micro/examples/micro_speech/micro_features/micro_model_settings.h"
#include <zephyr.h>
#include <kernel.h>
#include <drivers/i2s.h>

namespace {

constexpr int MY_STACK_SIZE = 500;
constexpr int MY_PRIORITY = -1;

struct k_thread my_thread_data;
K_THREAD_STACK_DEFINE(my_stack_area, MY_STACK_SIZE);
constexpr int AUDIO_SAMPLES_PER_CH_PER_FRAME = 128;
constexpr int AUDIO_NUM_CHANNELS = 1;
constexpr int AUDIO_SAMPLES_PER_FRAME = 
        AUDIO_SAMPLES_PER_CH_PER_FRAME * AUDIO_NUM_CHANNELS;
constexpr int AUDIO_SAMPLE_BYTES = 2;
constexpr int AUDIO_SAMPLE_BIT_WIDTH = 16;

constexpr int AUDIO_FRAME_BUF_BYTES = 
        AUDIO_SAMPLES_PER_FRAME * AUDIO_SAMPLE_BYTES;
constexpr int I2S_PLAY_BUF_COUNT = 500;

bool g_is_audio_initialized = false;
constexpr int kAudioCaptureBufferSize = kAudioSampleFrequency * 0.5;
int16_t g_audio_capture_buffer[kAudioCaptureBufferSize];
int16_t g_audio_output_buffer[kMaxAudioSampleSize];
int32_t g_latest_audio_timestamp = 0;

struct device *host_i2s_rx_dev;
struct k_mem_slab i2s_rx_mem_slab;
char rx_buffers[AUDIO_FRAME_BUF_BYTES * I2S_PLAY_BUF_COUNT];
struct i2s_config i2s_rx_cfg;

void CaptureSamples(const int16_t *sample_data) {
  const int sample_size = AUDIO_SAMPLES_PER_FRAME;
  const int32_t time_in_ms =
      g_latest_audio_timestamp + (sample_size / (kAudioSampleFrequency / 1000));
  const int32_t start_sample_offset =
      g_latest_audio_timestamp * (kAudioSampleFrequency / 1000);
  for (int i = 0; i < sample_size; ++i) {
    const int capture_index =
        (start_sample_offset + i) % kAudioCaptureBufferSize;
    g_audio_capture_buffer[capture_index] = sample_data[i];
  }
  // This is how we let the outside world know that new audio data has arrived.
  g_latest_audio_timestamp = time_in_ms;
}

void getAudio(void *, void *, void *)
{
    void *rx_mem_block;
    size_t size;
    while (1) {
       auto ret = i2s_read(host_i2s_rx_dev, &rx_mem_block, &size);
       CaptureSamples((int16_t*)rx_mem_block);
       k_mem_slab_free(&i2s_rx_mem_slab, &rx_mem_block);
    }
}

// Initalization for receiving audio data
TfLiteStatus InitAudioRecording(tflite::ErrorReporter *error_reporter) {
    int ret;
    //configure rx device
    host_i2s_rx_dev = device_get_binding("i2s_rx");
    if (!host_i2s_rx_dev) {
        error_reporter->Report("unable to find i2s_rx device");
        return kTfLiteError;
    }
    k_mem_slab_init(&i2s_rx_mem_slab, rx_buffers, AUDIO_FRAME_BUF_BYTES,
    I2S_PLAY_BUF_COUNT);

    /* configure i2s for audio playback */
    i2s_rx_cfg.word_size = AUDIO_SAMPLE_BIT_WIDTH;
    i2s_rx_cfg.channels = AUDIO_NUM_CHANNELS;
    i2s_rx_cfg.format = I2S_FMT_DATA_FORMAT_I2S;
    i2s_rx_cfg.options = I2S_OPT_FRAME_CLK_SLAVE;
    i2s_rx_cfg.frame_clk_freq = kAudioSampleFrequency;
    i2s_rx_cfg.block_size = AUDIO_FRAME_BUF_BYTES;
    i2s_rx_cfg.mem_slab = &i2s_rx_mem_slab;
    i2s_rx_cfg.timeout = -1;
    ret = i2s_configure(host_i2s_rx_dev, I2S_DIR_RX, &i2s_rx_cfg);

    if (ret != 0) {
        error_reporter->Report("i2s_configure failed with %d error", ret);
        return kTfLiteError;
    }
    /* start i2s rx driver */
    ret = i2s_trigger(host_i2s_rx_dev, I2S_DIR_RX, I2S_TRIGGER_START);
    if (ret != 0) {
        error_reporter->Report("i2s_trigger failed with %d error", ret);
        return kTfLiteError;
    }
    // creating thread problably can't failed 
    k_thread_create(&my_thread_data, my_stack_area,
                    K_THREAD_STACK_SIZEOF(my_stack_area),
                    getAudio,
                    NULL, NULL, NULL,
                    MY_PRIORITY, 0, K_NO_WAIT);
    error_reporter->Report("I2s cofigured");
    return kTfLiteOk;
}

}  // namespace

// Main entry point for getting audio data.
TfLiteStatus GetAudioSamples(tflite::ErrorReporter *error_reporter,
                             int start_ms, int duration_ms,
                             int *audio_samples_size, int16_t **audio_samples) {
    if (!g_is_audio_initialized) {
        TfLiteStatus init_status = InitAudioRecording(error_reporter);
        if (init_status != kTfLiteOk) {
            return init_status;
        }
        g_is_audio_initialized = true;
    }
    // This should only be called when the main thread notices that the latest
    // audio sample data timestamp has changed, so that there's new data in the
    // capture ring buffer. The ring buffer will eventually wrap around and
    // overwrite the data, but the assumption is that the main thread is checking
    // often enough and the buffer is large enough that this call will be made
    // before that happens.
    const int start_offset = start_ms * (kAudioSampleFrequency / 1000);
    const int duration_sample_count =
        duration_ms * (kAudioSampleFrequency / 1000);

    for (int i = 0; i < duration_sample_count; ++i) {
      const int capture_index = (start_offset + i) % kAudioCaptureBufferSize;
      g_audio_output_buffer[i] = g_audio_capture_buffer[capture_index];
    }
    *audio_samples_size = kMaxAudioSampleSize;
    *audio_samples = g_audio_output_buffer;
    return kTfLiteOk;
}

int32_t LatestAudioTimestamp() {
  return g_latest_audio_timestamp;
}
