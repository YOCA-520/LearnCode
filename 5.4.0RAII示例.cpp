// ### 占位空文件：学到对应小节时，把代码敲进来 ###
// 5.4.0 RAII 示例
// 📍 对应教程：第 5 章 5.4 节（构造获取、析构释放）


#include <iostream>
#include <fstream>//文件流
#include <string>

// 代码	                                         名字	    禁止的操作
// Logger(const Logger&) = delete;	            拷贝构造	用已有对象创建新对象
// Logger& operator=(const Logger&) = delete;	拷贝赋值    把已有对象赋给另一个已存在的对象
//operator= 是赋值运算符，返回 Logger&（自身引用）是为了支持链式赋值：a = b = c;。删掉它自然也就禁止链式赋值了。
class Logger{ 
    Logger (const Logger&)=delete;
    Logger& operator=(const Logger&)=delete;

private:
    std::ofstream file_;
public:
    //构造函数：打开文件
    explicit Logger(const std::string& fileneme):file_(fileneme){
        file_.open(fileneme,std::ios::app);//追加模式打开文件
        if(!file_.is_open()){
            throw std::runtime_error("无法打开文件");
        }else{
            std::cout<<"文件"<<fileneme<<"打开成功"<<std::endl;
        }
    }



//析构函数：关闭文件
    ~Logger(){
        file_.close();
        if(!file_.is_open()){
            std::cout<<"文件关闭成功"<<std::endl;
        }else{
            std::cout<<"文件关闭失败"<<std::endl;
        }
    }



    void write(const std::string& msg){
        if(file_.is_open()){
            file_<<msg<<std::endl;
        }else{
            std::cout<<"文件未打开,写入失败"<<std::endl;
        }
    }


};



void testLogger(){
    Logger log("5.4.0.app.log");
    log.write("这是日志信息");
    log.write("这是日志信息2");
    log.write("这是日志信息3");
}

int main(){
    std::cout<<"程序启动"<<std::endl;
    testLogger();
    std::cout<<"程序结束"<<std::endl;
    return 0;
}