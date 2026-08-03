#include<iostream>
#include<vector>
#include<algorithm>
#include<string>


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
        int index;
        std::string name;
        while(true){
            std::cout<<"===学生管理系统==="<<std::endl;
            std::cout<<"请输入您的选择："<<std::endl;
            std::cout<<"1.添加学生"<<std::endl;
            std::cout<<"2.打印所有学生信息"<<std::endl;
            std::cout<<"3.删除学生"<<std::endl;
            std::cout<<"4.搜索学生"<<std::endl;
            std::cout<<"5.退出"<<std::endl;
            std::cin>>index;
            if(index == 1){
                inputMessage();
            }else if(index == 2){
                printMessage();
            }else if(index == 3){
                std::cout<<"请输入要删除的学生姓名：";
                std::cin>>name;
                deleteStudent(name);
            }else if(index == 4){
                IndexStudent();
            }else if(index == 5){
                break;
            }else{
                std::cout<<"输入错误"<<std::endl;
            }
        }

    }

    void addStudent(Student& newStudent){
        students.push_back(newStudent);
    }
    
    void inputMessage(){

        std::string name="";
        int score=0;
        std::string sex="";
        std::string address="";//address(住址)
        std::string phone="";
        while(true){
            std::cout<<"请输入学生姓名：";
            std::cin>>name;
            std::cout<<"请输入学生成绩：";
            std::cin>>score;
            std::cout<<"请输入学生性别：";
            std::cin>>sex;
            std::cout<<"请输入学生住址：";
            std::cin>>address;
            std::cout<<"请输入学生手机号：";
            std::cin>>phone;
            if(name.empty() || score == 0 || sex.empty() || address.empty() || phone.empty()){
                std::cout<<"请重新输入完整信息！！"<<std::endl;
                continue;
            }else{
                Student newStudent = {name,score,sex,address,phone};
                addStudent(newStudent);
                std::cout<<"添加成功"<<std::endl;
                break;
            }
        }
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
        std::cout<<"回到主菜单？(y/n)";
        std::cin>>index;
        if(index == "y"){
            return;
        }else{
            exit(0);
        }
    }

    void deleteStudent(std::string& name){
        auto it = std::find_if(students.begin(), students.end(), [&](const Student& student){
            return student.name == name;//这里的return只结束当前lambda表达式，不会结束find_if函数
        });
        if(it != students.end()){
            students.erase(it);
            std::cout<<"学生"<<name<<"删除成功"<<std::endl;
        }else{
            std::cout<<"未找到学生"<<name<<std::endl;
        }
    }

    void IndexStudent(){
        std::string index="";
        while(true){
            std::vector<std::string> nameList;
            std::cout<<"输入以检索名称：";
            std::cin>>index;   
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
                    std::cin>>choice;
                    if(choice == "n"){
                        break;
                    }
                }else{
                    std::cout<<"未找到学生"<<std::endl;
                    std::cout<<"是否继续搜索？(y/n)";
                    std::string choice;
                    std::cin>>choice;
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