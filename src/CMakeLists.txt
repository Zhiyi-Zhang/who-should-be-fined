cmake_minimum_required (VERSION 3.14)
project (WSBF)

set(CMAKE_CXX_STANDARD 11)
include_directories(".")

file(GLOB file_handler_src
    "*.hpp"
    "*.cpp"
    "tinycrypt/*.c"
    "tinycrypt/*.h"
)

add_executable (file-handler-test ${file_handler_src})