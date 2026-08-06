#include <iostream>
#include <vector>
#include <string>
#include <optional>

struct Student{//struct(结构体)
    std::string name;
    int id;
    int score;

};

//按id查找学生，用optional表示可能找不到。
std::optional<Student> findStudentById(const std::vector<Student>& students,int targetId/*目标的ID*/){
    for(const auto& student:students){
        if(student.id==targetId){
            return student;//找到目标学生，返回其信息(只寻找唯一一个)
        }
    }
    return std::nullopt;//未找到目标学生，返回空optional
}

//获取学生成绩，用optional表示可能找不到
std::optional<int> getStudentScore(const std::vector<Student>& students,int targetId){
    auto student=findStudentById(students,targetId);
    if(student){
        return student->score;//返回目标学生的成绩
    }
    return std::nullopt;//未找到目标学生，返回空optional
}

int main(){
    std::vector<Student> classl={
        {"张三",1001,90},
        {"李四",1002,85},
        {"王五",1003,92},
        {"赵六",1004,88}
    };


    //查找存在的学生
    auto result=getStudentScore(classl,1001);

    //value_or()方法：如果optional对象有值，返回该值；如果optional对象没有值，返回默认值。
    //value_or()方法返回该值，而不是一个引用。会复制默认值。
    std::cout<<"找到的学生1001的成绩："<<result.value_or(-1)<<std::endl;

    //查找不存在的学生
    auto result2=getStudentScore(classl,1005);
    std::cout<<"未找到的学生1005的成绩："<<result2.value_or(-1)
        <<"-1表示不存在"<<std::endl;
    
    //安全的使用optional
    if(auto score=getStudentScore(classl,1001)){
        std::cout<<"找到的学生1001的成绩："<<*score<<std::endl;
    }
}