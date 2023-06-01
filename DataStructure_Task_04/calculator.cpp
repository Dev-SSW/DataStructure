#include "calculator.h"
#include <string>
#include <iostream>
#include <stack>
#include <list>
#include <cmath>
using namespace std;
// strtok로 공백 기준 자르기 ex) ( , 1 , + , 2 , ) , ** , 2 이런 식으로 쪼개기
// list<string> tokens (리스트를 사용해서 넣기) 
// 스택에 특수문자 넣고 숫자는 받자마자 출력
// * 위에 + 나 - 가 오면 스택에서 꺼내서 출력
// **는 pow함수를 사용해서 제곱시키기
double sum = 0; //총합
int prior(string op)
{
	if (op == "+" || op == "-")
	{
		return 1;
	}
	if (op == "*" || op == "/" || op == "%" || op == "**" || op == "//")
	{
		return 2;
	}
	return 0;
}
calculator::calculator(const string& math_expr)
: m_math_expr(math_expr)
{
	stack<string> st; //char로 잘라진 연산자를 받는 스택
	string result; //결과 값을 담는 string
	char* str = NULL;
	char* token = strtok_s((char*)math_expr.c_str(), " ", &str);
	while (token != NULL)
	{
		string line = token; // char이 담긴 token을 string인 line에 담아서 조건문 비교시키기
		if (line >= "0" && line <= "9") // 변수가 나오면 바로 출력  ex) a b c
		{
			result += line;
			result += " ";
			token = strtok_s(NULL, " ", &str);
			continue;
		}
		if (line == "(")
		{
			st.push(line);
			token = strtok_s(NULL, " ", &str);
			continue;
		}
		if (line == ")")
		{
			while (st.top() != "(")
			{
				result += st.top();
				result += " ";
				st.pop();
			}
			st.pop(); // ( 지우기)
			token = strtok_s(NULL, " ", &str);
			continue;
		}
		if (st.empty() || prior(st.top()) < prior(line))  // ex ) +위에 *
		{
			st.push(line);
			token = strtok_s(NULL, " ", &str);
			continue;
		}
		else
		{   //지금의 연산기호가 top에 있는 연산기호의 우선 순위보다 작거나 같으면 ex) * 위에 +이 오면 또는 +위에 +
			while (!st.empty() && prior(line) <= prior(st.top())) // top의 우선 순위보다 작거나 같은 값이 나올 때 까지 
			{
				result += st.top();
				result += " ";
				st.pop();
			}
			st.push(line);  // 우선 순위보다 작아지면 push
			token = strtok_s(NULL, " ", &str);
			continue;
		}
	}
	if (!st.empty()) // 끝났을 때
	{
		while (!st.empty())
		{
			result += st.top();
			result += " ";
			st.pop();
		}
	}
	// 후위 표기법으로 변환 완료 (result)
	cout << "후위표기법으로 변환되었습니다 : " << result << endl;

	//여기서부터 계산기
	stack<string> cals; //숫자를 담는 스택

	char* cstr = NULL;
	char* ctoken = strtok_s((char*)result.c_str(), " ", &cstr);  //후위표기법으로 변환된 result를 쪼갠다. 남은 무나졍ㄹ은 cstr에 저장
	while (ctoken != NULL)
	{
		string cline = ctoken;   //char형인 ctoken을 cline에 저장 (비교를 위해)
		if (cline >= "0" && cline <= "9") 
		{
			cals.push(cline);   // 숫자면 스택에 삽입
			ctoken = strtok_s(NULL, " ", &cstr);  //다시 쪼개기
			continue;
		}
		if (cline == "+")
		{
			double a = 0, b = 0, c = 0;
			a = stod(cals.top());
			cals.pop();
			b = stod(cals.top());
			cals.pop();
			c = a + b;
			cals.push(to_string(c)); // 다시 string 형으로 바꿔서 푸쉬
			ctoken = strtok_s(NULL, " ", &cstr);  //다시 쪼개기
			continue;
		}
		if (cline == "-")
		{
			double a = 0, b = 0, c = 0;
			a = stod(cals.top());
			cals.pop();
			b = stod(cals.top());
			cals.pop();
			c = b - a;
			cals.push(to_string(c));
			ctoken = strtok_s(NULL, " ", &cstr);  //다시 쪼개기
			continue;
		}
		if (cline == "*")
		{
			double a = 0, b = 0, c = 0;
			a = stod(cals.top());
			cals.pop();
			b = stod(cals.top());
			cals.pop();
			c = a * b;
			cals.push(to_string(c));
			ctoken = strtok_s(NULL, " ", &cstr);  //다시 쪼개기
			continue;
		}
		if (cline == "/")
		{
			double a = 0, b = 0, c = 0;
			a = stod(cals.top());
			cals.pop();
			b = stod(cals.top());
			cals.pop();
			c = b / a;
			cals.push(to_string(c));
			ctoken = strtok_s(NULL, " ", &cstr);  //다시 쪼개기
			continue;
		}
		if (cline == "%")
		{
			int a = 0, b = 0, c = 0;
			a = stoi(cals.top());
			cals.pop();
			b = stoi(cals.top());
			cals.pop();
			c = b % a;
			cals.push(to_string(c));
			ctoken = strtok_s(NULL, " ", &cstr);  //다시 쪼개기
			continue;
		}
		if (cline == "**")
		{
			double a = 0, b = 0, c = 0;
			a = stod(cals.top());
			cals.pop();
			b = stod(cals.top());
			cals.pop();
			c = pow(b, a);
			cals.push(to_string(c));
			ctoken = strtok_s(NULL, " ", &cstr);  //다시 쪼개기
			continue;
		}
		if (cline == "//")
		{
			int a = 0, b = 0, c = 0;
			a = stoi(cals.top());
			cals.pop();
			b = stoi(cals.top());
			cals.pop();
			c = b / a;
			cals.push(to_string(c));
			ctoken = strtok_s(NULL, " ", &cstr);  //다시 쪼개기
			continue;
		}
	}
	sum = stod(cals.top());
	cals.pop();
}


void calculator::print_result() const
{
	double dummy_value = 0.0;
	dummy_value = sum;
	cout << this->m_math_expr << " = " << dummy_value << endl;	
}