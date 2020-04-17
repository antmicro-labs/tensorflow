# /tensorflow/tensorflow/lite/micro/examples/micro_speech/simple_features
set(TF_MICRO_DIR ${PROJECT_SOURCE_DIR}/../../..)
set(SIMPLE_FEATURES ${PROJECT_SOURCE_DIR}/../simple_features)

add_library (
	simple_features
	${SIMPLE_FEATURES}/simple_features_generator.cc
	${SIMPLE_FEATURES}/simple_features_generator.h
	${SIMPLE_FEATURES}/no_power_spectrum_data.cc
	${SIMPLE_FEATURES}/no_power_spectrum_data.h
	${SIMPLE_FEATURES}/yes_power_spectrum_data.cc
	${SIMPLE_FEATURES}/yes_power_spectrum_data.h
	${SIMPLE_FEATURES}/simple_model_settings.h
)

target_include_directories(simple_features PRIVATE
	${TF_MICRO_DIR}/../../..
        )
