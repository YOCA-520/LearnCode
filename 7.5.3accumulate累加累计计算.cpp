#include <iostream>
#include <vector>
#include <numeric>//累加算法  accumulate(逐步积累)需要这个头
#include <string>

    //循环抽象写法（抽象为类）
    // 小助手：把 vector 打印成 "1,2,3。" 或 "1x2x3" 这样的形式
std::string printList(const std::vector<int>& v,
                const std::string& sep,        // 元素之间的分隔符
                const std::string& endSep = "") {  // 结尾符号（默认空）
    std::string outString="";
    for (size_t i = 0; i < v.size(); ++i) {
        outString+=std::to_string(v[i]);//to_string()将整数转换为字符串，确保元素是整数类型
        if (i != v.size() - 1) outString+=sep;   // 中间 → 分隔符
        else outString+=endSep; // 最后 → 结尾符//这里不需要to_string()，也不需要，因为传参是固定死的字符串类型
    }
    return outString;
}

int main(){
    std::vector<int> scores={80,90,75,95,88};//scores(分数的复数形式)，这里表示分数的vector容器名


    auto sum=std::accumulate(scores.begin(),scores.end(),0);//0表示加法类型，确保计算精度高
    //等同于：auto sum=std::accumulate(scores.begin(),scores.end(),0);

    std::cout<<"总分："<<sum<<std::endl;
    //accumulate的初始值决定了计算过程的精度。
    //注意：这里要转换为double类型，否则会丢失精度
    //static_cast<double>(sum)将sum转换为double类型，确保计算精度高,强制类型转换
    std::cout<<"平均分："<<static_cast<double>(sum)/scores.size()<<std::endl;
    std::cout<<"平均分："<<sum/scores.size()<<std::endl;

    //用lambda自定义积累操作：求乘积
    std::vector<int> numbers={11,22,66,88,25,44,66,44};

    //product乘积
    auto product =std::accumulate(numbers.begin(),numbers.end(),1,//初始值为1，确保乘积结果正确
        //"初始值"就是计算开始前，手里先拿着的一个数。
        // 它是 accumulate 的第三个参数，
        // 作用有两个：① 起步的数、② 决定计算类型。
        // 这里初始值为1，说明是乘积类型，而不是加法类型，加法是0，乘法是1
        [](int a,int b){return a*b;});

    std::cout<<"numbers:";
    for(auto i=0;i<numbers.size();i++){//虽然不会编译失败，但是这里不建议使用auto i:numbers，因为i是索引，不是元素
        std::cout<<numbers[i];
        if(i!=numbers.size()-1){
            std::cout<<",";
        }else{
            std::cout<<"。";
        }
    }
    std::cout<<std::endl;

    std::cout<<"numbers的乘积是：";
    for(size_t i=0;i<numbers.size();i++){//直接用size_t类型（无符号整数），确保索引在有效范围内
        std::cout<<numbers[i];
        if(i!=numbers.size()-1){
            std::cout<<"x";
        }
    }
    std::cout<<"="<<product<<"(int溢出结果错误)"<<std::endl;//结果错误1603374080，
    //因为product是int类型，只能表示-2147483648到2147483647之间的整数，超过范围范围，会丢失精度
    //auto会有限推理成int类型，所以会丢失精度，建议用long long类型

    //抽象写法调用
    std::cout<<"numbers的乘积是："<<printList(numbers,"x","=")<<product<<"(int溢出结果错误)"<<std::endl;


    long long product2 =std::accumulate(numbers.begin(),numbers.end(),1LL,
        [](long long a,long long b){return a*b;});//改用long long类型，确保计算精度高
    
    std::cout<<"改为long long类型后，numbers的乘积是："<<printList(numbers,"x","=")<<product2<<std::endl;
}
