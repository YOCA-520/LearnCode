#include "HelloSpdlog.h"

int main() {
    std::cout << fmt::format("圆周率：{:.2f}\n", 3.14159);
    spdlog::info("程序启动");
    spdlog::warn("磁盘空间不足，还剩 {}%", 10);
    spdlog::error("打开文件失败：{}", "config.ini");
    return 0;
}