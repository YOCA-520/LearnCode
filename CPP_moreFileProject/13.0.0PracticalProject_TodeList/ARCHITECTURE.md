# TodoList 项目结构与文件关系详解

> 适合初学者的项目地图：先看这张图，再看代码，事半功倍。
> 本项目是一个命令行待办清单程序（C++20 + CMake + nlohmann_json）。

---

## 一、项目目录总览

```
13.0.0PracticalProject_TodeList/
│
├── CMakeLists.txt              ← 构建配置（告诉 CMake 怎么编译）
├── include/                    ← 头文件目录（声明：告诉别人"有什么"）
│   ├── todo.h                  ← Todo 结构体：一条任务的数据定义
│   ├── todo_manager.h          ← TodoManager 类声明：程序的大脑
│   ├── logger.h                ← Logger 类声明：写日志文件
│   └── utils.h                 ← 工具集声明：JSON 与 Todo 互转 + 文件读写
│
├── src/                        ← 源文件目录（实现：告诉别人"怎么做"）
│   ├── main.cpp                ← 程序入口（main 函数）
│   ├── todo_manager.cpp        ← TodoManager 类的实现（业务逻辑核心）
│   ├── logger.cpp              ← Logger 类的实现
│   └── utils.cpp               ← 工具集的实现
│
├── locales/                    ← 语言文件（本项目暂未使用，可忽略）
├── .idea/                      ← CLion 的 IDE 配置文件（不用管）
└── cmake-build-debug/          ← 构建输出目录（自动生成，不用管）
```

**核心规律：`include/` 里是"声明"，`src/` 里是"实现"，一一对应。**
`xxx.h` 和 `xxx.cpp` 配对出现（todo / todo_manager / logger / utils），这就是 C++ 多文件项目最常见的组织方式。

---

## 二、文件关系总图（最重要的一张图）

```
                        ┌──────────────────────────┐
                        │       CMakeLists.txt     │
                        │  (构建配置：收集源文件、  │
                        │   引入 JSON 库、生成exe)  │
                        └────────────┬─────────────┘
                                     │ 编译链接
                                     ▼
                        ┌──────────────────────────┐
                        │      main.cpp            │
                        │  (程序入口，只做 3 件事：  │
                        │   建管理器 → run → 兜底)   │
                        └────────────┬─────────────┘
                                     │ 创建并调用
                                     ▼
                        ┌──────────────────────────┐
                        │   TodoManager            │
                        │  (todo_manager.h/.cpp)   │
                        │  程序的大脑：菜单循环、   │
                        │  增删改查、排序、统计     │
                        └───────┬──────────┬───────┘
                                │          │
              持有(成员变量)     │          │ 调用(辅助功能)
                                ▼          ▼
                 ┌────────────────┐  ┌────────────────┐
                 │  Logger        │  │  utils 工具集   │
                 │ (logger.h/.cpp)│  │ (utils.h/.cpp) │
                 │ 写日志文件      │  │ JSON 互转+读写  │
                 │                │  │                │
                 │ 13.3.0app.log  │  │ 13.3.0todo.json│
                 └────────────────┘  └────────────────┘
                        │                     │
                        ▼                     ▼
                  ┌─────────────┐      ┌─────────────┐
                  │ Todo 结构体  │◄────►│ Todo 结构体  │
                  │ (todo.h)    │      │ (todo.h)    │
                  └─────────────┘      └─────────────┘
                  Logger 里没有 Todo，        utils 里大量使用 Todo：
                  它只用 std::string         todo.h 是"公共地基"
```

---

## 三、#include 依赖关系（谁包含谁）

```
                ┌──────────────┐
                │   main.cpp   │
                └──────┬───────┘
                       │ #include "todo_manager.h"
                       ▼
              ┌───────────────────┐
              │  todo_manager.h   │
              └───┬─────┬─────┬───┘
                  │     │     │
       #include    │     │     │ #include "todo.h"
      "logger.h"   │     │     ▼
                  │     │   ┌──────────────┐
                  ▼     │   │   todo.h     │  ← 最底层的"公共地基"
              ┌─────────┐ │   └────────────┘     被 3 处依赖
              │ logger.h│ │
              └─────────┘ │
                          │ #include "todo.h"
                          ▼
                 ┌───────────────────┐
                 │   utils.h         │
                 │ (+ nlohmann/json) │
                 └───────────────────┘
```

