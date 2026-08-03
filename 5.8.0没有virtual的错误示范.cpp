#include <iostream>
#include <string>

// Animal* animalPtr=&dog;
// 1. 这行代码在做什么？
// &dog：获取在栈上创建的 dog 对象的内存首地址。

// Animal* animalPtr：声明一个指针变量 animalPtr，它的类型是“指向 Animal 类型的指针”。

// 赋值操作：把 dog 的内存地址存进 animalPtr 里。

// 比喻理解：
// dog 是一条真正的“金毛犬”。
// animalPtr 是一个标签盒，上面写着“这是一个动物”。
// 把金毛犬的地址贴在这个标签盒里——在 C++ 中，“狗也是一种动物”（子类对象也是基类对象），所以 C++ 允许你用父类指针指向子类对象。这叫静态向上转型（Upcasting）。

// 2. 为什么 animalPtr->speak() 打印的是“发出动物声音”？
// 这是你最疑惑的地方：明明 animalPtr 里面装的是 dog 的地址，为什么调用的却是 Animal 的 speak()？

// 核心原因在于：你的 Animal::speak() 前面没有加 virtual（虚函数）关键字！

// 编译器的“眼镜”类型：
// 当你使用 dog.speak() 时：
// 编译器的类型是 Dog，它在编译阶段就明确知道这是条狗，所以直接调用了 Dog::speak()（输出：“在汪汪叫”）。

// 当你使用 animalPtr->speak() 时：
// 编译器在编译阶段（Early Binding / 静态绑定）看的是指针的声明类型，也就是 Animal*。
// 因为没有 virtual 关键字，编译器心想：“既然你的指针类型是 Animal*，而且 speak() 只是普通函数，那我就直接去调用 Animal 类的 speak() 好了，懒得管你实际指向什么对象！”

// 这就导致了“明明指针指向的是狗，调用的却是动物声音”的现象。
class Animal{
public:
    explicit Animal(const std::string& name):name_(name){}

    void speak()const{//没有virtual关键字，子类重写时，调用的是基类的方法
        std::cout<<name_<<"发出动物声音"<<std::endl;
    }
    const std::string& GetName()const{return name_;}
    //定义获取名称的方法，返回const引用，防止修改名称

protected:
    std::string name_;
};

class Dog:public Animal{
public:
    explicit Dog(const std::string& name):Animal(name){}
    void speak()const{//虽然也定义了speak但没有virtual关键字，调用的是基类的方法
        std::cout<<name_<<"在汪汪叫"<<std::endl;
    }
};

int main(){
    Dog dog("旺财");
    dog.speak();

    //重点：用父类指针指向子类对象
    Animal* animalPtr=&dog;
    animalPtr->speak();// ❌ 输出：旺财 发出动物声音（调了 Animal::speak！）
    return 0;
}
