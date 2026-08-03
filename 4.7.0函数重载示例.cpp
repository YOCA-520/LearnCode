// ### 占位空文件：学到对应小节时，把代码敲进来 ###
// 4.7.0 函数重载
// 📍 对应教程：第 4 章 4.7 节（同名函数不同参数）

#include <iostream>
#include <string>

    //✅ 重载：三个函数同名 printMax，编译器按参数自动匹配
    // 💡 代码里的 (a > b ? a : b) 是三目运算符（ternary operator）：
    //    条件 ? 值1 : 值2 —— 条件成立取"值1"，否则取"值2"
    //    大白话：a > b 吗？是就输出 a，不是就输出 b。相当于 if-else 的一行简写

void printMax(int a,int b){
    std::cout<<"数据类型为整数"<<std::endl;
    std::cout<<"a和b中的较大值是："<<(a>b?a:b)<<std::endl;
    //(a>b?a:b)：(三目运算符)如果a大于b，就取a，否则取b
    //类比if-else语句
    //if(a>b){
    //    std::cout<<"a大于b"<<std::endl;
    //}else{
    //    std::cout<<"a不大于b"<<std::endl;
    //}
}

void printMax(double a,double b){
    std::cout<<"数据类型为双精度浮点数"<<std::endl;
    std::cout<<"a和b中的较大值是："<<(a>b?a:b)<<std::endl;
}

void printMax(std::string a,std::string b){
    std::cout<<"数据类型为字符串"<<std::endl;
    std::cout<<"a和b中的较大值是："<<(a>b?a:b)<<std::endl;
}

int main(){
    printMax(3,5); //调用第一个函数
    printMax(3.0,5.0); //调用第二个函数
    printMax("apple","banana"); //调用第三个函数
}