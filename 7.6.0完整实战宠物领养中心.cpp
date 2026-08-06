// ### 占位空文件：学到对应小节时，把代码敲进来 ###
// 7.6.0 完整实战：宠物领养中心
// 📍 对应教程：第 7 章 7.6 节（类 + 交互 + 日志 + Lambda 算法）
// 提示：这是新版主题，你原来的 7.6.0 学生成绩文件保留


#include<iostream>
#include<vector>
#include<algorithm>//算法头文件
#include<string>
#include<fstream>//文件流头文件
#include<chrono>//时间头文件(C++11新增)
#include<ctime>//时间头文件(C时间库)

//时间工具函数
std::string currentTime(){//获取当前时间字符串
    auto now=std::chrono::system_clock::now();
    std::time_t time=std::chrono::system_clock::to_time_t(now);
    //将C++11时间点转换为C时间戳

    char buf[32];
    //格式输出：%年-%月-%日 %时:%分:%秒
    std::strftime(buf,sizeof(buf),"%Y-%m-%d %H:%M:%S",std::localtime(&time));
    return std::string(buf);
}

//日志类
class Logger{
private:
    std::ofstream file_;// RAII：构造打开、析构关闭
    void write(const std::string& tag,const std::string& msg){
        if(file_.is_open()){
            file_<<"["<<currentTime()<<"] "<<"["<<tag<<"] "<<msg<<std::endl;
        }
    }
    


public:
    explicit Logger(const std::string& filename):
        file_(filename,std::ios::app){}
    Logger(const Logger&)=delete;
    //禁止复制对象，防止多个日志文件打开
    Logger& operator=(const Logger&)=delete;//operator(运算符) 连等赋值会用到
    //这里相当于禁止连等赋值，禁止复制构造

    void info(const std::string& msg){write("INFO",msg);}
    void warn(const std::string& msg){write("WARN",msg);}
    void error(const std::string& msg){write("ERROR",msg);}


};

//宠物自定义结构体数据
struct Pet{//struct 结构体定义  Pet(宠物)
    std::string name;
    std::string type;
    int age;
    std::string owner;//狗修金（宠物的主人）
    bool adopted;//adopted（收养过去式）是否已被领养
};

//管理类：领养中心adoptedCenter
class PetManager{
private:
    //声明成员变量
    std::vector<Pet> pets_;//宠物列表
    Logger logger_{"7.6.0.pet_center.log"};//初始化日志记录器

    //阻塞函数：等待用户输入
    void waitForUserInput(){
        std::cout<<"===按下回车或输入任意字符继续...:"<<std::flush;
        std::string input;
        std::getline(std::cin,input);
    }

    

    //登记宠物
    void addPet(){
        std::vector<std::string> prompt={
            "请输入宠物姓名(exit退出)：",
            "请输入宠物类型(exit退出)：",
            "请输入宠物年龄(exit退出)：",
            "请输入宠物主人姓名(exit退出)：",
            "是否已被领养？(y/n)(exit退出)："
        };
        std::vector<std::string> results={"","","","",""};
        Pet newPet;
        for(int i=0;i<prompt.size();i++){
            while(true){
                std::cout<<prompt[i]<<std::flush;
                std::string input;
                std::getline(std::cin,input);
                
                //基础校验，不能为空
                if(input.empty()){
                    std::cout<<"请重新输入,不能为空"<<std::endl;
                    continue;
                }

                //输入特殊字符，退出当前循环
                if(input == "exit"){
                    std::cout<<"返回主菜单"<<std::endl;
                    return;
                }

                //特殊索引值i=2，宠物年龄是否为数字校验
                if(i == 2){
                    try{
                        int age=std::stoi(input);
                        if(age<0||age>50){
                            std::cout<<"宠物年龄必须在0-50之间"<<std::endl;
                            continue;
                        }
                    }catch(...){
                        std::cout<<"宠物年龄必须为数字"<<std::endl;
                        continue;
                    }
                }

                //i=4，是否已被领养是否为y或n
                if(i == 4){
                    if(input != "y" && input != "n"){
                        std::cout<<"是否已被领养必须为y或n"<<std::endl;
                        continue;
                    }
                }
                results[i]=input;
                
                break;
                
            }
            
        }
        newPet.name=results[0];
        newPet.type=results[1];
        newPet.age=std::stoi(results[2]);
        newPet.owner=results[3];
        newPet.adopted=results[4]=="y";
        pets_.push_back(newPet);
        std::cout<<"添加成功"<<std::endl;

        waitForUserInput();
    }

