// lambda可以捕获他在作用域中的变量

// 捕获方式总结
// 捕获方式	        语法	            说明
// 按值捕获	        [=]	                捕获所有外部变量的副本
// 按引用捕获	     [&]	            捕获所有外部变量的引用
// 混合捕获	        [a, &b]	            a 按值，b 按引用
// 值捕获可修改	     [a]() mutable {}	按值捕获但允许在内部修改
// 默认值+个别引用	 [=, &b]	        默认按值，但 b 按引用
// 默认引用+个别值	 [&, a]	            默认按引用，但 a 按值


#include <iostream> 

int main(){
    int a {1};
    int b {2};

    //直接捕获[=]：捕获所有外部变量的“快照”
    auto lambdal=[=](int x){
        return x*a+b;//a和b是拷贝进来的
    };

    std::cout<<"按值捕获："<<lambdal(5)<<std::endl;

    //按引用捕获[&]：捕获外部变量的“引用”（可以修改）
    auto lambda2=[&](int x){
        a=20;
        return x*a+b;//a和b是引用进来的
    };
    std::cout<<"按引用捕获："<<lambda2(5)<<std::endl;
    std::cout<<"a已被修改为："<<a<<std::endl;

    //还可以自定义引用捕获的变量
    auto lambdal3=[a,&b](int x){
        return x*a+b;//a是复制进来的，b是引用进来的
    };
    std::cout<<"自定义引用捕获："<<lambdal3(5)<<std::endl;

    //按值捕获但允许修改（加mutable（可变的））
    auto lambda4=[a]()mutable{
        a+=10;
        return a;
    };
}
