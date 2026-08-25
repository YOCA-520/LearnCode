#include <iostream>
#include "math_utils.h"

int main()
{
	auto result = add(10, 20);
	std::cout << "10 + 20 = " << result << std::endl;

	auto result2 = multiply(6, 7);
	std::cout << "6 * 7 = " << result2 << std::endl;

	return 0;
}
