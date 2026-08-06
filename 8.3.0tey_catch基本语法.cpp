#include <iostream>
#include <string>
#include <stdexcept>//标准异常库

int divide(int a,int b)/*（除法）用来触发异常*/{
    if(b==0){
        throw/*throw(投掷)用来抛出异常*/ std::runtime_error("除数不能为0!");
    }
    return a/b;
}

int main(){
    try{
        //尝试运行可能触发异常的代码
        int result=divide(10,0);
        std::cout<<"10/0="<<result<<std::endl;
    }catch(const std::runtime_error& e){
        std::cout<<"捕获到异常："<<e.what()<<std::endl;
    }

    //正常执行：不回因为异常而中断
    std::cout<<"程序继续执行"<<std::endl;
    return 0;
}

