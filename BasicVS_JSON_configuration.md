# VS Code 任务配置（tasks.json）从零开始教程

本教程用一个最简单的 C++ 单文件例子（`hello.cpp`），从"能跑的最小配置"开始，**一步一步加字段**，最后得到一份完整的 `tasks.json`。

> `tasks.json` 是 JSONC 格式，**允许写 `//` 注释**，学习时可以放心加注释。

## 0. 文件放哪？

在项目根目录建一个 `.vscode` 文件夹，里面放 `tasks.json`：

```
你的项目/
├── .vscode/
│   └── tasks.json      ← 放这里
├── hello.cpp
└── ...其他文件
```

## 1. 第 0 步：先跑通一个最简单的任务

先不管编译，验证"任务"这个机制怎么用：

```json
{
    "version": "2.0.0",             // 配置文件版本，固定 2.0.0，别改
    "tasks": [                      // 任务列表（数组），一个 { } 就是一个任务
        {
            "label": "打印 Hello",   // 任务名字（运行任务列表里看到的），必须唯一
            "type": "shell",        // 类型：shell=交给系统终端执行
            "command": "echo Hello World"  // 要执行的命令
        }
    ]
}
```

保存后：**终端 → 运行任务… → 选择「打印 Hello」**，终端输出 `Hello World`。
说明配置没问题、任务能跑。接下来一步步往这个任务里加东西。

## 2. 第 1 步：让任务去编译 C++ 单文件

把 `command` 换成编译器，并加上编译参数：

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "编译 hello.cpp",
            "type": "cppbuild",        // 类型：cppbuild=编译构建（直接执行命令）
            "command": "g++",          // 编译器（需在 PATH 里；不在就写完整路径）
            "args": [                  // 逐个传给 g++ 的参数
                "-std=c++20",          // 用 C++20 标准
                "-g",                  // 生成调试信息（配合 F5 调试）
                "hello.cpp",           // 要编译的源文件
                "-o", "hello.exe"      // -o 指定输出文件：hello.exe
            ]
        }
    ]
}
```

到这里已经能编译出 `hello.exe`，但还有两个不方便：
- 按 `Ctrl+Shift+B` 没反应（还没加入 build 组）
- 编译报错不会跳到「问题」面板（还没配 problemMatcher）

## 3. 第 2 步：加 options.cwd，路径才可靠

上面的 `hello.cpp`、`hello.exe` 都是相对路径，VS Code 默认以**当前打开的文件所在目录**为基准，容易找错。指定工作目录最稳妥：

```json
"options": {
    "cwd": "${workspaceFolder}"   // ${workspaceFolder} = 项目根目录
}
```

加上后，所有相对路径都从项目根目录算起，`hello.cpp` 一定能找到。

## 4. 第 3 步：加 group，让 Ctrl+Shift+B 一键编译

```json
"group": {
    "kind": "build",     // 归入 build 组 → Ctrl+Shift+B 会触发它
    "isDefault": true    // 有多个 build 任务时，默认执行它
}
```

加上后，按 `Ctrl+Shift+B` 就能直接编译，不用再去菜单里找。

## 5. 第 4 步：加 problemMatcher，报错自动跳到「问题」面板

```json
"problemMatcher": ["$gcc"]
```

作用：从终端输出里识别 gcc 报错（`文件名:行号: 错误信息`），自动标红并显示在「问题」面板，点一下就能跳到出错那一行。

## 6. 第 5 步：再加一个"运行"任务，用 dependsOn 串起来

编译好了，还想一键运行。再加一个任务，让它**先编译再运行**：

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "编译 hello.cpp",              // 任务①：编译
            "type": "cppbuild",
            "command": "g++",
            "args": ["-std=c++20", "-g", "hello.cpp", "-o", "hello.exe"],
            "options": { "cwd": "${workspaceFolder}" },
            "problemMatcher": ["$gcc"],
            "group": { "kind": "build", "isDefault": true }
        },
        {
            "label": "运行 hello.exe",              // 任务②：运行
            "type": "shell",                       // 运行程序用 shell 即可
            "command": "hello.exe",                // 运行编译好的程序
            "options": { "cwd": "${workspaceFolder}" },
            "group": "test",                       // test 组：不占 Ctrl+Shift+B
            "dependsOn": "编译 hello.cpp"           // 先编译再运行（值=编译任务的 label，必须一字不差）
        }
    ]
}
```

> `dependsOn` 的值必须和所依赖任务的 `label` 完全一致，否则找不到。

## 7. 回顾：你其实只加了 5 个字段

对比第 1 步那 5 行配置，到第 6 步只多了 `args`、`options.cwd`、`group`、`problemMatcher`、`dependsOn`，就把一个"打印一句话"的任务，升级成了"一键编译 + 一键运行"的完整流程。

## 8. 字段速查表

