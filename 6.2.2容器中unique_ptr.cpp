#include <iostream>
#include <memory>//智能指针头文件
#include <vector>//容器头文件
#include <string>//字符串头文件

class Animal{
public:
    explicit Animal(const std::string& name):name_(name){}
    ~Animal(){
        std::cout<<name_<<"离开了。"<<std::endl;
    }

    void makeSound()const{
        std::cout<<name_<<"在叫。"<<std::endl;
    }


private:
    std::string name_;
};


int main(){
    //vector存储unique_ptr:每个动物都是唯一的
    std::vector<std::unique_ptr<Animal>> animals;

    //添加动物
    animals.push_back(std::make_unique<Animal>("小黑"));
    animals.push_back(std::make_unique<Animal>("小白"));
    animals.push_back(std::make_unique<Animal>("小绿"));

    //遍历所有动物
    for(const auto& animal:animals){//unique_ptr不能拷贝，只能通过引用或针访问
        animal->makeSound();
    }



    std::cout<<"动物们即将离开..."<<std::endl;


}