#include <iostream>
#include <unordered_map> //unordered_map(无序映射表)
#include <string>

int main()
{
    std::unordered_map<std::string, double> prices; // 价格

    // add product[产品] price
    prices["apple"] = 5.5;
    prices["banana"] = 3.2;
    prices["orange"] = 4.0;
    prices["grapes"] = 12.8;

    //---1.check whether the key exists.   //check[核对]//whether[是否]//exists[存在]
    // Use .find(key) to lookup the specified key in unordered_map.  //to look[查找]//specified[特定的，指定的]
    // if found,return an iterator pointing to this key-value pair.  //iterator[迭代器]//pointing to[指向，指着]
    // if not found，return .end() (the marker as "nomatching").  //nomatching[无匹配项]
    /* Therefore,the standard way to judge whether the lookup succeeds is:   //standaed[标准]//way[方法]//judge[判断]//lookup[查阅]//succeeds[成功]
       if(redult!=.end())   */
    /* //refer[表概念指向；参考；谈到；针对](这里可翻译为[代指])
       // element[元素]//position[位置(空间，职位)]//past[下一个]//sentinel[哨兵守卫]   */
    // end() does not refer to the last element,but the position past the last element--a sentinel marker.

    std::string item /*物品*/ = "榴莲";
    if (prices.find(item) != prices.end())
    {
        std::cout << item << item << " price is:" << prices[item] << "RMB." << std::endl;
    }
    else
    {
        std::cout << "not found price of :" << item << "." << std::endl;
    }

    //---2.Safe Access,use ：at()
    // prices["apple"] can be used for access to，but if key does not exist,会自己创建
    // this 有时候不是你想要的，（不小心写错key，in unordered_map会多出一个空条目）
    //.at()更安全，kay不存在时会抛出 std::out_of_range 异常，不会偷偷创建
    // 所以"只查一下”时用.at(),“想添加或修改时”用[]
    try
    {
        std::cout << "apple price :" << prices.at("apple") << std::endl;
        std::cout << "荔枝 price :" << prices.at("荔枝") << std::endl;
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "not found price is item" << e.what() << "." << std::endl;
    }

    //---3.delete element
    //.erase(key) delete specified key-value pair
    // if key does not exist,nothing happens.
    prices.erase("apple"); // delete apple
    
    // total[总数]//kind[种类]//products[产品]//remain[保持]//operation[操作]
    std::cout << "A total of " << prices.size() << " kind of products remain after the deletion operation." << std::endl;

    // 4.check whether it is empty
    //.empty() return turn (unordered_map is empty) or false (unordered_map not is empty)
    if (prices.empty())
    {
        std::cout << "this unordered_map is empty!" << std::endl;
    }

    return 0;
}
