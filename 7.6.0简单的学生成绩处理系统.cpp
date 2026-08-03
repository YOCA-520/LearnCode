#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<limits>//numeric_limits 求忽略的最大字符数



class StudentManager{
public:
    struct Student{
        std::string name;
        int score;
        std::string sex;
        std::string address;//address(住址)
        std::string phone;
    };

    std::vector<Student> students;

    void run(){
        

        std::string input;
        auto index=0;
        std::string name;
        while(true){
            std::cout<<"===学生管理系统==="<<std::endl;
            std::cout<<"请输入您的选择："<<std::endl;
            std::cout<<"1.添加学生"<<std::endl;
            std::cout<<"2.打印所有学生信息"<<std::endl;
            std::cout<<"3.删除学生"<<std::endl;
            std::cout<<"4.搜索学生"<<std::endl;
            std::cout<<"5.退出"<<std::endl;
            std::cout<<"请输入您的选择："<<std::flush;
            std::getline(std::cin,input);
            try{
                int num=std::stoi(input);
                index=num;
            }catch(...){
                std::cout<<"请输入数字！"<<std::endl;
                continue;
            }
            if(index == 1){
                inputMessage();
            }else if(index == 2){
                printMessage();
            }else if(index == 3){
                std::cout<<"请输入要删除的学生姓名：";
                getline(std::cin,name);
                deleteStudent(name);
            }else if(index == 4){
                IndexStudent();
            }else if(index == 5){
                break;
            }else{
                std::cout<<"没有这个选项"<<std::endl;
            }
        }

    }

    void addStudent(Student newStudent){
        //这里直接使用按值传递，避免拷贝构造和移动构造的调用
        //按值传递右值不拷贝，同时std::move()将右值转换为左值，调用移动构造,不拷贝数据
        //const &（常量引用，不能修改对象）所以不能使用移动构造，只能使用拷贝构造
        students.push_back(std::move(newStudent));
    }
    
    void inputMessage(){
        
        //定义提示语句
        std::vector<std::string> prompts={//prompts(提示的复数形式)提示语句容器名
            "请输入学生姓名(exit退出)：",
            "请输入学生成绩(exit退出)：",
            "请输入学生性别(exit退出)：",
            "请输入学生住址(exit退出)：",
            "请输入学生手机号(exit退出)："
        };
        
        std::vector<std::string> results;//按顺序存放5项输入结果
        std::string input="";//输入缓冲区
        

        //用for循环处理每一项输入
        for(size_t i=0;i<prompts.size();i++){                
            while(true){
                std::cout<<prompts[i];
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

                //特殊索引值i=1，学生成绩是否为数字校验
                if(i == 1){
                    try{
                        int sco=std::stoi(input);
                        if(sco<0||sco>100){
                            std::cout<<"学生成绩必须在0-100之间"<<std::endl;
                            continue;
                        }
                    }catch(...){
                        std::cout<<"学生成绩必须为数字"<<std::endl;
                        continue;
                    }
                }
                //i=2，学生性别是否为男或女校验
                if(i == 2){
                    if(input != "男" && input != "女"){
                        std::cout<<"学生性别必须为男或女"<<std::endl;
                        continue;
                    }
                }
                //i=4，学生手机号是否为11位数字且开头是1校验
                if(i == 4){
                    if(input.size() != 11 || input[0] != '1'){
                        std::cout<<"学生手机号必须为11位数字且开头是1"<<std::endl;
                        continue;
                    }
                }
                results.push_back(input);
                break;
            }
            
        }

        //提取结果（成绩转换为int）并且封装为Student对象
        std::string name=results[0];
        int score=std::stoi(results[1]);
        std::string sex=results[2];
        std::string address=results[3];
        std::string phone=results[4];

        //调用addStudent()函数添加学生
        Student newStudent={name,score,sex,address,phone};
        addStudent(newStudent);
        std::cout<<"添加成功"<<std::endl;

        // std::string name="",//score="",//address(住址)
        // std::string phone=""

        // while(true){
        //     std::cout<<"请输入学生姓名：";
        //     std::cin>>name;
        //     std::cout<<"请输入学生成绩：";
        //     std::cin>>score;
        //     std::cout<<"请输入学生性别：";
        //     std::cin>>sex;
        //     std::cout<<"请输入学生住址：";
        //     std::cin>>address;
        //     std::cout<<"请输入学生手机号：";
        //     std::cin>>phone;
        //     if(name.empty() || score == 0 || sex.empty() || address.empty() || phone.empty()){
        //         std::cout<<"请重新输入完整信息！！"<<std::endl;
        //         continue;
        //     }else{
        //         Student newStudent = {name,score,sex,address,phone};
        //         addStudent(newStudent);
        //         std::cout<<"添加成功"<<std::endl;
        //         break;
        //     }
        // }
    }

