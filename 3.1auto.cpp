#include<iostream>
#include<vector>
#include<string>
#include<map>

int main(){
    //用auto让编译器自动推导数据类型
    auto age = 18; //编译器会推导出age是int类型
    auto name = std::string("小明"); //编译器会推导出
    auto pi = 3.14159; //编译器会推导出pi是double类型

    std::cout<<name<<"今年"<<age<<"岁，圆周率是："<<pi<<std::endl;

    //避免类型写错
    std::vector<int>scores = {99,88,77};
    for(std::vector<int>::size_type i=0;i<scores.size();++i){
        //这里的size_type是vector类中定义的无符号整数类型，避免和负数比较
        std::cout<<"第"<<i+1<<"个成绩是："<<scores[i]<<std::endl;
    }

    //使用auto简化类型声明
    std::vector<int> scores2 = {99,88,77};
    for(auto i=0u;i<scores2.size();++i){
        //这里的u表示无符号整数类型，避免和负数比较 usesigned int
        std::cout<<"第"<<i+1<<"个成绩是："<<scores2[i]<<std::endl;
    }


    //复杂类型时必不可少
    std::map<std::string,std::vector<int>> classScores;
    //这是一个键对值的映射，键是字符串类型，值是一个整数动态数组类型

    //iterator是迭代器类型，类似于指针，指向容器中的元素，这里是指向map容器中的键值对元素，从第一个键对值开始往后
    for(std::map<std::string,std::vector<int>>::iterator it = classScores.begin();it!=classScores.end();++it){
        std::cout<<it->first<<std::endl;
        //it->first是迭代器指向的键值对中的键，
        //it->second是迭代器指向的键值对中的值
        //It->second.size()是迭代器指向的键值对中的值的大小
        //second.size()可以同时拿到键和值。
    }

    //不用auto的话这个类型写出来能绕地球三圈
    for(auto it = classScores.begin();it!=classScores.end();++it){
        std::cout<<it->first<<std::endl;
    }


    //auto的注意事项
    //auto会忽略引用和const，需要手动添加
    int someObject = 3;
    auto x = someObject;//这是拷贝，不是引用
    auto& ref =someObject;//这是引用
    const auto& cref=someObject;//这是常量引用


}