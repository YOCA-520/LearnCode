// ### 占位空文件：学到对应小节时，把代码敲进来 ###
// 5.10.0 自制日志类 v2
// 📍 对应教程：第 5 章 5.10 节（写文件 + 级别过滤 + =delete）
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>//chrono(计时)//包含时间函数(c语言旧方法)
#include <ctime>//strftime把时间格式化成字符串(c语言旧方法)

//获取当前时间字符串
std::string currentTime(){//current(当前的)
    //⚠️ strftime 不支持 %f（毫秒）！遇到不认识的格式会失败，导致缓冲区为空。
    //std::time_t 是一个 64位时间戳类型,本质是long long int
    //自 1970年1月1日 00:00:00 UTC（叫 epoch，纪元）以来经过的秒数。
    auto now=std::chrono::system_clock::now();//获取当前时间点
    std::time_t time=std::chrono::system_clock::to_time_t(now);//将时间点转换为时间戳
    char buf[32];// ⚠️ C 风格数组——strftime 是 C 语言老接口，只认这种缓冲（唯一的例外用法，平时不用它） 

    //格式输出：%年-%月-%日 %时:%分:%秒
    std::strftime(buf,sizeof(buf),"%Y-%m-%d %H:%M:%S",std::localtime(&time));

    return std::string(buf);
} 

class Logger{
private:
    std::ofstream file_;// RAII：构造打开、析构关闭
    int minLevel_;      // 0=INFO 1=WARNING 2=ERROR

    //日志函数：带时间戳+级别
    void log( int level,const std::string& tag,const std::string& msg){
        if(level<minLevel_)return;
        if(file_.is_open()){
            file_<<"["<<currentTime()<<"] "<<"["<<tag<<"] "<<msg<<std::endl;
        }
        //打印到控制台
        std::cout<<"["<<currentTime()<<"] "<<"["<<tag<<"] "<<msg<<std::endl;
    }



public:
    //构造函数，打开日志文件
    Logger(const std::string& filename,int minLevel=0)
        :file_(filename,std::ios::app),minLevel_(minLevel){
            if(!file_.is_open()){
                std::cerr<<"日志文件"<<filename<<"打开失败"<<std::endl;
            }
        }
    
    //析构函数，自动关闭日志文件，不用自己操心
    //所以不用写析构函数

    //禁止复制
    Logger(const Logger&)=delete;
    Logger& operator=(const Logger&)=delete;

    //三个便捷方法：内部走同一个log()
    void info(const std::string& msg){log(0,"INFO",msg);}
    void warn(const std::string& msg){log(1,"WARN",msg);}
    void error(const std::string& msg){log(2,"ERROR",msg);}

};

int main(){
    //阈值设为1：INFO级别会被过滤
    Logger logger("5.10.0.app.log",/*minLevel*/1);

    logger.info("这是INFO信息");
    logger.warn("这是WARN信息");
    logger.error("这是ERROR信息");
    logger.info("这是INFO信息");

    logger.info("程序即将结束");

    std::cout<<"程序结束,可打开5.10.0.app.log查看日志内容"<<std::endl;
}