// ============================================================
// logger.h —— 日志记录器（Logger）的类声明
//
// 作用：把程序运行过程中的重要事件（启动、添加任务、报错等）
//       追加写入一个日志文件（如 13.3.0app.log），方便事后排查问题。
//
// 注意：这里只有"声明"（类长什么样、有什么函数），
//       函数的具体实现放在 src/logger.cpp 里。
//       这种"声明与实现分离"的做法是 C++ 多文件项目的标准风格，
//       好处是：其他文件只需要看到声明就能调用，编译也更快。
// ============================================================

#pragma once
// 防止头文件被重复包含（详见 todo.h 顶部的说明）。

#include <fstream>
// 文件流头文件，ofstream 支持"写文件"。
#include <string>
// std::string 字符串类型。

// ------------------------------------------------------------------
// Logger 类：负责写日志文件
// ------------------------------------------------------------------
class Logger {
public:
	// explicit 禁止隐式转换：
	// 没有 explicit 时，代码里写 Logger l = "xxx"; 也能编译通过（隐式转换）。
	// 加上 explicit 后，必须写成 Logger l{"xxx"};（显式构造），
	// 可以避免不小心把字符串当成 Logger 用的低级错误。
	explicit Logger(const std::string& filename);
	// 构造函数：传入日志文件名，打开（或创建）该文件准备追加写入。

	// 下面两个函数 = delete 表示"禁止拷贝"。
	// Logger 内部持有一个 ofstream 文件对象，文件对象是不能被复制的
	// （复制一份会破坏文件的唯一性）。所以把拷贝构造和拷贝赋值都删掉，
	// 编译器遇到复制 Logger 的代码就会直接报错，从源头杜绝问题。
	Logger(const Logger&) = delete;
	Logger& operator =(const Logger&) = delete;

	bool isOpen() const;
	// 查询日志文件是否成功打开。调用方可以根据结果决定是否警告用户。
	// 末尾的 const 表示"这个函数不会修改 Logger 内部的成员"。

	void info(const std::string& msg);
	// 记一条"信息"级别的日志，例如"程序启动"。

	void warning(const std::string& msg);
	// 记一条"警告"级别的日志，例如"任务类别代码无效"。

	void error(const std::string& msg);
	// 记一条"错误"级别的日志，例如"任务文件无法打开"。

private:
	void write(const std::string& tag, const std::string& msg);
	// 私有辅助函数：真正把一行日志写到文件里。
	// tag 是日志级别标签（INFO / WARNING / ERROR），
	// 上面三个 public 函数只是把 tag 传进来而已。
	// 私有 = 只允许 Logger 自己调用，外部代码碰不到。

	std::ofstream file_;
	// 成员变量：日志文件对象。构造时打开，随对象销毁自动关闭。
	// ofstream 的追加模式（std::ios::app）在 logger.cpp 的构造函数里设置。
};
