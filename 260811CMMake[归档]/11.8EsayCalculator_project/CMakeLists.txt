#Set minimum CMake version required
cmake_minimum_required(VERSION 3.25)

#Set project language
project(EsayCalculator LANGUAGES CXX)

#Set C++ standard
set(CMAKE_CXX_STANDARD 20)

#Set C++ standard required[必须] 必须满足C++20标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Set extensions[扩展] //关闭扩展，例如编译器的扩展，仅启用C++20标准的扩展
set(CMAKE_CXX_EXTENSIONS OFF)

# add code file[代码文件]
add_executable(EsayCalculator src/main.cpp src/calculator.cpp)

#output executable directory[set输出目录]
#RUNTIME_OUTPUT_DIRECTORY[可执行文件输出目录] //设置可执行文件的输出目录，默认是当前构建目录
set_target_properties(EsayCalculator PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")


#set include directory
target_include_directories(EsayCalculator PRIVATE include)

