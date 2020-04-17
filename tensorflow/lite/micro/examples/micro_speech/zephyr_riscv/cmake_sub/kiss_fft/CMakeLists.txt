# /tensorflow/tensorflow/lite/micro/tools/make/downloads/kissfft
set(TF_MICRO_DIR ${PROJECT_SOURCE_DIR}/../../../)
set(KISS_FFT ${PROJECT_SOURCE_DIR}/../../../tools/make/downloads/kissfft)

add_library (
	kiss_fft
	${KISS_FFT}/kiss_fft.c
	${KISS_FFT}/kiss_fft.h
	${KISS_FFT}/_kiss_fft_guts.h
	${KISS_FFT}/COPYING
	${KISS_FFT}/tools/kiss_fftr.c
	${KISS_FFT}/tools/kiss_fftr.h
	)

target_include_directories(kiss_fft PRIVATE
	${KISS_FFT}
        )