| 字段 | 作用 |
|------|------|
| `type` | 任务类型：`cppbuild` 编译 / `shell` 命令行 / `process` 直接启动进程 |
| `label` | 任务名字，必须唯一 |
| `command` | 要执行的命令或程序 |
| `args` | 命令参数列表 |
| `options.cwd` | 运行时的当前目录（建议用 `${workspaceFolder}`） |
| `problemMatcher` | 把输出里的报错转成「问题」面板（C++ 用 `$gcc`） |
| `group.kind` | `build`（Ctrl+Shift+B）或 `test` |
| `group.isDefault` | 多个同类任务时默认执行谁 |
| `dependsOn` | 执行前先跑依赖的其他任务 |
| `detail` | 任务描述文字 |

## 9. type 类型详解

| 取值 | 中文意思 | 说明 |
|------|----------|------|
| `cppbuild` | C++ 构建 | 直接执行命令，专为编译设计（配 `$gcc` 解析报错） |
| `shell` | 命令行 | 交给系统终端执行，支持管道、重定向，适合运行程序/脚本 |
| `process` | 进程 | 直接启动进程，不走终端，无 shell 特性 |

**怎么选：** 编译 → `cppbuild`；运行程序/脚本 → `shell`；简单命令不想过终端 → `process`。

## 10. 常用变量

| 变量 | 含义 |
|------|------|
| `${workspaceFolder}` | 项目根目录路径 |
| `${file}` | 当前打开的文件路径 |
| `${fileDirname}` | 当前文件所在目录 |
| `${fileBasenameNoExtension}` | 当前文件名（不含扩展名） |

## 11. 怎么用

- `Ctrl+Shift+B`：运行 build 组默认任务（一键编译）
- **终端 → 运行任务…**：从列表选任意任务（如「运行 hello.exe」）
- 任务输出显示在终端，报错自动跳到「问题」面板

## 12. 进阶：多文件项目

前面的例子都是单个 `hello.cpp`。项目变大后会有**多个源文件**，比如宠物领养项目：

```
10.5Multi-file pet adoption practice project/
├── src/
│   ├── main.cpp          ← 程序入口
│   ├── pet_manager.cpp   ← 宠物管理
│   └── logger.cpp        ← 日志
├── include/
│   └── pet.h 等           ← 头文件（.h）统一放这里
├── bin/                   ← 编译输出目录
└── .vscode/tasks.json
```

### 12.1 改动只有三处

从第 6 步的单文件配置升级到多文件，**只改 `command` 和 `args`**，其他字段（`cwd`、`group`、`problemMatcher`、`dependsOn`）完全不用动：

1. `command`：写编译器的**完整路径**（多文件项目建议写全，避免 PATH 找不到）
2. `args` 里的源文件：从 1 个换成**所有 .cpp**
3. 头文件：加 `-I include` 告诉编译器去 `include` 文件夹找 `.h`

### 12.2 宠物领养项目的真实配置（对照学习）

```json
{
    "type": "cppbuild",       // 类型不变：编译构建
    "label": "C/C++: g++.exe 编译多文件项目",
    "command": "d:\\Tool\\msys64\\ucrt64\\bin\\g++.exe",  // 注意：JSON 里反斜杠要写成 \\（转义）
    "args": [
        "-fdiagnostics-color=always",  // 报错带颜色，更好辨认
        "-g",                         // 调试信息
        "-std=c++20",                 // C++20 标准
        "src\\main.cpp",              // 源文件①：入口
        "src\\pet_manager.cpp",       // 源文件②：宠物管理
        "src\\logger.cpp",            // 源文件③：日志
        "-I", "include",              // -I：去 include 目录找 .h 头文件
        "-o", "bin\\main.exe"         // 输出：链接生成一个 exe
    ],
    "options": { "cwd": "${workspaceFolder}" },
    "problemMatcher": ["$gcc"],
    "group": { "kind": "build", "isDefault": true }
}
```

要点：
- **多个 .cpp 一次列全**，g++ 会逐个编译、最后链接成一个 `bin\main.exe`
- **路径转义**：Windows 路径里的 `\` 在 JSON 里必须写成 `\\`（如 `src\\main.cpp`）
- `-I include` 是**相对路径**，配合 `options.cwd` 从项目根目录找 `include` 文件夹

### 12.3 两个容易踩的坑

1. **新增 .cpp 要手动加**：tasks.json 不会自动扫描文件夹。以后加了 `src\xxx.cpp`，记得回来把它加进 `args`，否则编译会漏掉它。
2. **`-o` 只输出一个 exe**：不管几个源文件，最后都链接成一个程序（这里是 `bin\main.exe`），不是每个 .cpp 一个 exe。

### 12.4 运行任务（依赖编译）

和单文件一样，再加一个 shell 运行任务串起来：

```json
{
    "type": "shell",
    "label": "运行程序 (bin\\main.exe)",
    "command": "bin\\main.exe",
    "options": { "cwd": "${workspaceFolder}" },
    "group": "test",
    "dependsOn": "C/C++: g++.exe 编译多文件项目"  // 先编译再运行
}
```

> 完整配置就在 `10.5Multi-file pet adoption practice project/.vscode/tasks.json`，可以直接打开对照。
