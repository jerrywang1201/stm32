add_library(i2c_lowlevel STATIC
  src/i2c_lowlevel.c
)
target_include_directories(i2c_lowlevel PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/include
)
