# Library is not used right know, don't know how to include it properly
set(TF_MICRO_DIR ${PROJECT_SOURCE_DIR}/../../../)

add_library (
	tf_sources
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

target_include_directories(
	tf_sources PRIVATE
	${TF_MICRO_DIR}/../../../
	${TF_MICRO_DIR}/tools/make/downloads/ruy
        ${TF_MICRO_DIR}/../micro/tools/make/downloads/gemmlowp
        ${TF_MICRO_DIR}/../micro/tools/make/downloads/flatbuffers/include
        $ENV{TOOLCHAIN_BASE}/include/c++/$ENV{TOOLCHAIN_VERSION}
        $ENV{TOOLCHAIN_BASE}/include
        $ENV{TOOLCHAIN_BASE}/include/c++/$ENV{TOOLCHAIN_VERSION}/riscv32-zephyr-elf/rv32i/ilp32
        )
