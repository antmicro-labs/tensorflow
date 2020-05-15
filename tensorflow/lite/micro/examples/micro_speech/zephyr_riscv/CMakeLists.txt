cmake_minimum_required(VERSION 3.13.1)
include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(tf_lite_microspeech)

set(TF_DIR ${PROJECT_SOURCE_DIR}/../../../../../../)
set(TF_LITE_DIR ${TF_DIR}/tensorflow/lite/)
set(TF_MICRO_DIR ${TF_DIR}/tensorflow/lite/micro/)

set(MICROFRONTEND ${TF_LITE_DIR}/experimental/microfrontend/lib/)
set(KISS_FFT ${TF_MICRO_DIR}/tools/make/downloads/kissfft/)

set(MICRO_SPEECH ${TF_MICRO_DIR}/examples/micro_speech/)
set(MICRO_FEATURES ${MICRO_SPEECH}/micro_features/)
set(SIMPLE_FEATURES ${MICRO_SPEECH}/simple_features/)

file(GLOB MICRO_SOURCES ${TF_MICRO_DIR}/*cc)
file(GLOB MICRO_HEADERS ${TF_MICRO_DIR}/*.h)
file(GLOB MICRO_TESTS_SOURCES ${TF_MICRO_DIR}/*test.cc)
file(GLOB MICRO_KERNELS_SOURCES ${TF_MICRO_DIR}/kernels/*cc)
file(GLOB MICRO_KERNELS_HEADERS ${TF_MICRO_DIR}/kernels/*.h)
file(GLOB MICRO_TESTS_KERNELS_SOURCES ${TF_MICRO_DIR}/kernels/*test.cc)
file(GLOB MICRO_MEMORY_SOURCES ${TF_MICRO_DIR}/memory_planner/*cc)
file(GLOB MICRO_MEMORY_HEADERS ${TF_MICRO_DIR}/memory_planner/*.h)
file(GLOB MICRO_TESTS_MEMORY_SOURCES ${TF_MICRO_DIR}/memory_planner/*test.cc)

list(REMOVE_ITEM MICRO_SOURCES ${MICRO_TESTS_SOURCES})
list(REMOVE_ITEM MICRO_KERNELS_SOURCES ${MICRO_TESTS_KERNELS_SOURCES})
list(REMOVE_ITEM MICRO_MEMORY_SOURCES ${MICRO_TESTS_MEMORY_SOURCES})

target_compile_options(app PRIVATE "-fno-threadsafe-statics")

target_sources(app PRIVATE
                ${MICRO_SOURCES}
                ${MICRO_KERNELS_SOURCES}
                ${MICRO_MEMORY_SOURCES}
                ${MICRO_HEADERS}
                ${MICRO_MEMORY_HEADERS}
                ${MICRO_KERNELS_HEADERS}
                ${TF_LITE_DIR}/c/common.c
                ${TF_LITE_DIR}/core/api/error_reporter.cc
                ${TF_LITE_DIR}/core/api/flatbuffer_conversions.cc
                ${TF_LITE_DIR}/core/api/op_resolver.cc
                ${TF_LITE_DIR}/core/api/tensor_utils.cc
                ${TF_LITE_DIR}/kernels/internal/quantization_util.cc
                ${TF_LITE_DIR}/kernels/kernel_util.cc
                src/audio_provider.cc
                ../command_responder.cc
                ../audio_provider.h
                ../command_responder.h
                ../feature_provider.cc
                ../feature_provider.h
                ../main.cc
                ../main_functions.cc
                ../main_functions.h
                ../recognize_commands.cc
                ../recognize_commands.h
                ../no_1000ms_sample_data.cc
                ../no_1000ms_sample_data.h
                ../yes_1000ms_sample_data.cc
                ../yes_1000ms_sample_data.h
                ../no_30ms_sample_data.h
                ../no_30ms_sample_data.cc
                ../yes_30ms_sample_data.h
                ../yes_30ms_sample_data.cc
                ${MICRO_FEATURES}/tiny_conv_micro_features_model_data.cc
                ${MICRO_FEATURES}/micro_features_generator.cc
                ${MICRO_FEATURES}/micro_model_settings.cc
                ${MICRO_FEATURES}/tiny_conv_micro_features_model_data.h
                ${MICRO_FEATURES}/micro_model_settings.h
                ${MICRO_FEATURES}/micro_features_generator.h
                ${KISS_FFT}/kiss_fft.c
                ${KISS_FFT}/tools/kiss_fftr.c
                ${KISS_FFT}/kiss_fft.h
                ${KISS_FFT}/_kiss_fft_guts.h
                ${KISS_FFT}/tools/kiss_fftr.h
                ${MICROFRONTEND}/fft.cc
                ${MICROFRONTEND}/fft_util.cc
                ${MICROFRONTEND}/filterbank.c
                ${MICROFRONTEND}/filterbank_util.c
                ${MICROFRONTEND}/frontend.c
                ${MICROFRONTEND}/frontend_util.c
                ${MICROFRONTEND}/log_lut.c
                ${MICROFRONTEND}/log_scale.c
                ${MICROFRONTEND}/log_scale_util.c
                ${MICROFRONTEND}/noise_reduction.c
                ${MICROFRONTEND}/noise_reduction_util.c
                ${MICROFRONTEND}/pcan_gain_control.c
                ${MICROFRONTEND}/pcan_gain_control_util.c
                ${MICROFRONTEND}/window.c
                ${MICROFRONTEND}/window_util.c
                ${MICROFRONTEND}/bits.h
                ${MICROFRONTEND}/fft.h
                ${MICROFRONTEND}/fft_util
                ${MICROFRONTEND}/filterbank.h
                ${MICROFRONTEND}/filterbank_util.h
                ${MICROFRONTEND}/frontend.h
                ${MICROFRONTEND}/frontend_util.h
                ${MICROFRONTEND}/log_lut.h
                ${MICROFRONTEND}/log_scale.h
                ${MICROFRONTEND}/log_scale_util.h
                ${MICROFRONTEND}/noise_reduction.h
                ${MICROFRONTEND}/noise_reduction_util.h
                ${MICROFRONTEND}/pcan_gain_control.h
                ${MICROFRONTEND}/pcan_gain_control_util.h
                ${MICROFRONTEND}/window.h
                ${MICROFRONTEND}/window_util.h
)

target_include_directories(app PRIVATE
${TF_DIR}
${TF_MICRO_DIR}/tools/make/downloads/ruy
${TF_LITE_DIR}/micro/tools/make/downloads/gemmlowp
${TF_MICRO_DIR}/tools/make/downloads/flatbuffers/include
${KISS_FFT})

add_compile_options(-DNDEBUG -DTF_LITE_STATIC_MEMORY)
