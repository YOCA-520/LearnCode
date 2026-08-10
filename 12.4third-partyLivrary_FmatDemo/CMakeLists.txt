cmake_minimum_required(VERSION 3.25)

#set language C++20
set(CMAKE_CXX_STANDARD 20)

#set language release//强制使用C++20标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set project name
set(PROJECT_NAME FmatDemo)
project(${PROJECT_NAME} CXX)

#set Code file
add_executable(${PROJECT_NAME} main.cpp)

#set executable file name and path
set_target_properties(${PROJECT_NAME}
    PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

#set include path
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

#use vcpkg to find fmt library
find_package(fmt CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
