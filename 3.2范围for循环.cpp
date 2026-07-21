#include<iostream>
#include<vector>

int main(){
    std::vector<int> numbers = {11,22,33,4,55,6,7,9};
    //传统for循环的烦恼
    //传统写法：需要写索引、判断边界、自增
    for (int i =0 ; i<numbers.size();i++){
        std::cout<<"循环执行到第"<<i<<"次："
        <<"本次输出的数字："<<numbers[i]<<std::endl;
    }
    //问题：索引 i 容易写错（从 0 还是 1 开始？条件写 < 还是 <=？），想遍历其他容器还要换写法。

    //范围for循环
    std::vector<int> numbers2 = {44,55,66,77,88,99};

    //现代写法：不用索引，不用管边界
    for(auto num:numbers2){
        std::cout<<"本次输出的数字："<<num<<std::endl;
    }
    
    //现代写法需要索引时的写法：方法一，带计数器的范围for
    size_t idx = 0;
    //size_t 是无符号整数类型，用于表示容器的索引或大小
    //size_t 可以理解为 unsigned int（无符号整数类型）
    for (auto num : numbers2) {
        std::cout << "索引=" << idx << " 本次输出的数字：" << num << std::endl;
        ++idx;
    }

    //三种常用模式
    std::vector<std::string> fruits
        ={"apple","orange","banana","peach"};
    //method 1:只读遍历
    for(const auto& fruit:fruits){
        //const auto& 避免拷贝数据，只读，引用传递
        std::cout<<"当前水果："<<fruit<<std::endl;
    }

    //method 2:修改元素
    for(auto &fruit:fruits){
        fruit="好吃的"+fruit;
        std::cout<<"修改后的水果："<<fruit<<std::endl;
    }

    //method 3:按数值拷贝（不推荐，除非元素类型很小）
    for(auto fruit:fruits){
        std::cout<<"当前水果："<<fruit<<std::endl;
    }

    //🔬 原理小知识：范围 for 循环底层依赖容器的 begin() 和 end() 迭代器（Iterator）。
    //迭代器就像容器的"向导"，告诉循环从哪里开始、到哪里结束。
    //你不需要理解迭代器的细节，编译器全帮你处理好了。







}