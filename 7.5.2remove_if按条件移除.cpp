#include <iostream>
#include <vector>
#include <algorithm>//算法库

int main(){
    std::vector<int> numbers={1,2,3,4,5,6,7,8,9,10};
    std::cout<<"原始容器：";
    for(const auto& n:numbers)std::cout<<n<<" ";
    std::cout<<std::endl;

    //移除所有偶数
    auto newEnd=std::remove_if(numbers.begin(),numbers.end(),
        [](int n){return n%2==0;}
    );

    std::cout<<"remove_if后(还没erase)(只是标记可删除并且返回新容器的末尾)的容器：";
    for(const auto& n:numbers)std::cout<<n<<" ";
    std::cout<<std::endl;

    //erase 删除标记的元素(真正的删除从newEnd开始到容器末尾)
    numbers.erase(newEnd,numbers.end());
    std::cout<<"erase后(删除了所有偶数)的容器：";
    for(const auto& n:numbers)std::cout<<n<<" ";
    std::cout<<std::endl;
}
