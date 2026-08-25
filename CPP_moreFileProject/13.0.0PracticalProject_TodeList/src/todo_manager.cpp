// ============================================================
// todo_manager.cpp —— TodoManager 类的实现（业务逻辑核心）
//
// 这是整个程序最核心的文件：所有菜单功能（添加/查看/完成/删除/
// 排序/统计）的实现都在这里。
//
// 代码组织：
//   上半部分（匿名命名空间里）：一批"纯辅助函数"，
//     比如读取一行输入、把类别代码翻译成中文等。它们不属于
//     TodoManager 类，只是被下面的成员函数调用。
//   下半部分：TodoManager 各成员函数的实现，与 todo_manager.h
//     里的声明一一对应。
//
// 依赖关系：
//   - utils.h 的 loadTodos / saveTodos：负责读、写 JSON 文件
//   - logger_（Logger 类）：负责记录运行日志
//   - Todo 结构体：任务数据
// ============================================================

#include "todo_manager.h"
#include "utils.h"
// utils.h：要用 loadTodos（启动加载）、saveTodos（改动后保存）。
#include <algorithm>
// std::stable_sort（稳定排序）、std::count_if（条件计数）。
#include <cstdint>
// std::int64_t、std::uintmax_t：定长整数类型（不依赖平台位宽）。
#include <iostream>
// std::cin / std::cout。
#include <map>
// std::map：键值对容器，这里存"类别代码 → 中文名"的对应表。
#include <optional>
// std::optional：表示"可能没有输入"（用户按了 Ctrl+Z/Ctrl+D 结束输入）。
#include <sstream>
// std::istringstream：把字符串当输入流解析（用于把字符串转成整数）。
#include <utility>
// std::move 等（本文件主要用 move 构造 optional 里的字符串）。

// ============================================================
// 匿名命名空间：以下辅助函数只在本文件可见
// （详细解释见 logger.cpp 顶部的说明，两者是同一个技巧）。
// ============================================================
namespace {

// 类别代码 → 中文名的对照表（显示给用户看时用）。
// std::map<键类型, 值类型> 按"键"自动排序，支持 .find() 快速查找。
const std::map<std::string, std::string> categoryLabels{
    {"work", "工作"},
    {"life", "生活"},
    {"study", "学习"}
};

// ------------------------------------------------------------------
// 读取一行输入（带提示语）
// 返回 optional：用户正常输入时里面有内容；
// 用户按 Ctrl+Z（Windows）/ Ctrl+D（Linux）结束输入时返回空。
// ------------------------------------------------------------------
std::optional<std::string> readLine(const std::string& prompt) {
    std::cout << prompt;
    // 先打印提示语，比如"任务标题："。

    std::string line;
    if (!std::getline(std::cin, line)) {
        // getline 读一整行（含空格）。读到文件结束符时返回"假"。
        return std::nullopt;
    }
    return line;
}

// ------------------------------------------------------------------
// 读取"不允许为空"的输入：空行会让用户重新输入，直到非空为止。
// ------------------------------------------------------------------
std::optional<std::string> readRequiredLine(const std::string& prompt) {
    while (true) {
        const auto line = readLine(prompt);
        if (!line) {
            // 用户主动结束输入（Ctrl+Z）→ 直接放弃本次操作。
            return std::nullopt;
        }
        if (line->find_first_not_of(" \t\r\n") != std::string::npos) {
            // find_first_not_of(" \t\r\n")：找到第一个"不是空格/制表符/换行"
            // 的字符位置。npos 表示"找不到"。
            // 所以这一句的意思就是"这一行里有没有非空白字符"？
            // 有 → 说明不是空行，接受它。
            return line;
        }
        std::cout << "输入不能为空，请重试。\n";
        // 全是空白 → 提示并重新循环。
    }
}

// ------------------------------------------------------------------
// 读取一个整数
// 严格校验：必须整体都是数字（用 istringstream 解析），
// 比如 "12abc" 这种"数字后带尾巴"的输入也会被拒绝。
// ------------------------------------------------------------------
std::optional<std::int64_t> readInteger(const std::string& prompt) {
    const auto line = readLine(prompt);
    if (!line) {
        return std::nullopt;
    }

    std::istringstream input(*line);
    // 把用户输入的那行字符串包装成"输入流"，方便像 cin 一样解析。
    // 这是"字符串 → 整数"转换的常用手法。

    std::int64_t value{};
    char extra{};
    // 这个 char 是"探针"：用来检查数字后面还有没有多余字符。

    if (!(input >> value) || (input >> extra)) {
        // 两种失败情况：
        // 1. input >> value 失败 → 开头就不是数字；
        // 2. input >> extra 成功 → 数字后面还有别的东西（如 "5abc"）。
        return std::nullopt;
    }
    return value;
}

// ------------------------------------------------------------------
// 读取任务序号，并校验它在 1～todos.size() 范围内
// 返回的是"数组下标"（0 起），不是用户看到的序号（1 起）。
// 例如用户输入 3，返回 2（第 3 条任务的数组下标是 2）。
// ------------------------------------------------------------------
std::optional<std::size_t> readTodoIndex(const std::vector<Todo>& todos) {
    const auto number = readInteger("请输入任务序号：");
    if (!number || *number < 1) {
        // 没输入或小于 1：序号必须从 1 开始。
        return std::nullopt;
    }

    const auto oneBased = static_cast<std::uintmax_t>(*number);
    // 转成无符号整数再比较，避免"负数转无符号"变巨大数的坑。
    if (oneBased > todos.size()) {
        // 序号超过任务总数：越界。
        return std::nullopt;
    }
    return static_cast<std::size_t>(oneBased - 1);
    // 用户看到的 1 号 = 数组下标 0，所以减 1。
}

// ------------------------------------------------------------------
// 类别代码 → 中文名（查上面的对照表）
// 查不到就原样返回代码本身（万一 JSON 里存了未知类别，也不至于报错）。
// ------------------------------------------------------------------
std::string categoryLabel(const std::string& category) {
    const auto found = categoryLabels.find(category);
    // map 的 find：找到返回指向该键值对的迭代器，找不到返回 end()。
    return found == categoryLabels.end() ? category : found->second;
}

// ------------------------------------------------------------------
// 打印一条任务（菜单列表里每一行长这样）：
//   1. [待办] [3级] 写周报（工作）
//   ↑序号 ↑状态 ↑优先级 ↑标题  ↑类别
// ------------------------------------------------------------------
void printTodo(std::size_t displayIndex, const Todo& todo) {
    std::cout << displayIndex << ". "
              << (todo.done ? "[完成]" : "[待办]")
              // 三目运算符：done 为真打印"[完成]"，否则打印"[待办]"。
              << " [" << todo.priority << "级] "
              << todo.title << "（" << categoryLabel(todo.category) << "）\n";
}

} // 匿名命名空间结束

