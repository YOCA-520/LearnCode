#include <fmt/format.h>
#include <fmt/color.h>

int main() {
    fmt::print("Hello from fmt {}!\n", FMT_VERSION);
    fmt::print(fmt::fg(fmt::color::green), "第三方库 fmt 接入成功!\n");
    return 0;
}
