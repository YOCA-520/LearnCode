// ### 占位空文件：学到对应小节时，把代码敲进来 ###
// 3.5.0 猜数字游戏
// 📍 对应教程：第 3 章 3.5.4 节（while + cin + 随机数）

#include <iostream>
#include <cstdlib>   //包含随机数函数(c语言旧方法)
#include <ctime>     //包含时间函数(c语言旧方法)

int main(){
    // ⚠️ rand/srand 是 C 语言时代的"旧随机数"，真实项目不推荐用
    //    现代 C++ 用 <random> 库（mt19937），第 15 章会正式学
    //    这里先用它，是为了让你专注 while/cin——先会跑，再换好车
    // 随机数种子：以当前时间为种子，每次运行结果不同
    // （否则每次运行 rand() 都产生同一串数字）
    // static_cast<类型>(值)：C++ 的类型转换写法，把一种类型转成另一种
    // 这里把 time() 返回的时间转成 unsigned 类型，供 srand 使用
    // （你已经在 3.3 节见过 static_cast<double>，这是同一个东西）
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    // 设置随机数种子，是生成随机数的必备前置操作

    // 生成随机数
    int secret=std::rand()%100+1;//取余100，得到0-99之间的随机数，再加1，得到1-100之间的随机数

    int guess=0;//guess 猜的数字
    int attempts=0;//attempts 猜的次数

    std::cout<<"欢迎来到猜数字游戏！"<<std::endl;
    std::cout<<"请在1-100之间猜一个数字："<<std::flush;
    while(guess!=secret){
        std::cin>>guess;
        attempts++;
        std::cout<<"第"<<attempts<<"次，你猜的数字是:"<<guess<<std::endl;
        if(guess<secret){
            std::cout<<"太小了，请再试一次："<<std::flush;
        }else if(guess>secret){
            std::cout<<"太大了，请再试一次："<<std::flush;
        }
    }1
    
    std::cout<<"恭喜你猜对了！你用了"<<attempts<<"次猜中了。"<<std::endl;
    


}
