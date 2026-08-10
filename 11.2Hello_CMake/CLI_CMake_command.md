# CMake 命令行构建速查

> 以下命令应在**包含 `CMakeLists.txt` 的项目根目录**中执行。`-S .` 表示源码目录为当前目录，`-B build` 表示将构建产物放到 `build` 目录。

## 1. 配置项目

```powershell
cmake -S . -B build
```

这一步会检测编译器并生成构建系统；首次构建前必须先执行。通常不需要手动 `mkdir build`，CMake 会自动创建该目录。

## 2. 构建项目

```powershell
cmake --build build
```

`--build build` 中的 `build` 必须与上一步 `-B build` 一致。若构建失败，可先重新执行配置命令，查看 CMake 的错误信息。

## 3. 使用 Visual Studio（Windows 默认）的 Debug / Release 配置

Visual Studio 是**多配置生成器**：Debug 和 Release 可共用同一个 `build` 目录，`CMAKE_BUILD_TYPE` 对它无效。

```powershell
# 构建 Debug 版本
cmake --build build --config Debug

# 构建 Release 版本
cmake --build build --config Release
```

本项目设置了运行文件输出目录后，生成的程序通常位于：

```text
build/bin/Debug/Hello_CMake.exe
build/bin/Release/Hello_CMake.exe
```

可直接运行 Debug 程序：

```powershell
.\build\bin\Debug\Hello_CMake.exe
```

## 4. 使用 Ninja 或 Unix Makefiles（单配置生成器）

Ninja、Unix Makefiles 等是**单配置生成器**，需要在配置阶段用 `CMAKE_BUILD_TYPE` 指定构建类型。为避免 Debug 和 Release 产物互相覆盖，建议使用不同的构建目录。

```powershell
# 配置并构建 Debug 版本
cmake -S . -B build-debug -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build-debug

# 配置并构建 Release 版本
cmake -S . -B build-release -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build-release
```

如果本机未安装 Ninja，请删去 `-G Ninja`，或改用已安装的单配置生成器。

## 5. 关于调试信息和优化选项

不要在命令行中写 `set(CMAKE_CXX_FLAGS_DEBUG ...)`：这是 **CMakeLists.txt 中的 CMake 语法**，不是 PowerShell 命令；而且 `-g`、`-O0`、`-O2` 是 GCC/Clang 选项，不适用于 MSVC。

通常只要选择对应构建类型即可：

- `Debug`：包含调试信息、通常关闭优化，适合调试。
- `Release`：通常启用优化并定义 `NDEBUG`，适合发布。

这些具体编译选项由当前生成器和编译器（如 MSVC、GCC、Clang）自动选择。只有确实需要自定义选项时，才应在 `CMakeLists.txt` 中通过 `target_compile_options()` 等目标级命令设置。
