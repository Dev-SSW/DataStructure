#include "BookList.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include <cstring>

using namespace std;

BookList::BookList(const string& filename)
{
	ifstream ifs;
	ifs.open(filename, ios::in);

	if (ifs.is_open())
	{
		string line;
		int line_no = 0;
		while (getline(ifs, line))  // ifs 파일에서 newline 까지 한줄씩 읽는다.
		{
#ifdef _DEBUG
			// cout << line << endl;
#endif
			if (++line_no == 1)
			{
				this->m_k = retrieve_k_value(line);
			}
			else
			{
				add_book(line);
			}
		}

		ifs.close();
	}

}

int BookList::retrieve_k_value(const string& line)
{
	int k = -1;

	char* str2 = NULL;
	char* token = strtok_s((char*)line.c_str(), " \t", &str2);
	int token_cnt = 0;

	while (token != NULL) // NULL이 아닐 때까지 반복한다. 
	{
#ifdef _DEBUG
		// cout << token << endl;
#endif 

		if (token_cnt == 2)
		{
			k = stoi(token);
		}

		token = strtok_s(NULL, " \t", &str2);

		token_cnt++;
	}

	return k;
}

void BookList::add_book(const string& book)
{
	m_books.push_back(book);
}

const vector<string>& BookList::get_books_list() const
{
	return this->m_books;
}

int BookList::get_k_value() const
{
	return this->m_k;
}