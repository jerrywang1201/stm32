cmake_minimum_required(VERSION 3.20)
project(stm32-min C ASM)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/toolchain-gcc-arm-none-eabi.cmake)
set(CMAKE_C_STANDARD 11)
set(MCU "STM32F446xx")
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/linker/STM32F411RETx_FLASH.ld)

set(C_DEFS
  -D${MCU}
  -DUSE_HAL_DRIVER
)

set(C_FLAGS
  -mcpu=cortex-m4
  -mthumb
  -mfpu=fpv4-sp-d16
  -mfloat-abi=hard
  -ffunction-sections -fdata-sections
  -Wall -Wextra -O2
)

add_executable(${PROJECT_NAME}
  src/main.c
  startup/startup_stm32f411xe.s
)

target_compile_definitions(${PROJECT_NAME} PRIVATE ${C_DEFS})
target_compile_options(${PROJECT_NAME} PRIVATE ${C_FLAGS})
target_link_options(${PROJECT_NAME} PRIVATE
  ${C_FLAGS}
  -Wl,--gc-sections
  -T${LINKER_SCRIPT}
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME} ${PROJECT_NAME}.hex
  COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME} ${PROJECT_NAME}.bin
  COMMAND ${CMAKE_SIZE} ${PROJECT_NAME}
)
