# Make us of the Zephyr's build system auto-detection capability

ifeq ($(TARGET), zephyr_vexriscv)
	export ZEPHYR_TOOLCHAIN_VARIANT?=zephyr
	# export TOOLCHAIN_BASE=${ZEPHYR_SDK_INSTALL_DIR}/riscv32-zephyr-elf/riscv32-zephyr-elf
	# export TOOLCHAIN_VERSION=8.3.0
micro_speech_bin: #third_party_downloads
	cmake -B ${GENDIR}/micro_speech/CMake -DBOARD="litex_vexriscv" -S tensorflow/lite/micro/examples/micro_speech/zephyr_riscv
	make -C ${GENDIR}/micro_speech/CMake
endif
