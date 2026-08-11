
 ### ① 搜索某个库
 ```
vcpkg search fmt
```
### ② 安装某个库
```
vcpkg install fmt
```
### ③ 查看已安装的库
```
vcpkg list
```

---

## 四、在 CMake 项目里接入 vcpkg

编译时，在 cmake 命令里带上 vcpkg 的配置文件（toolchain）：

```bash
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=$HOME/vcpkg/scripts/buildsystems/vcpkg.cmake
```

这样 CMake 就能自动找到 vcpkg 装好的库。

## 五、已安装的库（2026-08-10）

| 库 | 安装命令 | CMake 里的用法 |
|----|---------|---------------|
| fmt | `vcpkg install fmt` | `find_package(fmt CONFIG REQUIRED)`<br>`target_link_libraries(main PRIVATE fmt::fmt)` |
| nlohmann-json | `vcpkg install nlohmann-json` | `find_package(nlohmann_json CONFIG REQUIRED)`<br>`target_link_libraries(main PRIVATE nlohmann_json::nlohmann_json)` |
