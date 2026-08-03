//lambda表达式=
//匿名函数=
//无参数无返回值的函数=
//随用随销毁的函数

#include <iostream>

int main(){
    //定义一个lambda:计算两数之和 //function（功能，方法）
    //add的类型是std::function<int64_t(int64_t,int64_t)>（匿名函数）
    //是一个lambda表达式，用于定义一个匿名函数
    //int64_t是64位整数类型，这里表示返回值是64位整数
    auto add =[](int a,int b){
        return a+b;
    };

    //调用lambda
    int a {1};
    int b {2};
    std::cout<<"a+b="<<a+b<<add(a,b)<<std::endl;

    std::cout<<"4a+2b="<<a+b<<add(int (4*a),int (2*b))<<std::endl;

    //也可以直接调用（不赋值给变量）
    std::cout<<"直接调用lambda"<<[](int x){return x*x;}<<std::endl;

    return 0;

}