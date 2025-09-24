# 简单通用的 ARM 裸机工具链文件
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(TOOLCHAIN arm-none-eabi)

find_program(CMAKE_C_COMPILER   ${TOOLCHAIN}-gcc)
find_program(CMAKE_CXX_COMPILER ${TOOLCHAIN}-g++)
find_program(CMAKE_ASM_COMPILER ${TOOLCHAIN}-gcc)
find_program(CMAKE_AR           ${TOOLCHAIN}-ar)
find_program(CMAKE_OBJCOPY      ${TOOLCHAIN}-objcopy)
find_program(CMAKE_SIZE         ${TOOLCHAIN}-size)