### 依赖关系表

| 文件 | 包含的头文件 | 说明 |
|---|---|---|
| `main.cpp` | `todo_manager.h` | 只需要认识 TodoManager |
| `todo_manager.h` | `todo.h`, `logger.h` | 成员 `todos_` 用 Todo；成员 `logger_` 用 Logger |
| `todo_manager.cpp` | `todo_manager.h`, `utils.h` | 调用 loadTodos / saveTodos |
| `utils.h` | `todo.h`, `<nlohmann/json.hpp>` | 用 Todo 类型和 JSON 库 |
| `utils.cpp` | `utils.h` | — |
| `logger.h` | 只含标准库 | 最独立，谁也不依赖 |
| `logger.cpp` | `logger.h` | — |

**关键结论：**

1. **`todo.h` 是公共地基**——被 todo_manager.h 和 utils.h 同时依赖，它本身不依赖任何项目内文件。
2. **`logger.h` 完全独立**——只用标准库（`<fstream>`、`<string>`），谁都能调。
3. **依赖是"单向"的**——utils 不依赖 todo_manager，todo_manager 依赖 utils。单向依赖 = 逻辑清晰、好测试。
4. **头文件负责"声明"**——`#include "todo_manager.h"` 只是让编译器知道类长什么样，实现代码在编译时由 CMake 自动把 `.cpp` 一起编进来。

---

## 四、程序运行时的调用关系（程序跑起来之后）

```
启动
 │
 ▼
main() ──────────────► TodoManager manager;   ← 创建对象（此时日志文件被打开）
 │                        │
 │  manager.run()         │
 │                        ▼
 │                  ┌─────────────────────────────────────────┐
 │                  │  run() 主循环                           │
 │                  │  1. loadTodos("13.3.0todo.json") ◄──────│──► utils.cpp 读文件
 │                  │  2. 打印菜单，读用户选择                 │
 │                  │  3. switch 分派：                       │
 │                  │     1 → addTodo()        ──► saveChanges() ──► utils.cpp 写文件
 │                  │     2 → showAll()                        │
 │                  │     3 → showPending()                    │
 │                  │     4 → markDone()      ──► saveChanges()│
 │                  │     5 → removeTodo()    ──► saveChanges()│
 │                  │     6 → sortByPriority()──► saveChanges()│
 │                  │     7 → statistics()                     │
 │                  │     0 → saveChanges() + 退出 ◄───────────┘
 │                  └─────────────────────────────────────────┘
 │                        │
 │                        │ 每次操作都会调用 logger_.info(...)
 │                        ▼
 │                 ┌──────────────────┐
 │                 │  Logger::write   │────► 13.3.0app.log（日志文件）
 │                 └──────────────────┘
 ▼
return 0（正常退出）
```

**调用链范例**（以"添加任务"为例，完整走一遍）：

```
用户选"1. 添加"
   │
   ▼
TodoManager::addTodo()          [todo_manager.cpp]
   │ ① readRequiredLine 询问标题
   │ ② 询问类别，检查是否在 {work, life, study} 里
   │ ③ 询问优先级，循环校验 1～5
   │ ④ todos_.push_back(Todo{...})      ← 数据进入内存
   │ ⑤ logger_.info("添加任务：...")      ← 记日志 → logger.cpp → app.log
   │ ⑥ saveChanges()                    ← 立即保存
   ▼
TodoManager::saveChanges()      [todo_manager.cpp]
   │
   ▼
saveTodos(todos_, "...json")    [utils.cpp]
   │ ① 每个 Todo 用 todoToJson 转成 JSON 对象
   │ ② 打开文件（trunc 模式，清空旧内容）
   │ ③ document.dump(4) 生成带缩进的 JSON 文本并写入
   ▼
13.3.0todo.json  ← 磁盘上的最终结果
```

---

## 五、数据流（两种形态的转换）

