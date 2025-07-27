#include <iostream>
#include "Calculator.h"

int Calculator::add(int a, int b)
{
	return a + b;
}

int Calculator::subtract(int a, int b) { return a - b; }

int Calculator::multiply(int a, int b) { return a * b; }

int Calculator::divide(int a, int b)
{
	if (b != 0)
	{
		return a / b;
	}
	else
		return static_cast<int>(NAN);
}

void Calculator::message(const std::string& msg) const
{
	std::cout << msg << '\n';
}



