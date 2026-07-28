#include <iostream>
#include <string>

class 类名 {
public:
    // ── 构造函数 ──
    类名() = default;                            // 默认构造（让编译器生成）
    explicit 类名(std::string 参数) : 成员变量_(参数) {}       // 带参构造（加 explicit）

    // ── 析构函数 ──
    ~类名();

    // ── 拷贝控制 ──
    类名(const 类名&) = delete;                  // 禁止复制（如果需要）
    类名& operator=(const 类名&) = delete;

    // ── 成员函数 ──
    void 函数名() const;                         // const = 不修改成员变量

private:
    std::string 成员变量_;//std::string 变量名_;
    int 变量名_ = 0;
};