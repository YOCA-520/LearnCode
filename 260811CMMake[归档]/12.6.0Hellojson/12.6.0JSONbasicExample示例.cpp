#include <iostream>
#include <nlohmann/json.hpp> //唯一的头文件 功能全部在json类中

// using //using 创建别名 便于使用
using json = nlohmann::json; // sort by name

int main()
{
    // 1.contruct json (c++data -> json.txt)
    json pet = {
        {"name", "cat"},
        {"age", 3},
        {"color", "white"},
        {"owner", {{"name", "小明"}, {"phone", 1000000}}},
        {"adopted", false},
    };

    // 2. cout json txt (dump[缩进] =4 ，好看)
    std::cout << "==========================" << std::endl;
    std::cout << pet.dump(4) << std::endl;
    std::cout << "==========================" << std::endl;
    // 3. read json
    std::string name = pet["name"].get<std::string>();
    // type read

    int age = pet["age"].get<int>();
    std::cout << "pet name is :" << name << std::endl;
    std::cout << "pet age is :" << age << std::endl;

    // can nest get //nest[嵌套]
    std::string ownerName = pet["owner"]["name"].get<std::string>();
    std::cout << "pet owner name is :" << ownerName << std::endl;

    // 4.add json and modify json
    pet["age"] = 3;
    pet["vaccinated"] = true;
    std::cout << "===================================" << std::endl;
    std::cout << "modifed pet age is :" << pet.dump(4) << std::endl;
    std::cout << "===================================" << std::endl;

    // 5. delete json
    pet.erase("vaccinated"); // vaccinated[接种疫苗]

    return 0;
}
