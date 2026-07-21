#include<iostream>
#include<vector>

int main(){
    //创建时直接初始化（用花括号列出来）
    std::vector<int> numbers{11,22,33,44,55};

    //在末尾添加
    numbers.push_back(77);
    //在指定位置添加
    numbers.insert(numbers.begin() + 2, 88);
    //在下标为2的位置插入88，原来的元素往后移动


    //insert(迭代器, 个数, 值)在指定位置插


    //从末尾往前数第三个位置插入两个99
    numbers.insert(numbers.end() - 3, 2, 99);

    std::cout<<"动态数组添加后的值为：";
    for(int i=0;i<numbers.size();i++){
        std::cout<<numbers[i]<<"||";
    }
    std::cout<<std::endl;


    //获取收尾元素
    // .front() 返回第一个元素，等价于 numbers[0]
    // .back() 返回最后一个元素，等价于 numbers[numbers.size() - 1]
    // 比用 [] 更清晰、更安全（空 vector 调用 front/back 会崩溃，但空 vector 用 [0] 也一样）

    std::cout<<"第一个元素是："<<numbers.front()<<std::endl;
    std::cout<<"最后一个元素是："<<numbers.back()<<std::endl;

    // ── clear：清空所有元素 ─
    numbers.clear();
    std::cout<<"清空后数组的大小为："<<numbers.size()<<std::endl;

    std::vector<int> scores = {666, 520, 1314};


    // ── empty：判断是否为空 ──
    if(numbers.empty()){
        std::cout<<"numbers是空的"<<std::endl;
    }else{
        std::cout<<"numbers不是空的"<<std::endl;
    }

    if(scores.empty()){
        std::cout<<"scores是空的"<<std::endl;
    }else{
        std::cout<<"scores不是空的"<<std::endl;
    }


    
}