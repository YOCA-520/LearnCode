# 宠物领养中心多文件项目
cmake_minimum_required(VERSION 3.25)
project(PetAdoption LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 可执行文件
add_executable(pet_adoption
    src/main.cpp
    src/pet_manager.cpp
    src/logger.cpp
)

# 头文件搜索目录
target_include_directories(pet_adoption PRIVATE include)
