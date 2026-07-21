// 通过带日志的包装类，观察 RVO（返回值优化）是否生效
// 如果 ★ 拷贝构造 没有出现，就说明编译器优化掉了拷贝

//往后学习到一定程度才能看懂。左右值引用在后续章节

#include <iostream>
#include <string>
#include <vector>

struct LogString {
    std::string s;

    LogString(const char* c) : s(c) {   
        //等价于LogString(std::string c)｛s=c;｝
        std::cout << "  构造: " << s << "\n";
    }

    // 拷贝构造函数（加日志）
    LogString(const LogString& other) : s(other.s) {//other.s是other的成员变量s的引用
        //等价于LogString(std::string other.s)｛s=other.s;｝
        std::cout << "  ★ 拷贝构造: " << s << " (拷贝发生了！)\n";
    }

    // 移动构造函数（加日志）
    LogString(LogString&& other) noexcept : s(std::move(other.s)) {
        std::cout << "  ➤ 移动构造: " << s << "\n";
    }
};

std::vector<LogString> getFruits() {
    std::vector<LogString> fruits = {{"苹果"}, {"香蕉"}, {"橙子"}};
    std::cout << "--- getFruits 内 ---\n";
    return fruits;  // 这里本应发生拷贝，但编译器会做 RVO 优化
}

int main() {
    std::cout << "=== 调用 getFruits() ===\n";
    auto fruits = getFruits();

    std::cout << "=== 遍历结果 ===\n";
    for (const auto& f : fruits) {
        std::cout << "  " << f.s << "\n";
    }

    return 0;
}
