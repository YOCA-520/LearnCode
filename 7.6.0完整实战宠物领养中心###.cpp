// ### 占位空文件：学到对应小节时，把代码敲进来 ###
// 7.6.0 完整实战：宠物领养中心
// 📍 对应教程：第 7 章 7.6 节（类 + 交互 + 日志 + Lambda 算法）
// 提示：这是新版主题，你原来的 7.6.0 学生成绩文件保留


#include<iostream>
#include<vector>
#include<algorithm>//算法头文件
#include<string>
#include<fstream>//文件流头文件
#include<chrono>//时间头文件(C++11新增)
#include<ctime>//时间头文件(C时间库)

//时间工具函数
std::string currentTime(){//获取当前时间字符串
    auto now=std::chrono::system_clock::now();
    std::time_t time=std::chrono::system_clock::to_time_t(now);
    //将C++11时间点转换为C时间戳

    char buf[32];
    //格式输出：%年-%月-%日 %时:%分:%秒
    std::strftime(buf,sizeof(buf),"%Y-%m-%d %H:%M:%S",std::localtime(&time));
    return std::string(buf);
}

//日志类
class Logger{
private:
    std::ofstream file_;// RAII：构造打开、析构关闭

    void write(const std::string& tag,const std::string& msg){
        if(file_.is_open()){
            file_<<"["<<currentTime()<<"] "<<"["<<tag<<"] "<<msg<<std::endl;
        }
    }
    


public:
    explicit Logger(const std::string& filename):
        file_(filename,std::ios::app){}
    Logger(const Logger&)=delete;
    //禁止复制对象，防止多个日志文件打开
    Logger& operator=(const Logger&)=delete;//operator(运算符) 连等赋值会用到
    //这里相当于禁止连等赋值，禁止复制构造

    void info(const std::string& msg){write("INFO",msg);}
    void warn(const std::string& msg){write("WARN",msg);}
    void error(const std::string& msg){write("ERROR",msg);}


};

//宠物自定义结构体数据
struct Pet{//struct 结构体定义  Pet(宠物)
    std::string name;
    std::string type;
    int age;
    std::string owner;//狗修金（宠物的主人）
    bool adopted;//adopted（收养过去式）是否已被领养
}

