cmake_minimum_required(VERSION 3.20)
project(stm32-min C ASM)

# 如用命令行传入 -DCMAKE_TOOLCHAIN_FILE=...，下面这行可留可删
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/toolchain-gcc-arm-none-eabi.cmake)

set(MCU STM32F446xx)
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/linker/STM32F446RETx_FLASH.ld)

set(COMMON_C_FLAGS
  -mcpu=cortex-m4
  -mthumb
  -mfpu=fpv4-sp-d16
  -mfloat-abi=hard
  -ffunction-sections -fdata-sections
  -Wall -Wextra -O2
  -g
)

add_executable(${PROJECT_NAME}
  src/main.c
  src/system_stub.c  
  startup/startup_stm32f446xx.s
)

# 宏（不用写成 -Dxxx，CMake 会自动加 -D）
target_compile_definitions(${PROJECT_NAME} PRIVATE ${MCU})

# 编译与链接参数
target_compile_options(${PROJECT_NAME} PRIVATE ${COMMON_C_FLAGS})
target_link_options(${PROJECT_NAME} PRIVATE
  ${COMMON_C_FLAGS}
  -Wl,--gc-sections
  -T${LINKER_SCRIPT}
  --specs=nosys.specs          # 裸机常用；如需半主机 printf 改成 --specs=rdimon.specs 并链接 rdimon
)

# 生成 hex/bin 与 size 报告
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_NAME}.elf
  COMMAND ${CMAKE_OBJCOPY} -O ihex  ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
  COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
  COMMAND ${CMAKE_SIZE} ${PROJECT_NAME}.elf
)