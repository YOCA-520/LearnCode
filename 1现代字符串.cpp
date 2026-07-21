#include <iostream>
#include<string>
#include <cstring>

int main()
{
    //现代写法，不用指定大小，不用关心内存
    std::string name = "小明";
    std::string greeting = "你好" + name + "！";

    //字符串拼接
    std::string message = greeting+","+name+"!";
    std::cout<<message<<std::endl;//输出“你好！小明！”

    //获取字符串长度
    std::cout<<"字符串长度："<<message.size()<<std::endl;

    //追加内容
    message+= "欢迎来到C++编程世界！";
    std::cout<<message<<std::endl;


//老写法，需要指定大小，需要关心内存，容易出错

    // 字符数组写法（需要注意预留足够的空间容纳结束符 '\0'）
    char names[] = "小明"; 
    char greetings[10] = "你好"; 

    // 字符指针写法（通常用于只读字符串常量）
    const char* str = "Hello World";

    // ⚠️ 必须手动分配足够大的内存空间，否则拼接时会发生越界（极其危险）
    char messages[50] = "你好"; 

    // 使用 strcat 进行拼接
    strcat(messages, ", ");
    strcat(messages, names);
    strcat(messages, "! ");

    std::cout << messages << std::endl; // 输出: 你好, 小明! 
    
    // 获取长度，不包含结尾的 '\0'
    std::cout << "字符串长度: " << strlen(messages) << std::endl; 

}