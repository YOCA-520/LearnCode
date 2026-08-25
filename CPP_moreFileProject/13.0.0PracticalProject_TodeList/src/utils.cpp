// ============================================================
// utils.cpp —— 工具集的实现：JSON 与 Todo 互转 + 文件读写
//
// 实现了 utils.h 里声明的 4 个函数：
//   jsonToTodo  单条 JSON → Todo（严格校验，不合格就返回空）
//   todoToJson  Todo → JSON
//   loadTodos   整个 JSON 文件 → 任务列表（启动时调用）
//   saveTodos   任务列表 → 写回 JSON 文件（每次改动后调用）
//
// 设计思路：解析数据时"宁严勿松"——任何字段缺失、类型不对、
// 数值越界，宁可判定文件无效，也不让脏数据进入程序，
// 避免程序带着错误数据运行造成更难发现的 bug。
// ============================================================

#include "utils.h"
#include <filesystem>
// C++17 文件系统库：exists() 判断文件是否存在、error_code 获取错误详情。
#include <fstream>
// ifstream（读文件）/ ofstream（写文件）。
#include <utility>
// std::move：把对象"移动"给新主人，避免多余的拷贝（更高效）。

using json = nlohmann::json;
// 别名：以后写 json 就等价于写 nlohmann::json，代码更短。

// ------------------------------------------------------------------
// 把单个 JSON 对象解析成 Todo
// 返回 optional：成功时里面有值，失败时是空的（std::nullopt）。
// ------------------------------------------------------------------
std::optional<Todo> jsonToTodo(const json& value) {
    try {
        // 第一步：必须是 JSON 对象，且 4 个字段全都存在。
        if (!value.is_object()
            || !value.contains("title")
            || !value.contains("category")
            || !value.contains("priority")
            || !value.contains("done")) {
            return std::nullopt;
        }

        // 第二步：每个字段的类型必须正确
        // （title/category 必须是字符串、priority 必须是整数、done 必须是布尔）。
        const auto& priority = value.at("priority");
        if (!value.at("title").is_string()
            || !value.at("category").is_string()
            || !(priority.is_number_integer() || priority.is_number_unsigned())
            || !value.at("done").is_boolean()) {
            return std::nullopt;
        }

        // 第三步：类型正确后，把 4 个字段提取出来组装成 Todo。
        // .at("字段名") 取字段值，.get<T>() 转成指定类型。
        Todo todo{
            value.at("title").get<std::string>(),
            value.at("category").get<std::string>(),
            priority.get<int>(),
            value.at("done").get<bool>()
        };

        // 第四步：内容合法性校验。
        // 标题/类别不能是空字符串，优先级必须在 1～5 之间
        // （和 Todo 结构的约定一致）。
        if (todo.title.empty() || todo.category.empty()
            || todo.priority < 1 || todo.priority > 5) {
            return std::nullopt;
        }
        return todo;
        // 全部通过，返回组装好的 Todo。
    } catch (const json::exception&) {
        // json::exception 是 nlohmann_json 库自己的异常类型。
        // 缺字段、类型不匹配或整数越界都属于无效资源，不让异常穿过存储层。
        // 解释：.at() 遇到不存在的字段、.get() 遇到越界的整数都会抛异常，
        // 我们在最外层统一接住，把"异常"翻译成"返回空 optional"，
        // 这样上层代码（loadTodos）就不需要写 try-catch 了。
        return std::nullopt;
    }
}

// ------------------------------------------------------------------
// 把单个 Todo 转成 JSON 对象（保存时用）
// 用花括号初始化列表直接构造一个 JSON 对象：
// {"字段名", 值} 成对出现，生成 { "title": "...", ... } 这样的结构。
// ------------------------------------------------------------------
json todoToJson(const Todo& todo) {
    return json{
        {"title", todo.title},
        {"category", todo.category},
        {"priority", todo.priority},
        {"done", todo.done}
    };
}

// ------------------------------------------------------------------
// 从 JSON 文件加载整个任务列表（程序启动时调用）
// 返回值是 TodoLoadResult：任务列表 + 状态（见 utils.h）。
// ------------------------------------------------------------------
TodoLoadResult loadTodos(const std::string& filename) {
    std::error_code error;
    // 保存文件系统操作的错误信息。

    if (!std::filesystem::exists(filename, error)) {
        // 文件不存在 → 分两种情况：
        if (error) {
            // error 非空说明是"查询出错"（比如目录权限问题），
            return {{}, TodoLoadStatus::open_failed};
        }
        // error 为空说明文件真的不存在（比如第一次运行）。
        // 注意：这不是错误，只是"没有数据可加载"，调用方会提示用户。
        return {{}, TodoLoadStatus::not_found};
    }

    std::ifstream file(filename);
    // 打开文件准备读取。打开失败（权限不足等）时 file 为"假"。
    if (!file) {
        return {{}, TodoLoadStatus::open_failed};
    }

    try {
        json document;
        // 声明一个空的 JSON 值。

        file >> document;
        // 用流提取运算符（>>）把整个文件内容解析进 document。
        // 文件内容不是合法 JSON 时这里会抛 json::exception。

        if (!document.is_array()) {
            // 顶层必须是 JSON 数组：[{...}, {...}, ...]
            // 如果不是数组（比如是个对象或数字），说明文件格式不对。
            return {{}, TodoLoadStatus::invalid_json};
        }

        std::vector<Todo> loaded;
        loaded.reserve(document.size());
        // reserve：预先分配够用的内存，避免 push_back 反复扩容（小优化）。

        for (const auto& value : document) {
            // 遍历数组里的每一个 JSON 对象。
            const auto todo = jsonToTodo(value);
            if (!todo) {
                // 任意一条任务解析失败 → 整个文件判为无效。
                // 宁可全不加载，也不加载一半，避免数据不一致。
                return {{}, TodoLoadStatus::invalid_json};
            }
            loaded.push_back(*todo);
            // *todo 取出 optional 里装着的 Todo（此时已确认有值）。
        }
        return {std::move(loaded), TodoLoadStatus::ok};
        // std::move：把 loaded 的"所有权"转移给返回值，避免整个列表被拷贝一遍。
    } catch (const json::exception&) {
        return {{}, TodoLoadStatus::invalid_json};
    }
}

// ------------------------------------------------------------------
// 把整个任务列表写进 JSON 文件（每次增删改后调用）
// 返回 TodoSaveStatus 表示保存结果（见 utils.h）。
// ------------------------------------------------------------------
TodoSaveStatus saveTodos(const std::vector<Todo>& todos, const std::string& filename) {
    json document = json::array();
    // 先造一个空 JSON 数组。
    for (const auto& todo : todos) {
        document.push_back(todoToJson(todo));
        // 每个 Todo 转成 JSON 对象，追加进数组。
    }

    std::ofstream file(filename, std::ios::trunc);
    // std::ios::trunc = truncate（截断）：打开时清空旧内容再写入。
    // 因为我们写入的是"当前完整列表"，旧内容本来就要被整体替换。
    if (!file) {
        return TodoSaveStatus::open_failed;
    }
    file << document.dump(4);
    // dump(4)：把 JSON 对象转成带缩进的字符串（4 空格缩进），
    // 生成的文件美观、易读，方便用户手动编辑。
    file.flush();
    // 把缓冲内容立刻写到磁盘（与 logger.cpp 里 flush 同理）。
    return file ? TodoSaveStatus::ok : TodoSaveStatus::write_failed;
    // 写入后再检查一次 file 的状态：
    // 如果写的过程出错了（比如磁盘满了），此时会暴露出来。
}
