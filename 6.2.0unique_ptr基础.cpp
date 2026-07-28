#include <iostream>
#include <string>
#include <memory>//智能指针头文件

class Robot{
    public:
        explicit Robot(const std::string& name):name_(name){
            std::cout<<"构造函数："<<name_<<"出生了！"<<std::endl;
        }
        ~Robot(){
            std::cout<<"析构函数："<<name_<<"死啦了~都你害的！"<<std::endl;
        }

        void speak(const std::string& message="") const{
            if(message.empty()){
                std::cout<<"speak函数："<<name_<<"在说话。"<<std::endl;
            }else{
                std::cout<<"speak函数："<<name_<<"在说：“"<<message<<"”"<<std::endl;
            }
        }

    private:
        std::string name_;

};

int main() {
    // ✅ 现代写法：用 std::make_unique 创建智能指针
    // 尽量用 make_unique 而不是 new（更安全，不会忘 delete）
    auto robot =std::make_unique<Robot>("小爱同学");
    Robot robot2("LeiJun");

    // 调用成员函数（和普通指针一样的语法）
    robot->speak("Fuke LeiJun!");
    robot2.speak("Fuck 小爱同学！");

    // 不需要手动 delete！
    // 当 robot 离开作用域时，自动释放内存

    std::cout << "程序即将结束，机器人会自动关闭..." << std::endl;
    return 0;
}  // <- 这里自动调用 ~Robot()