
```cmake
cmake_minimum_required(VERSION 3.25)

# 项目信息
project(YourProjectName
    VERSION 1.0.0
    DESCRIPTION "项目描述"
    LANGUAGES CXX
)

# C++ 标准（2026 年常用 C++20，也可选择 C++23）
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 编译选项
# 💡 if(MSVC) 是 CMake 的条件判断语法
# MSVC 是 CMake 内置的"变量"，在 Windows + MSVC 编译器下为真
# 这里根据不同的编译器设置不同的编译选项
if(MSVC)
    # Windows MSVC 编译器选项：
    # /W4  = 警告等级 4（详细警告）
    # /utf-8 = 源代码用 UTF-8 编码（支持中文等 Unicode 字符）
    add_compile_options(/W4 /utf-8)
else()
    # GCC/Clang 编译选项：
    # -Wall -Wextra = 打开大多数警告
    # -Wpedantic = 严格按照 C++ 标准检查
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 收集所有源文件
# 💡 ${} 是 CMake 中"取变量的值"的语法
# ${PROJECT_NAME} 会展开成上面定义的 "YourProjectName"
# GLOB_RECURSE 会递归查找 src/ 下所有 .cpp 和 .h 文件
# ⚠️ 注意：GLOB_RECURSE 不会自动检测新添加的文件
# 如果你加了新文件，需要重新运行 cmake 配置
file(GLOB_RECURSE SOURCES
    src/*.cpp
    src/*.h
)

# 生成可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

# 头文件目录
target_include_directories(${PROJECT_NAME} PRIVATE include)

# 如果需要链接第三方库，在这里添加（下章讲）
# target_link_libraries(${PROJECT_NAME} PRIVATE some_library)
```
