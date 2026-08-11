// Multi-file pet adoption practice project//multi[多种]//practice[练习]
// pet_manager.cpp
// pet_manager implementation//宠物管理器实现
#include "pet_manager.h"
#include <iostream>
#include <algorithm> //algorithm[算法]//算法库
#include <vector>    //vector[向量]//向量库

void PetManager::run()
{
    logger_.info("PetManager run");
    int index = 0; // whether first input.
    while (true)
    {
        std::string input;
        int choice;
        std::cout << "\n=== Pet Adoption System ===\n";
        std::cout << "1. Add Pet\n";
        std::cout << "2. Show All Pets\n";
        std::cout << "3. filter by Breed\n";
        std::cout << "4. Adopt Pet\n";
        std::cout << "5. Remove Pet\n";
        std::cout << "6. Sort Pets\n";
        std::cout << "7. Statistics max age\n";
        std::cout << "8. Find Pet\n";
        std::cout << "0. Exit" << std::endl;
        if (index == 0)
        {
            std::cout << "Enter your choice: " << std::flush;
        }
        else
        {
            std::cout << "again input: " << std::flush;
        }
        std::cin >> input;
        if (input.empty())
        {
            index++;
            continue;
        }
        try
        {
            choice = std::stoi(input);
            if (choice < 0 || choice > 8)
            {
                logger_.error("Invalid choice. Please input a number between 0 and 8.");
                index++;
                continue;
            }
        }
        catch (const std::exception &e)
        {
            logger_.error(e.what());
            index++;
            continue;
        }

        switch (choice)
        {
        case 0:
            std::cout << "thank your using! bye~" << std::endl;
            exit(0);
        case 1:
            addPet();
            index = 0;
            break;
        case 2:
            showAll();
            index = 0;
            break;
        case 3:
            filterByBreed();
            index = 0;
            break;
        case 4:
            adoptPet();
            index = 0;
            break;
        case 5:
            removePet();
            index = 0;
            break;
        case 6:
            sortPets();
            index = 0;
            break;
        case 7:
            statistics();
            index = 0;
            break;
        case 8:
            findPet();
            index = 0;
            break;
        default:
            logger_.error("Invalid choice. Please input a number between 0 and 8.");
            index++;
            break;
        }
    }
}

void PetManager::addPet()
{
    logger_.info("Run addPet");
    Pet p;
    std::string input;
    std::string name;
    std::string breed;
    int age;
    while (true)
    {
        int index = 0;
        if (index == 0)
        {
            std::cout << "Enter pet name: ";
        }
        else
        {
            std::cout << "Again input pet name: ";
        }
        std::cin >> input;
        if (input.empty())
        {
            logger_.error("Input name is empty.");
            index++;
            continue;
        }
        name = input;
        break;
    }
    while (true)
    {
        int index = 0;
        if (index == 0)
        {
            std::cout << "Enter pet age: ";
        }
        else
        {
            std::cout << "Again input pet age: ";
        }
        std::cin >> input;
        if (input.empty())
        {
            logger_.error("Input age is empty.");
            index++;
            continue;
        }
        try
        {
            age = std::stoi(input);
        }
        catch (const std::exception &e)
        {
            logger_.error(e.what());
            index++;
            continue;
        }
        break;
    }
    while (true)
    {
        int index = 0;
        if (index == 0)
        {
            std::cout << "Enter pet breed: ";
        }
        else
        {
            std::cout << "Again input pet breed: ";
        }
        std::cin >> input;
        if (input.empty())
        {
            logger_.error("Input breed is empty.");
            index++;
            continue;
        }
        breed = input;
        break;
    }
    p.name = name;
    p.age = age;
    p.breed = breed;
    p.isAdopted = false;
    pets_.push_back(p);
    logger_.info("Add pet " + name + " success.");
}

void PetManager::showAll()
{
    logger_.info("Run showAll");
    if (pets_.empty())
    {
        logger_.info("No pets in the system.");
        std::cout << "No pets in the system." << std::endl;
        return;
    }
    std::cout << "All pets in the system:" << std::endl;
    for (const auto &p : pets_)
    {
        logger_.info("Pet " + p.name + " with breed " + p.breed + " is adopted.");
        std::cout << "Name: " << p.name << ", Age: " << p.age << ", Breed: " << p.breed << ", Is Adopted: " << (p.isAdopted ? "Yes" : "No") << std::endl;
    }
}

