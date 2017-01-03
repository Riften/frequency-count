/*
文件：words.h
内容：定义 words 类，可以完成单词词频的统计
*/
#ifndef MAP_H_INCLUDED
#define MAP_H_INClUDED

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
typedef pair<string, int> PAIR;

//比较函数，用于对vector的排序，完成按频率排序
struct myCom_value {
	bool operator()(const PAIR& lhs, const PAIR& rhs) {
		return lhs.second < rhs.second;
	}
};

struct myCom_key {
	bool operator()(const PAIR& lhs, const PAIR& rhs) {
		return lhs.first < rhs.first;
	}
};

inline bool isLetter(char c)
{
	return ((c <= 'z'&&c >= 'a') || (c <= 'Z' && c >= 'A'));
}

inline bool isLetter2(char c)
{
	return ((c <= 'z'&&c >= 'a') || (c <= 'Z' && c >= 'A') || c == '\'' || c == '-');
}
class words
{
private:
	//数据存储到map中，实现快速的排序输出
	map<string, int> m_dif;	//区分大小写
	map<string, int> m_sam;	//不区分大小写
	vector<PAIR>* v_dif;	//m1的频率排序
	vector<PAIR>* v_sam;	//m2的频率排序
	
	void add(string &str);	//向 map 中添加单词
	void sort_freq();		//按词频排序，并将结果保存在 vector 中
public:
	words(ifstream& in);
	~words() { delete v_dif; delete v_sam; }
	void print(int way, ostream &out);	//way = 1~8,代表 8 种输出方式
	void print_all(ostream &out);		//依次按照八中输出方式输出
};

words::words(ifstream& in)
{
	string str;
	char tmp_ch;
	char tmp_st[200];
	int size = 0;
	while (1)
	{
		size = 0;
		if(isLetter(tmp_ch = in.get()))
		{
			do {
				tmp_st[size++] = tmp_ch;
			} while (isLetter2(tmp_ch = in.get()));
		}
		if (size)
		{
			tmp_st[size] = '\0';
			str = tmp_st;
			add(str);
		}
		if (tmp_ch == EOF)	break;
	}
	//进行词频排序
	sort_freq();
}

void words::add(string &str)
{
	//为 m_dif 添加
	if (str.length())
	{
		auto ite = m_dif.find(str);	//
		if (ite != m_dif.end())	//找到了
		{
			ite->second++;
		}
		else
		{
			m_dif.emplace(PAIR(str, 1));
		}
	}
	//为 m_sam 添加
	{
		transform(str.begin(), str.end(), str.begin(), tolower);
		auto ite = m_sam.find(str);	//
		if (ite != m_sam.end())	//找到了
		{
			ite->second++;
		}
		else
		{
			m_sam.emplace(PAIR(str, 1));
		}
	}
}

void words::sort_freq()
{
	v_dif = new vector<PAIR>(m_dif.begin(), m_dif.end());
	v_sam = new vector<PAIR>(m_sam.begin(), m_sam.end());
	sort(v_dif->begin(), v_dif->end(), myCom_value());
	sort(v_sam->begin(), v_sam->end(), myCom_value());
	return;
}

void words::print(int way, ostream& out)
{
	if (m_dif.empty())
	{
		cout << "无单词\n";
		return;
	}
	switch (way)
	{
	case(1) :
		out << "区分大小写，按照字典序顺序\n";
		out << "词频\t单词\n";
		for (auto ite : m_dif)		//
		{
			out <<  ite.second <<'\t'<< ite.first << endl;
		}
		break;
	case(2):
		out << "区分大小写，按照字典序逆序\n";
		out << "词频\t单词\n";
		for (auto ite = --m_dif.end(); ite != m_dif.begin();ite--)
		{
			out << ite->second << '\t' << ite->first << endl;
		}
		out << m_dif.begin()->second << '\t' << m_dif.begin()->first << endl;
		break;
	case(3):
		out << "区分大小写，按照词频序升序\n";
		out << "词频\t单词\n";
		for (auto ite : *v_dif)
		{
			out << ite.second << '\t' << ite.first << endl;
		}
		break;
	case(4):
		out << "区分大小写，按照词频降序\n";
		out << "词频\t单词\n";
		for (auto ite = --(v_dif->end()); ite != v_dif->begin();ite--)
		{
			out << ite->second << '\t' << ite->first << endl;
		}
		out << v_dif->begin()->second << '\t' << v_dif->begin()->first << endl;
		break;
	case(5) :
		out << "不区分大小写，按照字典序顺序\n";
		out << "词频\t单词\n";
		for (auto ite : m_sam)		//
		{
			out << ite.second << '\t' << ite.first << endl;
		}
		break;
	case(6) :
		out << "不区分大小写，按照字典序逆序\n";
		out << "词频\t单词\n";
		for (auto ite = --m_sam.end(); ite != m_sam.begin(); ite--)
		{
			out << ite->second << '\t' << ite->first << endl;
		}
		out << m_sam.begin()->second << '\t' << m_sam.begin()->first << endl;
		break;
	case(7) :
		out << "不区分大小写，按照词频序升序\n";
		out << "词频\t单词\n";
		for (auto ite : *v_sam)
		{
			out << ite.second << '\t' << ite.first << endl;
		}
		break;
	case(8) :
		out << "不区分大小写，按照词频序降序\n";
		out << "词频\t单词\n";
		for (auto ite = --(v_sam->end()); ite != v_sam->begin(); ite--)
		{
			out << ite->second << '\t' << ite->first << endl;
		}
		out << v_sam->begin()->second <<'\t' << v_sam->begin()->first << endl;
		break;
	}
	return;
}


void words::print_all(ostream &out)
{
	for (int way = 1; way <= 8; way++)
	{
		print(way, out);
		out << "***************************\n";
	}
	return;
}
#endif