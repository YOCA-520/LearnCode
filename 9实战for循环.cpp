#include <iostream>
#include <vector>

int main(){
    //输入一个数组
    std::vector<double> numbers;
    std::cout<<"请输入一个数组(每输入一个元素后enter.输入-1结束)："
        <<std::endl;
    double num;
    while(std::cin>>num && num!=-1){
        numbers.push_back(num);
    }

    std::vector<double> bigNumbers;
    auto index=0;
    for(auto num:numbers){
        if(num>10){
            index++;
            bigNumbers.push_back(num);
        }
    } 
    std::cout<<"大于10的元素有"<<index<<"个"<<std::endl;
    std::cout<<"分别是：";
    for(auto num:bigNumbers){
        std::cout<<num<<" ";
    }
    std::cout<<std::endl;



}