void PetManager::filterByBreed() // filter[筛选]//根据品种筛选
{
    logger_.info("Run filterByBreed");
    std::string input;
    std::string breed;
    while (true)
    {
        int index = 0;
        if (index == 0)
        {
            std::cout << "Enter filter breed: ";
        }
        else
        {
            std::cout << "Again input filter breed: ";
        }
        std::cin >> input;
        if (input.empty())
        {
            logger_.error("Input breed is empty.");
            index++;
            continue;
        }
        breed = input;
        logger_.info("Filter by breed " + breed);
        break;
    }
    // count_if(开始迭代器, 结束迭代器, 匿配函数)
    auto count = std::count_if(pets_.begin(), pets_.end(), [breed](const Pet &p)
                               { return p.breed == breed; });
    if (count == 0)
    {
        logger_.info("No pet with breed " + breed + " in the system.");
        std::cout << "No pet with breed " + breed + " in the system." << std::endl;
        return;
    }
    for (const auto &p : pets_)
    {
        if (p.breed == breed)
        {
            logger_.info("Pet " + p.name + " with breed " + p.breed + " is adopted.");
            std::cout << "Name: " << p.name << ", Age: " << p.age << ", Breed: " << p.breed << ", Is Adopted: " << (p.isAdopted ? "Yes" : "No") << std::endl;
        }
    }
}

void PetManager::adoptPet()
{
    logger_.info("Run adoptPet");
    std::vector<int> bufPetIndexList;
    int choice;
    std::string input;
    std::string name;
    while (true)
    {
        int index = 0;
        if (index == 0)
        {
            std::cout << "Enter pet name to adopt: ";
        }
        else
        {
            std::cout << "Again input pet name to adopt: ";
        }
        std::cin >> input;
        if (input.empty())
        {
            logger_.error("Input name is empty.");
            index++;
            continue;
        }
        name = input;

        auto count = std::count_if(pets_.begin(), pets_.end(), [name](const Pet &p)
                                   { return p.name == name; });
        if (count == 0)
        {
            logger_.info("No pet with name " + name + " in the system.");
            std::cout << "No pet with name " + name + " in the system." << std::endl;
            continue;
        }
        std::cout << "find pet " << name << std::endl;
        for (int i = 0; i < (int)pets_.size(); i++)
        {
            if (input == pets_[i].name)
            {
                std::cout << pets_[i].name << " ";
                bufPetIndexList.push_back(i);
            }
        }
        std::cout << std::endl;
        while (count > 1)
        {
            int index = 0;
            if (index == 0)
            {
                std::cout << "Which pet do you want to adopt? (1-" << count << "):";
            }
            else
            {
                std::cout << "Again input choice to adopt(1-" << count << "): ";
            }
            std::cin >> choice;
            if (choice < 1 || choice > count)
            {
                logger_.error("Input choice is invalid.");
                index++;
                continue;
            }
            pets_[bufPetIndexList[choice - 1]].isAdopted = true;
            logger_.info("Pet " + pets_[bufPetIndexList[choice - 1]].name + " with breed " + pets_[bufPetIndexList[choice - 1]].breed + " is adopted.");
            std::cout << "Pet " + pets_[bufPetIndexList[choice - 1]].name + " with breed " + pets_[bufPetIndexList[choice - 1]].breed + " is adopted." << std::endl;
            break;
        }
        if (count == 1)
        {
            pets_[bufPetIndexList[0]].isAdopted = true;
            logger_.info("Pet " + pets_[bufPetIndexList[0]].name + " with breed " + pets_[bufPetIndexList[0]].breed + " is adopted.");
            std::cout << "Pet " + pets_[bufPetIndexList[0]].name + " with breed " + pets_[bufPetIndexList[0]].breed + " is adopted." << std::endl;
        }
        break;
    }
}