// ============================================================
// 以下是 TodoManager 类的成员函数实现
// ============================================================

// ------------------------------------------------------------------
// run()：程序主循环——显示菜单、根据选择分派到各功能函数
// ------------------------------------------------------------------
void TodoManager::run() {
    // 第 1 步：启动时从 JSON 文件加载任务列表。
    const TodoLoadResult loaded = loadTodos("13.3.0todo.json");
    // loadTodos 的实现在 utils.cpp，返回"任务列表 + 状态"。

    switch (loaded.status) {
    case TodoLoadStatus::ok:
        // 加载成功：把文件里的任务倒进内存里的 todos_。
        todos_ = loaded.todos;
        break;
    case TodoLoadStatus::not_found:
        // 文件不存在：第一次运行，没任务很正常。
        std::cout << "首次运行，暂时没有任务。\n";
        break;
    case TodoLoadStatus::open_failed:
        // 文件打不开：直接退出。
        // 为什么退出？因为退出时 saveChanges 会覆盖写文件，
        // 如果现在文件就打不开，退出时的保存也会失败，
        // 但更重要的是先提示用户，避免继续操作造成误解。
        logger_.error("任务文件无法打开");
        std::cout << "任务文件无法打开，本次不会覆盖原文件。\n";
        return;
    case TodoLoadStatus::invalid_json:
        // 文件内容损坏：直接退出，防止把坏数据倒进内存后
        // 又被"保存"回去，把原文件彻底覆盖掉。
        logger_.error("任务文件不是有效的 Todo JSON");
        std::cout << "任务文件格式错误，请先备份并修复 JSON；本次不会覆盖原文件。\n";
        return;
    }

    // 第 2 步：检查日志文件是否打开成功（打不开不致命，警告一下就行）。
    if (!logger_.isOpen()) {
        std::cout << "警告：日志文件无法打开，程序仍可运行。\n";
    }
    logger_.info("程序启动，当前任务数：" + std::to_string(todos_.size()));
    // std::to_string：把数字转成字符串，方便拼进日志消息。

    // 第 3 步：主循环。每次循环：打印菜单 → 读选择 → 分派执行。
    while (true) {
        std::cout << "\n=== 待办清单 ===\n"
                  << "1. 添加  2. 查看全部  3. 未完成  4. 标记完成\n"
                  << "5. 删除  6. 按优先级排序  7. 统计  0. 退出\n";

        const auto choice = readInteger("请选择：");
        if (!choice) {
            // 输入不是整数，或用户按了 Ctrl+Z（结束输入）。
            if (std::cin.eof() || !std::cin) {
                // 输入流到了末尾（用户想结束程序）：先保存再退出。
                // 这样即使用户用 Ctrl+Z 退出，数据也不会丢。
                saveChanges();
                return;
            }
            std::cout << "无效选择，请输入菜单编号。\n";
            continue;
        }

        // switch：根据用户选择分派到对应的功能函数。
        switch (*choice) {
        case 1: addTodo(); break;          // 添加任务
        case 2: showAll(); break;          // 查看全部
        case 3: showPending(); break;      // 只查看未完成
        case 4: markDone(); break;         // 标记完成
        case 5: removeTodo(); break;       // 删除任务
        case 6: sortByPriority(); break;   // 按优先级排序
        case 7: statistics(); break;       // 统计
        case 0:
            // 正常退出：先保存，再记日志，再告别。
            saveChanges();
            logger_.info("程序退出");
            std::cout << "再见！\n";
            return;
        default:
            // 菜单里没有的选项（比如 8、9、-1）。
            std::cout << "无效选择，请输入菜单编号。\n";
            break;
        }
    }
}

