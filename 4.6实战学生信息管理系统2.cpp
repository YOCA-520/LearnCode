#include<iostream>
#include<string>
#include<vector>

//显示所有学生（const 引用：高效只读）
void displayStudents(const std::vector<std::string>& students){
    if(students.empty()){
        std::cout<<"当前没有学生信息。"<<std::endl;
        return;
    }
    std::cout<<"学生列表：";
    for(const std::string& student:students){
        std::cout<<student<<" ";
    }
    std::cout<<std::endl;
    
}

//添加学生
void addStudent(std::vector<std::string>& students,const std::string& name){
    students.push_back(name);
    std::cout<<"添加学生："<<name<<"成功。"<<std::endl;
}

//查找学生
bool findStudent(const std::vector<std::string>& students,
    const std::string& target){
        for(const auto& student:students){
            if(student==target){
                return true;
            }
        }  
        return false;
     std::cout<<"未找到学生"<<target<<"。"<<std::endl;
}


int main(){
    std::vector<std::string> students;

    //添加学生
    addStudent(students,"可口可乐");
    addStudent(students,"雪碧");
    addStudent(students,"可乐");


    displayStudents(students);//显示所有学生

    //查找学生

    auto searchName="雪碧";
    if(findStudent(students,searchName)){//返回值是一个bool值，可以用来写判断逻辑
        std::cout<<"找到学生："<<searchName<<"。"<<std::endl;
    }else{
        std::cout<<"未找到学生："<<searchName<<"。"<<std::endl;
    }

    auto searchName2="傻碧";
    if(findStudent(students,searchName2)){//返回值是一个bool值，可以用来写判断逻辑
        std::cout<<"找到学生："<<searchName2<<"。"<<std::endl;
    }else{
        std::cout<<"未找到学生："<<searchName2<<"。"<<std::endl;
    }

}