void PetManager::removePet()
{
    logger_.info("Run removePet");
    std::vector<int> bufPetIndexList;
    std::string input;
    std::string mame;
    int choice;
    while (true)
    {
        int index = 0;
        if (index == 0)
        {
            std::cout << "Enter pet name to remove: ";
        }
        else
        {
            std::cout << "Again input pet name to remove: ";
        }
        std::cin >> input;
        if (input.empty())
        {
            logger_.error("Input name is empty.");
            index++;
            continue;
        }
        mame = input;
        auto count = std::count_if(pets_.begin(), pets_.end(), [mame](const Pet &p)
                                   { return p.name == mame; });

        std::cout << "find pet multiple :" << count << std::endl;
        for (int i = 0; i < (int)pets_.size(); i++)
        {
            if (input == pets_[i].name)
            {
                std::cout << pets_[i].name << " ";
                bufPetIndexList.push_back(i);
                logger_.info("add pet:" + pets_[i].name + " to buffer remove list.");
            }
        }
        std::cout << std::endl;
        while (count > 1)
        {
            int index = 0;
            if (index == 0)
            {
                std::cout << "Which pet do you want to remove? (1-" << count << "):";
            }
            else
            {
                std::cout << "Again input choice to remove(1-" << count << "): ";
            }
            std::cin >> input;
            if (input.empty())
            {
                logger_.error("Input choice is empty.");
                index++;
                continue;
            }
            try
            {
                choice = std::stoi(input);
            }
            catch (const std::exception &e)
            {
                logger_.error(e.what());
                std::cout << "Input choice is invalid." << std::endl;
                index++;
                continue;
            }
            if (choice < 1 || choice > count)
            {
                logger_.error("Input choice is invalid.");
                index++;
                continue;
            }
            pets_.erase(pets_.begin() + bufPetIndexList[choice - 1]);
            break;
        }
        if (count == 1)
        {
            pets_.erase(pets_.begin() + bufPetIndexList[0]);
        }
        break;
    }
}

void PetManager::sortPets()
{
    logger_.info("Run sortPets");
    std::sort(pets_.begin(), pets_.end(), [](const Pet &a, const Pet &b)
              { return a.age > b.age; });
    logger_.info("Pets sorted by age.");
    std::cout << "Pets sorted by age." << std::endl;
    showAll();
}

void PetManager::statistics()
{
    logger_.info("Run statistics");
    if (pets_.empty())
    {
        logger_.error("No pets in the system.");
        std::cout << "No pets in the system." << std::endl;
        return;
    }
    std::cout << "Total pets: " << (int)pets_.size() << std::endl;
    std::cout << "Total adopted pets: " << std::count_if(pets_.begin(), pets_.end(), [](const Pet &p)
                                                         { return p.isAdopted; })
              << std::endl;
    std::cout << "Total unadopted pets: " << (int)pets_.size() - std::count_if(pets_.begin(), pets_.end(), [](const Pet &p)
                                                                               { return p.isAdopted; })
              << std::endl;
    std::cout << "unadopted and max age: " << std::max_element(pets_.begin(), pets_.end(), [](const Pet &a, const Pet &b)
                                                               { return a.age > b.age; })
                                                  ->age
              << std::endl;
}

void PetManager::findPet()
{
    logger_.info("Run findPet");
    std::string input;
    std::string mame;
    while (true)
    {
        int index = 0;
        if (index == 0)
        {
            std::cout << "Enter pet name to find: ";
        }
        else
        {
            std::cout << "Again input pet name to find: ";
        }
        std::cin >> input;
        if (input.empty())
        {
            logger_.error("Input name is empty.");
            index++;
            continue;
        }
        mame = input;
        auto count = std::count_if(pets_.begin(), pets_.end(), [mame](const Pet &p)
                                   { return p.name == mame; });
        while (true)
        {
            std::cout << "find pet number:" << count << std::endl;
            for (int i = 0; i < (int)pets_.size(); i++)
            {
                if (input == pets_[i].name)
                {
                    std::cout << pets_[i].name << " ";
                }
            }
            break;
        }
        break;
    }
}
