#include <iostream>
#include <memory>
#include <vector>
#include <string>

//怪物基类
class Monster{
public:
    explicit Monster(const std::string& name,int hp,int damage,bool damageReduction)
        :name_(name),hp_(hp),damage_(damage),damageReduction_(damageReduction){}

    virtual ~Monster()=default;//虚析构函数

    virtual void attack()const=0;//纯虚函数：子类必须重写

    bool isAlive()const{
        return hp_>0;
    }

    void takeDamage(int damage)  {
        if(damageReduction_){
            damage/=2;
            hp_-=damage;
            std::cout<<name_<<"（伤害减免）"<<"受到"<<damage<<"点伤害"<<std::endl;
            if(hp_<0){
                hp_=0;
            }
        }else{
            hp_-=damage;
            std::cout<<name_<<"受到"<<damage<<"点伤害"<<std::endl;
            if(hp_<0){
                hp_=0;
            }
        }
    }

    const std::string& getName()const{//获取名称
        return name_;
    }
    const int& getHp()const{
        return hp_;
    }

protected:
    std::string name_;//名称
    int hp_;//生命值
    int damage_;//伤害值
    bool damageReduction_;//是否有伤害减免
};

//怪物龙
class Dragon:public Monster{
public:
    explicit Dragon(const std::string& name,int hp,int damage,bool damageReduction)
        :Monster(name,hp,damage,damageReduction){}
    void attack()const override{
        std::cout<<name_<<"喷出火焰！伤害"<<damage_<<"点"<<std::endl;
    }
};

//怪物哥布林
class Goblin:public Monster{
public:
    explicit Goblin(const std::string& name,int hp,int damage,bool damageReduction)
        :Monster(name,hp,damage,damageReduction){}
    void attack()const override{
        std::cout<<name_<<"挥动小刀！伤害"<<damage_<<"点"<<std::endl;
    }
};

int main(){
    std::vector<std::unique_ptr<Monster>> monsters;
    monsters.push_back(std::make_unique<Dragon>("龙王",500,200,true));
    monsters.push_back(std::make_unique<Goblin>("QQ人",10,10,false));
    monsters.push_back(std::make_unique<Goblin>("精英QQ人",100,100,true));
   
    std::cout<<"--------游戏开始--------"<<std::endl;
    std::cout<<"--------怪物发起攻击--------"<<std::endl;
    for(const auto& m:monsters){
        m->attack();
    }

    std::cout<<"--------玩家发起攻击--------"<<std::endl;
    for(const auto& m:monsters){
        m->takeDamage(200);
    }

    std::cout<<"--------回合结算：--------"<<std::endl;
    for(const auto& m:monsters){
        std::cout<<m->getName()<<"剩余生命值："<<m->getHp()<<"    ";
        if(m->isAlive()){
            std::cout<<m->getName()<<"存活"<<std::endl;
        }else{
            std::cout<<m->getName()<<"死亡"<<std::endl;
        }
    }
    std::cout<<"--------战斗结束--------"<<std::endl;
    
    //移除死亡的怪物
    for(auto it=monsters.begin();it!=monsters.end();){
        if(!(*it)->isAlive()){
            std::cout<<(*it)->getName()<<"已离场（unique_ptr已经释放）"<<std::endl;
            it=monsters.erase(it);//erase会自动释放unique_ptr
        }else{
            ++it;
        }
    }
    
}
