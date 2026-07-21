#include <iostream>
#include <vector>
#include <string>

int main(){
    //储存学生信息
    std::vector<std::string> students
        ={"张三","李四","王五","赵六"};
    std::vector<float> scores
        = {90.5,85.0,92.3,88.5};

    //用auto和范围for遍历输出
    std::cout<<"===成绩单==="<<std::endl;
    for(size_t i=0;i<students.size();i++){
        std::cout<<students[i]<<"的成绩是："
        <<scores[i]<<"分"<<std::endl;
    }

    //计算平均分
    auto total = 0.0f;
    for(const auto& score:scores){
        total += score;
    }
    //auto average=total/scores.size();
    //这种写法不会报错但容易出错
    //如果 total 是 int 类型，除法结果会自动转换为 int 类型，导致平均分小数部分丢失
    auto average = static_cast<double>(total) / scores.size();
    //static_cast<double>(total) 将 total 转换为 double 类型，确保除法结果为浮点数
    //static_cast<目标类型>(变量)安全强制类型转换语法
    std::cout<<"平均分为："<<average<<std::endl;


    //找出最高分
    auto maxScore = scores[0];
    for(const auto& score:scores){
        if(score>maxScore){
            maxScore=score;
        }
    }
    std::cout<<"最高分是："<<maxScore<<std::endl;
    



}