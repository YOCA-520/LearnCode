// =============================================
// 📝 我关于 explicit 的理解笔记
// =============================================
//
// 1. 没有 explicit 时：
//      LogFile a = name;
//      本来 a 是 LogFile 类型，name 是 string 类型，类型不匹配
//      但编译器看到 LogFile 有个构造函数能接收 string
//      就偷偷帮我调了它，等价于 LogFile a(name);
//
// 2. 有 explicit 时：
//      编译器就不帮这个忙了，类型不匹配就直接报错
//      逼我老老实实写 LogFile a(name); 不能偷懒
//
// 3. explicit 就是为了防止编译器多管闲事
//      比如有个函数 void f(LogFile x);
//      我写 f(name); 没 explicit 的话编译器会偷偷帮我变成 f(LogFile(name));
//      我根本不知道多了个临时对象，可能会出 bug
//      所以一般单参数的构造函数最好都加上 explicit
//
// 4. 补充：=delete 是禁止拷贝
//      两个 LogFile 对象管理同一个文件 → 析构时都去关闭 → 崩溃
//      所以用 =delete 禁止复制，保证一个文件只被一个对象管
// =============================================

#include<iostream>
#include<fstream>
#include<string>

class LogFile{
public:
    //构造函数：打开文件（获取资源）
    //explicit 关键字：防止编译器偷偷做“隐式类型转换”转换为构造函数
    //不能写LogFile log =“app.log”（虽然语法上也允许）
    //加了explicit 关键字后，只能通过显式类型转换来调用构造函数
    explicit LogFile(const std::string& filename){
        file_.open(filename ,std::ios::app);//追加模式
        if(file_.is_open()){
            std::cout<<"日志文件已打开:"<<filename<<std::endl;
            write("===日志开始==");
        }else{
            std::cout<<"日志文件打开失败:"<<filename<<std::endl;
        }

    }

    //析构函数：关闭文件（释放资源）
    ~LogFile(){
        if(file_.is_open()){
            write("===日志结束==");
            file_.close();
            std::cout<<"日志文件已关闭:"<<std::endl;
        }
    }


    // 下面这两行是 C++ 的"拷贝控制"语法，可能看起来有点奇怪，我们拆开解释：
    //
    // ① LogFile(const LogFile&)  —— 这叫"拷贝构造函数"
    //    大白话：如果你用另一个 LogFile 对象来创建新的 LogFile，
    //    比如 LogFile log2 = log1; 就会调用这个函数
    //    const LogFile& 表示"传进来的源对象"，我只会读它，不会改它
    //
    // ② LogFile& operator=(const LogFile&)  —— 这叫"拷贝赋值运算符"
    //    大白话：如果你把一个 LogFile 赋值给另一个已经存在的 LogFile，
    //    比如 log1 = log2; 就会调用这个函数
    //
    // ③ = delete 的意思是"删除这个函数"，禁止使用它
    //    一个文件只能由一个 LogFile 对象管理，如果拷贝了，
    //    两个对象都会试图关闭同一个文件 → 出问题！
    //    所以用 = delete 禁止拷贝，防止意外
    LogFile(const LogFile&)=delete;//禁止拷贝构建
    LogFile& operator=(const LogFile&)=delete;//禁止拷贝赋值

    //写入日志的方法
    void write(const std::string& message){
        if(file_.is_open()){
            file_<<message<<std::endl;
        }
    }

private:
    std::ofstream file_;//文件流对象，本身也是RAII的资源
};

    //测试函数
void testLog(){
    LogFile log("app.log");
    log.write("用户登录了系统。");
    log.write("用户执行了操作A。");
    log.write("用户退出了系统。");
    //函数结束log对象会被析构，文件会被关闭
}//<-析构函数在这里调用


int main(){
    std::cout<<"==RAII 演示=="<<std::endl;
    testLog();
    std::cout<<"==RAII 演示结束=="<<std::endl;

    //验证文件内容
    std::cout<<"\n====查看日志文件==="<<std::endl;
    std::ifstream reader("app.log");
    std::string line;
    while (std::getline(reader,line)){
        std::cout<<line<<std::endl;
    }
}

