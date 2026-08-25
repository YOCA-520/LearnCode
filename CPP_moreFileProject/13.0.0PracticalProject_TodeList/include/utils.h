// ============================================================
// utils.h —— 工具集：JSON 与 Todo 之间的"翻译官" + 文件读写
//
// 作用：程序内存里用的是 std::vector<Todo>（任务列表），
//       磁盘上存的却是 JSON 文件（如 13.3.0todo.json）。
//       这两个世界之间需要互相转换，本文件就负责这件事：
//
//   Todo    →  JSON  （todoToJson + saveTodos，保存时用）
//   JSON    →  Todo  （jsonToTodo + loadTodos，启动加载时用）
//
// 这样设计的好处：TodoManager 只管业务逻辑，完全不用关心
// "JSON 怎么解析、文件怎么打开"这些琐事，职责分离、代码更清晰。
//
// 依赖的第三方库：nlohmann_json（vcpkg 安装的 JSON 解析库，
// 在 CMakeLists.txt 里通过 find_package 引入，头文件用 <nlohmann/json.hpp>）。
// ============================================================

#pragma once
// 防止头文件被重复包含。

#include <nlohmann/json.hpp>
// 第三方 JSON 库的头文件（尖括号 = 从 vcpkg 的 include 目录找）。
// 提供 nlohmann::json 类型：可以表示 JSON 里的对象/数组/数字/字符串等。

#include <optional>
// std::optional：表示"可能有值，也可能没有值"。
// 比如 jsonToTodo 解析失败时就返回 std::nullopt（空），
// 调用方可以用 if (result) 判断有没有成功。
#include <string>
#include <vector>
#include "todo.h"
// 需要 Todo 结构体。

// ------------------------------------------------------------------
// 枚举：一次"加载任务"的结果状态
// 用枚举代替"随便返回一个整数"，代码可读性更强：
// 调用方用 switch (status) 就能清晰地看到每一种情况。
// ------------------------------------------------------------------
enum class TodoLoadStatus {
    ok,           // 加载成功
    not_found,    // JSON 文件不存在（可能是第一次运行）
    open_failed,  // 文件存在但打不开（权限问题等）
    invalid_json  // 文件内容不是合法的 Todo JSON（格式损坏）
};

// ------------------------------------------------------------------
// 结构体：加载结果 = 任务列表 + 状态
// 一个函数同时想返回"数据"和"结果状态"，就可以用一个结构体打包。
// ------------------------------------------------------------------
struct TodoLoadResult {
    std::vector<Todo> todos;                    // 加载出来的任务列表（失败时为空）
    TodoLoadStatus status = TodoLoadStatus::ok; // 加载结果状态（默认成功）
};

// 保存结果的状态枚举：保存任务时可能遇到两种失败
enum class TodoSaveStatus {
    ok,           // 保存成功
    open_failed,  // 文件打不开
    write_failed  // 写入过程出错
};

// ------------------------------------------------------------------
// 函数声明（具体实现都在 src/utils.cpp 里）
// ------------------------------------------------------------------

// 把单个 JSON 对象解析成 Todo。字段缺失/类型不对/数值越界时返回空。
std::optional<Todo> jsonToTodo(const nlohmann::json& value);

// 把单个 Todo 转换成 JSON 对象（保存时每个任务转成一个 JSON 对象）。
nlohmann::json todoToJson(const Todo& todo);

// 从 JSON 文件加载整个任务列表（打开文件 → 解析 → 逐条校验 → 返回）。
TodoLoadResult loadTodos(const std::string& filename);

// 把整个任务列表写入 JSON 文件（转 JSON → 打开文件 → 写入 → 返回状态）。
TodoSaveStatus saveTodos(const std::vector<Todo>& todos, const std::string& filename);
