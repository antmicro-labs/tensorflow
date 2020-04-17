set(TF_MICRO_DIR ${PROJECT_SOURCE_DIR}/../../../)
set(TF_DIR ${TF_MICRO_DIR}/../../../)

add_library (
	zephyr_src
	audio_provider.cc
	audio_provider.h
)

target_include_directories(
	zephyr_src PRIVATE
	${TF_DIR}
)