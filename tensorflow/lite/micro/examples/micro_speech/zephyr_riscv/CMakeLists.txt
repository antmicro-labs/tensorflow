cmake_minimum_required(VERSION 3.13.1)
find_package(Zephyr REQUIRED)
project(tf_lite_micro_speech)

set(TF_MICRO_DIR ${PROJECT_SOURCE_DIR}/../../../)
set(TF_DIR ${TF_MICRO_DIR}/../../../)

set(MICRO_SPEECH ${PROJECT_SOURCE_DIR}/..)
set(MICRO_FEATURES ${PROJECT_SOURCE_DIR}/../micro_features)
set(KISS_FFT ${PROJECT_SOURCE_DIR}/../../../tools/make/downloads/kissfft)
set(MICROFRONTEND ${PROJECT_SOURCE_DIR}/../../../../experimental/microfrontend/lib)
set(SIMPLE_FEATURES ${PROJECT_SOURCE_DIR}/../simple_features)

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

#list(REMOVE_ITEM MICRO_SOURCES ${TF_MICRO_DIR}/debug_log.cc)

#add_subdirectory(src)
#add_subdirectory(cmake_sub/simple_features)
#add_subdirectory(cmake_sub/micro_features)
#add_subdirectory(cmake_sub/micro_speech)
#add_subdirectory(cmake_sub/kiss_fft)
#add_subdirectory(cmake_sub/microfrontend)

target_compile_options(app PRIVATE "-fno-threadsafe-statics")

target_sources (
	app PRIVATE
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

        # zephyr_src
        src/audio_provider.cc
	src/audio_provider.h
        src/command_responder.cc
	src/command_responder.h
        #src/main.cc
        #src/debug_log.cc
        src/assert.cc
        
        # micro_speech
        #${MICRO_SPEECH}/command_responder.cc
	#${MICRO_SPEECH}/command_responder.h
	#${MICRO_SPEECH}/audio_provider.cc
	#${MICRO_SPEECH}/audio_provider.h
	${MICRO_SPEECH}/feature_provider.cc
	${MICRO_SPEECH}/feature_provider.h
	${MICRO_SPEECH}/main.cc
        ${MICRO_SPEECH}/main_functions.cc
	${MICRO_SPEECH}/main_functions.h
	${MICRO_SPEECH}/recognize_commands.cc
	${MICRO_SPEECH}/recognize_commands.h
	${MICRO_SPEECH}/no_1000ms_sample_data.cc
	${MICRO_SPEECH}/no_1000ms_sample_data.h
	${MICRO_SPEECH}/yes_1000ms_sample_data.cc
	${MICRO_SPEECH}/yes_1000ms_sample_data.h
	${MICRO_SPEECH}/no_30ms_sample_data.cc
	${MICRO_SPEECH}/no_30ms_sample_data.h
	${MICRO_SPEECH}/yes_30ms_sample_data.cc
        ${MICRO_SPEECH}/yes_30ms_sample_data.h
        
        # micro_features
        ${MICRO_FEATURES}/tiny_conv_micro_features_model_data.cc
	${MICRO_FEATURES}/tiny_conv_micro_features_model_data.h
	${MICRO_FEATURES}/micro_model_settings.cc
	${MICRO_FEATURES}/micro_model_settings.h
	${MICRO_FEATURES}/micro_features_generator.cc
        ${MICRO_FEATURES}/micro_features_generator.h

        ${MICRO_FEATURES}/yes_micro_features_data.cc
	${MICRO_FEATURES}/yes_micro_features_data.h
	${MICRO_FEATURES}/no_micro_features_data.cc
	${MICRO_FEATURES}/no_micro_features_data.h
	${MICRO_FEATURES}/no_feature_data_slice.cc
	${MICRO_FEATURES}/no_feature_data_slice.h
	${MICRO_FEATURES}/yes_feature_data_slice.cc
        ${MICRO_FEATURES}/yes_feature_data_slice.h
        
        # kiss_fft
        ${KISS_FFT}/kiss_fft.c
	${KISS_FFT}/kiss_fft.h
	${KISS_FFT}/_kiss_fft_guts.h
	#${KISS_FFT}/COPYING
	${KISS_FFT}/tools/kiss_fftr.c
        ${KISS_FFT}/tools/kiss_fftr.h
        
        # microfrontend
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
        
        # simple_features
        #${SIMPLE_FEATURES}/simple_features_generator.cc
        #${SIMPLE_FEATURES}/simple_features_generator.h
        #${SIMPLE_FEATURES}/simple_model_settings.h
	#${SIMPLE_FEATURES}/no_power_spectrum_data.cc
	#${SIMPLE_FEATURES}/no_power_spectrum_data.h
	#${SIMPLE_FEATURES}/yes_power_spectrum_data.cc
	#${SIMPLE_FEATURES}/yes_power_spectrum_data.h
	
	)

#target_link_libraries(
#	app PRIVATE
#	zephyr_src
#	micro_features
#	simple_features
#	micro_speech
#	kiss_fft
#	microfrontend
#	)

target_include_directories(
	app PRIVATE
	${TF_MICRO_DIR}/../../../
	${TF_MICRO_DIR}/tools/make/downloads/ruy
        ${TF_MICRO_DIR}/../micro/tools/make/downloads/gemmlowp
        ${TF_MICRO_DIR}/../micro/tools/make/downloads/flatbuffers/include
        ${KISS_FFT}
        )

add_compile_options(-DNDEBUG -DTF_LITE_STATIC_MEMORY)

