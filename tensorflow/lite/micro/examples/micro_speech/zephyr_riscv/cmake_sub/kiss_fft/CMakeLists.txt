# /tensorflow/tensorflow/lite/micro/tools/make/downloads/kissfft
add_library (
	kiss_fft
	../../../../../tools/make/downloads/kissfft/kiss_fft.c
	../../../../../tools/make/downloads/kissfft/kiss_fft.h
	../../../../../tools/make/downloads/kissfft/_kiss_fft_guts.h
	../../../../../tools/make/downloads/kissfft/COPYING
	../../../../../tools/make/downloads/kissfft/tools/kiss_fftr.c
	../../../../../tools/make/downloads/kissfft/tools/kiss_fftr.h
	)

target_include_directories(kiss_fft PRIVATE
	../../../../../tools/make/downloads/kissfft
        )
