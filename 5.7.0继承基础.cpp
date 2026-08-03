#include <iostream>
#include <string>

// 访问修饰符	自己内部	子类内部	外部代码
// public	    ✅	        ✅	       ✅
// protected	✅	        ✅	       ❌
// private	    ✅	        ❌          ❌ 

//继承的核心含义是 "子类是一种父类"（is-a relationship）


//基类
class Animal{
public:
    explicit Animal(const std::string& name):name_(name){
        std::cout<<"创建动物"<<name_<<std::endl;
    }

    void speak(const std::string& message="")const{
        if(!message.empty()){
           //name_=message;//()后添加的const限制修改name_
            std::cout<<name_<<"在说:"<<message<<std::endl;
        }
    
    }

    const std::string& GetName()const{return name_;}
    //定义获取名称的方法，返回const引用，防止修改名称

protected://子类可以访问，private不能访问(仅在基类中定义)
    std::string name_;

};

//派生类（子类）
class Dog:public Animal{
public:
    //构造函数：先初始化基类成员，再初始化子类成员
    explicit Dog(const std::string& name,int big=10):Animal(name),big_(big){
        std::cout<<"创建狗"<<name_<<std::endl;
    }
    //定义狗的构造函数，调用动物的构造函数初始化名称

    //子类可以访问基类的保护成员，因为是继承关系

    //子类新增功能：定义一个方法，用于判断狗是否大
    void big()const{
        if(big_>=10) {
            std::cout<<name_<<"是大狗"<<std::endl;
        }else{
            std::cout<<name_<<"是小狗"<<std::endl;
        }
    }

private:
    int big_;
};


class Cat:public Animal{
public:
    explicit Cat(const std::string& name,const std::string& personality):
        Animal(name),personality_(personality){
        std::cout<<"创建猫"<<name_<<std::endl;
    }

    void personality()const{//personality性格
        std::cout<<"猫"<<name_<<"的性格是"<<personality_<<"的"<<std::endl;
    }

private:
    std::string personality_;
};


int main(){
    Dog dog("旺财",15);
    Dog dog2("发财",5);
    dog.big();
    dog2.big();

    Cat cat("小白","活泼");
    Cat cat2("小黑","懒散");
    cat2.personality();
    cat2.personality();

    cat.speak();
    dog.speak("嗨嗨害！");

}