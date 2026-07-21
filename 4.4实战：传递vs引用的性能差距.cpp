#include<iostream>
#include<string>
#include<vector>
#include<chrono>//用于测量时间 计时器

void processByValue(std::vector<int> data){
    auto sum=0;
    for(const auto& num:data){
        sum+=num;
    }
    std::cout<<"值传递：和="<<sum<<std::endl;
}

//引用传递（零拷贝）
void processByConstRef(const std::vector<int>& data){
    auto sum=0;
    for(const auto& num:data){
        sum+=num;
    }
    std::cout<<"const 引用传递：和="<<sum<<std::endl;
}

int main(){
    //创建一个包含1000万个整数的大向量
    std::vector<int> bigData(10000000,42);

    std::cout<<"数据大小："<<bigData.size()
        <<"个元素"<<std::endl;

    //用<chrono>测量时间，看看两种传参方式的速度差异
    // 💡 <chrono> 是 C++11 引入的时间库，用来精确测量时间
	    //    high_resolution_clock 是高精度时钟（可以理解为一个"高精度秒表"）
	    //    now() 表示"读取当前时间"，相当于按下秒表
	    //    两个 now() 的差值就是中间代码的执行时间
	    //    duration_cast<milliseconds> 把时间差转换成"毫秒"为单位
	    //    最后 .count() 拿到具体的毫秒数字
    
    //测试值传递
    auto start1=std::chrono::high_resolution_clock::now();
    //记录时间开始

    processByValue(bigData);
    auto end1=std::chrono::high_resolution_clock::now();
    //记录时间结束

    auto duration1=std::chrono::duration_cast<std::chrono::milliseconds>(end1-start1);
    std::cout<<"值传递耗时："<<duration1.count()<<"毫秒"<<std::endl;

    //测试引用传递
    auto start2=std::chrono::high_resolution_clock::now();
    //记录时间开始

    processByConstRef(bigData);
    auto end2=std::chrono::high_resolution_clock::now();
    //记录时间结束

    auto duration2=std::chrono::duration_cast<std::chrono::milliseconds>(end2-start2);
    std::cout<<"const 引用传递耗时："<<duration2.count()<<"毫秒"<<std::endl;
}