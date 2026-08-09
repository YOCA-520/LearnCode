#include <iostream>
#include <unordered_map> //unordered_map(无序映射表)的头文件
#include <string>

int main()
{
    std::unordered_map<std::string, int> ages;
    // one unordered_map(无序映射表)
    // index is string type，value is int type

    // add key-value paid method(方法) 1:using [] opertor(操作符)
    ages["张三"] = 18;
    ages["李四"] = 19;
    ages["aliex"] = 21;

    // add key-value method 2:using insert()[插入] funcation
    ages.insert({"XiaoMing", 30});

    // value access(访问) by key 
    std::cout << "unordered_map(无序映射表) access by key:张三 is age:" << ages["张三"] << std::endl;

    // modefy(修改) the value  by assignment operator
    ages["张三"] = 19;
    std::cout << "unordered_map assignment(赋值) operator:张三 is new age:" << ages["张三"] << std::endl;

    // supports(支持) increment(增量) calculation(计算)
    ages["aliex"] += 3;
    std::cout << "unordered_map supports(支持) caculation(计算):aliex age in 3 years time:" /*张三三年后的年龄*/ << ages["aliex"] << std::endl;

    // get sise
    std::cout << "unordered_map in total:" /*总计的*/ << ages.size() << "people" << std::endl;

    return 0;
}
