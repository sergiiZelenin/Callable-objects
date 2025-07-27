#pragma once
#include <string>


class Calculator
{
public:
	int add(int a, int b);
	int subtract(int a, int b);
	int multiply(int a, int b);
	int divide(int a, int b);

	void message(const std::string&) const;
};

