#include<iostream>
#include<vector>

int main(){
    //创建一个存放整数的动态数组
    std::vector<int> scores;

    //用push_back()在末尾添加元素（往后添加）
    scores.push_back(666);
    scores.push_back(520);
    scores.push_back(1314);

    //获取数组大小
    std::cout<<"动态数组的大小为："<<scores.size()<<std::endl;

    //像普通数组一样访问[]
    std::cout<<"第一个元素是："<<scores[0]<<std::endl;
    std::cout<<"最后一个元素是："<<scores[scores.size()-1]<<std::endl;
    std::cout<<"最后一个元素是："<<scores.back()<<std::endl;
    //back()返回最后一个元素(引用不是值)
    //std::cout<<"最后一个元素是："<<scores[scores.length()-1]<<std::endl;
    //length()是字符串的函数，不能用于动态数组()相当于是获取长度而不是个数。

}