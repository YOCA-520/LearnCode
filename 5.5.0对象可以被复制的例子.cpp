#include <iostream>

class Score{
    public:
        Score(int value):value_(value) {}
        int getValue() const{return value_;}
    private:
        int value_;
};


int main(){
    Score a(95);
    Score b=a;//可以复制，编译器自动生成拷贝构造函数：Score(Score& other)
    std::cout<<a.getValue()<<",b="
        <<b.getValue()<<std::endl;

}
// 问题：有些对象不应该被复制
// 之前写的 Logger 类——如果两个 Logger 对象指向同一个文件：

// Logger log1("app.log");   // log1 打开了 app.log
// Logger log2 = log1;       // ❌ log2 复制了 log1，它们共享同一个文件
//                           // 当 log1 析构时 → 关闭文件
//                           // 当 log2 析构时 → 再次关闭同一个文件 → 崩溃！