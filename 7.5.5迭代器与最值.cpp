// ### 占位空文件：学到对应小节时，把代码敲进来 ###
// 7.5.5 迭代器与最值
// 📍 对应教程：第 7 章 7.5.5 节（迭代器专题 + max_element/min_element）
#include <iostream>
#include <vector>

int main(){
    std::vector<int> numbers ={11,22,33,44,77};

    //begin()指向第一个元素，end()指向最后一个元素的下一个位置
    //所以循环条件是it!=numbers.end(),而不是<=
    //<=会多循环一次
    
    //迭代器类似指针，可以指向容器中的元素
    //所以可以使用*it取出元素值
    //也可以使用++it指向下一个元素
    //也可以使用it++指向当前元素，然后指向下一个元素
    //也可以使用it--指向上一个元素，然后指向当前元素
    //也可以使用it+=n指向it后的第n个元素
    for(auto it=numbers.begin();it!=numbers.end();it++){
        std::cout<<*it<<" ";//*it从指针取出元素值
        if(it!=numbers.end()-1){
            std::cout<<",";
        }
    }
    std::cout<<std::endl;
    std::cout<<"-----------------"<<std::endl;
}