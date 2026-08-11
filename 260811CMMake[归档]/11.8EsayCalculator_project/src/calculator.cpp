#include "calculator.h"


std::optional <double> Calculator::calculate(
    double a, double b,const std::string& operatorStr
)const{
    if(operatorStr == "/"){
        return divide(a,b);
    }
    if(operatorStr == "*"){
        return a*b;
    }
    if(operatorStr == "+"){
        return a+b;
    }
    if(operatorStr == "-"){
        return a-b;
    }
    return std::nullopt;//not support operator
}

std::optional<double> Calculator::divide(double a, double b) const{
    if(b == 0.0){
        return std::nullopt;//divide by zero
    }
    return a/b;
}
