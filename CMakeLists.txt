cmake_minimum_required(VERSION 3.15)
project(stm32-min C ASM)

enable_language(ASM)

set(CPU_FLAGS
  -mcpu=cortex-m4
  -mthumb
  -mfpu=fpv4-sp-d16
  -mfloat-abi=softfp
)

add_executable(${PROJECT_NAME}.elf
  modules/main.c
  modules/system_stub.c
  modules/retarget.c
  modules/system_init.c
  startup/startup_stm32f446xx.s
)

target_compile_options(${PROJECT_NAME}.elf PRIVATE
  ${CPU_FLAGS} -O2 -g -ffunction-sections -fdata-sections -Wall -Wextra
)

target_link_options(${PROJECT_NAME}.elf PRIVATE
  ${CPU_FLAGS}
  -T${CMAKE_SOURCE_DIR}/linker/STM32F446RETx_FLASH.ld
  -Wl,--gc-sections -Wl,-Map=${PROJECT_NAME}.map
  --specs=nano.specs
  -specs=nosys.specs
  -nostartfiles
  # 如需 printf 浮点支持则取消下一行注释
  # -u _printf_float
)

add_subdirectory(modules/i2c_lowlevel)
add_subdirectory(modules/ens160)
add_subdirectory(modules/uart2)



target_link_libraries(${PROJECT_NAME}.elf
  PRIVATE i2c_lowlevel ens160 uart2
)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
  COMMAND arm-none-eabi-objcopy -O ihex   ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
  COMMAND arm-none-eabi-objcopy -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
  COMMENT "Generating HEX and BIN"
)