// ------------------------------------------------------------------
// addTodo()：添加一条任务（标题 → 类别 → 优先级，逐个询问）
// ------------------------------------------------------------------
void TodoManager::addTodo() {
    // 1. 标题（不能为空）
    const auto title = readRequiredLine("任务标题：");
    if (!title) {
        return; // 用户中途结束输入，放弃本次添加
    }

    // 2. 类别代码（必须存在于对照表里）
    const auto category = readRequiredLine("类别代码（work/life/study）：");
    if (!category) {
        return;
    }
    if (!categoryLabels.contains(*category)) {
        // map 的 contains（C++20 新增）：判断键是否存在。
        std::cout << "类别代码无效。\n";
        logger_.warning("添加失败：类别代码无效");
        return;
    }

    // 3. 优先级（1～5，循环问到合法为止）
    int priority = 0;
    while (priority < 1 || priority > 5) {
        const auto value = readInteger("优先级（1～5，5 最高）：");
        if (!value) {
            if (std::cin.eof() || !std::cin) {
                return; // 用户结束输入，放弃添加
            }
            std::cout << "请输入整数 1～5。\n";
            continue;
        }
        if (*value < 1 || *value > 5) {
            std::cout << "请输入 1～5。\n";
            continue;
        }
        priority = static_cast<int>(*value);
    }

    // 4. 三个条件都满足：构造 Todo 加入列表。
    // 注意初始化顺序：title, category, priority, done（和结构体声明顺序一致）。
    todos_.push_back(Todo{*title, *category, priority, false});
    // *title 是 optional 的解引用，取出里面的字符串。

    logger_.info("添加任务：" + *title);
    std::cout << "已添加任务。\n";
    saveChanges();
    // 每次改动立即保存：即使程序意外退出，数据也已经落盘。
}

// ------------------------------------------------------------------
// showAll()：查看全部任务（按列表顺序，含已完成）
// ------------------------------------------------------------------
void TodoManager::showAll() const {
    if (todos_.empty()) {
        std::cout << "还没有任务。\n";
        return;
    }
    for (std::size_t i = 0; i < todos_.size(); ++i) {
        // 展示序号 = 数组下标 + 1（用户看到的序号从 1 开始）。
        printTodo(i + 1, todos_[i]);
    }
}

// ------------------------------------------------------------------
// showPending()：只显示未完成的任务
// ------------------------------------------------------------------
void TodoManager::showPending() const {
    std::size_t displayIndex = 0;
    // 未完成任务的"展示序号"单独计数（从 1 开始），
    // 这样用户看到的序号是连续的（1. 2. 3.），中间不留空号。
    for (const auto& todo : todos_) {
        if (!todo.done) {
            ++displayIndex;
            printTodo(displayIndex, todo);
        }
    }
    if (displayIndex == 0) {
        // 一条未完成的任务都没显示过。
        std::cout << "全部完成，或暂时没有任务。\n";
    }
}

