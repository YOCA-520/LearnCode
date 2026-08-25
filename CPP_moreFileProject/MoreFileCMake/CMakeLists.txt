#set CMake version
cmake_minimum_required(VERSION 3.25)

#set project and language
set(MoreFile LANGUAGE CXX)

#set language version
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#if in MSVC user utf-8
if(MSVC)
add_compile_options(/W4 /utf-8)
#/w4 werning level 4 (详细警告)
else()
#in gcc / Clang
#-Wall -Wextra(打开大多数警报)
#-Wpedantic(严格遵循 c++ 标准检查)
add_compile_options(-Wall -Wextra -Wpedantic)
endif()

#set output path of the executable file
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

#生成 excutable file
add_executable(${PROJECT_NAME} src/main.cpp src/math_utils.cpp )

#include path
target_include_directories(${PROJECT_NAME} PRIVATE include)
