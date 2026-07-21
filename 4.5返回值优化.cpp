// 大白话：你可能会想——"getFruits() 里面创建了 fruits，return 的时候不是要复制一份给外面吗？"
// 答案是：现代 C++ 编译器很聪明，它会识别出"反正这个 fruits 函数用完后也不要了，不如直接让外面的变量用它的内存"。
// 所以实际运行时没有发生拷贝，就像你直接把碗端出去，而不是重新做一碗。这叫 RVO（Return Value Optimization）。

#include <iostream>
#include <string>
#include <vector>

//放心的直接返回容器，编译器会自己优化
std::vector<std::string> getFruits(){
    std::vector<std::string> fruits ={"苹果","香蕉","橙子"};
    std::cout<<"getFruits函数内打印结果："<<" ";
    for(const auto& fruit:fruits){
        std::cout<<fruit<<" ";
    }
    std::cout<<std::endl;
    return fruits;
    //编译器会优化成直接构造，不会发生拷贝构造
}


int main(){
    //高效，没有拷贝发生
    auto fruits = getFruits();

    fruits.push_back("葡萄");

    std::cout<<"main函数内打印结果："<<" ";
    for(const auto& fruit:fruits){
        std::cout<<fruit<<" ";
    }
    std::cout<<std::endl;




    
}


