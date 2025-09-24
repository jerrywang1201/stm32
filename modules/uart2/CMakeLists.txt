add_library(uart2 STATIC
  src/uart2.c
)
target_include_directories(uart2 PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/include
)
