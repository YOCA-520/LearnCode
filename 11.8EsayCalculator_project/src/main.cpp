#include <iostream>
#include "calculator.h"

void printResult(double a, double b, const std::string &op, const Calculator &calc)
{
    auto r = calc.calculate(a, b, op);
    std::cout << a << op << b << " = ";
    if (r.has_value())
    {
        std::cout << r.value() << std::endl;
    }
    else
    {
        std::cout << "error(除零或不支持的运算符)" << std::endl;
    }
}

int main()
{
    Calculator calc;

    std::cout << "====EsayCalculator====" << std::endl;
    printResult(10, 2, "/", calc);
    printResult(10, 2, "*", calc);
    printResult(10, 2, "+", calc);
    printResult(10, 2, "-", calc);
    printResult(10, 0, "/", calc);

    return 0;
}
