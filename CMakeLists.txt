cmake_minimum_required(VERSION 3.14)
project(mystring LANGUAGES C)

set(CMAKE_BUILD_TYPE Debug)

INCLUDE(CheckCCompilerFlag)

add_executable(mystring 
    src/main.c
    src/interp_engine.c
    include/interp_engine.h
    src/ie_string.c
    include/ie_string.h
    )

# add_custom_target(tests)
add_executable(tests
    src/interp_engine.c
    include/interp_engine.h
    src/tests.c
)

target_include_directories(mystring PRIVATE include)
target_include_directories(tests PRIVATE include)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)