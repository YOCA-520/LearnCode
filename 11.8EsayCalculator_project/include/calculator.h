#pragma once

#include <string>
#include <optional>//   可选类型

class Calculator{
    // perform calculation[执行计算]
public:
    std::optional<double> calculate(double a, double b,const std::string& operatorStr) const;

private:
    std::optional<double> divide(double a, double b) const;
};
