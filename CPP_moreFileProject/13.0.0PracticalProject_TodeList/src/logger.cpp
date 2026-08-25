// ============================================================
// logger.cpp —— Logger 类的实现
//
// 这里实现 logger.h 里声明的所有函数：
//   构造时打开日志文件（追加模式），
//   info/warning/error 三种级别都调 write() 真正落盘。
//
// 日志行的格式：
//   [2026-08-13 10:30:00][INFO]程序启动，当前任务数：3
//   ^ 时间戳            ^级别  ^消息内容
// ============================================================

#include "logger.h"
// 引入自己的类声明（实现必须先看声明）。
#include <chrono>
// C++11 引入的"时间库"：system_clock 等，用于获取当前时间。
#include <ctime>
// C 语言风格的时间结构：std::tm、time_t、localtime_s/localtime_r。
#include <iomanip> //格式化输出头文件：std::put_time 格式化时间
#include <sstream> //字符串流：std::ostringstream，把内容拼成字符串

namespace
{ // 匿名命名空间：内部函数只在本文件可见，其他文件看不见。
  // 相当于"私有工具函数"，不会污染全局命名空间，
  // 也不会和别的文件的同名函数冲突。

    // 获取当前时间，格式化为 " 2026-08-13 10:30:00" 这样的字符串。
    std::string currentTime() {
        const auto now = std::chrono::system_clock::now();
        // 取当前时刻（系统时钟的"时间点"类型）。

        const std::time_t tt = std::chrono::system_clock::to_time_t(now);
        // 把"时间点"转换成 time_t（自 1970-01-01 起的秒数）。

        std::tm local{};
        // C/C++ 标准库提供的结构体类型 std::tm，
        // 用来拆分保存具体的日历时间（比如年、月、日、时、分、秒）。

    #ifdef _WIN32
        // 条件编译：_WIN32 是 Windows 上编译器自动定义的宏。
        // Windows 和 Linux 提供了不同名字的"秒数→日历时间"函数，
        // 用 #ifdef 让同一份代码在两个平台都能编译。
        if (localtime_s(&local, &tt) != 0) {
            // Windows 版：成功返回 0，失败返回错误码。
            return "unknown-time";
        }
    #else
        if (localtime_r(&tt, &local) == nullptr) {
            // Linux/macOS 版：成功返回指针，失败返回 nullptr。
            return "unknown-time";
        }
    #endif

        std::ostringstream output;
        // 字符串流：像 cout 一样 << 拼接，最后 .str() 取整串。
        // 好处是比字符串 + 拼接更高效、更安全。
        output << std::put_time(&local, " %Y-%m-%d %H:%M:%S");
        // put_time 按模板格式化时间：%Y 年 %m 月 %d 日 %H 时 %M 分 %S 秒。
        return output.str();
    }
}

// ------------------------------------------------------------------
// 以下就是 logger.h 里声明的函数的具体实现
// ------------------------------------------------------------------

// 构造函数：打开日志文件（追加模式）
// :file_(filename, std::ios::app) 是"初始化列表"——在进入函数体之前，
// 就用 filename 和"追加模式"初始化成员 file_。
// std::ios::app = append（追加）：新内容写在文件末尾，不覆盖旧内容。
Logger::Logger(const std::string& filename)
    : file_(filename, std::ios::app) {}

// isOpen：查询日志文件是否成功打开
bool Logger::isOpen() const {
    return file_.is_open(); // ofstream 自带的方法，打开成功返回 true
}

// info：记一条 INFO 级别日志（普通信息，如"程序启动"）
void Logger::info(const std::string& msg) {
    write("INFO", msg);
}

// warning：记一条 WARNING 级别日志（有问题但不致命，如"类别代码无效"）
void Logger::warning(const std::string& msg) {
    write("WARNING", msg);
}

// error：记一条 ERROR 级别日志（出错，如"文件打不开"）
void Logger::error(const std::string& msg) {
    write("ERROR", msg);
}

// write：私有辅助函数，真正把一行日志写进文件
void Logger::write(const std::string& tag, const std::string& msg) {
    if (!file_) {
        // !file_ 等于"文件没打开或已出错"（ofstream 重载了 bool 运算符）。
        // 此时直接返回：日志系统不应该让程序崩溃。
        return;
    }
    file_ << "[" << currentTime() << "]"
          << "[" << tag << "]"
          << msg << "\n";
    // 拼接一行：时间戳 + 级别标签 + 消息内容 + 换行。

    file_.flush(); // = file_ << std::flush;
    // 立即把缓冲区里的内容真正写到磁盘。
    // 如果不 flush，内容可能还留在内存缓冲区里，
    // 万一程序崩溃，最后几条日志就丢了。
}
