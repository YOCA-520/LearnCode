#Cmake minimum version//minimum[最小] //version[版本]
cmake_minimum_required(VERSION 3.25)
#Cmake minimum version is 3.25

#define project name
#LANGUAGES CXX 表示使用C++语言
project(Hello_CMake LANGUAGES CXX)

#Set the C++ standard to C++20//standard[标准] 20 表示使用C++20标准
set(CMAKE_CXX_STANDARD 20)

#如果不支持C++20标准，会报错
#检查编译器是否支持C++20标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#ON 是CMake里的"真" ， OFF 是"假"，相当于true和false
#禁用编译器特有的扩展，比如GNU和MSVC
#保证代码在所有编译器上行为一致
set(CMAKE_CXX_EXTENSIONS OFF)

#指定输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#指定要构建的可执行文件
#语法：add_executable(可执行文件名 源文件1 源文件2 ...)
#编译成功后，会生成Hello_CMake.exe 或者Hello_CMake.app(linux)文件
#将src/main.cpp和src/Hello_CMake.cpp编译成一个Hello_CMake.exe
#如果想将项目编译成多个exe文件，写多个add_executable命令即可
add_executable(Hello_CMake src/main.cpp src/Hello_CMake.cpp)

#指定头文件搜索目录，让 #include "Hello_CMake.h" 能找到 include/ 下的头文件
target_include_directories(Hello_CMake PRIVATE include)

