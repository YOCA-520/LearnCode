#include <iostream>
#include <string>
#include <vector>
#include <memory>

// 理解 override
// void speak() const override { ... }
// 关键字	作用
// virtual	写在父类中，表示"这个函数可以被子类重写"
// override	写在子类中，表示"我要重写父类的虚函数"——如果父类没有这个虚函数，编译器报错
// final	写在子类中，表示"不能再被后续子类重写"（进阶，暂不展开）

class Animal{
public:
    explicit Animal(const std::string& name):name_(name){}

    //virtual=“这个函数可能被子类重写，运行时根据实际对象的类型调用不同的函数”
    //virtual虚函数
    virtual void speak()const{
        std::cout<<name_<<"发出动物声音"<<std::endl;
    }
    //virtual虚析构函数:确保通过父类指针调用子类析构函数时，
    //子类析构函数也被调用避免内存泄漏
    virtual ~Animal()=default;
    //default析构函数:默认的析构函数，不执行任何操作。

    const std::string& getName()const{
        return name_;
    }


private:
    std::string name_;
};

class Dog:public Animal{
public:
    explicit Dog(const std::string& name):Animal(name){

    }

    //override重写父类虚函数="我明确表示要重写父类的虚函数"
    //如果父类没有这个虚函数，编译器会报错
    void speak()const override{
        std::cout<<getName()<<"发出汪汪汪"<<std::endl;
    }
};

class Cat:public Animal{
public:
    explicit Cat(const std::string& name):Animal(name){}
    void speak()const override{
        std::cout<<getName()<<"发出喵喵喵"<<std::endl;
    }

};

void letAnimalSpeak(const Animal& animal){
    //同一个函数，传入不同对象，表现出不同行为
    animal.speak();
}

int main(){
    Dog dog("旺财");
    Cat cat("小白");
    //直接调用
    dog.speak();
    cat.speak();

    std::cout<<"\n--------通过引用调用（多态）--------"<<std::endl;

    letAnimalSpeak(dog);
    letAnimalSpeak(cat);
    std::cout<<"\n--------通过指针管理多种动物--------"<<std::endl;
    //用unique_ptr<Animal>可以指向任意子类
    std::vector<std::unique_ptr<Animal>> animals;
    animals.push_back(std::make_unique<Dog>("旺财"));
    animals.push_back(std::make_unique<Cat>("小白"));
    //遍历vector，调用每个对象的speak()函数
    for(const auto& animal:animals){
        animal->speak();
    }
    return 0;
}