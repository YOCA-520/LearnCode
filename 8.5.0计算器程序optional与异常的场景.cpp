// 8.5 std::optional vs 异常：什么时候用哪个？
//场景            推荐方案                   例子
//可能没有结果     （不是错误）                 std::optional 查找用户、解析可选字段
//参数不合法        异常                       除数为零、索引越界
//外部资源失败        异常                      文件打不开、网络连接失败
//性能关键路径        optional 或错误码         游戏引擎每帧处理
//错误需要传播给上层   异常                      GUI 应用中的深层调用链

//黄金法则：“没有数值不是异常”用std::optional。发生了不该发生的事件，用异常。
//异常：程序运行时发生错误，导致程序无法继续执行。
//错误码：程序运行时发生错误，但是程序可以继续执行。
//std::optional：程序运行时发生错误，但是程序可以继续执行，只是没有数值。

#include<iostream>
#include<optional>//可选值
#include<string>
#include<sstream>//字符串流
#include<stdexcept>//异常

//安全的除法：返回optional，除以0时返回空
std::optional<double> safeDivide(double a,double b){
    if(b==0){
        return std::nullopt;//除以0不是异常，而是无效操作
    }
    return a/b;//返回结果
}

//从字符串解析数字，失败时返回空
std::optional<double> parseNumber/*解析数字*/(const std::string& str){
    // 💡 std::istringstream 是"输入字符串流"
    // 大白话：它把一个字符串"伪装"成 cin 这样的输入流
    // 然后你就可以像从键盘读输入一样，从字符串里读数据
    // iss >> value 就是从字符串中读取一个数字到 value 变量中
    // 如果读取成功（字符串开头确实是数字），iss >> value 返回 true
    // 如果读取失败（比如字符串是 "abc"），返回 false
    std::istringstream iss(str);
    double value;
    if(iss>>value){
        return value;
    }
    return std::nullopt;//parse(解析) failed(失败)，return empty(nullptr);
}

int main(){
    std::cout<<"=====safe calculator(安全计算机)====="<<std::endl;
    std::cout<<"please input:number(space)operator(space)number),for example:1+2."<<std::endl;
    std::cout<<"supported(支持) operator:+ - * /"<<std::endl;

    std::string input;
    while(true){
        std::cout<<"\n>";
        std::getline(std::cin,input);

        if(input.empty()){
            continue;
        }
        if(input=="exit"||input=="quit"){
            break;
        }

        std::istringstream iss(input);
        std::string aStr,op/*operator 符*/,bStr;
        // 从字符串流中读取数字、operator 符、数字
        iss>>aStr>>op>>bStr;

        //解析两个数字
        auto a=parseNumber(aStr);
        auto b=parseNumber(bStr);

        if(!a||!b){
            std::cout<<"can not parse number,please check input"<<std::endl;
            continue;
        }

        //计算结果
        std::optional<double> result;
        if(op=="+")result=*a+*b;
        else if(op=="-")result=*a-*b;
        else if(op=="*")result=*a*(*b);
        else if(op=="/")result=safeDivide(*a,*b);
        else{
            std::cout<<"unknown operator!"<<std::endl;
            continue;
        }

        //输出结果
        if(result){
            std::cout<<"result is:"<<*result<<std::endl;

        }else{
            std::cout<<"divide by zero is!"<<std::endl;

        }
    }
    std::cout<<"=====safe calculator end====="<<std::endl;
}
