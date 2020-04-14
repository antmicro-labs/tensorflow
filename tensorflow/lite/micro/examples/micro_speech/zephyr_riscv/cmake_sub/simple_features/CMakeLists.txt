# /tensorflow/tensorflow/lite/micro/examples/micro_speech/simple_features
add_library (
	simple_features
	../../../simple_features/simple_features_generator.cc
	../../../simple_features/simple_features_generator.h
	../../../simple_features/no_power_spectrum_data.cc
	../../../simple_features/no_power_spectrum_data.h
	../../../simple_features/yes_power_spectrum_data.cc
	../../../simple_features/yes_power_spectrum_data.h
	../../../simple_features/simple_model_settings.h
)

target_include_directories(simple_features PRIVATE
	${TF_MICRO_DIR}/../../..
        )
