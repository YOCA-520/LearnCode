// ### 占位空文件：学到对应小节时，把代码敲进来 ###
// 4.8.0 自制日志函数 v1
// 📍 对应教程：第 4 章 4.8 节（chrono 时间戳 + 日志级别）


#include <iostream>
#include <string>
#include <chrono> //chrono(计时)//包含时间函数(c语言旧方法)
#include <ctime>  //strftime把时间格式化成字符串(c语言旧方法)
#include <cstdio> //snprintf 把毫秒拼到时间字符串后面

//获取当前时间返回字符串
std::string currentTime(){//current(当前的)
    auto now=std::chrono::system_clock::now();//获取当前时间点

    std::time_t time=std::chrono::system_clock::to_time_t(now);//将时间点转换为时间戳

    //⚠️ strftime 不支持 %f（毫秒）！遇到不认识的格式会失败，导致缓冲区为空。
    //所以先格式化到「秒」，毫秒后面再单独拼
    char buf[32];// ⚠️ C 风格数组——strftime 是 C 语言老接口，只认这种缓冲（唯一的例外用法，平时不用它）

    //毫秒：把自epoch以来的总毫秒数对1000取余，得到不足1秒的那部分毫秒
    //duration_cast<类型>(时间点)：把时间点转换为指定类型的时间点
    //time_since_epoch()：返回自epoch(协调世界时)以来的时间点
    auto ms=std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch())%1000;

    //格式输出：%年-%月-%日 %时:%分:%秒
    //strftime(缓冲区,缓冲区大小,格式字符串,时间指针)
    std::strftime(buf,sizeof(buf),"%Y-%m-%d %H:%M:%S",std::localtime(&time));

    //把毫秒拼到秒后面：例如 2026-08-03 12:34:56.789
    char result[40];
    //snprintf(缓冲区,缓冲区大小,格式字符串,参数...)
    std::snprintf(result,sizeof(result),"%s.%03lld",buf,(long long)ms.count());
    return std::string(result);


}

//日志函数：带时间戳+级别
void log(const std::string& level,const std::string& msg){
    std::cout<<"["<<currentTime()<<"] "<<"["<<level<<"] "<<msg<<std::endl;
}

int main(){
    log("INFO","程序启动");
    log("DEBUG","这是调试信息");
    log("WARN","这是警告信息");
    log("ERROR","这是错误信息");
    log("INFO","程序结束");
    
    int a=10;
    if(a>5){
        log("INFO","a大于5");
    }else{
        log("WARN","a不大于5");
    }

}