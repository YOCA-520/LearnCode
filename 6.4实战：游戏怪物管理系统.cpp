#include<iostream>
#include<memory>
#include<vector>
#include<string>

//怪物基类
class Monster{
public:
    explicit Monster(const std::string& name,int hp):name_(name),hp_(hp){
        
    }

    virtual ~Monster()=default;//虚析构函数，确保子类对象被正确析构

    virtual void attack()const=0;//纯虚函数，子类必须实现

    bool isAlive()const{
        return hp_>0;
    }

    void takeDamage(int damage){
        hp_-=damage;
        std::cout<<name_<<"受到"<<damage<<"点伤害！\n"
            <<name_<<"当前生命值："<<hp_<<std::endl;
    }

    const std::string& getName()const{return name_;}



protected:
    std::string name_;
    int hp_;
};

//具体怪物类
class Dragon :public Monster{
public:
    explicit Dragon(const std::string&name,int hp):Monster(name,hp){}
};