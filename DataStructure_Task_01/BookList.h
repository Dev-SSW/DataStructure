#pragma once
#include <vector>
#include <string>
using namespace std;
class BookList
{
public:
	void add_book(const string& book);
	const vector<string>& get_books_list() const;
	BookList(const string& filename);
	int retrieve_k_value(const string& line);
	int get_k_value() const;
private:
	vector<string> m_books;
	int m_k;
};

