#include <iostream>
#include <vector>
#include <algorithm> //算法头文件，sort函数头文件，用于排序。
#include <string>

int main(){
    std::vector<std::string> fruits ={"苹果","香蕉","橙子","葡萄","桃子","西瓜","哈密瓜"};
    std::cout<<"原始水果列表：";
    for(const auto& f:fruits)std::cout<<f<<" ";
    std::cout<<std::endl;

    //按名称长度排序（长的在前）
    std::sort(fruits.begin(),fruits.end(),[](const std::string& a,const std::string& b){
        return a.size()>b.size();
    });

    std::cout<<"按名称长度排序（长的在前）：";
    for(const auto& f:fruits)std::cout<<f<<" ";
    std::cout<<std::endl;
    
}