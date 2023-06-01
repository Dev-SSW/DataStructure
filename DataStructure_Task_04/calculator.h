#pragma once
#include <string>

using namespace std;

class calculator
{
public:
	calculator(const string & math_expr);
	void print_result() const;

private:
	string m_math_expr;
};

