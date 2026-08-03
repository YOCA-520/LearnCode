// 💡 for_each 对容器中的每一个元素执行同一个操作。
// 它和范围 for 循环很像，区别是：for_each 是函数，可以和其他算法组合使用。
// 大白话：一排人站好了，你挨个跟他们握手。

#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    std::vector<int> numbers={1,2,3,4,5,6,7,8,9,10};
    //打印每个数的平方
    //for_each (遍历循环)对容器中的每一个元素执行同一个操作
    std::for_each(numbers.begin(),numbers.end(),[](int n){
        //numbers.begin(),numbers.end(),[](int n)
        //这一块称为lambda表达式，用于定义一个匿名函数
        //也可以叫迭代器（范围，传参）
        std::cout<<n<<"的平方是："<<n*n<<std::endl;
    });

    //std::transform (变换)对容器中的每一个元素执行同一个操作，将结果存储到新容器中
    std::vector<int> numbers2={11,22,33,44,55,77};
    //注意：必须提前定义好容器的大小，否则会报错。
    //因为transform是写入已有位置，而不是插入，
    std::vector<int> doubled(numbers2.size());

    //将所有元素x2
    //transform( 输入范围，输出范围，lambda表达式 )
    std::transform(numbers2.begin(),numbers2.end(),doubled.begin(),
        [](int n){return n*2;}
    );

    std::cout<<"原始容器：";
    for(const auto& n:numbers2)std::cout<<n<<" ";
    std::cout<<std::endl;

    std::cout<<"翻倍后的容器：";
    for(const auto& n:doubled)std::cout<<n<<" ";
    std::cout<<std::endl;



}