//这是lambda最经典的应用场景
#include <iostream>
#include <vector>
#include <algorithm>//（算法头文件）sort函数头文件，用于排序。

int main(){
    std::vector<int> scores{1231,43424,53,1231,54526,65461,141};

    std::cout<<"原始分数：";
    for(const auto& s:scores){
        std::cout<<s<<" ";
    }
    std::cout<<std::endl;

    //默认升序排序
    std::sort(scores.begin(),scores.end());
    std::cout<<"默认升序排序：";
    for(const auto& s:scores)std::cout<<s<<" ";
    std::cout<<std::endl;

    //用lambda自定义排序规则：按分数从高到低排序（降序排序）
    std::sort(scores.begin(),scores.end(),[](int a,int b){
        return a>b;//如果a>b,a排在前面，b排在后面
    });

    std::cout<<"降序（lambda自定义）：";
    for(const auto& s:scores)std::cout<<s<<" ";
    std::cout<<std::endl;

}
