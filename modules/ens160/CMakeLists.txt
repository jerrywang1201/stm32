add_library(ens160 STATIC
  src/ens160.c
)
target_include_directories(ens160 PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/include
)
target_link_libraries(ens160 PRIVATE i2c_lowlevel)
