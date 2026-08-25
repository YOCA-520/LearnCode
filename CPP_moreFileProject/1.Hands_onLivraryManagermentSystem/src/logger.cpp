#include "logger.h" // 确保引用了你的 logger.h 头文件路径
#include <iostream>
#include <chrono>
#include <ctime>

// 匿名命名空间：仅在当前 cpp 文件内部可见

std::string currentTime() {
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto nowtime = *std::localtime(&now);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d-%H-%M-%S", &nowtime);
    return buffer;
}


// 构造函数实现
Logger::Logger(const std::string& fileName) : file_(fileName, std::ios::app) {
    if (file_.is_open()) {
        file_ << "[" << currentTime() << "]" << "[INFO]" << "Log start success!" << std::endl;
    } else {
        std::cout << "[" << currentTime() << "]" << "[ERROR]" << "Log start failed!" << std::endl;
    }
}

// 成员函数实现
void Logger::info(const std::string& logMsg) {
    writeLog("INFO", logMsg);
}

void Logger::warning(const std::string& logMsg) {
    writeLog("WARNING", logMsg);
}

void Logger::error(const std::string& logMsg) {
    writeLog("ERROR", logMsg);
}

void Logger::writeLog(const std::string& logType, const std::string& logMsg) {
    if (file_.is_open()) {
        file_ << "[" << currentTime() << "]" << "[" << logType << "]" << logMsg << std::endl;
    } else {
        std::cout << "[" << currentTime() << "]" << "[ERROR]" << "Failed to write log!" << std::endl;
    }
}