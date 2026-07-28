#include <iostream>
#include <string>
#include <fstream>

class Logger{
    public:
        explicit Logger(const std::string& filename):filename_(filename){
            file_.open(filename,std::ios::app);//追加模式打开
            if(file_.is_open()){
                std::cout<<"文件：“"<<filename_<<"”已打开。"<<std::endl;
            }else{
                std::cout<<"文件：“"<<filename_<<"”打开失败，程序终止。"<<std::endl;
                exit(1);
            }
        }
        ~Logger(){
            if(file_.is_open()){
                file_.close();
                std::cout<<"文件：“"<<filename_<<"”已关闭。"<<std::endl;
            }else{
                std::cout<<"文件：“"<<filename_<<"”未打开，不执行操作。"<<std::endl;
            }
        }

        void write(const std::string& message){
            if(file_.is_open()){
                file_<<message<<std::endl;
                std::cout<<"已写入日志：“"<<message<<"”"<<std::endl;
            }else{
                std::cout<<"文件未打开，写入失败"<<std::endl;
            }
        }

        //禁止复制
        // 如果不加这两行，编译器会默认生成拷贝构造函数和赋值运算符
        // 有了 = delete，下面的 Logger log2 = log1; 会在编译时报错   
        //实际上不加好像也会报错     
        Logger(const Logger&)=delete;// 禁止拷贝构造
        Logger& operator=(const Logger&)=delete;// 禁止拷贝赋值

    private:
        std::string filename_;
        std::ofstream file_;
};

int main() {
    Logger log1("5.5.2test.log");
    log1.write("第一条日志");

    // Logger log2 = log1;  // ❌ 编译错误！Logger 禁止复制！
    //                      // 这就从根源上杜绝了"两个对象抢同一个文件"的问题

    std::cout << "✅ 安全：Logger 不能被复制，不会出现双重释放" << std::endl;
   
}