// std::optional（C++17 引入）是一个"包装器"
// ——它要么包含一个有效值，要么为空（std::nullopt）。
// 💡 大白话：std::optional 就像外卖快递——要么送到了（有值），
// 要么没送到（空）。你一眼就知道是什么状态，不用猜。

#include <iostream>
#include <optional>// 引入 std::optional(可选择的)
#include <vector>
#include <string>


//现代写法,返回值明确表示“可能有结果，也可能没有。”
//optional（可选择的，包含一个值或为空）
std::optional<int> findScore(const std::vector<int>& scores,int target/*目标*/ ){
    for(size_t i=0;i<scores.size();i++){
        if(scores[i]==target){
            return scores[i];//查找成功，返回目标值
        }
    }
    return std::nullopt;//查找失败，返回空值
}

int main(){
    std::vector<int> scores={80,90,75,95,88};

    //查找一个存在的分数
    auto result=findScore(scores,88);
    if(result.has_value()){
        std::cout<<"find! score is:"<<result.value()<<std::endl;
    }else{
        std::cout<<"no find result scores."<<std::endl;
    }

    //查找一个不存在的分数
    auto result2=findScore(scores,100);
    if(result2){//bool转换，等价于has_value()
        std::cout<<"find! score is:"<<*result2<<std::endl;
    }else{
        std::cout<<"no find result scores."<<std::endl;
    }

}
