// 调用规则：
// 1. 写 maxOf<int>(1, 2) 这类 <类型> 时，明确调用函数模板。
// 2. 写 maxOf(1, 2) 且存在完全匹配的普通函数时，优先调用普通函数重载。
// 3. 没有对应普通函数时（如 std::string），编译器会自动推导类型并调用模板。
// 4. std::string 的 > 按字典/字符编码顺序比较，不是比较字符串长度。

// template
// 模板
#include <iostream>
#include <vector>
#include <string>

struct TestSomeTypeData
{
    int num = 0;
    std::string strn = "";
    double dbl = 0;
};

// normal implementation[普通实现]
// Normal implementation:One function per type //per type[每个类型]
int maxOf(int a, int b)
{
    std::cout << "maxOf(" << a << "," << b << "):" << (a > b ? a : b) << std::endl;
    return a > b ? a : b;
}
double maxOf(double a, double b)
{
    std::cout << "maxOf(" << a << "," << b << "):" << (a > b ? a : b) << std::endl;
    return a > b ? a : b;
}

// template implementation[模板实现]
// Write once,compiler auto-generate the code.//compiler[编译器]//generrate[生成]//code[代码]
// Template container for any type//模板容器任意类型
// 一个能装任意类型的容器
template <typename T> //"T"is name of the template.
T maxOf(T a, T b)
{
    std::cout << "Template maxOf(" << a << "," << b << "):" << (a > b ? a : b) << std::endl;
    return a > b ? a : b;
}

template <typename R>
class Box
{
public:
    explicit Box(const R &value) : value_(value) {};
    R get() const { return value_; }

private:
    R value_;
};

int main()
{
    TestSomeTypeData testSomeTypeData = {
        333,
        "fuck",
        3.14};

    maxOf<int>(1, 2);
    maxOf<double>(1.0, 2.0);

    // 调用时不用写 <int>，编译器根据参数自动推导 T
    maxOf(1, 2);
    maxOf(3.5, 2.5);                                 // T = double
    maxOf(std::string("苹果"), std::string("香蕉")); // T = std::string

    Box<int> numBox2(42);
    Box<std::string> strBox2("hello");
    Box<double> doubleBox2(3.14);

    auto &[num, strn, dbl] = testSomeTypeData;
    Box<int> numBox3(num);
    Box<std::string> strBox3(strn);
    Box<double> dblBox3(dbl);

    maxOf(num, 3);
    maxOf(strn, std::string("apple"));
    maxOf(dbl, 5.66);

    return 0;
}
