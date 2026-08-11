#Set Cmake version 3.25
cmake_minimum_required(VERSION 3.25)

#:LANGUAGES CXX 表示这是一个CPP project
project(HelloCMake LANGUAGES CXX)

#use V++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#set 输出位置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#指定要构建的CPP文件
add_executable(helloCmake src/main.cpp)

#MSVC下让源码、字符串输出按照 UTF-8 处理
if(MSVC)
	target_compile_options(helloCmake PRIVATE /utf-8)
endif()