    void printMessage(){

        std::cout<<"===全部学生信息如下==="<<std::endl;
        std::cout<<"学生姓名\t学生成绩\t学生性别\t学生住址\t学生手机号"<<std::endl;
        for(Student student:students){
            std::cout<<student.name<<"\t";
            std::cout<<student.score<<"\t";
            std::cout<<student.sex<<"\t";
            std::cout<<student.address<<"\t";
            std::cout<<student.phone<<std::endl;
        }
        std::string index="";
        while(index != "y"){
            std::cout<<"回到主菜单？(y/n)";
            std::getline(std::cin,index);
            if(index == "y"){
                return;
            }else{
                std::cout<<"不回主菜单也没有别的内容了TT......"<<std::endl;
            }
        }
        
    }

    void deleteStudent(const std::string& name){
        
        auto it = std::find_if(students.begin(), students.end(), [&](const Student& student){
            return student.name == name;//这里的return只结束当前lambda表达式，不会结束find_if函数
        });
        if(it != students.end()){
            students.erase(it);
            std::cout<<"学生"<<name<<"删除成功"<<std::endl;
        }else{
            std::cout<<"未找到学生"<<name<<std::endl;
        }
        
        std::cout<<"回车返回主菜单:"<<std::flush;
        std::cin.get();//真正阻塞等待按键
    
    }

    void IndexStudent(){
          

        std::string index="";
        while(true){
            std::vector<std::string> nameList;
            std::cout<<"输入以检索名称：";
            std::getline(std::cin,index);
            for(const auto& student:students){
                nameList.push_back(student.name);}
            
            auto count = std::count_if(nameList.begin(), nameList.end(),
                [&](const std::string& name){
                    return name.starts_with(index);
                });
            
                if(count > 0){
                    std::cout<<"找到"<<count<<"个学生"<<std::endl;
                    std::cout<<"分别是：";
                    for(const auto& name:nameList){
                        if(name.starts_with(index))std::cout<<name<<"\t";
                    }
                    std::cout<<std::endl;
                    std::cout<<"是否继续搜索？(y/n)";
                    std::string choice;
                    std::getline(std::cin,choice);
                    if(choice == "n"){
                        break;
                    }
                }else{
                    std::cout<<"未找到学生"<<std::endl;
                    std::cout<<"是否继续搜索？(y/n)";
                    std::string choice;
                    std::getline(std::cin,choice);
                    if(choice == "n"){
                        break;
                    }
                }
            
        }
        
        
    }   

};

int main(){
    StudentManager studentManager;
    studentManager.addStudent({"张三",90,"男","北京市","13800000000"});
    studentManager.addStudent({"李四",85,"女","上海市","13900000000"});
    studentManager.addStudent({"王五",95,"男","北京市","13800000001"});
    studentManager.addStudent({"Bob",92,"男","北京市","13800000002"});
    studentManager.addStudent({"Alice",87,"女","上海市","13900000002"});
    studentManager.addStudent({"Charlie",90,"男","北京市","13800000003"});
    studentManager.addStudent({"David",85,"女","上海市","13900000003"});
    studentManager.addStudent({"Eve",95,"男","北京市","13800000004"});

    studentManager.run();
    return 0;
}