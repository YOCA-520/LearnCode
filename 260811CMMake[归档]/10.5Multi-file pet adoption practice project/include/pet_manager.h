//Multi-file pet adoption practice project//multi[多种]//practice[练习]
//pet_manager.h
//interface declaration//interface[接口]//接口声明
#pragma once //pragma[编译] //编译一次，这里是为了防止重复包含
#include <string>
#include <vector>
#include "pet.h"//use Pet struct from 10.5.0pet.h
#include "logger.h"//use Logger class from 10.5.0logger.h

class PetManager{//manager[管理器]//宠物管理器类
public:
    void run();//only one this public interface//interface[接口]//接口

private:
    void addPet();
    void showAll();
    void filterByBreed();//filter[筛选]//根据品种筛选
    void adoptPet();
    void removePet();
    void sortPets();//sort[排序]//根据年龄排序宠物
    void statistics();//statistics[统计]//显示宠物统计信息
    void findPet();
    void showPet();

    std::vector<Pet> pets_;//pets[宠物]//declaration 宠物列表
    Logger logger_{"logs/pet_manager.log"};

};
