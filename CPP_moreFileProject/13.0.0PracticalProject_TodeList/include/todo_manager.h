// ============================================================
// todo_manager.h —— 待办清单管理器（TodoManager）的类声明
//
// 作用：程序的"大脑"。负责整个待办清单的运行流程：
//   显示菜单 → 根据用户选择添加/查看/完成/删除任务 → 自动保存到 JSON 文件。
//
// 它和别的文件的分工：
//   - Todo（todo.h）：一条任务的"数据盒子"。
//   - TodoManager（本文件）：负责管理一堆 Todo 的"业务逻辑"。
//   - utils.h：负责"数据持久化"——把 Todo 列表存成 JSON 文件 / 从 JSON 读回来。
//   - Logger（logger.h）：负责记录日志。
//
// 注意：这里是"声明"，实现代码在 src/todo_manager.cpp 里。
// ============================================================

#pragma once
// 防止头文件被重复包含。

#include <string>
// std::string
#include <vector>
// std::vector：动态数组，这里用来装所有的 Todo（任务列表）。
#include "logger.h"
// 需要使用 Logger 类记录运行日志（成员变量 logger_）。
// 注意：包含的是"双引号"路径，表示找项目自己的头文件（在 include 目录），
//       而不是系统库的 <尖括号> 头文件。
#include "todo.h"
// 需要使用 Todo 结构体（成员变量 todos_ 的元素类型）。

// ------------------------------------------------------------------
// TodoManager 类：管理待办清单的所有操作
// ------------------------------------------------------------------
class TodoManager {
public:
    void run();
    // 唯一对外的"总入口"：启动程序主循环（显示菜单、处理用户选择）。
    // main() 里只要调用 manager.run() 就够了，其余细节都藏在类内部。

private:
    // ---------- 以下都是私有成员函数：只有 TodoManager 自己能用 ----------

    void addTodo();
    // 添加任务：交互式询问标题、类别、优先级，然后存入列表并保存。

    void showAll() const;
    // 查看全部任务（按列表顺序显示，含已完成和未完成）。
    // const 表示调用时不会修改内部数据。

    void showPending() const;
    // 只查看"未完成"的任务。

    void markDone();
    // 标记完成：让用户输入序号，把对应任务改成"已完成"。

    void removeTodo();
    // 删除任务：让用户输入序号，从列表中移除对应任务。

    void sortByPriority();
    // 按优先级从高到低排序（完成后立即保存）。

    void statistics() const;
    // 统计：显示总任务数、已完成数、未完成数。

    void saveChanges();
    // 保存：把内存中的 todos_ 列表写入 JSON 文件（调用 utils.h 的 saveTodos）。

    // ---------- 私有成员变量 ----------

    std::vector<Todo> todos_;
    // 任务列表：程序运行时所有任务都存在这个 vector 里。
    // 启动时从 JSON 文件读入，每次增删改后写回 JSON 文件。

    Logger logger_{"13.3.0app.log"};
    // 日志记录器：往日志文件 "13.3.0app.log" 里写运行记录。
    // 注意后面的花括号：这是"成员初始化"，构造 TodoManager 时
    // 自动用 "13.3.0app.log" 构造这个 Logger（等价于调用了 Logger 的构造函数）。
};
