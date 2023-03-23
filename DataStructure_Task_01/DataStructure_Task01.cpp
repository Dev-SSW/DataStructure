// Find_kth_most_frequent_word.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
#include "BookList.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <ctime>
using namespace std;
//------------------------------------------------------------//
// ���⼭���� �ʿ��� �ڵ带 �߰��ϼ���.
// Ŭ������ �߰��ϰų� �Լ��� �����Ӱ� �߰��ϼ���

map<string, int> m;
string word;
int frequency;
int ccc = 0;
void BookList_Read_Line(const string& bookname)
{
    ifstream ifs;
    ifs.open(bookname, ios::in);

    if (ifs.is_open())
    {
        string line;
        while (getline(ifs, line))  // ifs ���Ͽ��� newline ���� ���پ� �д´�.
        {
            
            transform(line.begin(), line.end(), line.begin(), ::tolower);
            
            //slice_line_To_Token(line);
            char* str = NULL;
            char* token = strtok_s((char*)line.c_str(), " \t", &str);
            
            while (token != NULL)
            {
#ifdef _DEBUG
                // cout << token << endl;
#endif
                m[token]++;
                token = strtok_s(NULL, " \t", &str);
            }
        }
        ifs.close();
    }
}

//void slice_line_To_Token(const string& line)   
//{
//    char* str = NULL;
//    char* token = strtok_s((char*)line.c_str(), " \t", &str);
//  
//    while (token != NULL) 
//    {
//        m[token]++;
//        token = strtok_s(NULL, " \t", &str);
//    }
//}

int your_answer2(vector<pair<string, int>>& v, string word) //�ܾ��� �󵵼�
{
    int dummy;
    for (const auto& a : v) {
        if (a.first == word) {
            dummy = a.second;
        }
        
    }
    return dummy;
    /*int max = 0;
    for (const auto& b : m) {
        if (max < b.second) {
            max = b.second;
        }
    }
    return max;*/
}

string your_answer1(vector<pair<string, int>> &v,int k) //���� ���� �ܾ�
{
    string dummy;
    int count = 0;
    for (const auto& a : v) {
        if (count == k-1) {
            dummy = a.first;
        }
        count++;
    }
    return dummy;
    /*string dummy;
    for (const auto& a : m)
    {
        if (a.second == frequency) {
            dummy = a.first;
        }
    }
    return dummy;*/
    
}
static bool comp(pair<string, int>& a, pair<string, int>& b)
{
    return a.second > b.second;
}
    // ������� �ʿ��� �ڵ带 �߰��ϼ���
    //------------------------------------------------------------//

void print_result(const string& word, const int word_frequency)
{
    cout << "\n\n\n------------------------------------------" << endl;
    cout << "the most frequent word : " << word << endl;
    cout << "frequency  : " << word_frequency << endl;
    cout << "------------------------------------------\n\n\n" << endl;
}
int main()
{
    clock_t start, finish;
    start = clock();

    BookList booklist("books.txt");

    /*cout << "k = " << booklist.get_k_value() << endl;

    for (auto b : booklist.get_books_list())
        cout << b << endl;*/

    //------------------------------------------------------------//
    // ���⼭���� �ʿ��� �ڵ带 �߰��ϼ���.
    
    for (auto add : booklist.get_books_list()) 
    {
        BookList_Read_Line(add);
    }

    /*
    BookList list("moby_dick_or_the_whale_by_herman_melville.txt");
    BookList list1("Little_Women_Or_Meg_Jo_Beth_and_Amy_by_Louisa_May_Alcott.txt");
    BookList list2("Romeo_and_Juliet_by_William_Shakespeare.txt");
    BookList list3("The_Adventures_of_Ferdinand_Count_Fathom_Complete_by_T_Smollett.txt");
    BookList list4("Twenty_Years_After_by_Alexandre_Dumas.txt");
    */

    vector<pair<string, int>> v(m.begin(), m.end());
    sort(v.begin(), v.end(), comp); //�������� quick ����

    cout << "���� �Է��Ͻÿ�" << endl;

    finish = clock();
    cout << (double)(finish - start) / CLOCKS_PER_SEC;

    int k;
    cin >> k;

    word = your_answer1(v, k);
    frequency = your_answer2(v, word);
    


    // ������� �ʿ��� �ڵ带 �߰��ϼ���
    //------------------------------------------------------------//
    print_result(word, frequency);
    

    

    return 0;
}


