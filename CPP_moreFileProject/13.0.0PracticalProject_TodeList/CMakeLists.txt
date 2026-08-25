# ============================================================
# CMakeLists.txt —— 构建配置文件
#
# CMake 是什么：一个"构建系统生成器"。它不直接编译代码，
# 而是根据本文件生成编译器能用的构建脚本（如 Makefile / Ninja），
# 之后才真正编译链接。CLion 里点"构建"时自动完成整个过程。
#
# 本文件的工作：
#   1. 指定项目信息（名字、语言、C++ 版本）
#   2. 收集 src/ 下的所有 .cpp 和 include/ 下的所有 .h
#   3. 把它们编译链接成一个可执行文件（TodoList.exe）
#   4. 接入第三方 JSON 库（nlohmann_json，由 vcpkg 提供）
#
# 语法提示：CMake 里 # 开头是注释；${变量名} 表示取值。
# ============================================================

cmake_minimum_required(VERSION 3.25)
# 最低 CMake 版本要求（低于 3.25 的 CMake 会直接报错拒绝运行）。

# ---------- vcpkg 配置（第三方库管理工具） ----------
set(VCPKG_TARGET_TRIPLET "x64-mingw-dynamic")
# 指定 vcpkg 使用的目标平台三元组：
# x64（64 位）+ mingw（MinGW 编译器）+ dynamic（动态链接库）。

set(CMAKE_TOOLCHAIN_FILE
        "D:/Tool/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "vcpkg toolchain"
)
# 让 CMake 使用 vcpkg 的"工具链文件"。
# vcpkg 通过这个文件把自己的库（这里是 nlohmann_json）暴露给 CMake，
# 后面 find_package 才能找到它。
# CACHE STRING 表示这是一个可缓存的配置项（可在 IDE 里修改）。

project("TodoList" LANGUAGES CXX)
# 定义项目：名字叫 TodoList，只用 C++ 语言（不用 C）。
# project 会定义一个 PROJECT_NAME 变量，下面会用到。

set(CMAKE_CXX_STANDARD 20)
# 启用 C++20 标准。
# 本项目用到了 C++20 的特性：map::contains()（见 todo_manager.cpp）。

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
# 指定可执行文件的输出目录：构建目录下的 bin 文件夹。
# PROJECT_BINARY_DIR 是 CMake 自动定义的"构建目录"（cmake-build-debug）。
# 所以最终生成 cmake-build-debug/bin/TodoList.exe。

file(GLOB_RECURSE HEADERS "include/*.h")
file(GLOB_RECURSE SOURCES "src/*.cpp")
# GLOB_RECURSE：递归收集 include/ 下所有 .h 和 src/ 下所有 .cpp，
# 把文件列表分别存进 HEADERS / SOURCES 两个变量。
# 好处：以后新增源文件不用改这里，重新构建时自动包含。
# （缺点：新增文件后需要重新运行一次 CMake 才会被发现。）

add_executable(
        ${PROJECT_NAME}
        ${SOURCES}
        ${HEADERS}
)
# 核心命令：把上面收集到的源文件编译链接成一个"可执行程序"。
# ${PROJECT_NAME} 展开为 "TodoList"，即输出文件叫 TodoList。
# 头文件列进来是为了让 IDE 能看到它们（方便编辑），编译本身用不到。

target_include_directories(${PROJECT_NAME} PRIVATE include)
# 告诉编译器："include/ 目录是头文件搜索路径"。
# 这样源文件里写 #include "todo.h" 时，
# 编译器会先去 include/ 目录里找（不用写相对路径）。
# PRIVATE 表示这个路径只对本目标生效，不传给依赖本目标的其他目标。

find_package(nlohmann_json CONFIG REQUIRED)
# 查找 vcpkg 安装的第三方库 nlohmann_json（JSON 解析库）。
# CONFIG：用库自带的配置文件查找；REQUIRED：找不到就直接报错。

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
# 把 nlohmann_json 链接进我们的程序。
# 链接后，源文件里 #include <nlohmann/json.hpp> 才能找到头文件，
# 链接器也能找到库里的实现代码。
# PRIVATE 含义同上：这个依赖只属于 TodoList 自己。
