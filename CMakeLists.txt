cmake_minimum_required(VERSION 3.15)

# 先声明交叉编译环境 + 编译器，再调用 project()
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_C_COMPILER  arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

# 避免 macOS 注入 AppleClang 的 flags
set(CMAKE_OSX_ARCHITECTURES "" CACHE STRING "" FORCE)
set(CMAKE_OSX_SYSROOT "" CACHE PATH "" FORCE)
set(CMAKE_OSX_DEPLOYMENT_TARGET "" CACHE STRING "" FORCE)

project(stm32-min C ASM)
enable_language(ASM)

# CPU/FPU 作为“列表”传参，别写成带空格的一串字符串
set(CPU_FLAGS
  -mcpu=cortex-m4
  -mthumb
  -mfpu=fpv4-sp-d16
  -mfloat-abi=softfp
)

add_executable(${PROJECT_NAME}.elf
  src/main.c
  src/system_stub.c
  startup/startup_stm32f446xx.s
)

target_compile_options(${PROJECT_NAME}.elf PRIVATE
  ${CPU_FLAGS} -O2 -g -ffunction-sections -fdata-sections -Wall -Wextra
)
target_link_options(${PROJECT_NAME}.elf PRIVATE
  ${CPU_FLAGS}
  -T${CMAKE_SOURCE_DIR}/linker/STM32F446RETx_FLASH.ld
  -Wl,--gc-sections -Wl,-Map=${PROJECT_NAME}.map
  -specs=nosys.specs -nostartfiles
)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
  COMMAND arm-none-eabi-objcopy -O ihex   ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
  COMMAND arm-none-eabi-objcopy -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
)
