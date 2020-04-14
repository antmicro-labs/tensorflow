# /tensorflow/tensorflow/lite/micro/examples/micro_speech
add_library (
	micro_speech
   	../../../command_responder.cc
	../../../command_responder.h
	../../../audio_provider.cc
	../../../audio_provider.h
	../../../feature_provider.cc
	../../../feature_provider.h
	../../../main.cc
        ../../../main_functions.cc
	../../../main_functions.h
	../../../recognize_commands.cc
	../../../recognize_commands.h
	../../../no_1000ms_sample_data.cc
	../../../no_1000ms_sample_data.h
	../../../yes_1000ms_sample_data.cc
	../../../yes_1000ms_sample_data.h
	../../../no_30ms_sample_data.cc
	../../../no_30ms_sample_data.h
	../../../yes_30ms_sample_data.cc
	../../../yes_30ms_sample_data.h
)

target_include_directories(micro_speech PRIVATE
	${TF_MICRO_DIR}/../../..
	${TF_MICRO_DIR}/tools/make/downloads/ruy
        ${TF_MICRO_DIR}/../micro/tools/make/downloads/flatbuffers/include
        )
