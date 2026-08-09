// Multi-file pet adoption practice project//multi[多种]//practice[练习]
// logger.h
// logger declaration//logger[日志]//日志声明
#pragma once // pragma[编译] //编译一次，这里是为了防止重复包含
#include <string>
#include <fstream> //fstream[文件流]

class Logger
{
public:
    // Declaration only[只声明]
    explicit Logger(const std::string &filename);
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

    void info(const std::string &msg);
    void warning(const std::string &msg);
    void error(const std::string &msg);

private:
    void write(const std::string& tag,const std::string &msg);
    std::ofstream file_;
};
