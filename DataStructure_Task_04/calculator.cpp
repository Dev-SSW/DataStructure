#include "calculator.h"
#include <string>
#include <iostream>
#include <stack>
#include <list>
#include <cmath>
using namespace std;
// strtok�� ���� ���� �ڸ��� ex) ( , 1 , + , 2 , ) , ** , 2 �̷� ������ �ɰ���
// list<string> tokens (����Ʈ�� ����ؼ� �ֱ�) 
// ���ÿ� Ư������ �ְ� ���ڴ� ���ڸ��� ���
// * ���� + �� - �� ���� ���ÿ��� ������ ���
// **�� pow�Լ��� ����ؼ� ������Ű��
double sum = 0; //����
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
	stack<string> st; //char�� �߶��� �����ڸ� �޴� ����
	string result; //��� ���� ��� string
	char* str = NULL;
	char* token = strtok_s((char*)math_expr.c_str(), " ", &str);
	while (token != NULL)
	{
		string line = token; // char�� ��� token�� string�� line�� ��Ƽ� ���ǹ� �񱳽�Ű��
		if (line >= "0" && line <= "9") // ������ ������ �ٷ� ���  ex) a b c
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
			st.pop(); // ( �����)
			token = strtok_s(NULL, " ", &str);
			continue;
		}
		if (st.empty() || prior(st.top()) < prior(line))  // ex ) +���� *
		{
			st.push(line);
			token = strtok_s(NULL, " ", &str);
			continue;
		}
		else
		{   //������ �����ȣ�� top�� �ִ� �����ȣ�� �켱 �������� �۰ų� ������ ex) * ���� +�� ���� �Ǵ� +���� +
			while (!st.empty() && prior(line) <= prior(st.top())) // top�� �켱 �������� �۰ų� ���� ���� ���� �� ���� 
			{
				result += st.top();
				result += " ";
				st.pop();
			}
			st.push(line);  // �켱 �������� �۾����� push
			token = strtok_s(NULL, " ", &str);
			continue;
		}
	}
	if (!st.empty()) // ������ ��
	{
		while (!st.empty())
		{
			result += st.top();
			result += " ";
			st.pop();
		}
	}
	// ���� ǥ������� ��ȯ �Ϸ� (result)
	cout << "����ǥ������� ��ȯ�Ǿ����ϴ� : " << result << endl;

	//���⼭���� ����
	stack<string> cals; //���ڸ� ��� ����

	char* cstr = NULL;
	char* ctoken = strtok_s((char*)result.c_str(), " ", &cstr);  //����ǥ������� ��ȯ�� result�� �ɰ���. ���� ���������� cstr�� ����
	while (ctoken != NULL)
	{
		string cline = ctoken;   //char���� ctoken�� cline�� ���� (�񱳸� ����)
		if (cline >= "0" && cline <= "9") 
		{
			cals.push(cline);   // ���ڸ� ���ÿ� ����
			ctoken = strtok_s(NULL, " ", &cstr);  //�ٽ� �ɰ���
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
			cals.push(to_string(c)); // �ٽ� string ������ �ٲ㼭 Ǫ��
			ctoken = strtok_s(NULL, " ", &cstr);  //�ٽ� �ɰ���
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
			ctoken = strtok_s(NULL, " ", &cstr);  //�ٽ� �ɰ���
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
			ctoken = strtok_s(NULL, " ", &cstr);  //�ٽ� �ɰ���
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
			ctoken = strtok_s(NULL, " ", &cstr);  //�ٽ� �ɰ���
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
			ctoken = strtok_s(NULL, " ", &cstr);  //�ٽ� �ɰ���
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
			ctoken = strtok_s(NULL, " ", &cstr);  //�ٽ� �ɰ���
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
			ctoken = strtok_s(NULL, " ", &cstr);  //�ٽ� �ɰ���
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