#include <iostream>
#include "calculator.h"

int main() {
	Calculator calc;

	std::cout << "===MCMakeCalculator===" << std::endl;
	std::cout << "10 + 5 = " << *calc.calculate(10, 5, "+") << std::endl;
	std::cout << "10 - 5 = " << *calc.calculate(10, 5, "-") << std::endl;
	std::cout << "10 * 5 = " << *calc.calculate(10, 5, "*") << std::endl;
	std::cout << "20 / 3 = " << *calc.calculate(10, 5, "/") << std::endl;

	auto result = calc.calculate(10, 0, "/");
	if (result) {
		std::cout << "10 / 0 = " << *result << std::endl;
	}
	else {
		std::cout << "can not divisor is zero " << std::endl;
	}

	return 0;
}