```
┌─────────────────── 内存世界 ───────────────────┐      ┌──────── 磁盘世界 ────────┐
│                                               │      │                         │
│   std::vector<Todo> todos_                    │      │  13.3.0todo.json        │
│   ┌──────────────┐                            │      │  [                     │
│   │ Todo{        │                            │      │    {                   │
│   │  title="写周报"│   todoToJson / saveTodos  │      │      "title": "写周报", │
│   │  category=...│  ────────────────────────► │      │      "category": "work",│
│   │  priority=3  │                            │      │      "priority": 3,    │
│   │  done=false  │                            │      │      "done": false     │
│   │ }            │                            │      │    },                  │
│   └──────────────┘   jsonToTodo / loadTodos   │      │    ...                  │
│   └──────────────┘  ◄────────────────────────  │      │  ]                     │
│   ...              （启动时加载）               │      │                         │
└───────────────────────────────────────────────┘      └─────────────────────────┘

转换规则（utils.cpp 中的校验，宁严勿松）：
  ✅ 必须：顶层是数组、每条是对象、4 个字段齐全、类型正确、
           标题/类别非空、优先级 1～5
  ❌ 任一不满足 → 整份文件判为 invalid_json，程序拒绝加载
```

**日志数据流**（独立的一条小管道）：

```
TodoManager → logger_.info/warning/error → Logger::write
   → "[" + 时间戳 + "][" + 级别标签 + "] " + 消息 + "\n"
   → 13.3.0app.log（追加模式，不覆盖历史）
```

示例：`[2026-08-13 10:30:00][INFO]程序启动，当前任务数：3`

---

## 六、构建流程（CMake 怎么把这些文件变成 exe）

```
CMakeLists.txt
   │
   │ ① cmake_minimum_required / project   —— 项目元信息
   │ ② set(CMAKE_CXX_STANDARD 20)         —— 用 C++20
   │ ③ file(GLOB_RECURSE ...)             —— 收集 src/*.cpp + include/*.h
   │ ④ add_executable(TodoList ...)       —— 声明"我要编译一个可执行程序"
   │ ⑤ target_include_directories(include) —— 设置头文件搜索路径
   │ ⑥ find_package + target_link_libraries —— 接入 nlohmann_json
   ▼
生成构建脚本（Ninja / Makefile）
   │
   ▼
编译 src/*.cpp  → 各自生成 .o 目标文件 → 链接成一个整体
   │
   ▼
cmake-build-debug/bin/TodoList.exe   （可执行文件，可双击/命令行运行）
```

**为什么需要 `find_package`？** 项目用到了第三方库 nlohmann_json（JSON 解析）。
它由 vcpkg 预先安装，CMake 通过 `find_package` 找到它，
再用 `target_link_libraries` 把库"接"进程序——这样代码里写
`#include <nlohmann/json.hpp>` 才能编译通过。

---

## 七、一张表总结每个文件"负责什么"

| 文件 | 一句话职责 | 关键内容 |
|---|---|---|
| `CMakeLists.txt` | 构建配置 | 收集源文件、接入 JSON 库 |
| `main.cpp` | 程序入口 | 创建 TodoManager → run() → 异常兜底 |
| `todo.h` | 任务的数据定义 | `struct Todo`（标题/类别/优先级/完成状态） |
| `todo_manager.h` | 管理器声明 | 7 个功能函数 + 成员 `todos_` / `logger_` |
| `todo_manager.cpp` | 管理器实现（核心） | 菜单循环 + 增删改查 + 排序统计 + 保存 |
| `logger.h` | 日志类声明 | info / warning / error 三个级别 |
| `logger.cpp` | 日志类实现 | 时间戳格式化 + 追加写文件 |
| `utils.h` | 工具集声明 | 状态枚举、加载/保存函数声明 |
| `utils.cpp` | 工具集实现 | JSON↔Todo 互转、文件读写、严格校验 |

**阅读建议（由浅入深）：**

1. `todo.h`（30 秒）→ 先认识"任务"长什么样
2. `main.cpp` + `ARCHITECTURE.md` 关系图（1 分钟）→ 了解程序怎么跑起来的
3. `todo_manager.cpp` 的 `run()`（3 分钟）→ 看懂主循环怎么分派
4. `utils.cpp`（5 分钟）→ 看懂数据怎么存到文件
5. 最后再看 `logger`（选读）→ 日志属于锦上添花，不影响主流程
