ifeq ($(TARGET), zephyr_vexriscv)
	export ZEPHYR_TOOLCHAIN_VARIANT?=zephyr
micro_speech_bin:
	cmake -Wdev -B ${GENDIR}/micro_speech/CMake -GNinja -DBOARD="litex_vexriscv" -S tensorflow/lite/micro/examples/micro_speech/zephyr_riscv
	ninja -C ${GENDIR}/micro_speech/CMake
endif
