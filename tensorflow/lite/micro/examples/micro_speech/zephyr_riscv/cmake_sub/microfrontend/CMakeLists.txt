# /tensorflow/tensorflow/lite/experimental/microfrontend/lib
add_library (
	microfrontend
	../../../../../../experimental/microfrontend/lib/fft.cc
	../../../../../../experimental/microfrontend/lib/fft_util.cc
	../../../../../../experimental/microfrontend/lib/filterbank.c
	../../../../../../experimental/microfrontend/lib/filterbank_util.c
	../../../../../../experimental/microfrontend/lib/frontend.c
	../../../../../../experimental/microfrontend/lib/frontend_util.c
	../../../../../../experimental/microfrontend/lib/log_lut.c
	../../../../../../experimental/microfrontend/lib/log_scale.c
	../../../../../../experimental/microfrontend/lib/log_scale_util.c
	../../../../../../experimental/microfrontend/lib/noise_reduction.c
	../../../../../../experimental/microfrontend/lib/noise_reduction_util.c
	../../../../../../experimental/microfrontend/lib/pcan_gain_control.c
	../../../../../../experimental/microfrontend/lib/pcan_gain_control_util.c
	../../../../../../experimental/microfrontend/lib/window.c
	../../../../../../experimental/microfrontend/lib/window_util.c
	../../../../../../experimental/microfrontend/lib/bits.h
	../../../../../../experimental/microfrontend/lib/fft.h
	../../../../../../experimental/microfrontend/lib/fft_util
	../../../../../../experimental/microfrontend/lib/filterbank.h
	../../../../../../experimental/microfrontend/lib/filterbank_util.h
	../../../../../../experimental/microfrontend/lib/frontend.h
	../../../../../../experimental/microfrontend/lib/frontend_util.h
	../../../../../../experimental/microfrontend/lib/log_lut.h
	../../../../../../experimental/microfrontend/lib/log_scale.h
	../../../../../../experimental/microfrontend/lib/log_scale_util.h
	../../../../../../experimental/microfrontend/lib/noise_reduction.h
	../../../../../../experimental/microfrontend/lib/noise_reduction_util.h
	../../../../../../experimental/microfrontend/lib/pcan_gain_control.h
	../../../../../../experimental/microfrontend/lib/pcan_gain_control_util.h
	../../../../../../experimental/microfrontend/lib/window.h
	../../../../../../experimental/microfrontend/lib/window_util.h	
	)

target_include_directories(microfrontend PRIVATE
	../../../../../tools/make/downloads/kissfft
	${TF_MICRO_DIR}/../../..
	${TF_MICRO_DIR}/tools/make/downloads/ruy
        )
