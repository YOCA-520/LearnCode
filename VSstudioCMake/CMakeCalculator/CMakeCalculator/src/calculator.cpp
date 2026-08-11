#include "calculator.h"

std::optional <double> Calculator::calculate(
	double a, double b, const std::string& op) const {
	if (op == "+")return a + b;
	if (op == "-") return a - b;
	if (op == "/")return divide(a, b);
	if (op == "*" || op == "x")return (a * b);

	return std::nullopt;

}

std::optional<double> Calculator::divide(double a, double b)const {
	if(b == 0.0) return std::nullopt;
	return a / b;
}
	
