// 纯虚函数：= 0
// class Animal {
// public:
//     virtual void speak() const = 0;  // ← = 0 表示"纯虚函数"
// };
// 纯虚函数（Pure Virtual Function） 的特点：

// 基类不提供实现（或可以提供实现但子类必须重写）
// 包含纯虚函数的类称为抽象类（Abstract Class），不能创建对象
// // Animal animal("test");  // ❌ 编译错误！不能创建抽象类的对象
// Dog dog("旺财");           // ✅ 子类实现了所有纯虚函数，可以创建

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// ── 抽象类：形状 ──
// 抽象类 = "这个类太抽象了，不能直接造对象，但规定了子类必须实现什么"
class Shape{//形状
public:
    //纯虚函数：子类必须重写
    virtual void draw()const=0;//绘制

    //普通成员函数：子类可以直接继承
    void printInfo() const{
        std::cout<<"这是一个形状"<<std::endl;
    }

    virtual ~Shape()=default;//虚析构函数
};

//派生类：圆形
class Circle:public Shape{
public:
    void draw()const override{
        std::cout<<"绘制一个圆形"<<std::endl;
    }
};

//派生类：矩形
class Rectangle:public Shape{
public:
    void draw()const override{
        std::cout<<"绘制一个矩形"<<std::endl;
    }
};

//派生类：三角形
class Triangle:public Shape{
public:
    void draw()const override{
        std::cout<<"绘制一个三角形"<<std::endl; 
    }
};


int main (){
    //Shape s;会编译错误，不能直接创建抽象类的实例
    //但是可以用指针或引用指向子类对象
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>());
    shapes.push_back(std::make_unique<Rectangle>());
    shapes.push_back(std::make_unique<Triangle>());
    for(const auto& s:shapes){
        s->draw();//多态，每个形状自己画自己
    }

}
