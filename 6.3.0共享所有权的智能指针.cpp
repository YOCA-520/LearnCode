#include <iostream>
#include <memory>//智能指针头文件
#include <string>

class GameCharacter:public std::enable_shared_from_this<GameCharacter>{
public:
    explicit GameCharacter(const std::string& name):name_(name){
        std::cout<<name_<<"进入游戏！"<<std::endl;
    }
    ~GameCharacter(){
        std::cout<<name_<<"离开了游戏！"<<std::endl;
    }

    void attack(){
        std::cout<<name_<<"在攻击！"<<"攻击时引用数量："
            <<shared_from_this().use_count()<<std::endl;
    
    }


private:
    std::string name_;
};

void battle(std::shared_ptr<GameCharacter> character){
    std::cout<<"战斗开始！"<<std::endl;
    character->attack();
    std::cout<<"战斗结束！"<<std::endl;
    // 函数结束，这个 shared_ptr 被销毁，但对象还在（因为 main 中还有一个）
}

int main(){
    //用std::make_shared创建智能指针shared_ptr（共享指针）
    auto hero = std::make_shared<GameCharacter>("勇者");

    std::cout<<"当前引用数量："<<hero.use_count()<<std::endl;

    battle(hero);

    std::cout<<"战斗后引用数量："<<hero.use_count()<<std::endl;

    {
        auto anotherRef = hero;//共享所有权
        std::cout<<"共享引用数量："<<hero.use_count()<<std::endl;
    }//anotherRef被销毁，引用数量减少
    std::cout<<"共享结束引用数量："<<hero.use_count()<<std::endl;

    std::cout<<"程序即将结束..."<<std::endl;

}