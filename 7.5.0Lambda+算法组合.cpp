// 💡 find_if 在容器中"挨个检查"每个元素，找到第一个符合条件的元素就返回。
// 参数：(开始位置, 结束位置, 判断条件)
// 返回值：如果找到了 → 指向该元素的"迭代器"（类似指针）；找不到 → .end()（末尾标记）
// 大白话：在一排人（容器）里，挨个问"你姓李吗？"，第一个回答"是"的人揪出来


#include <iostream>
#include <vector>
#include <algorithm> //算法头文件，sort函数头文件，用于排序。
#include <string>


int main(){
    std::vector<std::string> names={"张三","李四","王五","赵六","王二","麻子"};
    std::cout<<"原始姓名列表：";
    for(const auto& n:names)std::cout<<n<<" ";
    std::cout<<std::endl;

    //查找姓李的人
    //find_if的三个参数
    //1.开始位置names.begin()->容器的第一个元素
    //2.结束位置names.end()->容器的最后一个元素的下一个位置
    //3.判断条件[](const std::string& n){return n[0]=='李';}

    auto it =std::find_if(names.begin(),names.end(),[](const std::string& name){
        return name.starts_with("李");//如果姓名的第一个字符是李，就返回true
    });
    
    //find_if返回的是迭代器（可以看作指向符合条件元素的指针）
    //如果没找到符合条件的元素，返回.end()（末尾哨兵）
    //所以一定要判断是否等于.end()（末尾哨兵）！
    if(it!=names.end()){
        std::cout<<"找到一个姓李的人："<<*it<<std::endl;
    }else{//*it取出迭代器指向的元素，打印出来
        std::cout<<"没有姓李的人"<<std::endl;
    }

    //统计所有姓李的人数

    //count计数
    auto count=std::count_if(names.begin(),names.end(),[](const std::string& name){
        return name.rfind("李",0)==0;
    });//count_if 和 find_if 类似，但它不是"找到就停"，而是"全部数一遍"

    std::cout<<"姓李的人有："<<count<<"人"<<std::endl;
    
    if(count>0){
        std::cout<<"分别是：";
        for(const auto& n:names){
            if(n.starts_with("李")) std::cout<<n<<" ";//if(lits(n))=“if(name.starts_with("李"))”
        }
        std::cout<<std::endl;
    }



    //复用写法
    //上述解耦写法，将判断条件和算法分离，使代码更清晰、更易维护。
    //例如，如果要统计所有姓王的人数，只需要修改判断条件lambda即可。
    auto lits2=[](const std::string& name){//判断条件lambda
        return name.starts_with("王");
    };

    auto find2=std::find_if(names.begin(),names.end(),lits2);//lits判断条件单独作为参数传递
    if(find2!=names.end()){
        std::cout<<"找到一个姓王的人："<<*find2<<std::endl;
    }else{
        std::cout<<"没有姓王的人"<<std::endl;
    }

    //统计所有姓王的人数
    //count计数
    auto count2=std::count_if(names.begin(),names.end(),lits2);//lits判断条件单独作为参数传递
    std::cout<<"姓王的人有："<<count2<<"人"<<std::endl;
    if(count2>0){
        std::cout<<"分别是：";
        for(const auto& n:names){
            if(lits2(n))std::cout<<n<<" ";
        }
        std::cout<<std::endl;
    }



    
   
}