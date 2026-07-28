#include <iostream>
#include <fstream>
#include <string>

class logger{
    public:
        explicit logger(const std::string& filename):filename_(filename) {
            file_.open(filename_,std::ios::app);
            if(file_.is_open()){
                std::cout<<filename_<<"文件正常打开了"<<std::endl;
            }else{
                std::cout<<filename_<<"文件打开失败"<<std::endl;
            }
        }
        ~logger(){
            if(file_.is_open()){
                file_.close();
                if(file_.is_open()){
                    std::cout<<filename_<<"文件关闭失败"<<std::endl;
                }else{
                    std::cout<<filename_<<"文件正常关闭了"<<std::endl;
                }
            }
        }
        void write(const std::string& msg){
            message_=msg;
            if(file_.is_open()){
                 file_<<message_<<std::endl;
                 std::cout<<"已将“"<<message_<<"”文本，写入文件："<<filename_<<std::endl;
            }else{
                std::cout<<filename_<<"文件未打开"<<std::endl;
            }
        }
           
         
        

    private:
        std::string filename_;
        std::ofstream file_;
        std::string message_;
};

int main(){
    logger log1("5.5.1test.log");
    log1.write("这是一条测试日志");

    // 问题：有些对象不应该被复制
    // 离开作用域时log1和log2都会尝试关闭同一个文件
    // logger log2=log1;//编译器报错
    // log2.write("这是一条测试日志2");

    std::cout<<"程序结束"<<std::endl;
}
