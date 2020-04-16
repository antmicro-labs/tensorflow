cmake_minimum_required(VERSION 3.13.1)
find_package(Zephyr REQUIRED)
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

list(REMOVE_ITEM MICRO_SOURCES ${MICRO_TESTS_SOURCES})
list(REMOVE_ITEM MICRO_KERNELS_SOURCES ${MICRO_TESTS_KERNELS_SOURCES})
list(REMOVE_ITEM MICRO_MEMORY_SOURCES ${MICRO_TESTS_MEMORY_SOURCES})

# YOU CAN FIND SUBDIRECTORIES IN cmake_sub/ directory
add_subdirectory(src)
add_subdirectory(cmake_sub/simple_features)
add_subdirectory(cmake_sub/micro_features)
add_subdirectory(cmake_sub/micro_speech)
add_subdirectory(cmake_sub/kiss_fft)
add_subdirectory(cmake_sub/microfrontend)

target_sources (
	app PRIVATE
        src/audio_provider.cc
        src/audio_provider.h
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

target_link_libraries(
	app PRIVATE
	src
	micro_features
	simple_features
	micro_speech
	kiss_fft
	microfrontend
	)

target_include_directories(
	app PRIVATE
	${TF_MICRO_DIR}/../../../
	${TF_MICRO_DIR}/tools/make/downloads/ruy
        ${TF_MICRO_DIR}/../micro/tools/make/downloads/gemmlowp
        ${TF_MICRO_DIR}/../micro/tools/make/downloads/flatbuffers/include
        $ENV{TOOLCHAIN_BASE}/include/c++/$ENV{TOOLCHAIN_VERSION}
        $ENV{TOOLCHAIN_BASE}/include
        $ENV{TOOLCHAIN_BASE}/include/c++/$ENV{TOOLCHAIN_VERSION}/riscv32-zephyr-elf/rv32i/ilp32
        )

add_compile_options(-DNDEBUG -DTF_LITE_STATIC_MEMORY)

