#include <iostream>


//第一个函数
int add(int a, int b){
    return a+b;//返回a+b的结果
}

//数值传递：函数收到的是原始数据的复印件，不会改变原始数据
void printStudentName(std::string name){
    std::cout<<"学生姓名:"<<name<<std::endl;
    //这里修改不会对原始数据有影响
    //函数内修改不会对原始数据产生影响，因为是值传递
    name="*改后*"+name;
    std::cout<<"修改后的姓名:"<<name<<std::endl;
}

//引用传递函数收到的是原始数据的别名（引用）
//修改形参会直接影响原始数据
//零拷贝，没有性能开销
void changeName(std::string& name){
    std::cout<<"修改前的姓名:"<<name<<std::endl;
    name="*改后*"+name;
    std::cout<<"修改后的姓名:"<<name<<std::endl;
}

//const引用传递：只能读取原始数据，不能修改原始数据
//用于传递大对象，避免拷贝开销
void printInfo(const std::string& info){
    std::cout<<"printInfo函数打印信息:"<<info<<std::endl;
    //info="*改后*"+info;
    //这行会报错，不允许修改const引用
   
}

int main(){
    //调用函数
    auto result=add(1,2);
    std::cout<<"1+2="<<result<<std::endl;
    
    //调用数值传递测试函数
    std::string name="张三";
    printStudentName(name);
    std::cout<<"main函数内打印name的值是:"<<name<<std::endl;
    //打印当前作用域数据
    //name 未被修改，保持原始值

    //调用引用传递测试函数
    changeName(name);
    std::cout<<"main函数内打印name的值是:"<<name<<std::endl;
    //打印当前作用域数据
    //name 被修改，保持修改后的值

    std::string message="这是一个重要的信息";
    printInfo(message);


}