cmake_minimum_required(VERSION 3.25)

project("LibraryManager" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")



add_executable(
        ${PROJECT_NAME}
        src/main.cpp
        src/catalog.cpp
        include/catalog.h
        include/book.h
        include/member.h
        include/text_catalog.h
        src/storage.cpp
        src/logger.cpp
        include/logger.h
)

target_include_directories(${PROJECT_NAME} PRIVATE include)

# 查找库
find_package(nlohmann_json CONFIG REQUIRED)
# 链接库
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)