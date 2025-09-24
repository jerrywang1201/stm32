# ---------- Target & Compilers ----------
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# 修改成 xPack 的绝对路径（bin 目录里的 arm-none-eabi-gcc）
set(TOOLCHAIN_BIN "/Users/wangjialong/Library/xPacks/@xpack-dev-tools/arm-none-eabi-gcc/14.2.1-1.1.1/.content/bin")

set(CMAKE_C_COMPILER  ${TOOLCHAIN_BIN}/arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_BIN}/arm-none-eabi-gcc)
set(CMAKE_AR      ${TOOLCHAIN_BIN}/arm-none-eabi-ar)
set(CMAKE_RANLIB  ${TOOLCHAIN_BIN}/arm-none-eabi-ranlib)
set(CMAKE_OBJCOPY ${TOOLCHAIN_BIN}/arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP ${TOOLCHAIN_BIN}/arm-none-eabi-objdump)
set(CMAKE_SIZE    ${TOOLCHAIN_BIN}/arm-none-eabi-size)

set(CMAKE_OSX_ARCHITECTURES "" CACHE STRING "" FORCE)
set(CMAKE_OSX_SYSROOT "" CACHE PATH "" FORCE)
set(CMAKE_OSX_DEPLOYMENT_TARGET "" CACHE STRING "" FORCE)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ---------- sysroot（xPack 会返回有效路径） ----------
execute_process(
  COMMAND ${CMAKE_C_COMPILER} -print-sysroot
  OUTPUT_VARIABLE GCC_SYSROOT
  OUTPUT_STRIP_TRAILING_WHITESPACE
  ERROR_QUIET
)
if(GCC_SYSROOT AND NOT GCC_SYSROOT STREQUAL "")
  add_compile_options(--sysroot=${GCC_SYSROOT})
  add_link_options(--sysroot=${GCC_SYSROOT})
endif()

# 交叉查找策略
set(CMAKE_FIND_ROOT_PATH ${GCC_SYSROOT})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
