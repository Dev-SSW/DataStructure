// my_calc.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
#include <iostream>
#include <string>
#include "calculator.h"
using namespace std;
int main(int argc, char* argv[])  // cmd를 실행하여 이 함수를 호출, argv[0]은 실행 경로가 되고, 값을 넣으면 차례대로 들어간다 																
{								  // ex) 1 + 2 라면 argv[1] = 1 , argv[2] = + , argv[3] = 2	, argc는 갯수가 들어간다 -> 4	
	if (argc != 2)
	{
		cout << "usage : my_calc.exe math_expr" << endl;
		cout << "example: my_calc.exe \"( 1 + 2 ) ** 2\" " << endl;
		return 0;
	}

	string expr = string(argv[1]);
	calculator my_calc(expr);
	my_calc.print_result();

	/*string expr ="";
	for (int i = 1; i < argc; i++)
	{
		expr += argv[i];
		expr += " ";
	}
	calculator my_calc(expr);
	my_calc.print_result();*/
	return 0;
}
