//Multi-file pet adoption practice project//multi[多种]//practice[练习]
//pet.h
//data declaration//数据声明

#pragma once //pragma[编译] //编译一次，这里是为了防止重复包含

#include <string>

struct Pet{
    std::string name;
    std::string breed;//breed[品种]
    int age;
    bool isAdopted;//adopted[领养]
};


