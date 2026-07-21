#include <iostream>
#include <string>

int main()
{
    std::string text = "Hello c++ World!";

    // 1. 获取字符串长度
    std::cout << "长度："<< text.length()<<std::endl;

    //2.判断是否为空字符串
    if(text.empty()){
        std::cout<<"字符串text是空的"<<std::endl;
    }else{
        std::cout<<"字符串text不是空的"<<std::endl;
    }

    //3.访问单个字符（像数组一样用[]访问字符串中的字符）
    std::cout<<"第一个字符是"<<text[0]<<std::endl;
    std::cout<<"最后一个字符是"<<text[text.size()-1]<<std::endl;
    std::cout<<"最后一个字符是"<<text[text.length()-1]<<std::endl;

    //4.查找子串，在字符串中查找段落
    std::string txt="c++";
    size_t pos =text.find(txt);
    if(pos !=std::string::npos){
        std::cout<<"在text中找到了C++,C开始的位置是:"
        <<pos<<"\n"<<"结束的位置是"<<pos+txt.length()-1<<std::endl;
    }
    
    //5.提取子串
    std::string sub =text.substr(7,3);//从位置7开始提取3个字符
    std::cout<<"提取的子串是："<<sub<<std::endl;


}