// 输入流中最核心的操作符就是 >>（提取运算符）。它的特点是：

//自动以空白字符（空格、Tab、换行符）作为分隔符。

//自动进行类型转换（将字符串形式的数据解析为指定变量的类型）。

//按顺序消费数据（每提取一次，流内部的读取指针就会往后移动）。

#include <iostream>
#include <sstream>
#include <optional>
#include <string>


// 安全解析：只有当"整个字符串"恰好是一个整数时才成功`
std::optional<int> parseInputToInt(const std::string& str) {
    std::istringstream iss(str);
    int num;
    // 第一步：iss >> num 提取，成功说明字符串开头是数字
    // 第二步：iss.eof() 检查，提取后流是否已到末尾（没有残留内容）
    // 两者同时成立，才说明整个字符串就是一个完整的整数
    if (iss >> num && iss.eof()) {
        return num;
    }
    return std::nullopt;
}

int main(){
    std::string text="12 34";
    std::istringstream stream(text);

    std::string value1;
    std::string value2;

    //1.利用流提取：按空格分割字符串，自动跳过开头的空格
    stream>>value1>>value2;

    std::cout<<"prased is value1:"<<value1<<std::endl;
    std::cout<<"prased is value2:"<<value2<<std::endl;

    //2.利用optional安全解析
    // 注意：text 是 "12 34"，含两个数字，有残留内容
    // 所以 parseInputToInt 会返回空（解析失败）——正好演示了"无剩余"条件
    auto parseValue = parseInputToInt(text);
    if (parseValue) {
        // 使用 * 解引用，获取解析后的整数
        std::cout << "解析结果：" << *parseValue << std::endl;
    } else {
        std::cout << "parse input failed" << std::endl;
    }

    // 换成"整个字符串就是一个整数"的例子，就能成功
    auto ok = parseInputToInt("3333");
    if (ok) {
        std::cout << "解析结果：" << *ok << std::endl;
    }
}
