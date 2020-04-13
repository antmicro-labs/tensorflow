# /tensorflow/tensorflow/lite/micro/examples/micro_speech/micro_features
add_library (
	micro_features
	../../../micro_features/tiny_conv_micro_features_model_data.cc
	../../../micro_features/tiny_conv_micro_features_model_data.h
	../../../micro_features/yes_micro_features_data.cc
	../../../micro_features/yes_micro_features_data.h
	../../../micro_features/micro_features_generator.cc
	../../../micro_features/micro_features_generator.h
	../../../micro_features/no_micro_features_data.cc
	../../../micro_features/no_micro_features_data.h
	../../../micro_features/tiny_conv_micro_features_model_data.cc
	../../../micro_features/tiny_conv_micro_features_model_data.h
	../../../micro_features/micro_model_settings.cc
	../../../micro_features/micro_model_settings.h
	../../../micro_features/no_feature_data_slice.cc
	../../../micro_features/no_feature_data_slice.h
	../../../micro_features/yes_feature_data_slice.cc
	../../../micro_features/yes_feature_data_slice.h
	)

target_include_directories(micro_features PRIVATE
	${TF_MICRO_DIR}/../../..
	${TF_MICRO_DIR}/tools/make/downloads/ruy
        )