    //查看所有宠物
    void viewAllPets(){
        if(pets_.empty()){
            std::cout<<"宠物列表为空"<<std::endl;
            return;
        }
        std::cout<<"===全部宠物信息如下==="<<std::endl;
        std::cout<<"宠物姓名  宠物类型  宠物年龄  宠物主人姓名  是否已被领养"<<std::endl;
        for(auto p:pets_){
            std::cout<<p.name<<"\t";
            std::cout<<p.type<<"\t\t";
            std::cout<<p.age<<"\t";
            std::cout<<p.owner<<"\t  ";
            std::cout<<(p.adopted?"是":"否")<<std::endl;

        }

        waitForUserInput();
    }

    //按品种查看宠物
    void viewPetsByTupe(){
        std::string breed;//breed(品种种类)
        while(true){
            std::cout<<"请输入要查看的宠物品种种类："<<std::flush;
            std::getline(std::cin,breed); //getline的参数(输入流,变量)
            if(breed.empty()){
                continue;
            }

            auto count=std::count_if(pets_.begin(),pets_.end(),[&](const Pet& p){
                return p.type == breed;
            });
            if(count == 0){
                std::cout<<"没有该品种的宠物"<<std::endl;
                continue;
            }

            std::cout<<"===该品种的宠物信息如下==="<<std::endl;
            std::cout<<"宠物姓名  宠物类型  宠物年龄  宠物主人姓名  是否已被领养"<<std::endl;
            for(auto p:pets_){
                if(p.type == breed){
                    std::cout<<p.name<<"\t"<<p.type<<"\t"<<p.age<<"\t"<<p.owner<<"\t"<<(p.adopted?"是":"否")<<std::endl;
                }
            }

            std::cout<<"继续搜索？（y）或输入任意键返回："<<std::flush;
            std::string input;
            std::getline(std::cin,input);
            if(input != "y"){
                break;
            }
        }
    }

    //办理领养（find_if找到->改变状态）
    void adoptPet(){//adopt(领养)
        std::string name;//name(宠物姓名)
        std::cout<<"请输入要领养的宠物姓名：";
        std::getline(std::cin,name);
        if(name.empty()){
            std::cout<<"请输入重新输入,不能为空"<<std::endl;
            return;
        }

        auto pet=std::find_if(pets_.begin(),pets_.end(),[&](const Pet& p){
            return p.name == name&&!p.adopted;
        });

        if(pet!=pets_.end()){
            pet->adopted=true;
            logger_.info("adopted pet: "+pet->name);
            std::cout<<"领养成功!"<<pet->name<<"找到新家了。"<<std::endl;
        }else{
            logger_.warn("adopt失败,nofind pet: "+name);
            std::cout<<"没有该宠物或已被领养"<<std::endl;
        }

        waitForUserInput();

    }

    //删除（erase-remove，find_if+erase）
    void deletePet(){
        std::string name;//name(宠物姓名)
        while(true){
            std::cout<<"请输入要删除的宠物姓名："<<std::flush;
            std::getline(std::cin,name);
            if(name.empty()){
                std::cout<<"====请输入重新输入,检索名不能为空！===="<<std::endl;
                continue;
            }
            auto pet=std::find_if(pets_.begin(),pets_.end(),[&](const Pet& p){
                return p.name == name;
            });

            if (pet!= pets_.end()){
                logger_.info("delete pet: "+pet->name);
                pets_.erase(pet);//find_if找到->erase删除
                std::cout<<"宠物“"<<name<<"”删除成功！"<<std::endl;
            }else{
                logger_.warn("delete失败,nofind pet: "+name);
                std::cout<<"没有找到名为“"<<name<<"”的宠物"<<std::endl;
            }
            std::cout<<"继续删除？（y）或输入任意键返回："<<std::flush;
            std::string input;
            std::getline(std::cin,input);
            if(input != "y"){
                break;
            }
            
        }
    }