// ------------------------------------------------------------------
// markDone()：把用户选中的任务标记为"已完成"
// ------------------------------------------------------------------
void TodoManager::markDone() {
    if (todos_.empty()) {
        std::cout << "还没有任务。\n";
        return;
    }
    const auto index = readTodoIndex(todos_);
    if (!index) {
        if (!(std::cin.eof() || !std::cin)) {
            std::cout << "序号无效。\n";
        }
        return;
    }

    Todo& todo = todos_[*index];
    // 注意是 Todo&（引用）不是拷贝：
    // 用引用才能修改列表里的原对象；如果写 Todo todo 就是改副本了。
    if (todo.done) {
        std::cout << "这条任务已经完成。\n";
        return;
    }
    todo.done = true;
    logger_.info("完成任务：" + todo.title);
    std::cout << "已完成：" << todo.title << "\n";
    saveChanges();
}

// ------------------------------------------------------------------
// removeTodo()：删除用户选中的任务
// ------------------------------------------------------------------
void TodoManager::removeTodo() {
    if (todos_.empty()) {
        std::cout << "还没有任务。\n";
        return;
    }
    const auto index = readTodoIndex(todos_);
    if (!index) {
        if (!(std::cin.eof() || !std::cin)) {
            std::cout << "序号无效。\n";
        }
        return;
    }

    logger_.warning("删除任务：" + todos_[*index].title);
    // 删除属于"不可恢复"的操作，日志里用 WARNING 级别记录。

    // vector 的 erase：删除指定位置的元素，后续元素自动前移。
    // 参数是"迭代器"，begin() + 下标 就定位到目标位置。
    // static_cast 把下标的无符号类型转成迭代器偏移量的有符号类型，
    // 避免"无符号相减得负数"这类隐蔽错误。
    todos_.erase(todos_.begin() + static_cast<std::vector<Todo>::difference_type>(*index));

    std::cout << "已删除。\n";
    saveChanges();
}

// ------------------------------------------------------------------
// sortByPriority()：按优先级从高到低排序
// ------------------------------------------------------------------
void TodoManager::sortByPriority() {
    // stable_sort：稳定排序——优先级相同的话，保持原来的先后顺序，
    // 这样先添加的任务在相同优先级下仍然排在前面。
    std::stable_sort(todos_.begin(), todos_.end(),
        [](const Todo& left, const Todo& right) {
            // 这是"lambda 表达式"（匿名函数）：告诉 sort 怎么比较两个元素。
            // 返回 true 表示 left 应该排在 right 前面。
            // 这里按优先级降序：大的（重要的）排前面。
            return left.priority > right.priority;
        });
    logger_.info("按优先级排序");
    std::cout << "已按优先级从高到低排序。\n";
    saveChanges();
    showAll();
    // 排完立刻显示一遍，用户马上能看到效果。
}

// ------------------------------------------------------------------
// statistics()：统计总任务/已完成/未完成的数量
// ------------------------------------------------------------------
void TodoManager::statistics() const {
    // count_if：统计满足条件的元素个数。lambda 里判断 done 是否为真。
    const auto doneCount = static_cast<std::size_t>(std::count_if(
        todos_.begin(), todos_.end(), [](const Todo& todo) { return todo.done; }));
    std::cout << "总任务：" << todos_.size()
              << "  已完成：" << doneCount
              << "  未完成：" << (todos_.size() - doneCount) << "\n";
    // 未完成 = 总数 - 已完成。
}

// ------------------------------------------------------------------
// saveChanges()：把内存中的任务列表写回 JSON 文件
// 在每次"数据有变化"之后调用（添加/完成/删除/排序/退出）。
// ------------------------------------------------------------------
void TodoManager::saveChanges() {
    const auto status = saveTodos(todos_, "13.3.0todo.json");
    // saveTodos 的实现在 utils.cpp。
    if (status == TodoSaveStatus::ok) {
        return; // 保存成功，什么都不用做
    }

    // 保存失败：记日志 + 明确告诉用户数据没有保存。
    logger_.error("任务保存失败");
    if (status == TodoSaveStatus::open_failed) {
        std::cout << "无法打开任务文件，数据尚未保存。\n";
    } else {
        std::cout << "写入任务文件失败，数据尚未确认保存。\n";
    }
}
