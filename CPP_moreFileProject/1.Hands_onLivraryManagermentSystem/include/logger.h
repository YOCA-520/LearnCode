//
// Created by Administrator on 2026/8/14.
//

#ifndef LIBRARYMANAGER_LOGGER_H
#define LIBRARYMANAGER_LOGGER_H

#pragma once

#include <string>
#include <fstream>

std::string currentTime();

class Logger {
public:
    // 构造函数与析构函数
    explicit Logger(const std::string& fileName);

    // 禁用拷贝构造和赋值运算符
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // 对外日志输出接口
    void info(const std::string& logMsg);
    void warning(const std::string& logMsg);
    void error(const std::string& logMsg);

private:
    std::ofstream file_;

    // 内部辅助方法
    void writeLog(const std::string& logType, const std::string& logMsg);
};

#endif //LIBRARYMANAGER_LOGGER_H
