#include<iostream>
#include<memory>
#include<vector>
#include<string>

//抽象基类
class Monster{
public:
    explicit Monster(const std::string& name,int hp,int damage):name_(name),hp_(hp),damage_(damage){}
    //纯虚函数，子类必须重写
    virtual ~Monster(){
        std::cout<<"怪物"<<name_<<"已离场"<<std::endl;
    };//默认虚析构函数

    //所有怪物都能攻击，但攻击方式不同。
    virtual void attack()=0;//攻击

    bool isAlive()const{return hp_>0;}//是否存活

    void takeDamage(int damage){//怪物受到伤害
        hp_-=damage;
        if(hp_<0)hp_=0;
        std::cout<<name_<<"受到"<<damage<<"点伤害，当前生命值"<<hp_<<std::endl;
    }
    const std::string& getName()const{return name_;}//获取名称

protected:
    std::string name_;
    int hp_;
    int damage_;
};

//怪物：龙
class Dragon:public Monster{
public:
    //调用基类构造函数
    explicit Dragon(const std::string& name,int hp,int damage):Monster(name,hp,damage){}
    void attack()override{
        std::cout<<"怪物龙："<<name_<<"攻击，造成"<<damage_<<"点伤害"<<std::endl;
    }
};

//怪物：哥布林
class Goblin:public Monster{
public:
    //调用基类构造函数
    explicit Goblin(const std::string& name,int hp,int damage):Monster(name,hp,damage){}
    void attack()override{
        std::cout<<"怪物哥布林："<<name_<<"攻击，造成"<<damage_<<"点伤害"<<std::endl;
    }
};


int main(){
    std::cout<<"----------怪物战斗开始----------"<<std::endl;
    std::vector<std::unique_ptr<Monster>> monsters;
    monsters.push_back(std::make_unique<Dragon>("龙王",1000,50));
    monsters.push_back(std::make_unique<Goblin>("QQ王",100,30));
    monsters.push_back(std::make_unique<Goblin>("QQ人",10,20));

    std::cout<<"----------------回合开始-----------"<<std::endl;
    for(const auto& m:monsters){
        m->attack();
    }

    std::cout<<"----------------勇者反击----------------"<<std::endl;
    for(const auto& m:monsters){
        m->takeDamage(60);
    }

    std::cout<<"----------------回合结算-----------"<<std::endl;

    for(const auto& m:monsters){
        if(!m->isAlive()) {
            std::cout<<m->getName()<<"已死亡"<<std::endl;
        }else{
            std::cout<<m->getName()<<"存活"<<std::endl;
        }
    }


    //vector销毁时，所有Monster对象也会被销毁，调用析构函数
    std::cout<<"----------战斗结束----------"<<std::endl;
    std::cout<<"勇者已离场"<<std::endl;
    return 0;
}