    //按年龄排序
    void sortPetsByAge(){
        std::sort(pets_.begin(),pets_.end(),[](const Pet& a,const Pet& b){
            return a.age>b.age;//大的在前
        });

        logger_.info("sort pets by age");

        std::cout<<"已经按照年龄排序"<<std::endl;

        std::cout<<"展示？（y）或输入其他返回主菜单："<<std::flush;
        std::string index;
        std::getline(std::cin,index);
        if(index == "y"){
            viewAllPets();
        }else{
            return;
        }
        
    }

    //统计
    void statistics(){//staristics(统计学/统计)
        auto waitingCount=std::count_if(pets_.begin(),pets_.end(),[](const Pet& p){
            return !p.adopted;
        });
        std::cout<<"等待领养的宠物数量为："<<waitingCount<<std::endl;
                            //element(元素)
        auto maxIt=std::max_element(pets_.begin(),pets_.end(),[](const Pet& a,const Pet& b){
            return a.age<b.age;//大的在前
        });
        if(maxIt!=pets_.end()){
            std::cout<<"年龄最大的宠物为："<<maxIt->name<<std::endl;
        }else{
            std::cout<<"没有宠物"<<std::endl;
        }
        
        waitForUserInput();

    }




public:
    //控制台登记宠物
    void addPetInConsole(const std::string& name,const std::string& type,int age,const std::string& owner,bool adopted){
        pets_.push_back({name,type,age,owner,adopted});
    }
    void run(){
        while(true){
            std::cout << "\n=== 🐾 宠物领养中心 ===" << std::endl;
            std::cout << "1. 登记宠物" << std::endl;
            std::cout << "2. 查看所有宠物" << std::endl;
            std::cout << "3. 按品种筛选" << std::endl;
            std::cout << "4. 办理领养" << std::endl;
            std::cout << "5. 删除宠物" << std::endl;
            std::cout << "6. 按年龄排序" << std::endl;
            std::cout << "7. 统计" << std::endl;
            std::cout << "0. 退出" << std::endl;
            std::cout << "请选择：";

            std::string choice;
            std::getline(std::cin,choice);
            if(choice.empty()){
                continue;
            }else if(choice == "0"){
                break;
            }else if(choice == "1"){
                addPet();
            }else if(choice == "2"){
                viewAllPets();
            }else if(choice == "3"){
                viewPetsByTupe();
            }else if(choice == "4"){
                adoptPet();
            }else if(choice == "5"){
                deletePet();
            }else if(choice == "6"){
                sortPetsByAge();
            }else if(choice == "7"){
                statistics();
            }else{
                std::cout<<"请输入重新输入"<<std::endl;
            }

        }
    }

};

int main(){

    PetManager manager;//Manager(管理者)
    manager.addPetInConsole("小白","杂种狗",8,"无",false);
    manager.addPetInConsole("小黑","泰迪",7,"无",false);
    manager.addPetInConsole("小绿","田园兔",5,"无",false);
    manager.addPetInConsole("小蓝","Tom",10,"无",false);
    manager.addPetInConsole("闪电","哈士奇",3,"无",false);
    manager.addPetInConsole("花","田园猫",5,"无",false);
    manager.addPetInConsole("小黄","田园猫",6,"无",false);
    manager.addPetInConsole("小紫","田园猫",4,"无",false);
    manager.addPetInConsole("小马","牛马",21,"老板",true);

    manager.run();

}

