# 根 CMakeLists —— 组织本仓库的多个子项目
cmake_minimum_required(VERSION 3.25)
project(LearnCode LANGUAGES CXX)

# 根目录下的大量单文件示例（*.cpp）：
# 推荐用 VS Code 任务"编译当前文件 (g++)"（Ctrl+Shift+B）逐个编译运行，
# 见 .vscode/tasks.json。

# 多文件子项目
add_subdirectory(11.2Hello_CMake)
add_subdirectory("10.5Multi-file pet adoption practice project")
