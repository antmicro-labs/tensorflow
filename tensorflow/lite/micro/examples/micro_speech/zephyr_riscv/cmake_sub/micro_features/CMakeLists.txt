# /tensorflow/tensorflow/lite/micro/examples/micro_speech/micro_features
set(TF_MICRO_DIR ${PROJECT_SOURCE_DIR}/../../../)
set(MICRO_FEATURES ${PROJECT_SOURCE_DIR}/../micro_features)

add_library (
	micro_features
	${MICRO_FEATURES}/tiny_conv_micro_features_model_data.cc
	${MICRO_FEATURES}/tiny_conv_micro_features_model_data.h
	${MICRO_FEATURES}/yes_micro_features_data.cc
	${MICRO_FEATURES}/yes_micro_features_data.h
	${MICRO_FEATURES}/micro_features_generator.cc
	${MICRO_FEATURES}/micro_features_generator.h
	${MICRO_FEATURES}/no_micro_features_data.cc
	${MICRO_FEATURES}/no_micro_features_data.h
	${MICRO_FEATURES}/tiny_conv_micro_features_model_data.cc
	${MICRO_FEATURES}/tiny_conv_micro_features_model_data.h
	${MICRO_FEATURES}/micro_model_settings.cc
	${MICRO_FEATURES}/micro_model_settings.h
	${MICRO_FEATURES}/no_feature_data_slice.cc
	${MICRO_FEATURES}/no_feature_data_slice.h
	${MICRO_FEATURES}/yes_feature_data_slice.cc
	${MICRO_FEATURES}/yes_feature_data_slice.h
	)

target_include_directories(micro_features PRIVATE
	${TF_MICRO_DIR}/../../..
	${TF_MICRO_DIR}/tools/make/downloads/ruy
        )
