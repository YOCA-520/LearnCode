// split the menu into multipe tables
// split[分割]//menu[菜单]//multipe tables[多个表格]
// 菜单分发表

#include <iostream>
#include <unordered_map> //unordered_map[无序映射]用于存储键值对的容器
#include <functional>    //functional[函数]用于存储函数对象的容器

// three functions:addPet,showAll,Adopt
void addPet()
{
    std::cout << "Add a pet:" << std::endl;
}
void showAll()
{
    std::cout << "Show all pets:" << std::endl;
}
void adopt()
{
    std::cout << "Adopt a pet:" << std::endl;
}

int main()
{
    // split table
    std::unordered_map<int, std::function<void()>> actions = {
        {1, addPet},
        {2, showAll},
        {3, adopt}};

    while (true)
    {
        std::cout << "=====Pet adoption center system======" << std::endl;
        std::cout << "1.Add a pet" << std::endl;
        std::cout << "2.Show all pets" << std::endl;
        std::cout << "3.Adopt a pet" << std::endl;
        std::cout << "4.Exit" << std::endl;
        std::cout << "Please enter your choice:";
        int choice;
        std::cin >> choice;
        if (choice == 4)
        {
            std::cout << "Thank you for using the system." << std::endl;
            break;
        }

        auto it = actions.find(choice);
        if (it != actions.end())
        {
            //this second is the actions[second] index table.
            it->second();//执行对应函数//second[第二个]//函数对象
        }
        else
        {
            // invalid choice[无效选择]
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}
