#include <iostream>
#include <tuple> //元组
#include <string>
#include <map> // 有序
// 需要按键排序或范围查询 → 用 map
// 追求平均查找速度，不关心顺序 → 用 unordered_map

// return multiple values form a function  //mutiple[多个]
// tuple 元组
// A special container that can store multiple types of values
// special[特殊]//container[容器] //store[存储]
std::tuple<std::string, int, double> getStudentInfo()
{
    return {"XiaoMing", 18, 95.5};
}

int main()
{
    // 1.unpacking the tuple //unpack[解包]
    auto [name, age, score] = getStudentInfo();
    std::cout << name << ":" << age << " age," << score << " score" << std::endl;

    // 2.unpacking the pair //pair[xx对]
    std::pair<int, std::string> studentId(1001, "ZhangSan");
    auto [id, stuName] = studentId;
    std::cout << "id:" << id << "," << "name:" << stuName << std::endl;

    // 3.unpacking the array //array[数组]
    int arr[] = {1, 2, 3, 4, 5};
    auto [a, b, c, d, e] = arr;
    std::cout << "a:" << a << "," << "b:" << b << "," << "c:" << c << "," << "d:" << d << "," << "e:" << e << std::endl;

    // 4.use within if statement condition //在 if 语句中使用
    std::map<std::string, int> data = {{"a", 1}, {"b", 2}, {"c", 3}};
    if (auto it = data.find("a"); it != data.end())
    {
        // data.find("a") return iterator to "a"
        auto [key, value] = *it;
        std::cout << "found a:" << key << "," << value << std::endl;
    }
}
