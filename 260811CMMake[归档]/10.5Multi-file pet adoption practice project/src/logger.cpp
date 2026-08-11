//Multi-file pet adoption practice project//multi[多种]//practice[练习]
//logger.cpp
//logger implementation//日志实现

#include "logger.h"
#include <chrono>
#include <ctime>

std::string currentTime(){
    auto now = std::chrono::system_clock::now();
    std::time_t nowToC=std::chrono::system_clock::to_time_t(now);
    char buf[32];
    // //strftime（buffer，buffer size，format[格式] string，time struct）
    std::strftime(buf,sizeof(buf),"%Y-%m-%d %H:%M:%S",std::localtime(&nowToC));
    return std::string(buf);
}

//constructor: open file //构造函数
Logger::Logger(const std::string& filename):file_(filename,std::ios::app){}

void Logger::info(const std::string& msg){write("INFO",msg);}
void Logger::warning(const std::string& msg){write("WARNING",msg);}
void Logger::error(const std::string& msg){write("ERROR",msg);}

void Logger::write(const std::string& tag,const std::string &msg){
    if(file_.is_open()){
        file_<<"["<<currentTime()<<"]"<<"["<<tag<<"]"<<msg<<std::endl;
    }
}
