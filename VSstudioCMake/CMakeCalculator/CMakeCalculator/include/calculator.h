#pragma once
#include <string>
#include <optional>

class Calculator {
public://interface[接口]
	//perform computation , return optional 
	std::optional<double> calculate(double a, double b, const std::string& op) const;

private:
	std::optional<double> divide(double a, double b) const;
};