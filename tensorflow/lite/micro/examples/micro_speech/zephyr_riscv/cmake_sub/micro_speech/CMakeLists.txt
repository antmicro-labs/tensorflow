# /tensorflow/tensorflow/lite/micro/examples/micro_speech
set(TF_MICRO_DIR ${PROJECT_SOURCE_DIR}/../../../)
set(MICRO_SPEECH ${PROJECT_SOURCE_DIR}/..)

add_library (
	micro_speech
   	${MICRO_SPEECH}/command_responder.cc
	${MICRO_SPEECH}/command_responder.h
	${MICRO_SPEECH}/audio_provider.cc
	${MICRO_SPEECH}/audio_provider.h
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
)

target_include_directories(micro_speech PRIVATE
	${TF_MICRO_DIR}/../../..
	${TF_MICRO_DIR}/tools/make/downloads/ruy
        ${TF_MICRO_DIR}/../micro/tools/make/downloads/flatbuffers/include
        )
