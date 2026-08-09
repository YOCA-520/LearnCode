// 机构化遍历

#include <iostream>
#include <unordered_map>
#include <string>

int main()
{
    std::unordered_map<std::string, int> scores;
    scores["ZhangSan"] = 94;
    scores["LiSi"] = 43;
    scores["WangEr"] = 66;
    scores["LiHua"] = 88;

    // 传统iterate way：需要手动解包 pair
    std::cout << "traditional iterate method" << std::endl; // method(方法)
    for (const auto &pair : scores)
    {
        std::cout << pair.first << " : " << pair.second << " score" << std::endl;
    }

    /*unpack[解除] directly[直接的]*/
    // structured bindings can unpack key-value pairs directly.
    std::cout << "\nstructured binding iterate:" << std::endl;
    for (const auto &[name, score] : scores)
    {
        std::cout << name << " : " << score << "score" << std::endl;
    }
    return 0;
}
