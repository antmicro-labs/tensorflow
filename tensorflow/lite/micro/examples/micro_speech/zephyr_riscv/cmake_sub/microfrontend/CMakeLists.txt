# /tensorflow/tensorflow/lite/experimental/microfrontend/lib
set(TF_MICRO_DIR ${PROJECT_SOURCE_DIR}/../../../)
set(KISS_FFT ${PROJECT_SOURCE_DIR}/../../../tools/make/downloads/kissfft)
set(MICROFRONTEND ${PROJECT_SOURCE_DIR}/../../../../experimental/microfrontend/lib)

add_library (
	microfrontend
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
	)

target_include_directories(microfrontend PRIVATE
	../../../../../tools/make/downloads/kissfft
	${TF_MICRO_DIR}/../../..
	${TF_MICRO_DIR}/tools/make/downloads/ruy
        )
