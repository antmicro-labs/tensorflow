cmake_minimum_required(VERSION 3.13.1)
find_package(Zephyr)
project(tf_lite_micro_speech)

set(TF_MICRO_DIR ${PROJECT_SOURCE_DIR}/../../../)
file(GLOB MICRO_SOURCES ${TF_MICRO_DIR}/*cc)
file(GLOB MICRO_HEADERS ${TF_MICRO_DIR}/*.h)
file(GLOB MICRO_TESTS_SOURCES ${TF_MICRO_DIR}/*test.cc)
file(GLOB MICRO_KERNELS_SOURCES ${TF_MICRO_DIR}/kernels/*cc)
file(GLOB MICRO_KERNELS_HEADERS ${TF_MICRO_DIR}/kernels/*.h)
file(GLOB MICRO_TESTS_KERNELS_SOURCES ${TF_MICRO_DIR}/kernels/*test.cc)
file(GLOB MICRO_MEMORY_SOURCES ${TF_MICRO_DIR}/memory_planner/*cc)
file(GLOB MICRO_MEMORY_HEADERS ${TF_MICRO_DIR}/memory_planner/*.h)
file(GLOB MICRO_TESTS_MEMORY_SOURCES ${TF_MICRO_DIR}/memory_planner/*test.cc)

# remove test sources from app sources
list(REMOVE_ITEM MICRO_SOURCES ${MICRO_TESTS_SOURCES})
list(REMOVE_ITEM MICRO_KERNELS_SOURCES ${MICRO_TESTS_KERNELS_SOURCES})
list(REMOVE_ITEM MICRO_MEMORY_SOURCES ${MICRO_TESTS_MEMORY_SOURCES})

# -fno-threadsafe-statics -- disables the mutex around initialization of local static variables
target_compile_options(app PRIVATE "-fno-threadsafe-statics")

target_sources(app PRIVATE
                src/assert.cc
                ../command_responder.cc
		../command_responder.h
		../audio_provider.cc
		../audio_provider.h
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
		../no_30ms_sample_data.cc
		../no_30ms_sample_data.h
		../yes_30ms_sample_data.cc
		../yes_30ms_sample_data.h
		../micro_features/tiny_conv_micro_features_model_data.cc
		../micro_features/tiny_conv_micro_features_model_data.h
		../micro_features/yes_micro_features_data.cc
		../micro_features/yes_micro_features_data.h
		../micro_features/micro_features_generator.cc
		../micro_features/micro_features_generator.h
		../micro_features/no_micro_features_data.cc
		../micro_features/no_micro_features_data.h
		../micro_features/tiny_conv_micro_features_model_data.cc
		../micro_features/tiny_conv_micro_features_model_data.h
		../micro_features/micro_model_settings.cc
		../micro_features/micro_model_settings.h
		../micro_features/no_feature_data_slice.cc
		../micro_features/no_feature_data_slice.h
		../micro_features/yes_feature_data_slice.cc
		../micro_features/yes_feature_data_slice.h
		../simple_features/simple_features_generator.cc
		../simple_features/simple_features_generator.h
		../simple_features/no_power_spectrum_data.cc
		../simple_features/no_power_spectrum_data.h
		../simple_features/yes_power_spectrum_data.cc
		../simple_features/yes_power_spectrum_data.h
		../simple_features/simple_model_settings.h
		../../../tools/make/downloads/kissfft/kiss_fft.c
		../../../tools/make/downloads/kissfft/kiss_fft.h
		../../../tools/make/downloads/kissfft/tools/kiss_fftr.c
		../../../tools/make/downloads/kissfft/tools/kiss_fftr.h
		../../../tools/make/downloads/kissfft/_kiss_fft_guts.h
		../../../tools/make/downloads/kissfft/COPYING
		../../../../experimental/microfrontend/lib/fft.cc
		../../../../experimental/microfrontend/lib/fft_util.cc
		../../../../experimental/microfrontend/lib/filterbank.c
		../../../../experimental/microfrontend/lib/filterbank_util.c
		../../../../experimental/microfrontend/lib/frontend.c
		../../../../experimental/microfrontend/lib/frontend_util.c
		../../../../experimental/microfrontend/lib/log_lut.c
		../../../../experimental/microfrontend/lib/log_scale.c
		../../../../experimental/microfrontend/lib/log_scale_util.c
		../../../../experimental/microfrontend/lib/noise_reduction.c
		../../../../experimental/microfrontend/lib/noise_reduction_util.c
		../../../../experimental/microfrontend/lib/pcan_gain_control.c
		../../../../experimental/microfrontend/lib/pcan_gain_control_util.c
		../../../../experimental/microfrontend/lib/window.c
		../../../../experimental/microfrontend/lib/window_util.c
		../../../../experimental/microfrontend/lib/bits.h
		../../../../experimental/microfrontend/lib/fft.h
		../../../../experimental/microfrontend/lib/fft_util
		../../../../experimental/microfrontend/lib/filterbank.h
		../../../../experimental/microfrontend/lib/filterbank_util.h
		../../../../experimental/microfrontend/lib/frontend.h
		../../../../experimental/microfrontend/lib/frontend_util.h
		../../../../experimental/microfrontend/lib/log_lut.h
		../../../../experimental/microfrontend/lib/log_scale.h
		../../../../experimental/microfrontend/lib/log_scale_util.h
		../../../../experimental/microfrontend/lib/noise_reduction.h
		../../../../experimental/microfrontend/lib/noise_reduction_util.h
		../../../../experimental/microfrontend/lib/pcan_gain_control.h
		../../../../experimental/microfrontend/lib/pcan_gain_control_util.h
		../../../../experimental/microfrontend/lib/window.h
		../../../../experimental/microfrontend/lib/window_util.h
                ${MICRO_SOURCES}
                ${MICRO_KERNELS_SOURCES}
                ${MICRO_MEMORY_SOURCES}
                ${MICRO_HEADERS}
                ${MICRO_KERNEL_HEADERS}
                ${MICRO_MEMORY_HEADERS}
                ${TF_MICRO_DIR}/../c/common.c
                ${TF_MICRO_DIR}/../core/api/error_reporter.cc
                ${TF_MICRO_DIR}/../core/api/flatbuffer_conversions.cc
                ${TF_MICRO_DIR}/../core/api/op_resolver.cc
                ${TF_MICRO_DIR}/../core/api/tensor_utils.cc
                ${TF_MICRO_DIR}/../kernels/internal/quantization_util.cc
                ${TF_MICRO_DIR}/../kernels/kernel_util.cc
                )

target_include_directories(app PRIVATE
		../../../tools/make/downloads/kissfft
		${TF_MICRO_DIR}/tools/make/downloads/ruy
                ${TF_MICRO_DIR}/../../../
                ${TF_MICRO_DIR}/../micro/tools/make/downloads/gemmlowp
                ${TF_MICRO_DIR}/../micro/tools/make/downloads/flatbuffers/include
                $ENV{TOOLCHAIN_BASE}/include/c++/$ENV{TOOLCHAIN_VERSION}
                $ENV{TOOLCHAIN_BASE}/include
                $ENV{TOOLCHAIN_BASE}/include/c++/$ENV{TOOLCHAIN_VERSION}/riscv32-zephyr-elf/rv32i/ilp32
                )

add_definitions(-DNDEBUG -DTF_LITE_STATIC_MEMORY)
