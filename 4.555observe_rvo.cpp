// 演示 RVO（返回值优化）：通过地址判断是否是同一个对象
// 如果返回时没有发生拷贝/移动，说明 RVO 生效了

#include <iostream>
#include <string>

struct Widget {
    std::string name;

    Widget(const char* n) : name(n) {
        std::cout << "  [构造] " << name << "  (this=" << this << ")\n";
    }

    Widget(const Widget& other) : name(other.name) {
        std::cout << "  [拷贝★] " << name << "  (this=" << this << ", from=" << &other << ")\n";
    }

    Widget(Widget&& other) noexcept : name(std::move(other.name)) {
        std::cout << "  [移动➤] " << name << "  (this=" << this << ", from=" << &other << ")\n";
    }
};

Widget getWidget() {
    Widget w("Hello");
    std::cout << "  getWidget 内部 w 的地址: " << &w << "\n";
    return w;  // 如果编译器做 RVO，不会发生拷贝/移动
}

int main() {
    std::cout << "=== 调用 getWidget() ===\n";
    Widget w2 = getWidget();
    std::cout << "  main 中 w2 的地址: " << &w2 << "\n\n";

    std::cout << "结论：如果两个地址相同 → 编译器做了 RVO，没有拷贝\n";
    std::cout << "      如果出现 [拷贝★] 或 [移动➤] → 拷贝发生了\n";

    return 0;
}
