#include<iostream>
#include<vector>
#include<string>

int main(){
    //用vactor数组存储学生姓名（字符串）
    std::vector<std::string> names;//定义（创建）

    names.push_back("小明");//添加元素
    names.push_back("小红");
    names.push_back("小刚");

    //用vector存储对应成绩
    std::vector<float> scores;
    scores.push_back(99.5);
    scores.push_back(88.5);
    scores.push_back(77.5);

    //输出所有学生姓名和成绩
    std::cout<<"学生姓名和成绩如下："<<std::endl;
    for(size_t nameIndex=0;nameIndex<names.size();nameIndex++){
        std::cout<<names[nameIndex]<<"的成绩是："<<scores[nameIndex]<<"。"<<std::endl;
    }
   






}